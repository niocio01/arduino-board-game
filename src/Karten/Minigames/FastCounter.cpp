#include "Karten/Minigames/QuickFinger.h"
#include "Treiber/LedTreiber.h"
#include <arduino.h>
#include "Treiber/PotiTreiber.h"
#include "Messages.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "Karten/Minigames/MinigameManager.h"

const uint8_t startCountdown = 3;
const uint8_t NoOfPresses = 30;

static uint8_t PressesP1;
static uint8_t PressesP2;

Messages_values leer8;
Messages_values FC_countdown;
static bool startDoneP1;
static bool startDoneP2;
static bool gameBegun;

uint8_t FC_startCountdownTimeRemaining = startCountdown;
uint8_t FC_endCountdownTimeRemaining = startCountdown;
uint32_t FC_lastCountTime;

uint32_t FinshTime_P1 = 0;
uint32_t FinshTime_P2 = 0;

void FastCounter_RunGame()
{
  if (!gameBegun)
  {
    if ((millis() - FC_lastCountTime) > 1000)
    {
      FC_lastCountTime = millis();
      FC_countdown.CountDown = FC_startCountdownTimeRemaining;
      Messages_ZeigeNachricht(SpielerEins, MSGxx_Start_in, &FC_countdown);
      Messages_ZeigeNachricht(SpielerZwei, MSGxx_Start_in, &FC_countdown);
      FC_startCountdownTimeRemaining = FC_startCountdownTimeRemaining - 1;
      if (FC_startCountdownTimeRemaining == 255)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_20_schnell_druecken, &leer8);
        Messages_ZeigeNachricht(SpielerZwei, MSG_20_schnell_druecken, &leer8);
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
      PressesP1 ++ ;
      if (PressesP1 == NoOfPresses)
      {
        FinshTime_P1 = millis();
      }
    }

    if (TasterHandler_Klick(SpielerZwei, TasterEins))
    {
      PressesP2 ++ ;
      if (PressesP2 == NoOfPresses)
      {
        FinshTime_P2 = millis();
      }
    }

    if (FinshTime_P1  != 0 and FinshTime_P2 != 0)
      {
      startDoneP1 = false; //reset
      startDoneP2 = false;
      gameBegun = false;
      FC_startCountdownTimeRemaining = startCountdown;
      FinshTime_P1 = 0;
      FinshTime_P2 = 0;

      if (PressesP1 == PressesP2)
      {
        if (FinshTime_P1 < FinshTime_P2)
        {
          PressesP1 = 0; //reset
          PressesP2 = 0;
          MinigameManager_GameEnded(Win_SpielerEins);
        }
        else
        {
          PressesP1 = 0; //reset
          PressesP2 = 0;
          MinigameManager_GameEnded(Win_SpielerZwei);
        }
      }

      else if (PressesP1 < PressesP2)
      {
        PressesP1 = 0; //reset
        PressesP2 = 0;
        MinigameManager_GameEnded(Win_SpielerEins);
      }
      else if (PressesP2 < PressesP1)
      {
        PressesP1 = 0; //reset
        PressesP2 = 0;
        MinigameManager_GameEnded(Win_SpielerZwei);
      }
    }
  }
}
