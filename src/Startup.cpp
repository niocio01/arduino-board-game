#include "Startup.h"
#include "LcdTreiber.h"
#include "LedTreiber.h"
#include "Messages.h"
#include "RfidTreiber.h"
#include "inttypes.h"
#include "SpielfeldLed.h"
#include "GlobalTypes.h"
#include "SpeakerTreiber.h"


static bool ledGestartet;
static bool lcdGestartet;
static bool rfidGestartet;
static bool tonGestartet;

void Startup_check(void)
{
  ledGestartet  = LedTreiber_Startup();
  lcdGestartet  = LcdTreiber_Startup();
  rfidGestartet = RfidTreiber_Startup();
  tonGestartet  = SpeakerTreiber_Startup();

  if (ledGestartet == true and lcdGestartet == true and rfidGestartet == true and tonGestartet == true)
  {
    LedTreiber_LedSchalten(192, Gruen);
    Messages_ZeigeNachricht(SpielerEins, Startup_OK);
    Messages_ZeigeNachricht(SpielerZwei, Startup_OK);
    //SpeakerTreiber_playTune();
  }

  else
  {
    LedTreiber_LedSchalten(192, Rot);
    Messages_ZeigeNachricht(SpielerEins, Startup_RFID_Fail);
    Messages_ZeigeNachricht(SpielerZwei, Startup_RFID_Fail);

  }
}
