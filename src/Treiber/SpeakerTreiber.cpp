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


void SpeakerTreiber_playTone(uint16_t frequency, uint16_t duration)
{

  //uint8_t FreqByte1 = (frequency >> 8) & 0xFF;
  //uint8_t FreqByte2 = frequency & 0xFF;

  uint8_t DurArray[2];
  DurArray[0] = (duration >> 8) & 0xFF;
  DurArray[1] = duration & 0xFF;

  Wire.beginTransmission(I2CAdressSound); // transmit to device
  //Wire.write(Select_Tone);        // select Tone
  Wire.write(frequency >> 8);
  Wire.write(frequency & 255);
  //Wire.write(DurArray, 2);

  //Wire.write(frequency);
  //Wire.write(duration);
  Wire.endTransmission();    // stop transmitting
}
