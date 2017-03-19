#include "KartenManager.h"
#include "LedTreiber.h"
#include "RfidTreiber.h"


/* enum KartenManager_Karten_t {
Speed=0,
Aussetzten,
Schild,
GewinnGarantiert
  };
*/

bool KartenManager_KarteStarten(uint8_t* kartenNr)
{
bool success = RfidTreiber_ReadCard(kartenNr);
if (success) {

}
return success;
}
