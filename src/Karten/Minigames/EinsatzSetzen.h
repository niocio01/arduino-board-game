#ifndef EINSATSSETZEN
#define  EINSATSSETZEN

#include "GlobalTypes.h"
#include <inttypes.h>

void EinsatzSetzen_MehrEinsatztBuffAnwenden(void);

uint8_t EinsatzSetzen_GetEinsatzDepot(GlobalTypes_Spieler_t spieler);

void EinsatzSetzen_SetEinsatzDepot(GlobalTypes_Spieler_t spieler, uint8_t newEinsatztDepot);

void EinsatzSetzen_Run(void);

#endif
