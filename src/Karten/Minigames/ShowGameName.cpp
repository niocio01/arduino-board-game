#include "Karten/Minigames/ShowGameName.h"
#include "Messages.h"

static MinigameManager_GameStatus_t Game;
static Messages_values gameName;

void ShowGameName_TellGame(MinigameManager_GameStatus_t newGame)
{
  Game = newGame;
}

void ShowGameName_Run(void)
{
  switch (Game) // game auswählen und Laufen lassen
  {
    case Reaktion:
    //gameName.MiniGameName = "Reaktion";
    break;

    case Simon:
    // code
    break;

    case ToneMaster:
    // code
    break;

    case QuickFinger:

    break;

    case FastCounter:
    // code
    break;

    case Timing:
    // code
    break;
  }
  Messages_ZeigeNachricht(SpielerEins, MSGxx_MinigameName, &gameName);
  Messages_ZeigeNachricht(SpielerZwei, MSGxx_MinigameName, &gameName);
}
