#include "Treiber/IRTreiber.h"
#include <IRLibDecodeBase.h>
#include <IRLib_P01_NEC.h>
#include <IRLibRecv.h>
#include "Treiber/LedTreiber.h"
#include <SoftReset.h>
#include <arduino.h>
#include "Karten/Minigames/MinigameManager.h"
#include "Treiber/SpielfeldLed.h"
#include "Karten/Buffs/Zeitreise.h"
#include "Karten/Buffs/AktiveBuffsAnzeigen.h"
#include "Treiber/SpeakerTreiber.h"
#include "pitches.h"

IRdecodeNEC myDecoder; // Now declare an instance of that decoder.
IRrecv myReceiver(6); //pin number for the receiver


#define MYPROTOCOL NEC //IR Protocoll

#define IR_BUTTON_CH_DOWN   0xFFA25D
#define IR_BUTTON_CH        0xFF629D
#define IR_BUTTON_CH_UP     0xFFE21D
#define IR_BUTTON_PREV      0xFF22DD
#define IR_BUTTON_NEXT      0xFF02FD
#define IR_BUTTON_PLAY      0xFFC23D
#define IR_BUTTON_VOL_DOWN  0xFFE01F
#define IR_BUTTON_VOL_UP    0xFFA857
#define IR_BUTTON_EQ        0xFF906F
#define IR_BUTTON_0         0xFF6897
#define IR_BUTTON_100       0xFF9867
#define IR_BUTTON_200       0xFFB04F
#define IR_BUTTON_1         0xFF30CF
#define IR_BUTTON_2         0xFF18E7
#define IR_BUTTON_3         0xFF7A85
#define IR_BUTTON_4         0xFF10EF
#define IR_BUTTON_5         0xFF38C7
#define IR_BUTTON_6         0xFF5AA5
#define IR_BUTTON_7         0xFF42BD
#define IR_BUTTON_8         0xFF4AB5
#define IR_BUTTON_9         0xFF52AD

static bool AktiveBuffsAnzeigen = false;

bool IRTreiber_Startup(void)
{
  myReceiver.enableIRIn(); // Start the receiver
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
    if (myReceiver.getResults())
    {
      if(myDecoder.decode())
      {
        switch(myDecoder.value)
        {
          case IR_BUTTON_CH_DOWN:
          LedTreiber_LedSchalten(77, Rot);
          break;

          case IR_BUTTON_CH:
          LedTreiber_LedSchalten(77, Gruen);
          break;

          case IR_BUTTON_CH_UP:
          LedTreiber_LedSchalten(77, Blau);
          break;

          case IR_BUTTON_PREV:
          break;

          case IR_BUTTON_NEXT:
          SpeakerTreiber_playTone(NOTE_C4, 2000);
          break;

          case IR_BUTTON_PLAY:
          MinigameManager_EinsatzGesetzt(1, 1);
          break;

          case IR_BUTTON_VOL_DOWN:
          break;

          case IR_BUTTON_VOL_UP:
          break;

          case IR_BUTTON_EQ:
          AktiveBuffsAnzeigen = true;
          break;

          case IR_BUTTON_0:
          break;

          case IR_BUTTON_100:
          SF_MovePlayerFigure(SpielerZwei, FigureEins, 5 ,true, false, true);
          break;

          case IR_BUTTON_200:
          SF_MovePlayerFigure(SpielerZwei, FigureEins, 2 ,true, false, true);
          break;

          case IR_BUTTON_1:
          SF_StartDim(5);
          break;

          case IR_BUTTON_2:
          SF_StartLauflicht(Gruen, 50);
          break;

          case IR_BUTTON_3:
          break;

          case IR_BUTTON_4:
          break;

          case IR_BUTTON_5:
          break;

          case IR_BUTTON_6:
          break;

          case IR_BUTTON_7:
          Zeitreise_DebugSituationErstellen();
          break;

          case IR_BUTTON_8:
          LedTreiber_AllBlack();
          break;

          case IR_BUTTON_9:
          soft_restart();
          break;

        }
      }
      myReceiver.enableIRIn();
    }
  }
}
