
#include "Startup.h"
#include <arduino.h>
#include "RfidTreiber.h"
#include "LedTreiber.h"
#include "inttypes.h"

void setup()
{
  Startup_check();
  Serial.begin(115200);
  Serial.println("Hello!");


}

void loop()
{
  uint8_t kartenDaten = RfidTreiber_ReadCard();
  Serial.print((char)kartenDaten);
  delay(5);
}
