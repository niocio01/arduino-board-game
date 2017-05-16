#include <Wire.h>
#include "Treiber/SpeakerTreiber.h"
#include "Treiber/LedTreiber.h"
#include "inttypes.h"

#define I2CAdressSound 9

const uint8_t Select_Stop = 1;
const uint8_t Select_Tone = 2;

bool SpeakerTreiber_Startup(void)
{
Wire.begin();        // join i2c bus (address optional for master)
return true;
}


void SpeakerTreiber_PlayTone(uint16_t frequency, uint16_t duration)
{
  uint8_t tuneArray[4];

  tuneArray[0] = (uint8_t)((frequency >> 8) & 0x00FF); // High Byte
  tuneArray[1] = (uint8_t)(frequency & 0x00FF);        // Low Byte
  tuneArray[2] = (uint8_t)((duration >> 8) & 0x00FF);  // High Byte
  tuneArray[3] = (uint8_t)(duration & 0x00FF);         // Low Byte

  Wire.beginTransmission(I2CAdressSound); // transmit to sound-device
  Wire.write(tuneArray, 4);               // transmit 4 Bytes (Index 0...3)
  Wire.endTransmission();                 // stop transmitting
}
