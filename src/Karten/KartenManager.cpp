#include "Karten/KartenManager.h"
#include "Treiber/RfidTreiber.h"
#include "Karten/Buffs/BuffManager.h"
#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"
#include "arduino.h"
#include "Karten/Minigames/MinigameManager.h"
#include "Messages.h"
#include "PlayerManager.h"
#include "StatusLedSituation.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "Karten/Buffs/AktiveBuffsAnzeigen.h"

uint8_t freeSteps = 1; // Anzahl schritte welche pro zug gratis gamacht werden können

static bool minigameInProgress = false;
static bool buffInProgress = false;
static bool MSGShown = false;
static bool AktiveBuffsAnzeigen = false;
Messages_values leer4;


void Kartenmanager_MinigameEnded(void)
{
  minigameInProgress = false;
  MSGShown = false;
}

void Kartenmanager_BuffProcessed(void)
{
  buffInProgress = false;
  MSGShown = false;
}

void Kartenmanager_AktiveBuffAnzeigen(bool anzeigen)
{
  if (anzeigen == true)
  {
    AktiveBuffsAnzeigen = true;
    MSGShown = true;
  }
  else
  {
    AktiveBuffsAnzeigen = false;
    MSGShown = false;
  }
}

void KartenManager_Main(void)
{
  if (!MSGShown)
  {
    MSGShown = true;

    if (PlayerManager_SpielerEinsAmZug())
    {
      Messages_ZeigeNachricht(SpielerEins, MSG_Karte_EndGame, &leer4);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Gegner_am_Zug, &leer4);
      StatusLedSituationSetzen(SpielerEins, Spielzug);
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
    }
    else
    {
      Messages_ZeigeNachricht(SpielerZwei, MSG_Karte_EndGame, &leer4);
      Messages_ZeigeNachricht(SpielerEins, MSG_Gegner_am_Zug, &leer4);
      StatusLedSituationSetzen(SpielerZwei, Spielzug);
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
    }
  }
  if (minigameInProgress)
  {
    MinigameManager_Run();
  }

  if (buffInProgress)
  {
    BuffManager_Run();
  }

  if (AktiveBuffsAnzeigen)
  {
    AktiveBuffsAnzeigen_Run();
  }

  if (MSGShown and minigameInProgress == false and buffInProgress == false
  and AktiveBuffsAnzeigen == false)
  {
    uint8_t * kartenNrRef;
    uint8_t  kartenNrValue;

    kartenNrRef = &kartenNrValue;
    bool success = RfidTreiber_ReadCard(kartenNrRef);
    if (success)
    {
      if (kartenNrValue < 80) // Für Buffs
      {
        BuffManager_TellBuff(kartenNrValue);
        buffInProgress = true;
      }

      else // für Minigames
      {
        minigameInProgress = true;
        switch (kartenNrValue) {

          case 97:
          MinigameManager_SetGame(Reaktion);
          break;

          case 98:
          MinigameManager_SetGame(Simon);
          break;

          case 99:
          MinigameManager_SetGame(ToneMaster);
          break;

          case 100:
          MinigameManager_SetGame(QuickFinger);
          break;

          case 101:
          MinigameManager_SetGame(FastCounter);
          break;

          case 102:
          MinigameManager_SetGame(Timing);
          break;
        }
        MinigameManager_StartNewGame();
      }
    }
    else
    {
      if (PlayerManager_SpielerEinsAmZug())
      {
        if (TasterHandler_Klick(SpielerEins, TasterEins))
        {
          LedTreiber_ControllsBlack();
          MinigameManager_EinsatzGesetzt(freeSteps, 0, true);
          minigameInProgress = true;
        }
      }
      else
      {
        if (TasterHandler_Klick(SpielerZwei, TasterEins))
        {
          LedTreiber_ControllsBlack();
          MinigameManager_EinsatzGesetzt(0, freeSteps, true);
          minigameInProgress = true;
        }
      }
    }
  }
}
