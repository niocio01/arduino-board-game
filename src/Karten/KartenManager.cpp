#include "Karten/KartenManager.h"
#include "Treiber/RfidTreiber.h"
#include "Karten/Buffs/BuffManager.h"
#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"

void KartenManager_Main(void)
{
  uint8_t * kartenNrRef;
  uint8_t  kartenNrValue;

  kartenNrRef = &kartenNrValue;
  bool success = RfidTreiber_ReadCard(kartenNrRef);
  if (success)
  {
    if (kartenNrValue <= 60)
    {
      BuffManager_BuffAnwenden(kartenNrValue);
      LedTreiber_LedSchalten(63,Rot);
    }
    else
    {
      MinigameManager_MinigameStarten(kartenNrValue);
    }
  }
}
