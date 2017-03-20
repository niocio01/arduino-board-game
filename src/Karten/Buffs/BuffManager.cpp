#include "Karten/Buffs/BuffManager.h"
#include "Karten/Buffs/KarteSpeed.h"
#include "Karten/Buffs/KarteAussetzen.h"


const uint8_t Speed =48;
const uint8_t Aussetzen =49;
const uint8_t Schild =50;
const uint8_t MehrEinsatz =51;
const uint8_t Lucky =52;

void BuffManager_BuffAnwenden(uint8_t kartenNrValue){
  if (kartenNrValue == Speed) {
    KarteSpeed_BuffAnwenden();
  }
  else if (kartenNrValue == Aussetzen) {
    KarteAussetzen_BuffAnwenden();
  }
  else if (kartenNrValue == Schild) {
    /* code */
  }
  else if (kartenNrValue == MehrEinsatz) {
    /* code */
  }
  else if (kartenNrValue == Lucky) {
    /* code */
  }
}
