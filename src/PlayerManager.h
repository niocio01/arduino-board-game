#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "globaltypes.h"


bool PlayerManager_SpielerEinsAmZug(void);
bool PlayerManager_SpielerZweiAmZug(void);

/*
Diese Funktionen Managen die Buffs, die auf einen
Spieler gesetzt werden können.
Die funkionen sprchen jeweils den Aktiven Spieler an.

Die Buffs werden jeweils auf den jeweiligen Spieler (aktiv/passiv)
gesetzt oder zurückgesetzt, dass es vom Spielfluss her sinn macht.
Siehe .cpp für nähere details dazu.

Es Gibt Drei Funktion:
Eine zum Setzen
Eine Zum Deaktivieren
Und Eine zum anbfragen des Statuses eines Buffs
*/


void PlayerManager_ActivateShield(GlobalTypes_Spieler_t spieler);
void PlayerManager_DeActivateShield(GlobalTypes_Spieler_t spieler);
bool PlayerManager_IsShieldActive(GlobalTypes_Spieler_t spieler);

void PlayerManager_ActivateSpeed(GlobalTypes_Spieler_t spieler);
void PlayerManager_DeActivateSpeed(GlobalTypes_Spieler_t spieler);
bool PlayerManager_IsSpeedActive(GlobalTypes_Spieler_t spieler);

void PlayerManager_ActivateAussetzen(GlobalTypes_Spieler_t spieler);
void PlayerManager_DeActivateAussetzen(GlobalTypes_Spieler_t spieler);
bool PlayerManager_IsAussetzenActive(GlobalTypes_Spieler_t spieler);

void PlayerManager_ActivateEinsatzSetzen(GlobalTypes_Spieler_t spieler);
void PlayerManager_DeActivateEinsatzSetzen(GlobalTypes_Spieler_t spieler);
bool PlayerManager_IsEinsatzSetzenActive(GlobalTypes_Spieler_t spieler);

void PlayerManager_ActivateGewinnGarantiert(GlobalTypes_Spieler_t spieler);
void PlayerManager_DeActivateGewinnGarantiert(GlobalTypes_Spieler_t spieler);
bool PlayerManager_IsGewinnGarantiertActive(GlobalTypes_Spieler_t spieler);

#endif
