
#include "Startup.h"
#include <arduino.h>
#include "Treiber/RfidTreiber.h"
#include "Treiber/LedTreiber.h"
#include "inttypes.h"
#include "Karten/KartenManager.h"
#include "Treiber/TasterTreiber.h"
#include "StatusLedSituation.h"
#include "Treiber/TasterLed.h"
#include "Treiber/PotiLed.h"
#include "Karten/Minigames/MinigameManager.h"


void setup()
{
  Startup_check();
}

void loop()
{
  TasterTreiber_Main();
  KartenManager_Main();
  MinigameManager_Main();
  //LedTreiber_LedSchalten(70,Schwarz);
}
