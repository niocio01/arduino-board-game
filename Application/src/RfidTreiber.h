#ifndef RFIDTREIBER_H
#define RFIDTREIBER_H

#include <inttypes.h>

bool RfidTreiber_Startup(void);
bool RfidTreiber_ReadCard(uint8_t * kartenDaten);


#endif
