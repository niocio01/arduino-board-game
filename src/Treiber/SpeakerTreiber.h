#ifndef SPEAKERTREIBER_H
#define SPEAKERTREIBER_H

#include "inttypes.h"

typedef enum
{
  Tune
}SpeakerTreiber_Tunes_t;

bool SpeakerTreiber_Startup(void);
void SpeakerTreiber_playTune(void);

#endif
