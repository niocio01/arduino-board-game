#include "Karten/KartenManager.h"
#include "Treiber/RfidTreiber.h"
#include "Karten/Buffs/BuffManager.h"
#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/LedTreiber.h"



bool KartenManager_KarteStarten(void)
{
  uint8_t * kartenNrRef;
  uint8_t  kartenNrValue;

  kartenNrRef = &kartenNrValue;
  bool success = RfidTreiber_ReadCard(kartenNrRef);
  if (success)
  {
    if (kartenNrValue <= 60) {
      BuffManager_BuffAnwenden(kartenNrValue);
      LedTreiber_LedSchalten(63,Rot);
    }
    else if(kartenNrValue >= 61){
      MinigameManager_MinigameStarten(kartenNrValue);
    }
  }
  return success;
}
