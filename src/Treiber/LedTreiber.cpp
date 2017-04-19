#include <Treiber/LedTreiber.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4
#define NUMPIXELS 268


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool LedTreiber_Startup(void)
{
  pixels.begin();
  for (uint16_t i = 0; i < NUMPIXELS + 1 ; i++)
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

void LedTreiber_AllBlack(void)
{
  for (uint16_t i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.show();
}

void LedTreiber_LedSchalten(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit /* = 255 */ )
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

void LedTreiber_LedSetzen(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit /* = 255 */ )
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
