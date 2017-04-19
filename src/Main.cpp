
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
#include "Treiber/IRTreiber.h"
#include "Treiber/PotiTreiber.h"
#include "Treiber/SpielfeldLed.h"


void setup()
{
  Startup_check();
}

void loop()
{
  TasterTreiber_Main();
  KartenManager_Main();
  IRTreiber_Main();
  SF_OperateSpielfeld_Main();
  //LedTreiber_LedSchalten(72, Weiss, PotiTreiber_Get_Val(SpielerZwei));
}
