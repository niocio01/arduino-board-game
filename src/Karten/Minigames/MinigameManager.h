#ifndef MINIGAMEMANAGER_H
#define MINIGAMEMANAGER_H

#include <inttypes.h>

typedef enum
{
  Reaktion,
  Simon,
  ToneMaster,
  QuickFinger,
  FastCounter,
  Timing
} MinigameManager_GameStatus_t;

    void MinigameManager_SetStatus(MinigameManager_GameStatus_t newGameStatus);
    void MinigameManager_Main(void);
    void MinigameManager_StartNewGame(void);
    void MinigameManager_EndGame(void);

#endif
