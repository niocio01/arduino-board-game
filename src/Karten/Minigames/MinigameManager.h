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

    void MinigameManager_Main(void);
    void MinigameManager_SetStatus(MinigameManager_GameStatus_t newGameStatus);
    void MinigameManager_StartNewGame(void);
    void MinigameManager_EinsatzGesetzt(uint8_t newEinsatzAktiverSpieler, uint8_t newEinsatzPassiverSpieler);
    void MinigameManager_EndGame(GlobalTypes_AktiverSpieler_t gewinner);

#endif
