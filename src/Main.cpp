
#include "Startup.h"
#include <arduino.h>
#include "RfidTreiber.h"
#include "LedTreiber.h"
#include "inttypes.h"
#include "KartenManager.h"

void setup()
{
  Startup_check();
  Serial.begin(115200);
  Serial.println("Hello!");


}

void loop()
{
  uint8_t kartenNr;
  if(KartenManager_KarteStarten(&kartenNr))
  {
    LedTreiber_LedSchalten(62,Gruen);
    Serial.println((char)kartenNr);
  }
  delay(5);
}
