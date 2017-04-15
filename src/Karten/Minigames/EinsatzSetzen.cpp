#include "Karten/Minigames/MinigameManager.h"
#include "Messages.h"
#include "Treiber/TasterTreiber.h"
#include "Treiber/LedTreiber.h"

struct Messages_values einsatztWerte;

static bool startDone;
static bool StartMsgShown;

void EinsatzSetzen_Run(void)
{
  if (!startDone)
  {
    if (!StartMsgShown) {
      Messages_ZeigeNachricht(SpielerEins, MSG_Einsatz_waehlen);
      Messages_ZeigeNachricht(SpielerZwei, MSG_Einsatz_waehlen);
      StartMsgShown = true;
    }
    if (TasterTreiber_TasteGedrueckt(SPIELER1_TASTE1))
    {
      LedTreiber_LedSchalten(70,Blau);
      startDone = true;
    }
  }
}
