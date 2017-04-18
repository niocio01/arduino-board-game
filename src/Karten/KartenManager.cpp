#include "Karten/KartenManager.h"
#include "Treiber/RfidTreiber.h"
#include "Karten/Buffs/BuffManager.h"
#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"
#include "arduino.h"
#include "Karten/Minigames/MinigameManager.h"

static bool minigameInProgress = false;


void Kartenmanager_MinigameEnded(void)
{
  minigameInProgress = false;
}

void KartenManager_Main(void)
{
  if (minigameInProgress == false)
  {
    uint8_t * kartenNrRef;
    uint8_t  kartenNrValue;

    kartenNrRef = &kartenNrValue;
    bool success = RfidTreiber_ReadCard(kartenNrRef);
    if (success)
    {
      if (kartenNrValue < 80) // Für Buffs
      {
        BuffManager_BuffAnwenden(kartenNrValue);
      }

      else // für Minigames
      {
        minigameInProgress = true;
        switch (kartenNrValue) {

          case 97:
          MinigameManager_SetGame(Reaktion);
          break;

          case 98:
          MinigameManager_SetGame(Simon);
          break;

          case 99:
          MinigameManager_SetGame(ToneMaster);
          break;

          case 100:
          MinigameManager_SetGame(QuickFinger);
          break;

          case 101:
          MinigameManager_SetGame(FastCounter);
          break;

          case 102:
          MinigameManager_SetGame(Timing);
          break;
        }
        MinigameManager_StartNewGame();
      }
    }
  }
  else
  {
    MinigameManager_Run();
  }
}
