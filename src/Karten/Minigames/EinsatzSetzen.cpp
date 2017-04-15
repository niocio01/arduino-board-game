#include "Karten/Minigames/MinigameManager.h"
#include "Messages.h"

struct Messages_values einsatztWerte;
static bool showStartMsg;

void EinsatzSetzen_Run(void)
{
if (showStartMsg) {
  Messages_ZeigeNachricht(SpielerEins, MSGxx_Einsatz_Punkte, einsatztWerte);
  Messages_ZeigeNachricht(SpielerZwei, MSGxx_Einsatz_Punkte);
  showStartMsg = true;
}

}
