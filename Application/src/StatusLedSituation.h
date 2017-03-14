#ifndef STATUSLEDSITUATION
#define STATUSLEDSITUATION

typedef enum
{
  SpielerEins,
  SpielerZwei
} StatusLedSituation_spieler_t;

typedef enum
{
  Spielzug,
  Minigame
} StatusLedSituation_Situation_t;

/* function: StatusLedSituationSetzten
Stellt die Status Led's auf eine bestimmte spiel situation
1. Param: spieler (SpielerEins,SpielerZwei)
2. Param: Situation (Spielzug,Minigame)
*/
void StatusLedSituationSetzten(StatusLedSituation_spieler_t spieler,
StatusLedSituation_Situation_t situation);

#endif
