#ifndef SPEAKERTREIBER_H
#define SPEAKERTREIBER_H

#include "inttypes.h"

typedef enum
{
  Tune
}SpeakerTreiber_Tunes_t;

bool SpeakerTreiber_Startup(void);
void SpeakerTreiber_playTone(uint32_t ton, uint32_t duration);
void SpeakerTreiber_main (void);

#endif
