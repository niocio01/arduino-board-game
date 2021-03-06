#ifndef STATUSLED_H
#define STATUSLED_H

#include "GlobalTypes.h"

typedef enum
{
  AmZug_Led,
  RFID_Led,
  Minigame_Led
} StatusLed_Name_t;

typedef enum
{
  Ein,
  Aus
} StatusLed_Zustand_t;


/* function: StatusLed_Setzen
setzen des zustands eines Status Leds.
1. Param: Spieler (spielerEins, spielerZwei)
2. Param: Status Led Name (AmZug, RFID, Minigame)
3. Param: Led Status (Ein, Aus) */
void StatusLed_Setzen(GlobalTypes_Spieler_t spieler,
  StatusLed_Name_t name,
  StatusLed_Zustand_t zustand);

#endif
