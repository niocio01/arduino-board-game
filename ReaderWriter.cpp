
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>


#define PN532_IRQ   (2)
#define PN532_RESET (3)

bool Write = true;
uint8_t myData = 123;

void PrintString(const byte * data);

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Connected to RFID Reader
  Serial.println("Connected");

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.print("Waiting for Card to be ");
  if (Write) {
    Serial.println("Writen !");
  }
  else {
    Serial.println("read");
  }
  Serial.println("");

}
void loop()
{


  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card

    Serial.print("Card ID:  ");
    nfc.PrintHex(uid, uidLength);


    if (uidLength == 4) {

      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
      // Serial.println("Trying to authenticate block 4 with default KEY");
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

      // Start with block 4 (the first block of sector 1) since sector 0
      // contains the manufacturer data and it's probably better just
      // to leave it alone unless you know what you're doing
      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);

      if (success) {
        uint8_t data[16] ;


        if (Write) {


          success = nfc.mifareclassic_WriteDataBlock (4, (uint8_t)myData);
          Serial.println("Information updated");
        }

        success = nfc.mifareclassic_ReadDataBlock(4, data);

        if (success) {

          // Data seems to have been read ... spit it out
          Serial.print("Data:     ");
          PrintString(data);
          Serial.println("");


        }
        else
        {
          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
          Serial.println("");
        }

      }
    }
    // Wait a bit before reading the card again
    delay(1000);
  }
}


void PrintString(const byte * data)
{
  uint32_t szPos = 0;

  while ((data[szPos] != 0) && (szPos < 16))
  {
    Serial.print((char)data[szPos]);
    szPos++;
  }
  Serial.println();
}
