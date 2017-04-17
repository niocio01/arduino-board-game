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

    void MinigameManager_Run(void);
    void MinigameManager_SetGame(MinigameManager_GameStatus_t newGameStatus);
    void MinigameManager_StartNewGame(void);
    void MinigameManager_EinsatzGesetzt(uint8_t newEinsatzP1, uint8_t newEinsatzP2);
    void MinigameManager_GameEnded(GlobalTypes_Spieler_t gewinner);

#endif
