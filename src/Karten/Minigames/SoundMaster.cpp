#include "Karten/Minigames/SoundMaster.h"
#include "Treiber/LedTreiber.h"
#include <arduino.h>
#include "Treiber/PotiTreiber.h"
#include "Messages.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/PotiLed.h"
#include "Karten/Minigames/MinigameManager.h"
#include "PlayerManager.h"
#include "GlobalTypes.h"
#include "Pitches.h"
#include "Treiber/SpeakerTreiber.h"
#include "arduino.h"

const uint16_t Pitchrange = 220;
const uint16_t TonePlayingTime = 1000;
const uint16_t TimeAfterTonePlayed = 500;
const uint8_t updateIntervall = 50;

GlobalTypes_Spieler_t SM_spieler;

Messages_values leer9;

static uint16_t Pitchgoal;
static uint16_t MinFreq;
static uint16_t MaxFreq;
static uint16_t currentPitch;
static uint16_t ScoreP1;
static uint16_t ScoreP2;
static uint16_t ToneStartTime;
static uint16_t lastUpdateTime;

static bool startMsgShown;
static bool startDone;
static bool PlayerDecided;
static bool TonePlayed;
static bool StartMSGBestaetigt;

void SoundMaster_Start(void)
{
  Serial.begin(9600);
  Serial.println("Hello");
}

void SoundMaster_RunGame(void)
{
  if (!PlayerDecided)
  {
    PlayerDecided = true;
    if (PlayerManager_SpielerEinsAmZug())
    {
      SM_spieler = SpielerEins;
    }
    else
    {
      SM_spieler = SpielerZwei;
    }

  }
  if (!startMsgShown)
  {
    startMsgShown = true;
    LedTreiber_ControllsBlack();
    if (SM_spieler == SpielerEins)
    {
      Messages_ZeigeNachricht(SpielerEins, MSG_Zuhoeren, &leer9);
      Messages_ZeigeNachricht(SpielerZwei,MSG_GegnerSpielt, &leer9);
    }
    else
    {
      Messages_ZeigeNachricht(SpielerZwei, MSG_Zuhoeren, &leer9);
      Messages_ZeigeNachricht(SpielerEins,MSG_GegnerSpielt, &leer9);
    }
    TasterLed_Setzen(SM_spieler, LedEins, Gruen);

    randomSeed(analogRead(A3));
    MinFreq = random(NOTE_C2, NOTE_C5);
    MaxFreq = MinFreq + Pitchrange;
    Pitchgoal = random(MinFreq, MaxFreq);
  }

  if (!startDone)
  {
    if (!StartMSGBestaetigt)
    {
      if (TasterHandler_Klick(SM_spieler, TasterEins))
      {
        SpeakerTreiber_PlayTone(Pitchgoal, TonePlayingTime);
        ToneStartTime = millis();
        StartMSGBestaetigt = true;
      }
    }
    else
    {
      if (millis() - ToneStartTime >= TonePlayingTime + TonePlayingTime)
      {
        startDone = true;
        Messages_ZeigeNachricht(SM_spieler, MSG_Frequenz, &leer9);
        PotiLed_Setzen(SM_spieler, Gruen);
      }
    }
  }

  else
  {
    if (millis() - lastUpdateTime >= updateIntervall)
    {
      lastUpdateTime = millis();
      currentPitch = map(PotiTreiber_Get_Val(SM_spieler), 0, 255, MinFreq, MaxFreq);
      SpeakerTreiber_PlayTone(currentPitch, updateIntervall + 50);

      if (TasterHandler_Klick(SM_spieler, TasterEins))
      {
        LedTreiber_ControllsBlack();
        startMsgShown = false;
        startDone = false;
        TonePlayed =false;
        StartMSGBestaetigt = false;

        if (SM_spieler == SpielerEins)
        {
          ScoreP1 = abs(Pitchgoal - currentPitch);
          SM_spieler = SpielerZwei;
        }
        else
        {
          ScoreP2 = abs(Pitchgoal - currentPitch);
          SM_spieler = SpielerEins;
        }
      }

      if (ScoreP1 and ScoreP2)
      {
        PlayerDecided = false;
        if (ScoreP1 > ScoreP2)
        {
          ScoreP1 = 0;
          ScoreP2 = 0;
          MinigameManager_GameEnded(Win_SpielerEins);
        }
        else if (ScoreP2 > ScoreP1)
        {
          ScoreP1 = 0;
          ScoreP2 = 0;
          MinigameManager_GameEnded(Win_SpielerZwei);
        }
        else if (ScoreP1 == ScoreP2)
        {
          ScoreP1 = 0;
          ScoreP2 = 0;
          MinigameManager_GameEnded(Win_Unentschieden);
        }
      }
    }
  }
}
