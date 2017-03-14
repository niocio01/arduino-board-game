#ifndef WEGLEDS_H
#define WEGLEDS_H

#include <inttypes.h>

typedef enum
{
  SpielerEins,
  SpielerZwei
} WegLed_spieler_t;

typedef enum
{
  Hauptweg,
  Verlaengerung1,
  Verlaengerung2,
  Verlaengerung3
} WegLed_abschnitt_t;

/* function: StatusLedSituationSetzten
Stellt die Status Led's auf eine bestimmte spiel situation
1. Param: spieler (SpielerEins,SpielerZwei)
2. Param: Situation (Spielzug,Minigame)
*/
void WegLed_LedSetzen(WegLed_spieler_t spieler,
WegLed_abschnitt_t abschnitt,
uint8_t nummer);

#endif
