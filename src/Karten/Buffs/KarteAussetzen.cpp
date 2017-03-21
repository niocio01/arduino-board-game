#include "Karten/Buffs/KarteAussetzen.h"
#include <inttypes.h>
#include "Treiber/LedTreiber.h"

void KarteAussetzen_BuffAnwenden(void){
LedTreiber_LedSchalten(71,Blau);
}
