
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

  if(KartenManager_KarteStarten())
  {
    //LedTreiber_LedSchalten(62,Gruen);
  }
  delay(5);
}
