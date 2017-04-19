#include "Karten/Buffs/BuffManager.h"
#include "PlayerManager.h"

const uint8_t FalleStellen =65;  // hex A
const uint8_t EinsatzSetzen =66; // hex B
const uint8_t Steinschlag =67;
const uint8_t Speed =68;
const uint8_t GewinnGarantiert =69;
const uint8_t Aussetzen =70;
const uint8_t Zeitreise =71;
const uint8_t MehrEinsatz =72;
const uint8_t Lucky =73;
const uint8_t Schild =74;

void BuffManager_BuffAnwenden(uint8_t kartenNrValue){
  if (kartenNrValue == FalleStellen) {
    /* code */
  }
  else if (kartenNrValue == EinsatzSetzen) {
    PlayerManager_ActivateEinsatzSetzen(); // auf Auktiven Spieler
  }
  else if (kartenNrValue == Steinschlag) {
    /* code */
  }
  else if (kartenNrValue == Speed) {
  }
  else if (kartenNrValue == GewinnGarantiert) {
    /* code */
  }
  else if (kartenNrValue == Aussetzen) {
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
