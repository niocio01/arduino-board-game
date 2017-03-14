#include <LedTreiber.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 16

void LedTreiber_Startup(bool gestartet)
{
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  gestartet = true;
}


/* function: LedTreiber_LedSchalten:
setzt den zustand eines neopixels und zeigt diesen an.
1. param: Led ID (1,2,3...)
2. param: Farbe (aus, weiss, rot, grün, blau)*/
void LedTreiber_LedSchalten(uint16_t ledID, GlobalLed_Farbe_t Farbe)
{
  strip.setBrightness(255);
  switch (Farbe)
  {
    case Aus:
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

    default:
      break;
  }
}
