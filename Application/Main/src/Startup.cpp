#include "Startup.h"
#include "LcdTreiber.h"

LedTreiber_Startup(bool ledGestartet);
LcdTreiber_Startup(bool lcdGestartet);
RfidRfidTreiber_Startup(bool rfidGestartet);

if (ledGestartet == true and lcdGestartet == true and rfidGestartet == true)
{
  LcdTreiber_DisplayMessage(LcdTreiber_Spieler_t SpielerEins,
      char zeileEins[] = "alles gestartet",);
  LcdTreiber_DisplayMessage(LcdTreiber_Spieler_t SpielerZwei,
      char zeileEins[] = "alles gestartet",);
}
