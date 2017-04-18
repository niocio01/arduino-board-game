#include "Karten/Minigames/ShowWinner.h"
#include "Messages.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"

Messages_values leer2;

static bool P1Won = false;
static bool P2Won = false;
static bool Unentschieden = false;
static bool ResultMSGShown = false;
static bool ResultBestaetigtP1 = false;
static bool ResultBestaetigtP2 = false;

void ShowWinner_TellResults(MinigameManager_Winner_t gewinner)
{
  switch(gewinner)
  {
    case Win_SpielerEins:
    P1Won = true;
    P2Won = false;
    Unentschieden = false;
    break;

    case Win_SpielerZwei:
    P1Won = false;
    P2Won = true;
    Unentschieden = false;
    break;

    case Win_Unentschieden:
    P1Won = false;
    P2Won = false;
    Unentschieden = true;
  }
}


void ShowWinner_Run(void)
{
  if (P1Won == true)
  {
    if (!ResultMSGShown)
    {
      Messages_ZeigeNachricht(SpielerEins, MSG_Win, &leer2);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Lose, &leer2);
      TasterLed_Setzten(SpielerEins, LedEins, Gruen);
      TasterLed_Setzten(SpielerZwei, LedEins, Gruen);
      ResultMSGShown = true;
    }

    if (!ResultBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        TasterLed_Setzten(SpielerEins, LedEins, Schwarz);
        ResultBestaetigtP1 = true;
      }
    }
    if (!ResultBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        TasterLed_Setzten(SpielerZwei, LedEins, Schwarz);
        ResultBestaetigtP2 = true;
      }
    }
    if (ResultBestaetigtP1 and ResultBestaetigtP2)
    {
      ResultMSGShown = false;
      ResultBestaetigtP1 = false;
      ResultBestaetigtP2 = false;
      MinigameManager_WinnerShown();
    }
  }

  if (P2Won == true)
  {
    if (!ResultMSGShown)
    {
      Messages_ZeigeNachricht(SpielerEins, MSG_Lose, &leer2);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Win, &leer2);
      TasterLed_Setzten(SpielerEins, LedEins, Gruen);
      TasterLed_Setzten(SpielerZwei, LedEins, Gruen);
      ResultMSGShown = true;
    }

    if (!ResultBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        TasterLed_Setzten(SpielerEins, LedEins, Schwarz);
        ResultBestaetigtP1 = true;
      }
    }
    if (!ResultBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        TasterLed_Setzten(SpielerZwei, LedEins, Schwarz);
        ResultBestaetigtP2 = true;
      }
    }
    if (ResultBestaetigtP1 and ResultBestaetigtP2)
    {
      ResultMSGShown = false;
      ResultBestaetigtP1 = false;
      ResultBestaetigtP2 = false;
      MinigameManager_WinnerShown();
    }
  }

  if (Unentschieden == true)
  {
    if (!ResultMSGShown)
    {
      Messages_ZeigeNachricht(SpielerEins, MSG_Tie, &leer2);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Tie, &leer2);
      TasterLed_Setzten(SpielerEins, LedEins, Gruen);
      TasterLed_Setzten(SpielerZwei, LedEins, Gruen);
      ResultMSGShown = true;
    }

    if (!ResultBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        TasterLed_Setzten(SpielerEins, LedEins, Schwarz);
        ResultBestaetigtP1 = true;
      }
    }
    if (!ResultBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        TasterLed_Setzten(SpielerZwei, LedEins, Schwarz);
        ResultBestaetigtP2 = true;
      }
    }
    if (ResultBestaetigtP1 and ResultBestaetigtP2)
    {
      ResultMSGShown = false;
      ResultBestaetigtP1 = false;
      ResultBestaetigtP2 = false;
      MinigameManager_StartNewGame(true);
    }
  }
}
