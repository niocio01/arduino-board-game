#ifndef LEDTREIBER_H
#define LEDTREIBER_H

#include <inttypes.h>
#include "GlobalLed.h"

void LedTreiber_startup(bool gestartet);
void LedTreiber_LedSchalten(uint16_t ledID, LedTreiber_LedFarbe_t ledFarbe);

#endif
