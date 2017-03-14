#ifndef MESSAGES_H
#define MESSAGES_H

#include "GlobalTypes.h"

typedef enum
{
  Startup,
  NeuesSpiel,
}Messages_Nachrichten_t;

void Messages_ZeigeNachricht(GlobalTypes_Spieler_t );

#endif
