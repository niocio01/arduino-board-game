#include "Karten/Minigames/QuickFinger.h"
#include "Treiber/LedTreiber.h"
#include <arduino.h>
#include "Treiber/PotiTreiber.h"
#include "Messages.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "Karten/Minigames/MinigameManager.h"

const uint8_t startCountdown = 3;
const uint8_t gameTime = 5;

static uint8_t PressesP1;
static uint8_t PressesP2;

Messages_values leer;
Messages_values countdown;
static bool startMsgShown;
static bool startDoneP1;
static bool startDoneP2;
static bool gameBegun;
static bool GameOver;

uint8_t startCountdownTimeRemaining = startCountdown;
uint8_t endCountdownTimeRemaining = startCountdown;
uint32_t lastCountTime;

void QuickFinger_RunGame()
{
  if (!gameBegun)
  {
    if ((millis() - lastCountTime) > 1000)
    {
      lastCountTime = millis();
      countdown.CountDown = startCountdownTimeRemaining;
      Messages_ZeigeNachricht(SpielerEins, MSGxx_Start_in, &countdown);
      Messages_ZeigeNachricht(SpielerZwei, MSGxx_Start_in, &countdown);
      startCountdownTimeRemaining = startCountdownTimeRemaining - 1;
      if (startCountdownTimeRemaining == 255)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Schnell_druecken, &leer);
        Messages_ZeigeNachricht(SpielerZwei, MSG_Schnell_druecken, &leer);
        TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
        TasterLed_Setzen(SpielerEins, LedEins, Gruen);
        gameBegun = true;
      }
    }
  }
  if (gameBegun)
  {
    if (TasterHandler_Klick(SpielerEins, TasterEins))
    {
      if (PressesP1 < 62)
      {
        LedTreiber_LedSchalten(PressesP1, Gruen, 50);
      }
      if (PressesP1 < 124)
      {
        LedTreiber_LedSchalten(PressesP1 - 62, Blau, 50);
      }
      if (PressesP1 < 186)
      {
        LedTreiber_LedSchalten(PressesP1 - 124, Rot, 50);
      }
      PressesP1 ++ ;
    }

    if (TasterHandler_Klick(SpielerZwei, TasterEins))
    {
      if (PressesP2 < 62)
      {
        LedTreiber_LedSchalten(PressesP2 + 62 , Gruen, 50);
      }
      if (PressesP2 > 61 and PressesP2 < 124)
      {
        LedTreiber_LedSchalten(PressesP2, Blau, 50);
      }
      if (PressesP2 > 123)
      {
        LedTreiber_LedSchalten(PressesP2 - 62, Rot, 50);
      }
      PressesP2 ++ ;
    }
    if (!GameOver)
    {
      if ((millis() - lastCountTime) > 1000)
      {
        lastCountTime = millis();
        countdown.CountDown = endCountdownTimeRemaining;
        Messages_ZeigeNachricht(SpielerEins, MSGxx_Endet_in, &countdown);
        Messages_ZeigeNachricht(SpielerZwei, MSGxx_Endet_in, &countdown);
        endCountdownTimeRemaining = endCountdownTimeRemaining - 1;
        if (endCountdownTimeRemaining == 255)
        {
          GameOver = true;
        }
      }
    }
    if (GameOver)
    {
      startMsgShown = false; //reset
      startDoneP1 = false;
      startDoneP2 = false;
      gameBegun = false;
      GameOver = false;
      startCountdownTimeRemaining = startCountdown;
      endCountdownTimeRemaining = gameTime;

      if (PressesP1 == PressesP2) // unentschieden
      {
        PressesP1 = 0; //reset
        PressesP2 = 0;
        MinigameManager_GameEnded(Win_Unentschieden);
      }

      if (PressesP1 > PressesP2) //gewinner herausfinden
      {
        PressesP1 = 0; //reset
        PressesP2 = 0;
        MinigameManager_GameEnded(Win_SpielerEins);
      }

      if (PressesP1 < PressesP2)
      {
        PressesP1 = 0; //reset
        PressesP2 = 0;
        MinigameManager_GameEnded(Win_SpielerZwei);
      }
    }
  }
}
