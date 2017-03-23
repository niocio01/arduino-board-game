#include "Startup.h"
#include "Treiber/LcdTreiber.h"
#include "Treiber/LedTreiber.h"
#include "Messages.h"
#include "Treiber/RfidTreiber.h"
#include "inttypes.h"
#include "Treiber/SpielfeldLed.h"
#include "GlobalTypes.h"
#include "Treiber/SpeakerTreiber.h"
#include "Treiber/TasterTreiber.h"


static bool ledGestartet;
static bool lcdGestartet;
static bool rfidGestartet;
static bool tonGestartet;
static bool tasterGestartet;

void Startup_check(void)
{
  extern struct Messages_values MessageValues;

  ledGestartet  = LedTreiber_Startup();
  lcdGestartet  = LcdTreiber_Startup();
  rfidGestartet = RfidTreiber_Startup();
  tonGestartet  = SpeakerTreiber_Startup();
  tasterGestartet = TasterTreiber_Startup();

  if (ledGestartet == true and lcdGestartet == true and rfidGestartet == true
    and tonGestartet and tasterGestartet == true)
  {
    LedTreiber_LedSchalten(192, Gruen);
    Messages_ZeigeNachricht(SpielerEins, MSG_Startup_OK, &MessageValues);
    Messages_ZeigeNachricht(SpielerZwei, MSG_Startup_OK, &MessageValues);
    //SpeakerTreiber_playTune();
  }

  else
  {
    LedTreiber_LedSchalten(192, Rot);
    Messages_ZeigeNachricht(SpielerEins, MSG_Startup_RFID_Fail, &MessageValues);
    Messages_ZeigeNachricht(SpielerZwei, MSG_Startup_RFID_Fail, &MessageValues);

  }
}
