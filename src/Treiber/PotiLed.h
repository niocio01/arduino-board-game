#ifndef POTILED_H
#define POTILED_H

#include "GlobalTypes.h"

/* function: PotiLed_Setzen
setzen des zustands eines Taster Leds.
1. Param: Spieler (spielerEins, spielerZwei)
2. Param: Led Farbe (Schwarz, weiss, rot, grün, blau) */
void PotiLed_Setzen(GlobalTypes_Spieler_t spieler,
  GlobalTypes_Farbe_t farbe);

#endif
