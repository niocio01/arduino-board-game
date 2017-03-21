#include "Treiber/TasterTreiber.h"
#include <arduino.h>
#include "inttypes.h"
#include "Treiber/LedTreiber.h"

const uint8_t P1T1Pin = 47;
const uint8_t P1T2Pin = 49;
const uint8_t P1T3Pin = 51;
const uint8_t P1T4Pin = 53;
const uint8_t P2T1Pin = 46;
const uint8_t P2T2Pin = 48;
const uint8_t P2T3Pin = 50;
const uint8_t P2T4Pin = 52;

const uint32_t debounceDelay = 50;
static uint8_t bufferAktuell;
static uint8_t bufferAlt;
static uint8_t BufferEntprellt;

bool TasterTreiber_Startup()
{
  bool P1T1State = false;
  bool P1T2State = false;
  bool P1T3State = false;
  bool P1T4State = false;
  bool P2T1State = false;
  bool P2T2State = false;
  bool P2T3State = false;
  bool P2T4State = false;

  pinMode(P1T1Pin, INPUT_PULLUP);
  pinMode(P1T2Pin, INPUT_PULLUP);
  pinMode(P1T3Pin, INPUT_PULLUP);
  pinMode(P1T4Pin, INPUT_PULLUP);
  pinMode(P2T1Pin, INPUT_PULLUP);
  pinMode(P2T2Pin, INPUT_PULLUP);
  pinMode(P2T3Pin, INPUT_PULLUP);
  pinMode(P2T4Pin, INPUT_PULLUP);

  P1T1State = digitalRead(P1T1Pin);
  P1T2State = digitalRead(P1T2Pin);
  P1T3State = digitalRead(P1T3Pin);
  P1T4State = digitalRead(P1T4Pin);
  P2T1State = digitalRead(P2T1Pin);
  P2T2State = digitalRead(P2T2Pin);
  P2T3State = digitalRead(P2T3Pin);
  P2T4State = digitalRead(P2T4Pin);

  if (!P1T1State and !P1T2State and !P1T3State and !P1T4State and !P2T1State and !P2T2State and !P2T3State and !P2T4State == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool TasterTreiber_TasteGedrueckt (uint8_t tastenNr)
{
  if (BufferEntprellt & tastenNr)
  {
    return true;
  }
  return false;
}

void TasterTreiber_Main (void)
{
  uint8_t bufferAktuell = 0x00;
  static uint32_t lastDebounceTime;

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (digitalRead(P1T1Pin) == true)
    {
      bufferAktuell |= SPIELER1_TASTE1;
    }
    if (digitalRead(P1T2Pin) == true)
    {
      bufferAktuell |= SPIELER1_TASTE2;
    }
    if (digitalRead(P1T3Pin) == true)
    {
      bufferAktuell |= SPIELER1_TASTE3;
    }
    if (digitalRead(P1T4Pin) == true)
    {
      bufferAktuell |= SPIELER1_TASTE4;
    }
    if (digitalRead(P2T1Pin) == true)
    {
      bufferAktuell |= SPIELER2_TASTE1;
    }
    if (digitalRead(P2T2Pin) == true)
    {
      bufferAktuell |= SPIELER2_TASTE2;
    }
    if (digitalRead(P2T3Pin) == true)
    {
      bufferAktuell |= SPIELER2_TASTE3;
    }
    if (digitalRead(P2T4Pin) == true)
    {
      bufferAktuell |= SPIELER2_TASTE4;
    }

    if (bufferAktuell == bufferAlt)
    {
      BufferEntprellt = bufferAktuell;
    }
    bufferAlt = bufferAktuell;
    lastDebounceTime = millis();
  }
}
