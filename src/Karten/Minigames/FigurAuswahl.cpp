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

static bool PlayerDecided;
static bool AussetzenMSGShown;
static bool ShowFelder;
static bool FigureChosen;

GlobalTypes_Figur_t ChosenFigure;


void FigurAuswahl_ReportResults(GlobalTypes_Spieler_t gewinner, uint8_t einsatz)
{
  zuFahrendeFelder = einsatz;
}

void FigurAuswahl_Run(void)
{
  if (!PlayerDecided)
  {
    SF_SetSpielfeldOn();
    if(PlayerManager_SpielerEinsAmZug())
    {
      spieler = SpielerEins;
      Messages_ZeigeNachricht(SpielerZwei, MSG_Gegner_WaehltFigur, & leer7);
    }
    else
    {
      spieler = SpielerZwei;
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
        TasterLed_Setzen(spieler, LedDrei, Rot); // Figur Eins
        TasterLed_Setzen(spieler, LedVier, Gelb); // Figur Zwei
      }
      else
      {
        TasterLed_Setzen(spieler, LedDrei, Blau); // Figur Eins
        TasterLed_Setzen(spieler, LedVier, Gruen); // Figur Zwei
      }
      felder.AnzFelder = zuFahrendeFelder;
      Messages_ZeigeNachricht(spieler, MSGxx_Felder_vorwaerts, & felder);
    }


    if (!FigureChosen) // figur auswählen
    {
      if (TasterHandler_Klick(spieler, TasterDrei))// Figur Eins
      {
        FigureChosen = true;
        ChosenFigure = FigureEins;
        SF_MovePlayerFigure(spieler,ChosenFigure,zuFahrendeFelder);
      }
      if (TasterHandler_Klick(spieler, TasterVier))// Figur Zwei
      {
        FigureChosen = true;
        ChosenFigure = FigureZwei;
        SF_MovePlayerFigure(spieler,ChosenFigure,zuFahrendeFelder);
      }
    }


    else // Figur ausgewählt
    {
      if (SF_PlayerFigureHasMoved(spieler,ChosenFigure))
      {
        MinigameManager_FigurAusgewaehlt();
      }
    }
  }
}
