#include <LedTreiber.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 267

bool LedTreiber_Startup(void)
{
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  return (true);
}


/* function: LedTreiber_LedSchalten:
setzt den zustand eines neopixels und zeigt diesen an.
1. param: Led ID (1,2,3...)
2. param: Farbe (aus, weiss, rot, grün, blau)*/
void LedTreiber_LedSchalten(uint16_t ledID, GlobalTypes_Farbe_t farbe)
{

  strip.setBrightness(150);
  switch (farbe)
  {
    case Schwarz:
      pixels.setPixelColor(ledID, 0, 0, 0);
      pixels.show();
      break;

    case Weiss:
      pixels.setPixelColor(ledID, 255, 255, 255);
      pixels.show();
      break;

    case Rot:
      pixels.setPixelColor(ledID, 255, 0, 0);
      pixels.show();
      break;

    case Gruen:
      pixels.setPixelColor(ledID, 0, 255, 0);
      pixels.show();
      break;

    case Blau:
      pixels.setPixelColor(ledID, 0, 0, 255);
      pixels.show();
      break;

    case Gelb:
      pixels.setPixelColor(ledID, 255, 255, 0);
      pixels.show();
      break;

    case Violett:
      pixels.setPixelColor(ledID, 255, 0, 255);
      pixels.show();
      break;


    default:
      break;
  }
}
