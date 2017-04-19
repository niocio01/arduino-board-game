#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"
#include "Karten/Minigames/QuickFinger.h"
#include "Karten/Minigames/EinsatzSetzen.h"
#include "Karten/Minigames/ShowWinner.h"
#include "Karten/Minigames/ShowGameName.h"
#include "GlobalTypes.h"
#include "FigurAuswahl.h"


MinigameManager_GameStatus_t currentGame;
static bool GameInProgress = false;
static bool einsatzSetztenAktiv = false;
static bool gewinnerBestimmt = false;
static bool WinnerShown = false;
static bool GameNameShown = false;
uint8_t einsatzP1;
uint8_t einsatzP2;
static bool SpielerEinsHatGewonnen;
static bool SpielerZweiHatGewonnen;

void MinigameManager_StartNewGame(bool useSameEinsatz)
{
  GameInProgress = true;
  WinnerShown = false;
  gewinnerBestimmt = false;
  if (useSameEinsatz == true)
  {
    einsatzSetztenAktiv = false;
  }
  else
  {
    einsatzSetztenAktiv = true;
  }
}

void MinigameManager_GameEnded(MinigameManager_Winner_t gewinner, bool SkipShowWinner)
{

  GameInProgress = false;
  gewinnerBestimmt = true;
  if (SkipShowWinner == true)
  {
    WinnerShown = true;
  }
  else
  {
    WinnerShown = false;
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

void MinigameManager_SetGame(MinigameManager_GameStatus_t newGame)
{
  currentGame = newGame;
  GameInProgress = true;
  einsatzSetztenAktiv = true;
  gewinnerBestimmt = false;
  ShowGameName_TellGame(newGame);

}

void MinigameManager_EinsatzGesetzt(uint8_t newEinsatzP1, uint8_t newEinsatzP2)
{
  einsatzP1 = newEinsatzP1;
  einsatzP2 = newEinsatzP2;
  einsatzSetztenAktiv = false;
}

void MinigameManager_WinnerShown(void)
{
  if (SpielerEinsHatGewonnen)
  {
  FigurAuswahl_TellResults(SpielerEins, einsatzP1 + 1);
  }

  if (SpielerZweiHatGewonnen)
  {
  FigurAuswahl_TellResults (SpielerZwei, einsatzP2 + 1);
  }
  WinnerShown = true;
}

void MinigameManager_GameNameShown(void)
{
  GameNameShown = true;
}

void MinigameManager_Run(void)
{
  if (GameInProgress == true)
  {
    if (einsatzSetztenAktiv == true and gewinnerBestimmt == false)
    {
      EinsatzSetzen_Run();
    }
    if (GameNameShown == false)
    {
      ShowGameName_Run();
    }
    if (einsatzSetztenAktiv == false and gewinnerBestimmt == false and GameNameShown == true)
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
  }
  else
  {
    if ( gewinnerBestimmt == true and WinnerShown == false) //game fertig
    {
      ShowWinner_Run(); //gewinner anzeigen oder bei unentschieden neustarten
    }
    else
    {
      //figur auswaehlen
    }
  }

}
