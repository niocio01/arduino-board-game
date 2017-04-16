#ifndef POTITREIBER_H
#define  POTITREIBER_H

#include "globaltypes.h"
#include <inttypes.h>

bool PotiTreiber_Startup(void);

uint8_t PotiTreiber_Get_Val (GlobalTypes_Spieler_t spieler);

#endif
