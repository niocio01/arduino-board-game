#include "Treiber/IRTreiber.h"
#include "Treiber/LedTreiber.h"
#include <SoftReset.h>
#include <arduino.h>
#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/SpielfeldLed.h"
#include "Karten/Buffs/Zeitreise.h"
#include "Karten/Buffs/AktiveBuffsAnzeigen.h"
#include <Wire.h>
#include "Treiber/SpeakerTreiber.h"
#include "Pitches.h"
#include "Treiber/SpielfeldLed.h"

#define I2CAdress 8

uint32_t LastUpdateTime;
uint16_t UpdateIntervall = 500;

#define PressedButton_None      0
#define PressedButton_CH_DOWN   1
#define PressedButton_CH        2
#define PressedButton_CH_UP     3
#define PressedButton_PREV      4
#define PressedButton_NEXT      5
#define PressedButton_PLAY      6
#define PressedButton_VOL_DOWN  7
#define PressedButton_VOL_UP    8
#define PressedButton_EQ        9
#define PressedButton_0         10
#define PressedButton_100       11
#define PressedButton_200       12
#define PressedButton_1         13
#define PressedButton_2         14
#define PressedButton_3         15
#define PressedButton_4         16
#define PressedButton_5         17
#define PressedButton_6         18
#define PressedButton_7         19
#define PressedButton_8         20
#define PressedButton_9         21

static bool AktiveBuffsAnzeigen = false;

void IRTreiber_PlayMelody(void);

bool IRTreiber_Startup(void)
{
  Wire.begin();        // join i2c bus (address optional for master)
  return true;
}

void IRTreiber_Main(void)
{
  {
    if (millis() - LastUpdateTime > UpdateIntervall)
    {
      Wire.requestFrom(I2CAdress, 1); // send command to request 8 bytes (uint8_t)

      int8_t PushedButton = Wire.read(); // receive a byte

      switch (PushedButton)
      {
        case PressedButton_None:
        break;

        case PressedButton_CH_DOWN:
        SpeakerTreiber_PlayTone(440, 10);
        break;

        case PressedButton_CH:
        SF_SetSpielfeldOff();
        LedTreiber_MapBlack();
        LedTreiber_Rainbow();
        IRTreiber_PlayMelody();
        delay(1000);
        SF_SetSpielfeldOn();
        break;

        case PressedButton_CH_UP:
        IRTreiber_PlayMelody();
        break;

        case PressedButton_PREV:
        SF_MovePlayerFigure(SpielerEins, FigureEins, 2);
        break;

        case PressedButton_NEXT:
        SF_MovePlayerFigure(SpielerEins, FigureZwei, 2);
        break;

        case PressedButton_PLAY:
        MinigameManager_EinsatzGesetzt(0, 0);
        break;

        case PressedButton_VOL_DOWN:
        SF_MovePlayerFigure(SpielerZwei, FigureZwei, 2);
        break;

        case PressedButton_VOL_UP:
        SF_MovePlayerFigure(SpielerZwei, FigureEins, 2);
        break;

        case PressedButton_EQ:
        break;

        case PressedButton_0:
        break;

        case PressedButton_100:
        SF_MovePlayerFigure(SpielerZwei, FigureZwei, 10);
        break;

        case PressedButton_200:
        SF_MovePlayerFigure(SpielerZwei, FigureZwei, -2);
        break;

        case PressedButton_1:
        SF_SetBranchPlayer (SpielerZwei, Branch1, true);
        break;

        case PressedButton_2:
        SF_SetBranchPlayer (SpielerZwei, Branch2, true);
        break;

        case PressedButton_3:
        SF_SetBranchPlayer (SpielerZwei, Branch3, true);
        break;

        case PressedButton_4:
        SF_SetBranchPlayer (SpielerEins, Branch1, true);
        break;

        case PressedButton_5:
        SF_SetBranchPlayer (SpielerEins, Branch2, true);
        break;

        case PressedButton_6:
        SF_SetBranchPlayer (SpielerEins, Branch3, true);
        break;

        case PressedButton_7:

        break;

        case PressedButton_8:
        soft_restart();
        break;

        case PressedButton_9:

        break;
      }
    }
  }
}

void IRTreiber_PlayMelody(void)
{
  int melody[] = {
  NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5
  };
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

  for (int thisNote = 0; thisNote < 8; thisNote++)
  {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    SpeakerTreiber_PlayTone(melody[thisNote], noteDuration);
    //tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
