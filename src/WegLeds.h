#ifndef WEGLEDS_H
#define WEGLEDS_H

#include <inttypes.h>
#include "GlobalTypes.h"



typedef enum
{
  FigurEins,
  FigurZwei
} WegLeds_Figur_t;

/* function: StatusLedSituationSetzen
Stellt die Status Led's auf eine bestimmte spiel situation
1. Param: spieler (SpielerEins,SpielerZwei)
2. Param: Situation (Spielzug,Minigame)
*/
void WegLeds_PosUpdate(GlobalTypes_AktiverSpieler_t aktiverSpieler,
  WegLeds_Figur_t figur, int8_t anzahl);

 void WegLeds_MapAnzeigen(void);

#endif
