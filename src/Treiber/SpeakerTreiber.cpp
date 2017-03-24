#include "Treiber/SpeakerTreiber.h"
#include "pitches.h"
#include "arduino.h"
#include "Treiber/LedTreiber.h"

#define SPEAKERPIN (13)
#define MUTEPIN (45)

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

bool SpeakerTreiber_Startup(void)
{
  pinMode(MUTEPIN, OUTPUT);
  digitalWrite(MUTEPIN, HIGH);
  tone(SPEAKERPIN, NOTE_C4, 200);
  //digitalWrite(MUTEPIN, LOW);
  return true;
}

void SpeakerTreiber_playTune(void)
{
  digitalWrite(MUTEPIN, HIGH);
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(13, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(13);
  }
  digitalWrite(MUTEPIN, LOW);
}
