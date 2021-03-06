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

static GlobalTypes_Spieler_t spieler;


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
      spieler = SpielerEins;
    }
    else
    {
      spieler = SpielerZwei;
    }
    TasterLed_Setzen(spieler, LedEins, Gruen);
    StatusLedSituationSetzen(spieler, Buff);

    switch (karte)
    {
      case EinsatzSetzen:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Einsatz_bestimmen, &leer3);
      PlayerManager_ActivateEinsatzSetzen(spieler);
      break;

      case Speed:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Speed, &leer3);
      PlayerManager_ActivateSpeed(spieler);
      break;

      case GewinnGarantiert:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Gewinn, &leer3);
      PlayerManager_ActivateGewinnGarantiert(spieler);
      break;

      case Aussetzen:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Aussetzen, &leer3);
      PlayerManager_ActivateAussetzen(spieler);
      break;

      case MehrEinsatz:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Mehr_Einsatz, &leer3);
      EinsatzSetzen_MehrEinsatztBuffAnwenden();
      break;

      case Lucky:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Lucky, &leer3);
      break;

      case Schild:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Schild, &leer3);
      PlayerManager_ActivateShield(spieler);
      break;

      case Zeitreise:
      Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Zeitreise, &leer3);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Zeitreise, &leer3);
      Zeitreise_BuffAnwenden();
      break;

      case FalleStellen:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Falle, &leer3);
      break;

      case Steinschlag:
      Messages_ZeigeNachricht(spieler, MSG_Buff_Steinschlag, &leer3);
      break;
    }
  }

  if (!MSGBestaetigt)
  {
    if (TasterHandler_Klick(spieler, TasterEins))
    {
      MSGBestaetigt = true;
    }
  }

  else
  {
    if (karte == Lucky)
    {
      randomSeed(analogRead(A3));
      karte = random(65, 74);
      MGSShown = false;
      MSGBestaetigt = false;
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
