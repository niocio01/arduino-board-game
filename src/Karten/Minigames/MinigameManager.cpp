#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"
#include "Karten/Minigames/QuickFinger.h"
//#include "FigurAuswahl.h"


MinigameManager_GameStatus_t currentGameStatus;
bool GameInProgress = false;
bool einsatzSetztenAktiv = false;
uint8_t einsatzAktiverSpieler;
uint8_t einsatzPassiverSpieler;

void MinigameManager_StartNewGame(void)
{
  einsatzSetztenAktiv = false; //debug
  GameInProgress = true;
}

void MinigameManager_EndGame(GlobalTypes_AktiverSpieler_t gewinner)
{
  if (gewinner == AktiverSpieler)
  {
    //FigurAuswahl_FigurAuswaehlen(AktiverSpieler, einsatzAktiverSpieler)
  }
  else
  {
    //FigurAuswahl_FigurAuswaehlen(PassiverSpieler, einsatzPassiverSpieler)
  }
  GameInProgress = false;
}

void MinigameManager_SetStatus(MinigameManager_GameStatus_t newGameStatus)
{
  currentGameStatus = newGameStatus;
}

void MinigameManager_EinsatzGesetzt(uint8_t newEinsatzAktiverSpieler, uint8_t newEinsatzPassiverSpieler)
{
  einsatzAktiverSpieler = newEinsatzAktiverSpieler;
  einsatzPassiverSpieler = newEinsatzPassiverSpieler;
  einsatzSetztenAktiv = false;
}

void MinigameManager_Main(void)
{
  if (GameInProgress == true)
  {
    if (einsatzSetztenAktiv == true)
    {
      //einsatz setzten
      einsatzSetztenAktiv = false; //debug
    }
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
