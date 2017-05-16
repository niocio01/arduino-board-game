#ifndef SPEAKERTREIBER_H
#define SPEAKERTREIBER_H

#include "inttypes.h"

bool SpeakerTreiber_Startup(void);
void SpeakerTreiber_PlayTone(uint16_t frequency, uint16_t duration);

#endif
