#include <Treiber/LedTreiber.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4
#define NUMPIXELS 269


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool LedTreiber_Startup(void)
{
  pixels.begin();
  for (uint16_t i = 0; i <= NUMPIXELS ; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.show();
  return true;
}

void LedTreiber_LedAnzeigen(void)
{
  pixels.show();
}

void LedTreiber_MapBlack(void)
{
  for (uint16_t i = 0; i <= 252; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
  }
}

void LedTreiber_AllBlack(void)
{
  for (uint16_t i = 0; i <= 252; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.setPixelColor(256, 0, 0, 0); // Poti P1
  pixels.setPixelColor(257, 0, 0, 0); // Taster 1 P1
  pixels.setPixelColor(258, 0, 0, 0); // Taster 2 P1
  pixels.setPixelColor(259, 0, 0, 0); // Taster 3 P1
  pixels.setPixelColor(260, 0, 0, 0); // Taster 4 P1

  pixels.setPixelColor(264, 0, 0, 0); // Poti P2
  pixels.setPixelColor(265, 0, 0, 0); // Taster 1 P2
  pixels.setPixelColor(266, 0, 0, 0); // Taster 2 P2
  pixels.setPixelColor(267, 0, 0, 0); // Taster 3 P2
  pixels.setPixelColor(268, 0, 0, 0); // Taster 4 P2

  pixels.show();
}

void LedTreiber_ControllsBlack(void)
{
  pixels.setPixelColor(256, 0, 0, 0); // Poti P1
  pixels.setPixelColor(257, 0, 0, 0); // Taster 1 P1
  pixels.setPixelColor(258, 0, 0, 0); // Taster 2 P1
  pixels.setPixelColor(259, 0, 0, 0); // Taster 3 P1
  pixels.setPixelColor(260, 0, 0, 0); // Taster 4 P1

  pixels.setPixelColor(264, 0, 0, 0); // Poti P2
  pixels.setPixelColor(265, 0, 0, 0); // Taster 1 P2
  pixels.setPixelColor(266, 0, 0, 0); // Taster 2 P2
  pixels.setPixelColor(267, 0, 0, 0); // Taster 3 P2
  pixels.setPixelColor(268, 0, 0, 0); // Taster 4 P2

  pixels.show();
}

void LedTreiber_LedSchalten(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit)
{
  switch (farbe)
  {
    case Schwarz:
    pixels.setPixelColor(ledID, 0, 0, 0);
    pixels.show();
    break;

    case Weiss:
    pixels.setPixelColor(ledID, helligkeit, helligkeit, helligkeit);
    pixels.show();
    break;

    case Rot:
    pixels.setPixelColor(ledID, helligkeit, 0, 0);
    pixels.show();
    break;

    case Gruen:
    pixels.setPixelColor(ledID, 0, helligkeit, 0);
    pixels.show();
    break;

    case Blau:
    pixels.setPixelColor(ledID, 0, 0, helligkeit);
    pixels.show();
    break;

    case Gelb:
    pixels.setPixelColor(ledID, helligkeit, helligkeit, 0);
    pixels.show();
    break;

    case Violett:
    pixels.setPixelColor(ledID, helligkeit, 0, helligkeit);
    pixels.show();
    break;
  }
}

void LedTreiber_LedSetzen(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit)
{
  switch (farbe)
  {
    case Schwarz:
    pixels.setPixelColor(ledID, 0, 0, 0);
    break;

    case Weiss:
    pixels.setPixelColor(ledID, helligkeit, helligkeit, helligkeit);
    break;

    case Rot:
    pixels.setPixelColor(ledID, helligkeit, 0, 0);
    break;

    case Gruen:
    pixels.setPixelColor(ledID, 0, helligkeit, 0);
    break;

    case Blau:
    pixels.setPixelColor(ledID, 0, 0, helligkeit);
    break;

    case Gelb:
    pixels.setPixelColor(ledID, helligkeit, helligkeit, 0);
    break;

    case Violett:
    pixels.setPixelColor(ledID, helligkeit, 0, helligkeit);
    break;
  }
}
