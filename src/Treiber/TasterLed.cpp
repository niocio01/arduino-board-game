#include "Treiber/TasterLed.h"
#include "Treiber/LedTreiber.h"


void TasterLed_Setzen(GlobalTypes_Spieler_t spieler,
  TasterLed_Nummer_t nummer,
  GlobalTypes_Farbe_t farbe)
  {
    if (spieler == SpielerEins)
    {
      switch(nummer)
      {
        case LedEins:
          LedTreiber_LedSchalten(257, farbe);
          break;

        case LedZwei:
          LedTreiber_LedSchalten(258, farbe);
          break;

        case LedDrei:
          LedTreiber_LedSchalten(259, farbe);
          break;

        case LedVier:
          LedTreiber_LedSchalten(260, farbe);
          break;

      }
    }
    else
    {
      switch(nummer)
      {
        case LedEins:
          LedTreiber_LedSchalten(265, farbe);
          break;

        case LedZwei:
          LedTreiber_LedSchalten(266, farbe);
          break;

        case LedDrei:
          LedTreiber_LedSchalten(267, farbe);
          break;

        case LedVier:
          LedTreiber_LedSchalten(268, farbe);
          break;

      }
    }
  }
