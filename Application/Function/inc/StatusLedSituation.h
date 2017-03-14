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

void StatusLedSituationSetzten(StatusLedSituation_spieler_t spieler,
StatusLedSituation_Situation_t situation);

#endif
