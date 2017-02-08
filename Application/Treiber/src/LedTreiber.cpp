#include <LedTreiber_local.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 16


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
pixels.begin();




void LedTreiber_LedSchalten(uint8_t ledID, LedTreiber_LedFarbe_t ledFarbe)
{
  strip.setBrightness(255);
  switch (ledFarbe)
  {
    case aus:
      pixels.setPixelColor(ledID, 0, 0, 0);
      pixels.show();
      break;

    case weiss:
      pixels.setPixelColor(ledID, 255, 255, 255);
      pixels.show();
      break;

    case rot:
      pixels.setPixelColor(ledID, 255, 0, 0);
      pixels.show();
      break;

    case grün:
      pixels.setPixelColor(ledID, 0, 255, 0);
      pixels.show();
      break;

    case blau:
      pixels.setPixelColor(ledID, 0, 0, 255);
      pixels.show();
      break;

    default:
      break;
  }
}
