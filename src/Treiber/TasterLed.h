#ifndef TASTERLED_H
#define TASTERLED_H

#include "GlobalTypes.h"

typedef enum
{
  LedEins,
  LedZwei,
  LedDrei,
  LedVier
} TasterLed_Nummer_t;

/* function: TasterLed_Setzen
setzen des zustands eines Taster Leds.
1. Param: Spieler (spielerEins, spielerZwei)
2. Param: Led Nummer (ledEins,ledZwei,ledDrei,ledVier)
3. Param: Led Farbe (aus, weiss, rot, grün, blau) */
void TasterLed_Setzen(GlobalTypes_Spieler_t spieler,
TasterLed_Nummer_t LedNummer,
GlobalTypes_Farbe_t farbe);

#endif
