#include "Karten/Minigames/ShowWinner.h"
#include "Messages.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/LedTreiber.h"

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
      LedTreiber_AllBlack();
      Messages_ZeigeNachricht(SpielerEins, MSG_Win, &leer2);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Lose, &leer2);
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
      ResultMSGShown = true;
      for (uint16_t i = 194; i <= 196; i++) { // Erster Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Gruen, 5);
      }
      for (uint16_t i = 198; i <= 200; i++) {  // Erster Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Rot, 5);
      }
      for (uint16_t i = 202; i <= 206; i++) { // Zweiter Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Gruen, 15);
      }
      for (uint16_t i = 208; i <= 212; i++) {  // Zweiter Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Rot, 15);
      }
      for (uint16_t i = 214; i <= 220; i++) { // Dritter Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Gruen, 40);
      }
      for (uint16_t i = 222; i <= 228; i++) {  // Dritter Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Rot, 40);
      }
      for (uint16_t i = 230; i <= 240; i++) { // Vierter Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Gruen, 80);
      }
      for (uint16_t i = 242; i <= 252; i++) {  // Vierter Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Rot, 80);
      }
      LedTreiber_LedSetzen(192, Blau, 80);
      LedTreiber_LedSetzen(193, Blau, 80);
      LedTreiber_LedSetzen(197, Blau, 80);
      LedTreiber_LedSetzen(201, Blau, 80);
      LedTreiber_LedSetzen(207, Blau, 80);
      LedTreiber_LedSetzen(213, Blau, 80);
      LedTreiber_LedSetzen(221, Blau, 80);
      LedTreiber_LedSetzen(229, Blau, 80);
      LedTreiber_LedSetzen(241, Blau, 80);

      LedTreiber_LedAnzeigen();
    }

    if (!ResultBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        TasterLed_Setzen(SpielerEins, LedEins, Schwarz);
        ResultBestaetigtP1 = true;
      }
    }
    if (!ResultBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
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
      LedTreiber_AllBlack();
      Messages_ZeigeNachricht(SpielerEins, MSG_Lose, &leer2);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Win, &leer2);
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
      ResultMSGShown = true;
      for (uint16_t i = 194; i <= 196; i++) { // Erster Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Rot, 5);
      }
      for (uint16_t i = 198; i <= 200; i++) {  // Erster Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Gruen, 5);
      }
      for (uint16_t i = 202; i <= 206; i++) { // Zweiter Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Rot, 15);
      }
      for (uint16_t i = 208; i <= 212; i++) {  // Zweiter Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Gruen, 15);
      }
      for (uint16_t i = 214; i <= 220; i++) { // Dritter Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Rot, 40);
      }
      for (uint16_t i = 222; i <= 228; i++) {  // Dritter Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Gruen, 40);
      }
      for (uint16_t i = 230; i <= 240; i++) { // Vierter Kreis Seite Spieler 1
        LedTreiber_LedSetzen(i, Rot, 80);
      }
      for (uint16_t i = 242; i <= 252; i++) {  // Vierter Kreis Seite Spieler 2
        LedTreiber_LedSetzen(i, Gruen, 80);
      }
      LedTreiber_LedSetzen(192, Blau, 80);
      LedTreiber_LedSetzen(193, Blau, 80);
      LedTreiber_LedSetzen(197, Blau, 80);
      LedTreiber_LedSetzen(201, Blau, 80);
      LedTreiber_LedSetzen(207, Blau, 80);
      LedTreiber_LedSetzen(213, Blau, 80);
      LedTreiber_LedSetzen(221, Blau, 80);
      LedTreiber_LedSetzen(229, Blau, 80);
      LedTreiber_LedSetzen(241, Blau, 80);
      
      LedTreiber_LedAnzeigen();
    }

    if (!ResultBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        TasterLed_Setzen(SpielerEins, LedEins, Schwarz);
        ResultBestaetigtP1 = true;
      }
    }
    if (!ResultBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
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
      LedTreiber_AllBlack();
      Messages_ZeigeNachricht(SpielerEins, MSG_Tie, &leer2);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Tie, &leer2);
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
      ResultMSGShown = true;
    }

    if (!ResultBestaetigtP1)
    {
      if (TasterHandler_Klick(SpielerEins, TasterEins))
      {
        TasterLed_Setzen(SpielerEins, LedEins, Schwarz);
        ResultBestaetigtP1 = true;
      }
    }
    if (!ResultBestaetigtP2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
        TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
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
