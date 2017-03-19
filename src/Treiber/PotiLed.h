#ifndef POTILED_H
#define POTILED_H

#include "Treiber/GlobalTypes.h"

/* function: PotiLed_Setzten
setzen des zustands eines Taster Leds.
1. Param: Spieler (spielerEins, spielerZwei)
2. Param: Led Farbe (Schwarz, weiss, rot, grün, blau) */
void PotiLed_Setzten(GlobalTypes_Spieler_t spieler,
  GlobalTypes_Farbe_t farbe);

#endif
