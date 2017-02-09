#include <PotiLed.h>


void PotiLed_Setzten(GlobalLed_Spieler_t Spieler,
  GlobalLed_Farbe_t farbe)
  {
    if (Spieler == eins)
    {
      LedTreiber_LedSchalten(8, farbe);
    }

    else
    {
      LedTreiber_LedSchalten(18, farbe);
    }
  }
