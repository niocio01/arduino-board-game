#include <Zaehler.h>

static uint8_t zaehlerSpieler1Figur1 = 0;
static uint8_t zaehlerSpieler1Figur2 = 0;
static uint8_t zaehlerSpieler2Figur1 = 0;
static uint8_t zaehlerSpieler2Figur2 = 0;

void Zaehler_Spieler1Figur1Erhoehen(uint8_t wert)
{
  if (((uint16_t)zaehlerSpieler1Figur1 + wert) < 256)
  zaehlerSpieler1Figur1 += wert;
}
else
{
  zaehlerSpieler1Figur1 = 255;
}

void Zaehler_Spieler1Figur2Erhoehen(uint8_t wert)
{
  if (((uint16_t)zaehlerSpieler1Figur1 + wert) < 256)
  zaehlerSpieler1Figur1 += wert;
}
else
{
  zaehlerSpieler1Figur1 = 255;
}
void Zaehler_Spieler2Figur1Erhoehen(uint8_t wert)
{
  if (((uint16_t)zaehlerSpieler1Figur1 + wert) < 256)
  zaehlerSpieler1Figur1 += wert;
}
else
{
  zaehlerSpieler1Figur1 = 255;
}

void Zaehler_Spieler2Figur2Erhoehen(uint8_t wert)
{
  if (((uint16_t)zaehlerSpieler1Figur1 + wert) < 256)
  zaehlerSpieler1Figur1 += wert;
}
else
{
  zaehlerSpieler1Figur1 = 255;
}

void Zaehler_Spieler1Figur1Erniedrigen(uint8_t wert)
{
  if (wert > zaehlerSpieler1Figur1)
  {
    zaehlerSpieler1Figur1 -= wert;
  }
  else
  {
    zaehlerSpieler1Figur1 = 0;
  }
}

void Zaehler_Spieler1Figur2Erniedrigen(uint8_t wert)
{
  if (wert > zaehlerSpieler1Figur1)
  {
    zaehlerSpieler1Figur1 -= wert;
  }
  else
  {
    zaehlerSpieler1Figur1 = 0;
  }
}

void Zaehler_Spieler2Figur1Erniedrigen(uint8_t wert)
{
  if (wert > zaehlerSpieler1Figur1)
  {
    zaehlerSpieler1Figur1 -= wert;
  }
  else
  {
    zaehlerSpieler1Figur1 = 0;
  }
}

void Zaehler_Spieler2Figur2Erniedrigen(uint8_t wert)
{
  if (wert > zaehlerSpieler1Figur1)
  {
    zaehlerSpieler1Figur1 -= wert;
  }
  else
  {
    zaehlerSpieler1Figur1 = 0;
  }
}

uint8_t Zaehler_Spieler1Figur1ZaehlerStandLesen(void)
{
  return (zaehlerSpieler1Figur1);
}

uint8_t Zaehler_Spieler1Figur2ZaehlerStandLesen(void)
{
  return (zaehlerSpieler1Figur2);
}

uint8_t Zaehler_Spieler2Figur1ZaehlerStandLesen(void)
{
  return (zaehlerSpieler2Figur1);
}

uint8_t Zaehler_Spieler2Figur2ZaehlerStandLesen(void)
{
  return (zaehlerSpieler2Figur2);
}

void Zaehler_Spieler1ZaehlerStandLoeschen(void)
{
  zaehlerSpieler1Figur1 = 0;
  zaehlerSpieler1Figur2 = 0;
}

void Zaehler_Spieler2ZaehlerStandLoeschen(void)
{
  zaehlerSpieler2Figur1 = 0;
  zaehlerSpieler2Figur2 = 0;
}
