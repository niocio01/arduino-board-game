#include "Karten/Buffs/BuffManager.h"
#include "PlayerManager.h"
#include "Messages.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "Karten/Minigames/MinigameManager.h"
#include <arduino.h>
#include "Karten/KartenManager.h"
#include "StatusLedSituation.h"
#include "Karten/Minigames/EinsatzSetzen.h"

const uint8_t FalleStellen =65;  // hex A
const uint8_t EinsatzSetzen =66; // hex B
const uint8_t Steinschlag =67;
const uint8_t Speed =68;
const uint8_t GewinnGarantiert =69;
const uint8_t Aussetzen =70;
const uint8_t Zeitreise =71;
const uint8_t MehrEinsatz =72;
const uint8_t Schild =73;
const uint8_t Lucky =74;

uint8_t karte;
static bool karteShown;
static bool MGSShown;
static bool MSGBestaetigt;
Messages_values leer3;



void BuffManager_TellBuff(uint8_t kartenNrValue)
{
  karte = kartenNrValue;
}


void BuffManager_Run(void)
{
  if (!MGSShown)
  {
    MGSShown =true;
    if (PlayerManager_SpielerEinsAmZug())
    {
      LedTreiber_AllBlack();
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
      StatusLedSituationSetzen(SpielerEins, Buff);

      if (karte == EinsatzSetzen)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Einsatz_bestimmen, &leer3);
      }
      if (karte == Speed)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Speed, &leer3);
      }
      if (karte == GewinnGarantiert)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Gewinn, &leer3);
      }
      if (karte == Aussetzen)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Aussetzen, &leer3);
      }
      if (karte == MehrEinsatz)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Mehr_Einsatz, &leer3);
      }
      if (karte == Lucky)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Lucky, &leer3);
      }
      if (karte == Schild)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Schild, &leer3);
      }
      if (karte == Zeitreise)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Zeitreise, &leer3);
      }
      if (karte == FalleStellen)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Falle, &leer3);
      }
      if (karte == Steinschlag)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Steinschlag, &leer3);
      }
    }

    if (PlayerManager_SpielerZweiAmZug())
    {
      LedTreiber_AllBlack();
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
      StatusLedSituationSetzen(SpielerZwei, Buff);

      if (karte == EinsatzSetzen)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Einsatz_bestimmen, &leer3);
      }
      if (karte == Speed)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Speed, &leer3);
      }
      if (karte == GewinnGarantiert)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Gewinn, &leer3);
      }
      if (karte == Aussetzen)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Aussetzen, &leer3);
      }
      if (karte == MehrEinsatz)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Mehr_Einsatz, &leer3);
      }
      if (karte == Lucky)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Lucky, &leer3);
      }
      if (karte == Schild)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Schild, &leer3);
      }
      if (karte == Zeitreise)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Zeitreise, &leer3);
      }
      if (karte == FalleStellen)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Falle, &leer3);
      }
      if (karte == Steinschlag)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Steinschlag, &leer3);
      }
    }
  }

  if (!MSGBestaetigt)
  {
    if (PlayerManager_SpielerEinsAmZug())
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        MSGBestaetigt = true;
      }
    }
    if (PlayerManager_SpielerZweiAmZug())
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        MSGBestaetigt = true;
      }
    }
  }

  if (MSGBestaetigt)
  {
    MGSShown = false;
    MSGBestaetigt = false;
    LedTreiber_AllBlack();

    if (karte == Lucky)
    {
      karte = random(65, 74);
    }

    else if (karte == EinsatzSetzen)
    {
      if (PlayerManager_SpielerEinsAmZug())
      {
        PlayerManager_ActivateEinsatzSetzen(SpielerEins);
      }
      else
      {
        PlayerManager_ActivateEinsatzSetzen(SpielerZwei);
      }
      Kartenmanager_BuffProcessed();
    }

    else if (karte == Speed)
    {
      if (PlayerManager_SpielerEinsAmZug())
      {
        PlayerManager_ActivateSpeed(SpielerEins);
      }
      else
      {
        PlayerManager_ActivateSpeed(SpielerZwei);
      }
      Kartenmanager_BuffProcessed();
    }

    else if (karte == GewinnGarantiert)
    {
      if (PlayerManager_SpielerEinsAmZug())
      {
        PlayerManager_ActivateGewinnGarantiert(SpielerEins);
      }
      else
      {
        PlayerManager_ActivateGewinnGarantiert(SpielerZwei);
      }
      Kartenmanager_BuffProcessed();
    }

    else if (karte == Schild)
    {
      if (PlayerManager_SpielerEinsAmZug())
      {
        PlayerManager_ActivateShield(SpielerEins);
      }
      else
      {
        PlayerManager_ActivateShield(SpielerZwei);
      }
      Kartenmanager_BuffProcessed();
    }

    else if (karte == Aussetzen)
    {
      if (PlayerManager_SpielerEinsAmZug())
      {
        PlayerManager_ActivateAussetzen(SpielerEins);
      }
      else
      {
        PlayerManager_ActivateAussetzen(SpielerZwei);
      }
      Kartenmanager_BuffProcessed();
    }

    else if (karte == MehrEinsatz)
    {
      EinsatzSetzen_MehrEinsatztBuffAnwenden();
      Kartenmanager_BuffProcessed();
    }

    else if (karte == Zeitreise)
    {
      Kartenmanager_BuffProcessed();
    }

    else if (karte == FalleStellen)
    {
      Kartenmanager_BuffProcessed();
    }

    else if (karte == Steinschlag)
    {
      Kartenmanager_BuffProcessed();
    }
  }
}
