#ifndef LCDTRIBER_H
#define LCDTRIBER_H

#include <inttypes.h>

typedef enum
{
  spielerEins,
  spielerZwei
} LcdTreiber_Spieler_t;

void LcdTreiber_Startup(bool gestartet);

/* function: LcdTreiber_DisplayMessage
Zeigt text auf einem LCD an.

void LcdTreiber_DisplayMessage(LcdTreiber_Spieler_t spieler,
char zeileEins[],
char zeileZwei[]);

#endif
