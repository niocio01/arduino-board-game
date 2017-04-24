#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"
#include "Karten/Minigames/QuickFinger.h"
#include "Karten/Minigames/EinsatzSetzen.h"
#include "Karten/Minigames/ShowWinner.h"
#include "Karten/Minigames/ShowGameName.h"
#include "GlobalTypes.h"
#include "FigurAuswahl.h"
#include "PlayerManager.h"
#include "Karten/Minigames/ShowGameAction.h"
#include "StatusLedSituation.h"

MinigameManager_GameStatus_t currentGame;

static bool showGameName;
static bool einsatzSetzen;
static bool showGameAction;
static bool runGame;
static bool showWinner;
static bool figurAuswaehlen;

uint8_t einsatzP1;
uint8_t einsatzP2;
static bool SpielerEinsHatGewonnen;
static bool SpielerZweiHatGewonnen;

void MinigameManager_SetGame(MinigameManager_GameStatus_t newGame)
{
  currentGame = newGame;
  ShowGameName_TellGame(newGame);
  ShowGameAction_TellGame(newGame);
}

void MinigameManager_StartNewGame(bool skipShowGameNameUndEinsatzSetzen)
{
  if (skipShowGameNameUndEinsatzSetzen == true)
  {
    showGameName = false;
    einsatzSetzen = false;
    runGame = true;

  }
  else
  {
    if (PlayerManager_SpielerEinsAmZug())
    {
      StatusLedSituationSetzen(SpielerEins, Minigame);
    }
    else
    {
      StatusLedSituationSetzen(SpielerZwei, Minigame);
    }
    showGameName = true;
  }
}

void MinigameManager_GameNameShown(void)
{
  showGameName = false;
  einsatzSetzen = true;
}

void MinigameManager_EinsatzGesetzt(uint8_t newEinsatzP1, uint8_t newEinsatzP2, bool continueWithFigurAuswahl)
{
  einsatzP1 = newEinsatzP1;
  einsatzP2 = newEinsatzP2;

  if (continueWithFigurAuswahl == true)
  {
    figurAuswaehlen = true;
  }
  else
  {
    einsatzSetzen = false;
    showGameAction = true;
  }
}

void MinigameManager_GameActionShown(void)
{
  showGameAction = false;
  runGame = true;
}

void MinigameManager_GameEnded(MinigameManager_Winner_t gewinner, bool SkipShowWinner)
{
  runGame = false;
  if (SkipShowWinner == true)
  {
    showWinner = false;
    figurAuswaehlen = true;
  }
  else
  {
    showWinner = true;
  }

  switch (gewinner)
  {
    case Win_SpielerEins:
    SpielerEinsHatGewonnen = true;
    SpielerZweiHatGewonnen = false;
    ShowWinner_TellResults(Win_SpielerEins);
    break;

    case Win_SpielerZwei:
    SpielerEinsHatGewonnen = false;
    SpielerZweiHatGewonnen = true;
    ShowWinner_TellResults(Win_SpielerZwei);
    break;

    case Win_Unentschieden:
    ShowWinner_TellResults(Win_Unentschieden);
    break;
  }
}

void MinigameManager_WinnerShown(void)
{
  showWinner = false;
  figurAuswaehlen = true;

  if (SpielerEinsHatGewonnen)
  {
    //  FigurAuswahl_TellResults (SpielerEins, einsatzP1 + 1);
  }

  if (SpielerZweiHatGewonnen)
  {
    //  FigurAuswahl_TellResults (SpielerZwei, einsatzP2 + 1);
  }
}


void MinigameManager_Run(void)
{
  if (showGameName)
  {
    ShowGameName_Run();
  }
  else if (einsatzSetzen)
  {
    EinsatzSetzen_Run();
  }
   else if (showGameAction)
  {
    ShowGameAction_Run();
  }
  else if (runGame)
  {
    switch (currentGame) // game auswählen und Laufen lassen
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

  else if (showWinner) //game fertig
  {
    ShowWinner_Run(); //gewinner anzeigen oder bei unentschieden neustarten
  }

  else if (figurAuswaehlen)
  {
    //figur auswaehlen
  }
}
