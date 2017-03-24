
#include "Startup.h"
#include <arduino.h>
#include "Treiber/RfidTreiber.h"
#include "Treiber/LedTreiber.h"
#include "inttypes.h"
#include "Karten/KartenManager.h"
#include "Treiber/TasterTreiber.h"
#include "StatusLedSituation.h"


void setup()
{
  Startup_check();
}

void loop()
{
  KartenManager_Main();
  TasterTreiber_Main();
  StatusLedSituationSetzten(SpielerEins, Minigame);
}
