#include "KartenManager.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/RfidTreiber.h"

const uint8_t Speed =48;
const uint8_t Aussetzen =49;
const uint8_t Schild =50;
const uint8_t MehrEinsatz =51;
const uint8_t Lucky =52;

bool KartenManager_KarteStarten(void)
{
  uint8_t * kartenNrRef;
  uint8_t  kartenNrValue;

  kartenNrRef = &kartenNrValue;
  bool success = RfidTreiber_ReadCard(kartenNrRef);
  if (success)
  {
    if (kartenNrValue == Speed) {

    }
  }
  return success;
}
