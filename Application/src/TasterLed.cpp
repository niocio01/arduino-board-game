#include <TasterLed.h>


void TasterLed_Setzten(GlobalLed_Spieler_t Spieler,
  TasterLed_Nummer_t nummer,
  GlobalLed_Farbe_t farbe)
  {
    if (Spieler == eins)
    {
      switch(nummer)
      {
        case LedEins:
          LedTreiber_LedSchalten(4, farbe);
          break;

        case LedZwei:
          LedTreiber_LedSchalten(5, farbe);
          break;

        case LedDrei:
          LedTreiber_LedSchalten(6, farbe);
          break;

        case LedVier:
          LedTreiber_LedSchalten(7, farbe);
          break;

      }
    }
    else
    {
      switch(nummer)
      {
        case LedEins:
          LedTreiber_LedSchalten(14, farbe);
          break;

        case LedZwei:
          LedTreiber_LedSchalten(15, farbe);
          break;

        case LedDrei:
          LedTreiber_LedSchalten(16, farbe);
          break;

        case LedVier:
          LedTreiber_LedSchalten(17, farbe);
          break;

      }
    }
  }
