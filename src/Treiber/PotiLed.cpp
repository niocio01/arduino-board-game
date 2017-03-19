#include <PotiLed.h>
#include "Treiber/LedTreiber.h"


void PotiLed_Setzten(GlobalTypes_Spieler_t spieler,
  GlobalTypes_Farbe_t farbe)
  {
    if (spieler == SpielerEins)
    {
      LedTreiber_LedSchalten(8, farbe);
    }

    else
    {
      LedTreiber_LedSchalten(18, farbe);
    }
  }
