#ifndef LCDTRIBER_H
#define LCDTRIBER_H

#include <inttypes.h>

typedef enum
{
  SpielerEins,
  SpielerZwei
} LcdTreiber_Spieler_t;

bool LcdTreiber_Startup(void);

/* function: LcdTreiber_DisplayMessage
Zeigt text auf einem LCD an.
1. Param: spieler (SpielerEins,SpielerZwei)
2. Papam: Nachricht Zeile eins
2. Papam: Nachricht Zeile zwei
*/
void LcdTreiber_DisplayMessage(LcdTreiber_Spieler_t spieler,
char zeileEins[],
char zeileZwei[]);

#endif
