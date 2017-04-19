#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "globaltypes.h"


/*
Diese Funktionen Managen die Buffs, die auf einen
Spieler gesetzt werden können.
Die funkionen sprchen jeweils den Aktiven Spieler an.

Die Buffs werden jeweils auf den jeweiligen Spieler (aktiv/passiv)
gesetzt oder zurückgesetzt, dass es vom Spielfluss her sinn macht.
Siehe .cpp für nähere details dazu.

Es Gibt Drei Funktion:
Eine zum Setzten
Eine Zum Deaktivieren
Und Eine zum anbfragen des Statuses eines Buffs
*/


void PlayerManager_ActivateShield(void);
void PlayerManager_DeActivateShield(void);
bool PlayerManager_IsShieldActive(void);

void PlayerManager_ActivateSpeed(void);
void PlayerManager_DeActivateSpeed(void);
bool PlayerManager_IsSpeedAcive(void);

void PlayerManager_ActivateAussetzen(void);
void PlayerManager_DeActivateAussetzen(void);
bool PlayerManager_IsAussetzenAcive(void);

void PlayerManager_ActivateEinsatzSetzen(void);
void PlayerManager_DeActivateEinsatzSetzen(void);
bool PlayerManager_IsEinsatzSetzenAcive(void);

void PlayerManager_ActivateGewinnGarantiert(void);
void PlayerManager_DeActivateGewinnGarantiert(void);
bool PlayerManager_IsGewinnGarantiertAcive(void);

#endif
