#include "Karten/Minigames/ShowGameAction.h"
#include "Messages.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/TasterLed.h"
#include "Karten/Minigames/MinigameManager.h"

static MinigameManager_GameStatus_t Game;
static Messages_values leer5;

static bool actionShown;
static bool actionBestaetigtP1;
static bool actionBestaetigtP2;


void ShowGameAction_TellGame(MinigameManager_GameStatus_t newGame)
{
  Game = newGame;
}

void ShowGameAction_Run(void)
{
  if (!actionShown)
  {
    actionShown = true;
    TasterLed_Setzen(SpielerEins, LedEins, Gruen);
    TasterLed_Setzen(SpielerZwei, LedEins, Gruen);

    switch (Game)
    {
      case Reaktion:
      Messages_ZeigeNachricht(SpielerEins, MSG_Rot_Licht_druecken, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Rot_Licht_druecken, &leer5);
      break;

      case Simon: // separat im game
      actionBestaetigtP1 = true;
      actionBestaetigtP2 = true;
      break;

      case ToneMaster: // separat im game
      actionBestaetigtP1 = true;
      actionBestaetigtP2 = true;
      break;

      case QuickFinger:
      Messages_ZeigeNachricht(SpielerEins, MSG_Schnell_druecken, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Schnell_druecken, &leer5);
      break;

      case FastCounter:
      Messages_ZeigeNachricht(SpielerEins, MSG_20_schnell_druecken, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_20_schnell_druecken, &leer5);
      break;

      case Timing:
      Messages_ZeigeNachricht(SpielerEins, MSG_Stopp_Licht, &leer5);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Stopp_Licht, &leer5);
      break;
    }
  }

  if (actionShown)
  {
    if (!actionBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        actionBestaetigtP1 = true;
        TasterLed_Setzen(SpielerEins, LedEins, Schwarz);
      }
    }

    if (!actionBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        actionBestaetigtP2 = true;
        TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
      }
    }
  }

  if (actionBestaetigtP1 and actionBestaetigtP2)
  {
    actionShown = false;
    actionBestaetigtP1 = false;
    actionBestaetigtP2 = false;

    MinigameManager_GameActionShown();
  }
}
