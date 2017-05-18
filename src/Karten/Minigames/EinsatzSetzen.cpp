#include "Karten/Minigames/MinigameManager.h"
#include "Messages.h"
#include "Treiber/TasterTreiber.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/TasterLed.h"
#include "Treiber/PotiTreiber.h"
#include "Treiber/PotiLed.h"
#include "arduino.h"
#include "Treiber/TasterHandler.h"
#include "PlayerManager.h"

const uint8_t AnzahlZusaezlicherEinsatzt = 10; //bei Buff Mehr Einsatz
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

static bool DoNormalRoutine = false;
static bool startMsgShown;
static bool startDoneP1;
static bool startDoneP2;
static bool enablePotLedP1;
static bool enablePotLedP2;
static bool EinsaztGewaehletP1;
static bool EinsaztGewaehletP2;


void EinsatzSetzen_MehrEinsatztBuffAnwenden(void)
{
  if (PlayerManager_SpielerEinsAmZug())
  {
    einsatzDepotP1 = einsatzDepotP1 + AnzahlZusaezlicherEinsatzt;
  }
  else
  {
    {
      einsatzDepotP2 = einsatzDepotP2 + AnzahlZusaezlicherEinsatzt;
    }
  }
}

uint8_t EinsatzSetzen_GetEinsatzDepot(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    return einsatzDepotP1;
  }
  else
  {
    return einsatzDepotP2;
  }
}

void EinsatzSetzen_SetEinsatzDepot(GlobalTypes_Spieler_t spieler, uint8_t newEinsatztDepot)
{
  if (spieler == SpielerEins)
  {
    einsatzDepotP1 = newEinsatztDepot;
  }
  else
  {
    einsatzDepotP2 = newEinsatztDepot;
  }
}

void EinsatzSetzen_Run(void)
{

  if (PlayerManager_SpielerEinsAmZug())
  {
    if (PlayerManager_IsEinsatzSetzenActive(SpielerEins))
    {
      if (!startMsgShown) {
        Messages_ZeigeNachricht(SpielerEins, MSG_Einsatz_waehlen, &leer);
        Messages_ZeigeNachricht(SpielerZwei, MSG_Gegner_bestimmt_Einsatz, &leer);
        TasterLed_Setzen(SpielerEins, LedEins, Gruen);
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
          TasterLed_Setzen(SpielerEins, LedEins, Gruen);
          PotiLed_Setzen(SpielerEins, Schwarz);
          Messages_ZeigeNachricht(SpielerEins, MSG_Einsatz_fuer_Gegner, &leer);
        }
      }


      if (EinsaztGewaehletP1 and !startDoneP2)
      {
        if (TasterHandler_Klick(SpielerEins, TasterEins))
        {
          PotiLed_Setzen(SpielerEins, Gruen);
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
        einsatzP2 = map(PotiTreiber_Get_Val(SpielerEins), 0, 255, 0, maxPunkteP2);
        points2.ValEinsatz = einsatzP2;
        Messages_ZeigeNachricht(SpielerEins, MSGxx_Einsatz_Punkte_FuerGegner, &points2);

        if (TasterHandler_Klick(SpielerEins, TasterEins))
        {
          EinsaztGewaehletP2 = true;
          TasterLed_Setzen(SpielerEins, LedEins, Schwarz);
          PotiLed_Setzen(SpielerEins, Schwarz);
        }
      }
      if (EinsaztGewaehletP2 and EinsaztGewaehletP1)
      {
        startMsgShown = false;
        startDoneP1 = false;
        startDoneP2 = false;
        enablePotLedP1 = false;
        enablePotLedP2 = false;
        EinsaztGewaehletP1 = false;
        EinsaztGewaehletP2 = false;
        PlayerManager_DeActivateEinsatzSetzen(SpielerEins);
        MinigameManager_EinsatzGesetzt(einsatzP1, einsatzP2);
      }
    }
    else
    {
      DoNormalRoutine = true;
    }
  }


  /*-----------------------------------------------------------------
  Einsatz für Spieler Eins und Zwei von Spieler Zwei wählen. */
  if (PlayerManager_SpielerZweiAmZug())
  {
    if (PlayerManager_IsEinsatzSetzenActive(SpielerZwei))
    {
      if (!startMsgShown) {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Einsatz_waehlen, &leer);
        Messages_ZeigeNachricht(SpielerEins, MSG_Gegner_bestimmt_Einsatz, &leer);
        TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
        startMsgShown = true;
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
          TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
          PotiLed_Setzen(SpielerZwei, Schwarz);
          Messages_ZeigeNachricht(SpielerZwei, MSG_Einsatz_fuer_Gegner, &leer);
        }
      }


      if (EinsaztGewaehletP2 and !startDoneP1)
      {
        if (TasterHandler_Klick(SpielerZwei, TasterEins))
        {
          PotiLed_Setzen(SpielerZwei, Gruen);
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
        einsatzP1 = map(PotiTreiber_Get_Val(SpielerZwei), 0, 255, 0, maxPunkteP1);
        points1.ValEinsatz = einsatzP1;
        Messages_ZeigeNachricht(SpielerZwei, MSGxx_Einsatz_Punkte_FuerGegner, &points1);

        if (TasterHandler_Klick(SpielerZwei, TasterEins))
        {
          EinsaztGewaehletP1 = true;
          TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
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
        PlayerManager_DeActivateEinsatzSetzen(SpielerZwei);
        MinigameManager_EinsatzGesetzt(einsatzP1, einsatzP2);
      }
    }
    else
    {
      DoNormalRoutine = true;
    }
  }




  /*-----------------------------------------------------------------
  Beide wählen Ihren eigenen Einsatz. */
  if (DoNormalRoutine)
  {
    if (!startMsgShown) {
      Messages_ZeigeNachricht(SpielerEins, MSG_Einsatz_waehlen, &leer);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Einsatz_waehlen, &leer);
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
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
        TasterLed_Setzen(SpielerEins, LedEins, Schwarz);
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
        TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
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
      DoNormalRoutine = false;
      MinigameManager_EinsatzGesetzt(einsatzP1, einsatzP2);
    }
  }
}
