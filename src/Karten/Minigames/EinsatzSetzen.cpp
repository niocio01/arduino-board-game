#include "Karten/Minigames/MinigameManager.h"
#include "Messages.h"
#include "Treiber/TasterTreiber.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/TasterLed.h"
#include "Treiber/PotiTreiber.h"
#include "Treiber/PotiLed.h"

//extern struct Messages_values messageVal;
static Messages_values points;
static Messages_values leer;

static bool StartMsgShown;
static bool startP1Done;
static bool startP2Done;

void EinsatzSetzen_Run(void)
{
  if (!StartMsgShown) {
    Messages_ZeigeNachricht(SpielerEins, MSG_Einsatz_waehlen, &leer);
    Messages_ZeigeNachricht(SpielerZwei, MSG_Einsatz_waehlen, &leer);
    TasterLed_Setzten(SpielerEins, LedEins, Gruen);
    TasterLed_Setzten(SpielerZwei, LedEins, Gruen);
    StartMsgShown = true;
  }

  if (TasterTreiber_TasteGedrueckt(SPIELER1_TASTE1))
  {
    LedTreiber_LedSchalten(70,Blau);
    startP1Done = true;
  }
  if (TasterTreiber_TasteGedrueckt(SPIELER2_TASTE1))
  {
    LedTreiber_LedSchalten(90,Blau);
    startP2Done = true;
  }
  if (startP1Done){
  //  Messages_ZeigeNachricht(SpielerEins, MSG_Welcome);
  }
  if (startP2Done){
  PotiLed_Setzen(SpielerZwei, Gruen);
  points.ValEinsatz = PotiTreiber_Get_Val(SpielerZwei);
  points.ValPunkte = 30;
  Messages_ZeigeNachricht(SpielerZwei, MSGxx_Einsatz_Punkte, &points);
  }
}
