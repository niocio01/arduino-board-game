#include <Treiber/RfidTreiber.h>
#include "Adafruit_PN532.h"
#include <Wire.h>
#include <SPI.h>
#include "Treiber/LedTreiber.h"
#include "arduino.h"

#define PN532_IRQ   (3)
#define PN532_RESET (2)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

static bool rfidGestartet = false;
bool RfidTreiber_Startup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata)
  {
    return (false);
  }
  else
  {
    // Set the max number of retry attempts to read from a card
      // This prevents us from waiting forever for a card, which is
      // the default behaviour of the PN532.
    nfc.setPassiveActivationRetries(0x01);
    // configure board to read RFID tags
    nfc.SAMConfig();
    return (true);
  }
}

bool RfidTreiber_ReadCard(uint8_t* kartenDaten)
{
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success)
  {
    uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // set Key
    success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya); //authenticate using Key
    success = nfc.mifareclassic_ReadDataBlock(4, kartenDaten); // Karte lesen
    Serial.println(*kartenDaten);
  }
  return success;
  }
