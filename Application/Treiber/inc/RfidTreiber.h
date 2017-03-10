#ifndef RFIDTREIBER_H
#define RFIDTREIBER_H

#include <inttypes.h>

void RfidTreiber_Startup(bool gestartet);
void RfidTreiber_ReadCard(bool karteVorhanden, uint8_t kartenDaten);


#endif
