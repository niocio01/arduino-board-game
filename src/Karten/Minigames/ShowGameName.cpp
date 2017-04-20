#include "Karten/Minigames/ShowGameName.h"
#include "Messages.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/TasterLed.h"

static MinigameManager_GameStatus_t Game;
static Messages_values leer5;

static bool NameShown;
static bool NameBestaetigtP1;
static bool NameBestaetigtP2;


void ShowGameName_TellGame(MinigameManager_GameStatus_t newGame)
{
  Game = newGame;
}

void ShowGameName_Run(void)
{
  if (!NameShown)
  {
    NameShown = true;
    TasterLed_Setzten(SpielerEins, LedEins, Gruen);
    TasterLed_Setzten(SpielerZwei, LedEins, Gruen);

    switch (Game)
    {
      case Reaktion:
      Messages_ZeigeNachricht(SpielerEins, MSG_Minigame_Reaktion, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Minigame_Reaktion, &leer5);
      break;

      case Simon:
      Messages_ZeigeNachricht(SpielerEins, MSG_Minigame_Simon, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Minigame_Simon, &leer5);
      break;

      case ToneMaster:
      Messages_ZeigeNachricht(SpielerEins, MSG_Minigame_ToneMaster, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Minigame_ToneMaster, &leer5);
      break;

      case QuickFinger:
      Messages_ZeigeNachricht(SpielerEins, MSG_Minigame_QuickFinger, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Minigame_QuickFinger, &leer5);
      break;

      case FastCounter:
      Messages_ZeigeNachricht(SpielerEins, MSG_Minigame_FastCounter, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Minigame_FastCounter, &leer5);
      break;

      case Timing:
      Messages_ZeigeNachricht(SpielerEins, MSG_Minigame_Timing, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Minigame_Timing, &leer5);
      break;
    }
  }

  if (NameShown)
  {
    if (!NameBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        NameBestaetigtP1 = true;
        TasterLed_Setzten(SpielerEins, LedEins, Schwarz);
      }
    }

    if (!NameBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        NameBestaetigtP2 = true;
        TasterLed_Setzten(SpielerZwei, LedEins, Schwarz);
      }
    }
  }

  if (NameBestaetigtP1 and NameBestaetigtP2)
  {
    NameShown = false;
    NameBestaetigtP1 = false;
    NameBestaetigtP2 = false;

    MinigameManager_GameNameShown();
  }
}
