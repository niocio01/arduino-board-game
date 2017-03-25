#include "Karten/KartenManager.h"
#include "Treiber/RfidTreiber.h"
#include "Karten/Buffs/BuffManager.h"
#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"
#include "arduino.h"


//bool KartenManager_KarteStarten(void)
void KartenManager_Main(void)
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
      switch (kartenNrValue) {

        case 97:
        MinigameManager_SetStatus(Reaktion);
        break;

        case 98:
        MinigameManager_SetStatus(Simon);
        break;

        case 99:
        MinigameManager_SetStatus(ToneMaster);
        break;

        case 100:
        MinigameManager_SetStatus(QuickFinger);
        break;

        case 101:
        MinigameManager_SetStatus(FastCounter);
        break;

        case 102:
        MinigameManager_SetStatus(Timing);
        break;
      }
    }
  }
}
