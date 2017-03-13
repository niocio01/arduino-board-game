#ifndef STATUSLED_H
#define STATUSLED_H

#include "GlobalLed.h"

typedef enum
{
  AmZug,
  RFID,
  Minigame
} StatusLed_Name_t;

typedef enum
{
  ledEin,
  ledAus
} StatusLed_Zustand_t;

/* function: StatusLed_Setzen
setzen des zustands eines Status Leds.
1. Param: Spieler (spielerEins, spielerZwei)
2. Param: Status Led Name (AmZug, RFID, Minigame)
3. Param: Led Status (ein, aus) */
void StatusLed_Setzen(GlobalLed_Spieler_t spieler,
  StatusLed_Name_t name,
  StatusLed_Zustand_t zustand);

#endif
