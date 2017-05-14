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
#include "Treiber/IRTreiber.h"
#include "Treiber/PotiTreiber.h"
#include "Treiber/SpielfeldLed.h"


static bool ledGestartet;
static bool lcdGestartet;
static bool rfidGestartet;
static bool tonGestartet;
static bool tasterGestartet;
static bool IRGestartet;
static bool PotiGestartet;

 Messages_values Leer;

void Startup_check(void)
{
  ledGestartet  = LedTreiber_Startup();
  lcdGestartet  = LcdTreiber_Startup();
  rfidGestartet = RfidTreiber_Startup();
  //tonGestartet  = SpeakerTreiber_Startup();
  tasterGestartet = TasterTreiber_Startup();
  // IRGestartet = IRTreiber_Startup();
  PotiGestartet = PotiTreiber_Startup();
  SF_InitData();
  SF_FiguresSetToStart(SpielerEins, FigureEins, Rot, 150);
  SF_FiguresSetToStart(SpielerEins, FigureZwei, Gelb, 150);
  SF_FiguresSetToStart(SpielerZwei, FigureEins, Blau, 150);
  SF_FiguresSetToStart(SpielerZwei, FigureZwei, Gruen, 150);


  if (ledGestartet == true and lcdGestartet == true and rfidGestartet == true
    and tasterGestartet == true and PotiGestartet == true)
  {

    Messages_ZeigeNachricht(SpielerEins, MSG_Startup_OK, &Leer);
    Messages_ZeigeNachricht(SpielerZwei, MSG_Startup_OK, &Leer);
    //SpeakerTreiber_playTune();
  }

  else
  {
    LedTreiber_LedSchalten(192, Rot);
    Messages_ZeigeNachricht(SpielerEins, MSG_Startup_RFID_Fail, &Leer);
    Messages_ZeigeNachricht(SpielerZwei, MSG_Startup_RFID_Fail, &Leer);

  }
}
