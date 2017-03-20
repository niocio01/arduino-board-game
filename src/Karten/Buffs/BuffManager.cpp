#include "Karten/Buffs/BuffManager.h"
#include "Karten/Buffs/KarteSpeed.h"
#include "Karten/Buffs/KarteAussetzen.h"


const uint8_t FalleStellen =48;  // hex 0
const uint8_t EinsatzSetzen =49; // hex 1
const uint8_t Steinschlag =50;
const uint8_t Speed =51;
const uint8_t GewinnGarantiert =52;
const uint8_t Aussetzen =53;
const uint8_t Zeitreise =54;
const uint8_t MehrEinsatz =55;
const uint8_t Lucky =56;
const uint8_t Schild =57;

void BuffManager_BuffAnwenden(uint8_t kartenNrValue){
  if (kartenNrValue == FalleStellen) {
    /* code */
  }
  else if (kartenNrValue == EinsatzSetzen) {
    /* code */
  }
  else if (kartenNrValue == Steinschlag) {
    /* code */
  }
  else if (kartenNrValue == Speed) {
    KarteSpeed_BuffAnwenden();
  }
  else if (kartenNrValue == GewinnGarantiert) {
    /* code */
  }
  else if (kartenNrValue == Aussetzen) {
    KarteAussetzen_BuffAnwenden();
  }
  else if (kartenNrValue == Zeitreise) {
    /* code */
  }
  else if (kartenNrValue == MehrEinsatz) {
    /* code */
  }
  else if (kartenNrValue == Lucky) {
    /* code */
  }
  else if (kartenNrValue == Schild) {
    /* code */
  }
}
