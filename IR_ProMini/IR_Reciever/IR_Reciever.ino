#include <IRLibDecodeBase.h>
#include <IRLib_P01_NEC.h>
#include <IRLibRecv.h>
#include <Wire.h>

static uint8_t IRBuffer;

#define I2CAdress 8
#define IRRecieverPin 2

#define MYPROTOCOL NEC //IR Protocoll

#define IR_BUTTON_CH_DOWN   0xFFA25D
#define IR_BUTTON_CH        0xFF629D
#define IR_BUTTON_CH_UP     0xFFE21D
#define IR_BUTTON_PREV      0xFF22DD
#define IR_BUTTON_NEXT      0xFF02FD
#define IR_BUTTON_PLAY      0xFFC23D
#define IR_BUTTON_VOL_DOWN  0xFFE01F
#define IR_BUTTON_VOL_UP    0xFFA857
#define IR_BUTTON_EQ        0xFF906F
#define IR_BUTTON_0         0xFF6897
#define IR_BUTTON_100       0xFF9867
#define IR_BUTTON_200       0xFFB04F
#define IR_BUTTON_1         0xFF30CF
#define IR_BUTTON_2         0xFF18E7
#define IR_BUTTON_3         0xFF7A85
#define IR_BUTTON_4         0xFF10EF
#define IR_BUTTON_5         0xFF38C7
#define IR_BUTTON_6         0xFF5AA5
#define IR_BUTTON_7         0xFF42BD
#define IR_BUTTON_8         0xFF4AB5
#define IR_BUTTON_9         0xFF52AD

#define PressedButton_None      0
#define PressedButton_CH_DOWN   1
#define PressedButton_CH        2
#define PressedButton_CH_UP     3
#define PressedButton_PREV      4
#define PressedButton_NEXT      5
#define PressedButton_PLAY      6
#define PressedButton_VOL_DOWN  7
#define PressedButton_VOL_UP    8
#define PressedButton_EQ        9
#define PressedButton_0         10
#define PressedButton_100       11
#define PressedButton_200       12
#define PressedButton_1         13
#define PressedButton_2         14
#define PressedButton_3         15
#define PressedButton_4         16
#define PressedButton_5         17
#define PressedButton_6         18
#define PressedButton_7         19
#define PressedButton_8         20
#define PressedButton_9         21

IRdecodeNEC myDecoder; // Now declare an instance of that decoder.
IRrecv myReceiver(IRRecieverPin); //pin number for the receiver


void setup()
{
  myReceiver.enableIRIn(); // Start the receiver

  Wire.begin(I2CAdress);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

  pinMode(LED_BUILTIN, OUTPUT); //debug Led
   Serial.println(F("Ready to receive IR signals"));
}


void requestEvent()
{
  Wire.write(IRBuffer); // respond with curent buffer
  IRBuffer = PressedButton_None;
  digitalWrite(LED_BUILTIN, LOW); // debug Led
}


void loop()
{
    if (myReceiver.getResults())
    {
      digitalWrite(LED_BUILTIN, HIGH); // debug Led
      if(myDecoder.decode())
      {
        switch(myDecoder.value)
        {
          case IR_BUTTON_CH_DOWN:
          IRBuffer = PressedButton_CH_DOWN;
          break;

          case IR_BUTTON_CH:
          IRBuffer = PressedButton_CH;
          break;

          case IR_BUTTON_CH_UP:
          IRBuffer = PressedButton_CH_UP;
          break;

          case IR_BUTTON_PREV:
          IRBuffer = PressedButton_PREV;
          break;

          case IR_BUTTON_NEXT:
          IRBuffer = PressedButton_NEXT;
          break;

          case IR_BUTTON_PLAY:
          IRBuffer = PressedButton_PLAY;
          break;

          case IR_BUTTON_VOL_DOWN:
          IRBuffer = PressedButton_VOL_DOWN;
          break;

          case IR_BUTTON_VOL_UP:
          IRBuffer = PressedButton_VOL_UP;
          break;

          case IR_BUTTON_EQ:
          IRBuffer = PressedButton_EQ;
          break;

          case IR_BUTTON_0:
          IRBuffer = PressedButton_0;
          break;

          case IR_BUTTON_100:
          IRBuffer = PressedButton_100;
          break;

          case IR_BUTTON_200:
          IRBuffer = PressedButton_200;
          break;

          case IR_BUTTON_1:
          IRBuffer = PressedButton_1;
          break;

          case IR_BUTTON_2:
          IRBuffer = PressedButton_2;
          break;

          case IR_BUTTON_3:
          IRBuffer = PressedButton_3;
          break;

          case IR_BUTTON_4:
          IRBuffer = PressedButton_4;
          break;

          case IR_BUTTON_5:
          IRBuffer = PressedButton_5;
          break;

          case IR_BUTTON_6:
          IRBuffer = PressedButton_6;
          break;

          case IR_BUTTON_7:
          IRBuffer = PressedButton_7;
          break;

          case IR_BUTTON_8:
          IRBuffer = PressedButton_8;
          break;

          case IR_BUTTON_9:
          IRBuffer = PressedButton_9;
          break;

        }
      }
      myReceiver.enableIRIn();
    }
  }
