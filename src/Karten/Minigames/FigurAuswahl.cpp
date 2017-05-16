#include "FigurAuswahl.h"
#include "Messages.h"
#include "Treiber/SpielfeldLed.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/TasterLed.h"
#include "PlayerManager.h"

MessageValues leer6;
static uint8_t zuFahrendeFelder;
GlobalTypes_Spieler_t spieler;


void FigurAuswahl_TellResults(GlobalTypes_Spieler_t gewinner, uint8_t einsatz)
{
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
    Messages_ZeigeNachricht(spieler, MSG_Aussetzen, leer6);
  }
}

void FigurAuswahl_Run(void)
{

}
