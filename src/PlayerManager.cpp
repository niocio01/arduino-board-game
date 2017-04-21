#include <inttypes.h>
#include "GlobalTypes.h"

static bool P1_AmZug;
static bool P1_SchildAktiv;
static bool P1_SpeedAktiv;
static bool P1_AussetzenAktiv;
static bool P1_EinsatzSetzenAktiv;
static bool P1_GewinnGarantiertAktiv;


//static bool P2_AmZug; Wird nicht abgefragt.
static bool P2_SchildAktiv;
static bool P2_SpeedAktiv;
static bool P2_AussetzenAktiv;
static bool P2_EinsatzSetzenAktiv;
static bool P2_GewinnGarantiertAktiv;

bool PlayerManager_SpielerEinsAmZug(void)
{
  if (P1_AmZug == true)
  {
    return true;
  }
}

bool PlayerManager_SpielerZweiAmZug(void)
{
  if (P1_AmZug == false)
  {
    return true;
  }
}


// Schild: hier wird der Status des Passiven Spielers ausgegeben.
// Und Vom Passiven Spieler zurückgesetzt.
void PlayerManager_ActivateShield(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_SchildAktiv = true;
  }
  else
  {
    P2_SchildAktiv = true;
  }
}
void PlayerManager_DeActivateShield(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_SchildAktiv = false;
  }
  else
  {
    P2_SchildAktiv = false;
  }
}
bool PlayerManager_IsShieldActive(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    if (P1_SchildAktiv)
    {
      return true;
    }
  }
  else
  {
    if (P2_SchildAktiv)
    {
      return true;
    }
  }
}

// Speed: Alles auf Aktiven Spieler bezogen
void PlayerManager_ActivateSpeed(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_SpeedAktiv = true;
  }
  else
  {
    P2_SpeedAktiv = true;
  }
}
void PlayerManager_DeActivateSpeed(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_SpeedAktiv = false;
  }
  else
  {
    P2_SpeedAktiv = false;
  }
}
bool PlayerManager_IsSpeedActive(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    if (P1_SpeedAktiv)
    {
      return true;
    }
  }
  else
  {
    if (P2_SpeedAktiv)
    {
      return true;
    }
  }
}

// Gewinn garantiert: Alles auf Aktiven Spieler bezogen
void PlayerManager_ActivateGewinnGarantiert(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_GewinnGarantiertAktiv = true;
  }
  else
  {
    P2_GewinnGarantiertAktiv = true;
  }
}
void PlayerManager_DeActivateGewinnGarantiert(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_GewinnGarantiertAktiv = false;
  }
  else
  {
    P2_GewinnGarantiertAktiv = false;
  }
}
bool PlayerManager_IsGewinnGarantiertActive(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    if (P1_GewinnGarantiertAktiv)
    {
      return true;
    }
  }
  else
  {
    if (P2_GewinnGarantiertAktiv)
    {
      return true;
    }
  }
}

// Einsatz setzen: Alles auf Aktiven Spieler bezogen
void PlayerManager_ActivateEinsatzSetzen(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_EinsatzSetzenAktiv = true;
  }
  else
  {
    P2_EinsatzSetzenAktiv = true;
  }
}
void PlayerManager_DeActivateEinsatzSetzen(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_EinsatzSetzenAktiv = false;
  }
  else
  {
    P2_EinsatzSetzenAktiv = false;
  }
}
bool PlayerManager_IsEinsatzSetzenActive(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    if (P1_EinsatzSetzenAktiv)
    {
      return true;
    }
  }
  else
  {
    if (P2_EinsatzSetzenAktiv)
    {
      return true;
    }
  }
}

// Aussetzen: Hier wird auf den Passiven Spieler gesetzt
// Und der Aktive zurückgesetzt.
void PlayerManager_ActivateAussetzen(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P2_AussetzenAktiv = true;
  }
  else
  {
    P1_AussetzenAktiv = true;
  }
}
void PlayerManager_DeActivateAussetzen(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    P1_AussetzenAktiv = false;
  }
  else
  {
    P2_AussetzenAktiv = false;
  }
}
bool PlayerManager_IsAussetzenActive(GlobalTypes_Spieler_t spieler)
{
  if (spieler == SpielerEins)
  {
    if (P1_AussetzenAktiv)
    {
      return true;
    }
  }
  else
  {
    if (P2_AussetzenAktiv)
    {
      return true;
    }
  }
}
