#ifndef LEDTREIBER_H
#define LEDTREIBER_H

#include <inttypes.h>

typedef enum
{
  aus,
  weiss,
  rot,
  gruen,
  blau
} LedTreiber_LedFarbe_t;

void LedTreiber_LedSchalten(uint8_t ledID, LedTreiber_LedFarbe_t ledFarbe);


#endif
