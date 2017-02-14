#ifndef TASTERLED_H
#define TASTERLED_H

#include "GlobalLed.h"

typedef enum
{
  ledEins,
  ledZwei,
  ledDrei,
  ledVier
} TasterLed_Nummer_t;

/* function: TasterLed_Setzten
setzen des zustands eines Taster Leds.
1. Param: Spieler (spielerEins, spielerZwei)
2. Param: Led Nummer (ledEins,ledZwei,ledDrei,ledVier)
3. Param: Led Farbe (aus, weiss, rot, grün, blau) */
void TasterLed_Setzten(GlobalLed_Spieler_t Spieler,
TasterLed_Nummer_t LedNummer,
GlobalLed_Farbe_t Farbe);

#endif
