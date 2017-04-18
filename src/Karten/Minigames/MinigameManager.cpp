#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"
#include "Karten/Minigames/QuickFinger.h"
#include "Karten/Minigames/EinsatzSetzen.h"
//#include "FigurAuswahl.h"


MinigameManager_GameStatus_t currentGame;
static bool GameInProgress = false;
static bool einsatzSetztenAktiv = false;
uint8_t einsatzP1;
uint8_t einsatzP2;

void MinigameManager_StartNewGame(void)
{
  einsatzSetztenAktiv = true;
  GameInProgress = true;
}

void MinigameManager_GameEnded(MinigameManager_Gewinner_t gewinner)
{
  switch (gewinner)
  {
    case Win_SpielerEins:
    LedTreiber_LedSchalten(193, Gruen);
    GameInProgress = false;
    einsatzSetztenAktiv = true;
    break;

    case Win_SpielerZwei:
    LedTreiber_LedSchalten(193, Rot);
    GameInProgress = false;
    einsatzSetztenAktiv = true;
    break;

    case Win_Unentschieden:
    GameInProgress = true;
    break;
  }
}

void MinigameManager_SetGame(MinigameManager_GameStatus_t newGame)
{
  currentGame = newGame;
}

void MinigameManager_EinsatzGesetzt(uint8_t newEinsatzP1, uint8_t newEinsatzP2)
{
  einsatzP1 = newEinsatzP1;
  einsatzP2 = newEinsatzP2;
  einsatzSetztenAktiv = false;
}

void MinigameManager_Run(void)
{
  if (GameInProgress == true)
  {
    if (einsatzSetztenAktiv == true)
    {
      EinsatzSetzen_Run();
    }
    else
    {
      switch (currentGame)
      {
        case Reaktion:
        // code
        break;

        case Simon:
        // code
        break;

        case ToneMaster:
        // code
        break;

        case QuickFinger:
        QuickFinger_RunGame();
        break;

        case FastCounter:
        // code
        break;

        case Timing:
        // code
        break;
      }
    }
  }
}
