#include "Karten/Buffs/KarteSpeed.h"
#include <inttypes.h>
#include "Treiber/LedTreiber.h"

void KarteSpeed_BuffAnwenden(void){
LedTreiber_LedSchalten(65,Gruen);
}
