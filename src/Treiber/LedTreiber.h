#ifndef LEDTREIBER_H
#define LEDTREIBER_H

#include <inttypes.h>
#include "GlobalTypes.h"


void LedTreiber_Rainbow(void);

bool LedTreiber_Startup(void);

/* function: LedTreiber_LedSchalten:
setzt den zustand eines neopixels und zeigt diesen an.
1. param: Led ID (1,2,3...)
2. param: Farbe (Schwarz, Weiss, Rot, Grün, Blau, Violett, Gelb)
3. param: helligkeit (0-255)(kann auch weggelassen werden, dann 255)
*/
void LedTreiber_LedSchalten(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit = 255);


/* function: LedTreiber_LedSetzen:
setzt den zustand eines neopixels zeigt diesen aber nicht!
1. param: Led ID (1,2,3...)
2. param: Farbe (Schwarz, Weiss, Rot, Grün, Blau, Violett, Gelb)
3. param: helligkeit (0-255)(kann auch weggelassen werden, dann 255)
*/
void LedTreiber_LedSetzen(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit = 255);

/* function: LedTreiber_LedAnzeigen:
Zeigt die zuvor gesetzten Leds
*/
void LedTreiber_LedAnzeigen(void);

/* function: LedTreiber_AllBlack:
schaltet alle LEDs aus.
*/
void LedTreiber_MapBlack(void);

void LedTreiber_AllBlack(void);

void LedTreiber_ControllsBlack(void);

#endif
