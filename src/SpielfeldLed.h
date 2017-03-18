#ifndef SPIELFELDLED_H
#define SPIELFELDLED_H

#include <inttypes.h>
#include "GlobalTypes.h"



/* function: SpielfeldLed_Setzten:
Status eines Spielfeld Leds setzten
1. Param: led Nummer (1,2,3...) (nicht Neopixel ID!)
2. Param: Led Farbe (Schwarz, weiss, rot, grün, blau) */
void SpielfeldLed_Setzten (uint16_t nummer, GlobalTypes_Farbe_t farbe);

#endif
