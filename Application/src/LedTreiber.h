#ifndef LEDTREIBER_H
#define LEDTREIBER_H

#include <inttypes.h>
#include "GlobalTypes.h"


bool LedTreiber_Startup(void);
void LedTreiber_LedSchalten(uint16_t ledID, GlobalTypes_Farbe_t farbe);

#endif
