#include "PotiTreiber.h"
#include "arduino.h"
#include <inttypes.h>

const uint8_t Poti1Pin = A0;
const uint8_t Poti2Pin = A1;


bool PotiTreiber_Startup(void)
{
  return true;
}

uint8_t PotiTreiber_Get_Val (GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    int Raw;
    uint8_t out;
    Raw = analogRead(Poti1Pin);      // read the input pin
    out = map(Raw, 0, 1023, 0, 255);
    return out;
  }
  else
  {
    int Raw;
    uint8_t out;
    Raw = analogRead(Poti2Pin);      // read the input pin
    out = map(Raw, 0, 1023, 0, 255);
    return out;
  }
}
