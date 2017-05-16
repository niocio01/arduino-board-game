#include <Wire.h>

#define I2CAdress 9
#define SPEAKERPIN 2
#define MUTEPIN 3


static bool TonePlaying = false;
static uint32_t ToneStartTime;
static uint32_t ToneDuration;
static uint16_t ToneFreqency;
static bool NewTone = false;


void setup ()
{
  tone(SPEAKERPIN, 440, 200);
  delay(200);
  pinMode(MUTEPIN, OUTPUT);
  digitalWrite(MUTEPIN, LOW);

  pinMode(LED_BUILTIN, OUTPUT); //debug Led
  digitalWrite(LED_BUILTIN, LOW); //RestPin

  Wire.begin(I2CAdress);        // join i2c bus
  Wire.onReceive(receiveEvent); // register event

  pinMode(LED_BUILTIN, OUTPUT); //debug Led
}


void loop()
{
  if (TonePlaying)
  {
    uint32_t currentTime = millis();
    {
      if ((millis() - ToneStartTime) > ToneDuration)
      {
        noTone(SPEAKERPIN);
        digitalWrite(MUTEPIN, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        TonePlaying = false;
      }

      if (NewTone)
      {
        digitalWrite(MUTEPIN, HIGH);
        tone(SPEAKERPIN, ToneFreqency, 0);
        digitalWrite(LED_BUILTIN, HIGH);
        NewTone = false;
      }
    }
  }
}

void receiveEvent(int howMany)
{
  uint16_t frequency;
  uint16_t duration;

  frequency = ((uint16_t)Wire.read()) << 8;      // High Byte
  frequency |= ((uint16_t)Wire.read() & 0x00FF); // Low Byte
  duration = ((uint16_t)Wire.read()) << 8;       // High Byte
  duration |= ((uint16_t)Wire.read() & 0x00FF);  // Low Byte

  tone(SPEAKERPIN, frequency, duration);

  ToneFreqency = frequency;
  ToneDuration = (uint32_t)duration;
  TonePlaying = true;
  ToneStartTime = millis();
  NewTone = true;
}
