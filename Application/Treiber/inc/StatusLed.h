#ifndef STATUSLED_H
#define STATUSLED_H

typedef enum
{
eins,
zwei
} StatusLed_Spieler_t;

typedef enum
{
AmZug,
RFID,
Minigame
} StatusLed_StatusLedName_t;

typedef enum
{
ein,
aus
} StatusLed_LedZustand_t;

/* function: statusLed
setzen des zustands eines Status Leds.
1. Param: Spieler (eins, zwei)
2. Param: Status Led Name (AmZug, RFID, Minigame)
3. Param: Led Status (ein, aus) */
void StatusLed(StatusLed_Spieler_t Spieler,
  StatusLed_StatusLedName_t StatusledName,
  StatusLed_LedZustand_t LedZustand);

#endif
