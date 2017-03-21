<<<<<<< HEAD
#ifndef SPIELFELDLED_H
#define SPIELFELDLED_H

#include <inttypes.h>
#include "GlobalTypes.h"

typedef enum
{
  Verlaengerung1,
  Verlaengerung2,
  Verlaengerung3
} GlobalTypes_Spieler_t;


/* function: SpielfeldLed_Setzten:
Status eines Spielfeld Leds setzten
1. Param: led Nummer (1,2,3...) (nicht Neopixel ID!)
2. Param: Led Farbe (Schwarz, weiss, rot, grün, blau) */
void SpielfeldLed_Setzten (uint16_t nummer, GlobalTypes_Farbe_t farbe, GlobalTypes_Spieler_t spieler);

#endif
=======
>>>>>>> origin/master
