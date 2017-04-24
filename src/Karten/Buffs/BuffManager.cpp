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
static bool MGSShown;
static bool MSGBestaetigt;
Messages_values leer3;



void BuffManager_TellBuff(uint8_t kartenNrValue)
{
  karte = kartenNrValue;
  MGSShown = false;
  MSGBestaetigt = false;
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
        PlayerManager_ActivateEinsatzSetzen(SpielerEins);
      }
      else if (karte == Speed)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Speed, &leer3);
        PlayerManager_ActivateSpeed(SpielerEins);
      }
      else if (karte == GewinnGarantiert)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Gewinn, &leer3);
        PlayerManager_ActivateGewinnGarantiert(SpielerEins);
      }
      else if (karte == Aussetzen)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Aussetzen, &leer3);
        PlayerManager_ActivateAussetzen(SpielerEins);
      }
      else if (karte == MehrEinsatz)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Mehr_Einsatz, &leer3);
        EinsatzSetzen_MehrEinsatztBuffAnwenden();
      }
      else if (karte == Lucky)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Lucky, &leer3);
        karte = random(65, 74);
        }
      else if (karte == Schild)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Schild, &leer3);
        PlayerManager_ActivateShield(SpielerEins);
      }
      else if (karte == Zeitreise)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Zeitreise, &leer3);
      }
      else if (karte == FalleStellen)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Falle, &leer3);
      }
      else if (karte == Steinschlag)
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Steinschlag, &leer3);
      }
    }

    else if (PlayerManager_SpielerZweiAmZug())
    {
      LedTreiber_AllBlack();
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
      StatusLedSituationSetzen(SpielerZwei, Buff);

      if (karte == EinsatzSetzen)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Einsatz_bestimmen, &leer3);
        PlayerManager_ActivateEinsatzSetzen(SpielerZwei);
      }
      else if (karte == Speed)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Speed, &leer3);
        PlayerManager_ActivateSpeed(SpielerZwei);
      }
      else if (karte == GewinnGarantiert)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Gewinn, &leer3);
        PlayerManager_ActivateGewinnGarantiert(SpielerZwei);
      }
      else if (karte == Aussetzen)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Aussetzen, &leer3);
        PlayerManager_ActivateAussetzen(SpielerZwei);
      }
      else if (karte == MehrEinsatz)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Mehr_Einsatz, &leer3);
        EinsatzSetzen_MehrEinsatztBuffAnwenden();
      }
      else if (karte == Lucky)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Lucky, &leer3);
        karte = random(65, 74);
      }
      else if (karte == Schild)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Schild, &leer3);
        PlayerManager_ActivateShield(SpielerZwei);
      }
      else if (karte == Zeitreise)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Zeitreise, &leer3);
      }
      else if (karte == FalleStellen)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Falle, &leer3);
      }
      else if (karte == Steinschlag)
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
    else
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        MSGBestaetigt = true;
      }
    }
  }

  else // reset und beeenden
  {
    MGSShown = false;
    MSGBestaetigt = false;
    LedTreiber_AllBlack();
    if (karte != Lucky)
    {
    Kartenmanager_BuffProcessed();
    }
  }
}
