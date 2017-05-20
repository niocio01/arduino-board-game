#include "FigurAuswahl.h"
#include "Messages.h"
#include "Treiber/SpielfeldLed.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/TasterLed.h"
#include "Treiber/LedTreiber.h"
#include "PlayerManager.h"
#include "Karten/Minigames/MinigameManager.h"

const uint8_t SpeedZusaezlicheFelder = 2;
Messages_values felder;

Messages_values leer7;
static uint8_t zuFahrendeFelder;
GlobalTypes_Spieler_t spieler;

static bool LooserMsgShown;
static bool AussetzenMSGShown;
static bool ShowFelder;
static bool FigureChosen;

GlobalTypes_Figur_t ChosenFigure;


void FigurAuswahl_ReportResults(GlobalTypes_Spieler_t gewinner, uint8_t einsatz)
{
  spieler = gewinner;
  zuFahrendeFelder = einsatz;
}

void FigurAuswahl_Run(void)
{
  if (!LooserMsgShown)
  {
    LooserMsgShown = true;
    SF_SetSpielfeldOn();
    if (spieler == SpielerEins)
    {
      Messages_ZeigeNachricht(SpielerZwei, MSG_Gegner_WaehltFigur, & leer7);
    }
    else
    {
      Messages_ZeigeNachricht(SpielerEins, MSG_Gegner_WaehltFigur, & leer7);
    }
  }

  if (PlayerManager_IsAussetzenActive(spieler)) // aussetzen
  {
    if (!AussetzenMSGShown)
    {
      AussetzenMSGShown = true;
      Messages_ZeigeNachricht(spieler, MSG_Aussetzen, & leer7);
      TasterLed_Setzen(spieler, LedEins, Gruen);
    }
    if (TasterHandler_Klick(spieler, TasterEins))
    {
      LedTreiber_ControllsBlack();
      PlayerManager_DeActivateAussetzen(spieler);
      MinigameManager_FigurAusgewaehlt();
    }
  }

  else // Nicht Aussetzen
  {
    if (!ShowFelder)
    {
      ShowFelder = true;
      if (PlayerManager_IsSpeedActive(spieler))
      {
        zuFahrendeFelder = zuFahrendeFelder + SpeedZusaezlicheFelder;
        PlayerManager_DeActivateSpeed(spieler);
      }
      if (spieler == SpielerEins)
      {
        TasterLed_Setzen(SpielerEins, LedDrei, Rot); // Figur Eins
        TasterLed_Setzen(SpielerEins, LedVier, Gelb); // Figur Zwei
      }
      else
      {
        TasterLed_Setzen(SpielerZwei, LedDrei, Blau); // Figur Eins
        TasterLed_Setzen(SpielerZwei, LedVier, Gruen); // Figur Zwei
      }
      felder.AnzFelder = zuFahrendeFelder;
      Messages_ZeigeNachricht(spieler, MSGxx_Felder_vorwaerts, &felder);
    }


    if (!FigureChosen) // figur auswählen
    {
      if (TasterHandler_Klick(spieler, TasterDrei))// Figur Eins
      {
        FigureChosen = true;
        ChosenFigure = FigureEins;
        LedTreiber_ControllsBlack();
        SF_MovePlayerFigure(spieler,ChosenFigure,zuFahrendeFelder);
      }
      if (TasterHandler_Klick(spieler, TasterVier))// Figur Zwei
      {
        FigureChosen = true;
        ChosenFigure = FigureZwei;
        LedTreiber_ControllsBlack();
        SF_MovePlayerFigure(spieler,ChosenFigure,zuFahrendeFelder);
      }
    }


    else // Figur ausgewählt
    {
      if (SF_PlayerFigureHasMoved(spieler,ChosenFigure))
      {
        LooserMsgShown = false;
        AussetzenMSGShown = false;
        ShowFelder = false;
        FigureChosen = false;
        MinigameManager_FigurAusgewaehlt();
      }
    }
  }
}
