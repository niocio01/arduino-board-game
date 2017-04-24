#ifndef MINIGAMEMANAGER_H
#define MINIGAMEMANAGER_H

#include <inttypes.h>
#include "globaltypes.h"

typedef enum
{
  Reaktion,
  Simon,
  ToneMaster,
  QuickFinger,
  FastCounter,
  Timing
} MinigameManager_GameStatus_t;

typedef enum
{
  Win_SpielerEins,
  Win_SpielerZwei,
  Win_Unentschieden
} MinigameManager_Winner_t;


    void MinigameManager_Run(void);
    void MinigameManager_SetGame(MinigameManager_GameStatus_t newGameStatus);
    void MinigameManager_StartNewGame(bool useSameEinsatz = false);
    void MinigameManager_EinsatzGesetzt(uint8_t newEinsatzP1, uint8_t newEinsatzP2, bool continueWithFigurAuswahl = false);
    void MinigameManager_GameEnded(MinigameManager_Winner_t gewinner, bool skipShowWinner = false);
    void MinigameManager_WinnerShown(void);
    void MinigameManager_GameNameShown(void);
    void MinigameManager_GameActionShown(void);

#endif
