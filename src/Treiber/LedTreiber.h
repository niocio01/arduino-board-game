#ifndef LEDTREIBER_H
#define LEDTREIBER_H

#include <inttypes.h>
#include "GlobalTypes.h"


bool LedTreiber_Startup(void);

/* function: LedTreiber_LedSchalten:
setzt den zustand eines neopixels und zeigt diesen an.
1. param: Led ID (1,2,3...)
2. param: Farbe (Schwarz, Weiss, Rot, Grün, Blau, Violett, Gelb)
3. param: helligkeit (0-255)(kann auch weggelassen werden, dann 255)
*/
void LedTreiber_LedSchalten(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit = 255);

#endif
