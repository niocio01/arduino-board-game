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
#include "Karten/Buffs/Zeitreise.h"
#include "Karten/Buffs/AktiveBuffsAnzeigen.h"
//#include "Treiber/LedTreiber.h"

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

static uint8_t karte;
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
    MGSShown = true;
    if (PlayerManager_SpielerEinsAmZug())
    {
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
      StatusLedSituationSetzen(SpielerEins, Buff);

      switch (karte)
      {
        case EinsatzSetzen:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Einsatz_bestimmen, &leer3);
        PlayerManager_ActivateEinsatzSetzen(SpielerEins);
        break;

        case Speed:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Speed, &leer3);
        PlayerManager_ActivateSpeed(SpielerEins);
        break;

        case GewinnGarantiert:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Gewinn, &leer3);
        PlayerManager_ActivateGewinnGarantiert(SpielerEins);
        break;

        case Aussetzen:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Aussetzen, &leer3);
        PlayerManager_ActivateAussetzen(SpielerEins);
        break;

        case MehrEinsatz:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Mehr_Einsatz, &leer3);
        EinsatzSetzen_MehrEinsatztBuffAnwenden();
        break;

        case Lucky:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Lucky, &leer3);
        break;

        case Schild:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Schild, &leer3);
        PlayerManager_ActivateShield(SpielerEins);
        break;

        case Zeitreise:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Zeitreise, &leer3);
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Zeitreise, &leer3);
        Zeitreise_BuffAnwenden();
        break;

        case FalleStellen:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Falle, &leer3);
        break;

        case Steinschlag:
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Steinschlag, &leer3);
        break;
      }

    }

    else
    {
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
      StatusLedSituationSetzen(SpielerZwei, Buff);

      switch (karte)
      {
        case EinsatzSetzen:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Einsatz_bestimmen, &leer3);
        PlayerManager_ActivateEinsatzSetzen(SpielerZwei);
        break;

        case Speed:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Speed, &leer3);
        PlayerManager_ActivateSpeed(SpielerZwei);
        break;

        case GewinnGarantiert:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Gewinn, &leer3);
        PlayerManager_ActivateGewinnGarantiert(SpielerZwei);
        break;

        case Aussetzen:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Aussetzen, &leer3);
        PlayerManager_ActivateAussetzen(SpielerZwei);
        break;

        case MehrEinsatz:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Mehr_Einsatz, &leer3);
        EinsatzSetzen_MehrEinsatztBuffAnwenden();
        break;

        case Lucky:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Lucky, &leer3);
        break;

        case Schild:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Schild, &leer3);
        PlayerManager_ActivateShield(SpielerZwei);
        break;

        case Zeitreise:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Zeitreise, &leer3);
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Zeitreise, &leer3);
        Zeitreise_BuffAnwenden();
        break;

        case FalleStellen:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Falle, &leer3);
        break;

        case Steinschlag:
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Steinschlag, &leer3);
        break;
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

  if (MSGBestaetigt)
  {
    if (karte == Lucky)
    {
      karte = random(65, 74);
    }
    else
    {
      MGSShown = false;
      MSGBestaetigt = false;
      Kartenmanager_BuffProcessed();
    }
    if (karte == Zeitreise)
    {
      Kartenmanager_AktiveBuffAnzeigen(true);
    }
  }
}
