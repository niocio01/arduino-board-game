#include "Karten/Minigames/QuickFinger.h"
#include "Treiber/LedTreiber.h"
#include <arduino.h>
#include "Treiber/PotiTreiber.h"
#include "Messages.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "Karten/Minigames/MinigameManager.h"

const uint8_t startCountdown = 5;
const uint8_t gameTime = 10;

static uint8_t PressesP1;
static uint8_t PressesP2;

Messages_values leer;
Messages_values countdown;
static bool startMsgShown;
static bool startDoneP1;
static bool startDoneP2;
static bool gameBegun;

uint8_t startCountdownTimeRemaining = 5;
uint8_t endCountdownTimeRemaining = 10;
uint16_t lastCountTime;

void QuickFinger_RunGame()
{
  if (!startMsgShown)
  {
    Messages_ZeigeNachricht(SpielerZwei, MSG_Schnell_druecken, &leer);
    Messages_ZeigeNachricht(SpielerZwei, MSG_Schnell_druecken, &leer);
    TasterLed_Setzten(SpielerEins, LedEins, Gruen);
    TasterLed_Setzten(SpielerZwei, LedEins, Gruen);
    startMsgShown = true;
  }

  if (!startDoneP1)
  {
    if (TasterHandler_Klick(SpielerEins, TasterEins))
    {
      TasterLed_Setzten(SpielerEins, LedEins, Schwarz);
      startDoneP1 = true;
    }
  }

  if (!startDoneP2)
  {
    if (TasterHandler_Klick(SpielerZwei, TasterEins))
    {
      TasterLed_Setzten(SpielerZwei, LedEins, Schwarz);
      startDoneP2 = true;
    }
  }

  if (startDoneP1 and startDoneP2 and !gameBegun)
  {
    if ((millis() - lastCountTime) > 1000)
    {
      countdown.CountDown = startCountdownTimeRemaining;
      Messages_ZeigeNachricht(SpielerEins, MSGxx_Start_in, &countdown);
      Messages_ZeigeNachricht(SpielerZwei, MSGxx_Start_in, &countdown);
      lastCountTime = millis();
      startCountdownTimeRemaining = startCountdownTimeRemaining - 1;
      if (startCountdownTimeRemaining == 255)
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Schnell_druecken, &leer);
        Messages_ZeigeNachricht(SpielerZwei, MSG_Schnell_druecken, &leer);
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
    if ((millis() - lastCountTime) > 1000)
    {
      countdown.CountDown = endCountdownTimeRemaining;
      Messages_ZeigeNachricht(SpielerEins, MSGxx_Endet_in, &countdown);
      Messages_ZeigeNachricht(SpielerZwei, MSGxx_Endet_in, &countdown);
      lastCountTime = millis();
      endCountdownTimeRemaining = endCountdownTimeRemaining - 1;
      if (endCountdownTimeRemaining == 255)
      {
        startMsgShown = false; //reset
        startDoneP1 = false;
        startDoneP2 = false;
        gameBegun = false;
        startCountdownTimeRemaining = startCountdown;
        endCountdownTimeRemaining = gameTime;

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

        if (PressesP1 == PressesP2) // unentschieden
        {
          PressesP1 = 0; //reset
          PressesP2 = 0;
          MinigameManager_GameEnded(Win_Unentschieden);
          // weil bereits alles andere geresettet wurde, wird das spiel
          // beim nächsten durchlauf automatisch neustarten
          // es wird gespielt bis ein eindeutiger sieger feststeht.
        }
      }
    }
  }
}
