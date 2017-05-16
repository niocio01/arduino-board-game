#include <Wire.h>

#define I2CAdress 9
#define SPEAKERPIN 2
#define MUTEPIN 3

static uint16_t MinFreq = 120;
static uint16_t MaxFreq = 1500;

const uint8_t Select_Stop = 1;
const uint8_t Select_Tone = 2;

static uint8_t PotiWert = 1;
static uint8_t MelodyNr = 1;

static bool tonePlaying;
static uint32_t TimeStartTone;
static uint32_t duration;
static uint16_t Freqency;
static uint16_t oldFreq;
static bool NewTone;


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
  if (tonePlaying)
  {
    uint32_t currentTime = millis();
    {
      if ((millis() - TimeStartTone) > duration)
      {
        noTone(SPEAKERPIN);
        digitalWrite(MUTEPIN, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        tonePlaying = false;
      }

      if (NewTone)
      {
        digitalWrite(MUTEPIN, HIGH);
        tone(SPEAKERPIN, Freqency, 0);
        digitalWrite(LED_BUILTIN, HIGH);
        NewTone = false;
      }
    }
  }
}

void receiveEvent(int howMany)
{
  uint8_t ModeSelect;
  int frequency;
  uint8_t a, b;
  uint8_t duration2;

  //ModeSelect = Wire.read();
  /*
  if (ModeSelect = Select_Stop)
  {
  noTone(SPEAKERPIN);
  digitalWrite(MUTEPIN, LOW);
}
*/
//  if (ModeSelect = Select_Tone)
{
  //a = Wire.read();
  // b = Wire.read();
  // Freqency = a;
  //frequency = (frequency << 8) bitor b;
  frequency = Wire.read() << 8;
  frequency |= Wire.read();

//  a = Wire.read();
  //b = Wire.read();
  duration = a;
  //duration2 = (duration2 << 8) | b;


  //tone(SPEAKERPIN, frequency, duration2);
  duration = 500;
  tonePlaying = true;
  TimeStartTone = millis();
  NewTone = true;
  }
}
