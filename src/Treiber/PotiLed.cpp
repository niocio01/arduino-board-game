#include "Treiber/PotiLed.h"
#include "Treiber/LedTreiber.h"


void PotiLed_Setzten(GlobalTypes_Spieler_t spieler,
  GlobalTypes_Farbe_t farbe)
  {
    if (spieler == SpielerEins)
    {
      LedTreiber_LedSchalten(256, farbe);
    }

    else
    {
      LedTreiber_LedSchalten(264, farbe);
    }
  }
