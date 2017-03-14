#include "SpielfeldLed.h"
#include <inttypes.h>
#include "LedTreiber.h"

// tabelle zur zuweiseung von Spielfeld Led Nr. zu Led ID
static const uint16_t tabLedID [] =
20, // Led ID für Spielfeld Led Nummer 0
21, // Led ID für Spielfeld Led Nummer 1
23, // Led ID für Spielfeld Led Nummer 2
24, // Led ID für Spielfeld Led Nummer 3
25, // Led ID für Spielfeld Led Nummer 4
45, // Led ID für Spielfeld Led Nummer 5
46, // Led ID für Spielfeld Led Nummer 6
48  // Led ID für Spielfeld Led Nummer 7
;

void SpielfeldLed_Setzten (uint16_t nummer, GlobalTypes_Farbe_t farbe)
{
  LedTreiber_LedSchalten(tabLedID[nummer], farbe);
}
