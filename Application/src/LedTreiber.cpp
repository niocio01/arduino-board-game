#include <LedTreiber.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 267


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool LedTreiber_Startup(void)
{
  pixels.begin();
  return (true);
}



void LedTreiber_LedSchalten(uint16_t ledID, GlobalTypes_Farbe_t farbe, uint8_t helligkeit /* = 255 */ )
{

  //strip.setBrightness(150);
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


    default:
      break;
  }
}
