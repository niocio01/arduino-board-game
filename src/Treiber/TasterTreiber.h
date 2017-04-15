#include <inttypes.h>
#include "globaltypes.h"

#define SPIELER1_TASTE1 (0X01)
#define SPIELER1_TASTE2 (0X02)
#define SPIELER1_TASTE3 (0X04)
#define SPIELER1_TASTE4 (0X08)
#define SPIELER2_TASTE1 (0X10)
#define SPIELER2_TASTE2 (0X20)
#define SPIELER2_TASTE3 (0X40)
#define SPIELER2_TASTE4 (0X80)

bool TasterTreiber_Startup();

bool TasterTreiber_TasteGedrueckt (uint8_t tastenNr);

void TasterTreiber_Main (void);
