#ifndef MESSAGES_H
#define MESSAGES_H

#include "Treiber/GlobalTypes.h"

typedef enum
{
  Startup_OK,
  Startup_RFID_Fail
}Messages_Nachrichten_t;

void Messages_ZeigeNachricht(GlobalTypes_Spieler_t spieler,
  Messages_Nachrichten_t nachricht);

#endif
