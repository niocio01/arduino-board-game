#ifndef LEDTREIBER_H
#define LEDTREIBER_H

#include <inttypes.h>
#include "GlobalLed.h"


bool LedTreiber_Startup(void);
void LedTreiber_LedSchalten(uint16_t ledID, GlobalLed_Farbe_t ledFarbe);

#endif
