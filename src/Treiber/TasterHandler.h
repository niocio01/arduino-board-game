#ifndef TASTERHANDLER
#define  TASTERHANDLER
#include "globaltypes.h"
typedef enum
{
TasterEins,
TasterZwei,
TasterDrei,
TasterVier
} TasterHandler_Tasten_t;

/* function: TasterHandler_Klick:
prüft, ob ein Taster drückt wurde (Drücken und loslassen).
1. param: Spieler (SpielerEins, SpielerZwei)
2. param: taste (TasterEins, TasterZwei, TasterDrei, TasterVier)
übergibt Bool, ob Taste gerückt wurde, oder nicht.
*/
bool TasterHandler_Klick(GlobalTypes_Spieler_t spieler, TasterHandler_Tasten_t taste);

#endif
