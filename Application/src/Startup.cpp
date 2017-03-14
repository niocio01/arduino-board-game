#include "Startup.h"
#include "LcdTreiber.h"
#include "LedTreiber.h"
#include "Messages.h"
#include "RfidTreiber.h"
#include "inttypes.h"
#include "SpielfeldLed.h"
#include "GlobalTypes.h"


static bool ledGestartet;
static bool lcdGestartet;
static bool rfidGestartet;

void Startup(void)
{
  for (uint16_t i = 0; i < 251; i++)
  {
    LedTreiber_LedSchalten(i, Rot);
  }

  ledGestartet = LedTreiber_Startup();
  lcdGestartet = LcdTreiber_Startup();
  rfidGestartet= RfidTreiber_Startup();

  if (ledGestartet == true and lcdGestartet == true and rfidGestartet == true)
  {

  }
}
