
#include "Startup.h"
#include <arduino.h>
#include "Treiber/RfidTreiber.h"
#include "Treiber/LedTreiber.h"
#include "inttypes.h"
#include "Karten/KartenManager.h"
#include "Treiber/TasterTreiber.h"


void setup()
{
  Startup_check();
}

void loop()
{
  KartenManager_Main();
  TasterTreiber_Main();
  if (TasterTreiber_TasteGedrueckt(SPIELER2_TASTE1))
  {
    LedTreiber_LedSchalten(100,Rot);
  }
  else
  {
    LedTreiber_LedSchalten(100,Blau);
  }
}
