#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"

MinigameManager_GameStatus_t currentGameStatus;
bool GameInProgress;
bool startNewGame;

void MinigameManager_SetStatus(MinigameManager_GameStatus_t newGameStatus)
{
  currentGameStatus = newGameStatus;
}

void MinigameManager_Main(void){
  if (GameInProgress == true)
  {
    if (startNewGame == true)
    {
      //einsatz setzten
    }
    else
    {
      switch (currentGameStatus)
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
        // code
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
