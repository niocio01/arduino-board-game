
#include "Startup.h"
#include <arduino.h>
#include "Treiber/RfidTreiber.h"
#include "Treiber/LedTreiber.h"
#include "inttypes.h"
#include "Karten/KartenManager.h"

void setup()
{
  Startup_check();
  Serial.begin(115200);
  Serial.println("Hello!");


}

void loop()
{
  uint8_t kartenNr;
  if(KartenManager_KarteStarten())
  {
    LedTreiber_LedSchalten(62,Gruen);
    Serial.println(kartenNr);
  }
  delay(5);
}
