#include "Treiber/TasterLed.h"
#include "Treiber/LedTreiber.h"


void TasterLed_Setzten(GlobalTypes_Spieler_t spieler,
  TasterLed_Nummer_t nummer,
  GlobalTypes_Farbe_t farbe)
  {
    if (spieler == SpielerEins)
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
