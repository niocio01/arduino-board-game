#include "Treiber/SpeakerTreiber.h"
#include "pitches.h"
#include "arduino.h"
#include "Treiber/LedTreiber.h"

#define SPEAKERPIN (13)
#define MUTEPIN (45)

static uint32_t StartTime;
static uint32_t toneDuration;
static bool tonePlaying;

bool SpeakerTreiber_Startup(void)
{
  //SpeakerTreiber_playTone(NOTE_C2, 1000);
  digitalWrite(MUTEPIN, LOW);
  return true;
}

void SpeakerTreiber_playTone(uint32_t ton, uint32_t duration)
{
  /*
  digitalWrite(MUTEPIN, HIGH);
  tone (SPEAKERPIN, ton);
  StartTime = millis();
  toneDuration = duration;
  tonePlaying = true;
  */
}


void SpeakerTreiber_main (void)
{
  /*
if (tonePlaying)
{
  if ((millis() - StartTime) > toneDuration)
  {
    noTone(SPEAKERPIN);
    digitalWrite(MUTEPIN, LOW);
    tonePlaying = false;
  }
}
*/
}
