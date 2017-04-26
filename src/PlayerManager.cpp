#include <inttypes.h>
#include "GlobalTypes.h"

static bool P1_AmZug = false;
static bool P1_SchildAktiv = false;
static bool P1_SpeedAktiv = false;
static bool P1_AussetzenAktiv = false;
static bool P1_EinsatzSetzenAktiv = false;
static bool P1_GewinnGarantiertAktiv = false;


//static bool P2_AmZug; Wird nicht abgefragt.
static bool P2_SchildAktiv = false;
static bool P2_SpeedAktiv = false;
static bool P2_AussetzenAktiv = false;
static bool P2_EinsatzSetzenAktiv = false;
static bool P2_GewinnGarantiertAktiv = false;

bool PlayerManager_SpielerEinsAmZug(void)
{
  if (P1_AmZug == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool PlayerManager_SpielerZweiAmZug(void)
{
  if (P1_AmZug == false)
  {
    return true;
  }
  else
  {
    return false;
  }
}



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
    else
    {
      return false;
    }
  }
  else
  {
    if (P2_SchildAktiv)
    {
      return true;
    }
    else
    {
      return false;
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
    else
    {
      return false;
    }
  }
  else
  {
    if (P2_SpeedAktiv)
    {
      return true;
    }
    else
    {
      return false;
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
    else
    {
      return false;
    }
  }
  else
  {
    if (P2_GewinnGarantiertAktiv)
    {
      return true;
    }
    else
    {
      return false;
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
    else
    {
      return false;
    }
  }
  else if (spieler == SpielerZwei)
  {
    if (P2_EinsatzSetzenAktiv)
    {
      return true;
    }
    else
    {
      return false;
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
    else
    {
      return false;
    }
  }
  else
  {
    if (P2_AussetzenAktiv)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}
