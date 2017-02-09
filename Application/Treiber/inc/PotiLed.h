#ifndef POTILED_H
#define POTILED_H

#include "GlobalLed.h"

/* function: PotiLed_Setzten
setzen des zustands eines Taster Leds.
1. Param: Spieler (spielerEins, spielerZwei)
2. Param: Led Farbe (aus, weiss, rot, grün, blau) */
void PotiLed_Setzten(GlobalLed_Spieler_t Spieler,
GlobalLed_Farbe_t Farbe);

#endif
