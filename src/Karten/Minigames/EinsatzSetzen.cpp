#include "Karten/Minigames/MinigameManager.h"
#include "Messages.h"
#include "Treiber/TasterTreiber.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/TasterLed.h"
#include "Treiber/PotiTreiber.h"
#include "Treiber/PotiLed.h"
#include "arduino.h"

//extern struct Messages_values messageVal;
static Messages_values points;
static Messages_values leer;

static uint8_t einsatzDepotP1 = 30;
static uint8_t einsatzDepotP2 = 30;
uint8_t maxPunkteP1;
uint8_t maxPunkteP2;
const uint8_t maxPunkte = 5;

static uint8_t einsatztP1;
static uint8_t einsatztP2;

static bool startMsgShown;
static bool startDoneP1;
static bool startDoneP2;
static bool enablePotLedP1;
static bool enablePotLedP2;
static bool EinsaztGewaehletP1;
static bool EinsaztGewaehletP2;

void EinsatzSetzen_Run(void)
{
  if (!startMsgShown) {
    Messages_ZeigeNachricht(SpielerEins, MSG_Einsatz_waehlen, &leer);
    Messages_ZeigeNachricht(SpielerZwei, MSG_Einsatz_waehlen, &leer);
    TasterLed_Setzten(SpielerEins, LedEins, Gruen);
    TasterLed_Setzten(SpielerZwei, LedEins, Gruen);
    startMsgShown = true;
  }

  if (TasterTreiber_TasteGedrueckt(SPIELER1_TASTE1))
  {
    LedTreiber_LedSchalten(70,Blau);
    startDoneP1 = true;
  }
  if (TasterTreiber_TasteGedrueckt(SPIELER2_TASTE1))
  {
    LedTreiber_LedSchalten(90,Blau);
    startDoneP2 = true;
  }
  if (startDoneP1)
  {

  }
  if (startDoneP2){
    if(!enablePotLedP2)
    {
      PotiLed_Setzen(SpielerZwei, Gruen);
      enablePotLedP2 = true;
    }
    if(!EinsaztGewaehletP2)
    {
      if (einsatzDepotP2 < maxPunkte)
      {
        maxPunkteP2 = einsatzDepotP2;
      }
      else
      {
        maxPunkteP2 = maxPunkte;
      }
      einsatztP2 = map(PotiTreiber_Get_Val(SpielerZwei), 0, 255, 0, maxPunkteP2);
      points.ValEinsatz = einsatztP2;
      points.ValPunkte = einsatzDepotP2;
      Messages_ZeigeNachricht(SpielerZwei, MSGxx_Einsatz_Punkte, &points);
      //if (TasterTreiber_TasteGedrueckt(SPIELER2_TASTE1))
      {
    //    EinsaztGewaehletP2 = true;
      }
    }
  }
}
