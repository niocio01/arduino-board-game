#ifndef STATUSLEDSITUATION
#define STATUSLEDSITUATION

#include "GlobalTypes.h"

typedef enum
{
  Spielzug,
  Minigame,
  Buff
} StatusLedSituation_Situation_t;

/* function: StatusLedSituationSetzen
Stellt die Status Led's auf eine bestimmte spiel situation
1. Param: spieler (SpielerEins,SpielerZwei)
2. Param: Situation (Spielzug,Minigame)
*/
void StatusLedSituationSetzen(GlobalTypes_Spieler_t spieler,
StatusLedSituation_Situation_t situation);

#endif
