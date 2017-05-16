#include "FigurAuswahl.h"
#include "Messages.h"
#include "Treiber/SpielfeldLed.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/TasterLed.h"
#include "PlayerManager.h"

const uint8_t SpeedZusaezlicheFelder = 2;

Messages_values leer7;
static uint8_t zuFahrendeFelder;
GlobalTypes_Spieler_t spieler;


void FigurAuswahl_ReportResults(GlobalTypes_Spieler_t gewinner, uint8_t einsatz)
{
  zuFahrendeFelder = einsatz;
  if(PlayerManager_SpielerEinsAmZug())
  {
    spieler = SpielerEins;
  }
  else
  {
    spieler = SpielerZwei;
  }

  if (PlayerManager_IsAussetzenActive(spieler))
  {
  Messages_ZeigeNachricht(spieler, MSG_Aussetzen, & leer7);
  TasterHandler_Klick(spieler, TasterEins);
  TasterLed_Setzen(spieler, LedEins, Gruen);
  PlayerManager_DeActivateAussetzen(spieler);
  }
  else
  {

    if(PlayerManager_IsSpeedActive(spieler))
    {
      zuFahrendeFelder = zuFahrendeFelder + SpeedZusaezlicheFelder;
      PlayerManager_DeActivateSpeed(spieler);

    }
  Messages_ZeigeNachricht(spieler, MSGxx_Felder_vorwaerts, & leer7);

}
}

void FigurAuswahl_Run(void)
{

}
