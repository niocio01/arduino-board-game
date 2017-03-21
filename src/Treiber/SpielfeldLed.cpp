#include "Treiber/SpielfeldLed.h"
#include <inttypes.h>
#include "Treiber/LedTreiber.h"



void SpielfeldLed_Setzten (uint16_t nummer, GlobalTypes_Farbe_t farbe)
{
  LedTreiber_LedSchalten(tabLedID[nummer], farbe);
}
*/

void SpielfeldLed_Setzten (uint16_t nummer, GlobalTypes_Farbe_t farbe)
{
  LedTreiber_LedSchalten(nummer, farbe);
}
