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

bool IRTreiber_Startup(void)
{
  Wire.begin();        // join i2c bus (address optional for master)
  return true;
}

void IRTreiber_Main(void)
{
  if (AktiveBuffsAnzeigen)
  {
    AktiveBuffsAnzeigen_Run();
  }
  else
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
        LedTreiber_LedSchalten(77, Rot);
        break;

        case PressedButton_CH:
        LedTreiber_LedSchalten(77, Gruen);
        break;

        case PressedButton_CH_UP:
        LedTreiber_LedSchalten(77, Blau);
        break;

        case PressedButton_PREV:
        break;

        case PressedButton_NEXT:
        break;

        case PressedButton_PLAY:
        MinigameManager_EinsatzGesetzt(1, 1);
        break;

        case PressedButton_VOL_DOWN:
          SF_MovePlayerFigure(SpielerZwei, FigureEins, -2);
        break;

        case PressedButton_VOL_UP:
        SF_MovePlayerFigure(SpielerZwei, FigureEins, 10);
        break;

        case PressedButton_EQ:
        AktiveBuffsAnzeigen = true;
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
        SF_SetSpielfeldOff();
        break;

        case PressedButton_5:
        SpeakerTreiber_PlayTone(150, 400);
        break;

        case PressedButton_6:
        SpeakerTreiber_PlayTone(1500, 800);
        break;

        case PressedButton_7:
        Zeitreise_DebugSituationErstellen();
        break;

        case PressedButton_8:
        LedTreiber_AllBlack();
        break;

        case PressedButton_9:
        soft_restart();
        break;
      }
    }
  }
}
