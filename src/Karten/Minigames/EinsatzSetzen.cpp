#include "Karten/Minigames/MinigameManager.h"
#include "Messages.h"
#include "Treiber/TasterTreiber.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/TasterLed.h"
#include "Treiber/PotiTreiber.h"
#include "Treiber/PotiLed.h"
#include "arduino.h"
#include "Treiber/TasterHandler.h"


static uint8_t einsatzDepotP1 = 30;
static uint8_t einsatzDepotP2 = 30;
const uint8_t maxPunkte = 5;

static Messages_values points1;
static Messages_values points2;
static Messages_values leer;


uint8_t maxPunkteP1;
uint8_t maxPunkteP2;
static uint8_t einsatzP1;
static uint8_t einsatzP2;

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

  if (!startDoneP1)
  {
    if (TasterHandler_Klick(SpielerEins, TasterEins))
    {
      PotiLed_Setzen(SpielerEins, Gruen);
      startDoneP1 = true;
    }
  }
  if(startDoneP1 and !EinsaztGewaehletP1)
  {
    if (einsatzDepotP1 < maxPunkte)
    {
      maxPunkteP1 = einsatzDepotP1;
    }
    else
    {
      maxPunkteP1 = maxPunkte;
    }
    einsatzP1 = map(PotiTreiber_Get_Val(SpielerEins), 0, 255, 0, maxPunkteP1);
    points1.ValEinsatz = einsatzP1;
    points1.ValPunkte = einsatzDepotP1;
    Messages_ZeigeNachricht(SpielerEins, MSGxx_Einsatz_Punkte, &points1);

    if (TasterHandler_Klick(SpielerEins, TasterEins))
    {
      EinsaztGewaehletP1 = true;
      TasterLed_Setzten(SpielerEins, LedEins, Schwarz);
      PotiLed_Setzen(SpielerEins, Schwarz);
    }
  }


  if (!startDoneP2)
  {
    if (TasterHandler_Klick(SpielerZwei, TasterEins))
    {
      PotiLed_Setzen(SpielerZwei, Gruen);
      startDoneP2 = true;
    }
  }
  if(startDoneP2 and !EinsaztGewaehletP2)
  {
    if (einsatzDepotP2 < maxPunkte)
    {
      maxPunkteP2 = einsatzDepotP2;
    }
    else
    {
      maxPunkteP2 = maxPunkte;
    }
    einsatzP2 = map(PotiTreiber_Get_Val(SpielerZwei), 0, 255, 0, maxPunkteP2);
    points2.ValEinsatz = einsatzP2;
    points2.ValPunkte = einsatzDepotP2;
    Messages_ZeigeNachricht(SpielerZwei, MSGxx_Einsatz_Punkte, &points2);

    if (TasterHandler_Klick(SpielerZwei, TasterEins))
    {
      EinsaztGewaehletP2 = true;
      TasterLed_Setzten(SpielerZwei, LedEins, Schwarz);
      PotiLed_Setzen(SpielerZwei, Schwarz);
    }
  }
  if (EinsaztGewaehletP1 and EinsaztGewaehletP2)
  {
    startMsgShown = false;
    startDoneP1 = false;
    startDoneP2 = false;
    enablePotLedP1 = false;
    enablePotLedP2 = false;
    EinsaztGewaehletP1 = false;
    EinsaztGewaehletP2 = false;
    MinigameManager_EinsatzGesetzt(einsatzP1, einsatzP2);
  }
}
