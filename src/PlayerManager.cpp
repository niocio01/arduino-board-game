#include <inttypes.h>

static bool P1_AmZug;
static bool P1_SchildAktiv;
static bool P1_SpeedAktiv;
static bool P1_AussetzenAktiv;
static bool P1_EinsatztSetzenAktiv;
static bool P1_GewinnGarantiertAktiv;


//static bool P2_AmZug; Wird nicht abgefragt.
static bool P2_SchildAktiv;
static bool P2_SpeedAktiv;
static bool P2_AussetzenAktiv;
static bool P2_EinsatztSetzenAktiv;
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
void PlayerManager_ActivateShield(void)
{
  if (P1_AmZug)
  {
    P1_SchildAktiv = true;
  }
  else
  {
    P2_SchildAktiv = true;
  }
}
void PlayerManager_DeActivateShield(void)
{
  if (P1_AmZug)
  {
    P2_SchildAktiv = false;
  }
  else
  {
    P1_SchildAktiv = false;
  }
}
bool PlayerManager_IsShieldActive(void)
{
  if (P1_AmZug)
  {
    if (P2_SchildAktiv)
    {
      return true;
    }
  }
  else
  {
    if (P1_SchildAktiv)
    {
      return true;
    }
  }
}

// Speed: Alles auf Aktiven Spieler bezogen
void PlayerManager_ActivateSpeed(void)
{
  if (P1_AmZug)
  {
    P1_SpeedAktiv = true;
  }
  else
  {
    P2_SpeedAktiv = true;
  }
}
void PlayerManager_DeActivateSpeed(void)
{
  if (P1_AmZug)
  {
    P1_SpeedAktiv = false;
  }
  else
  {
    P2_SpeedAktiv = false;
  }
}
bool PlayerManager_IsSpeedAcive(void)
{
  if (P1_AmZug)
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
void PlayerManager_ActivateGewinnGarantiert(void)
{
  if (P1_AmZug)
  {
    P1_GewinnGarantiertAktiv = true;
  }
  else
  {
    P2_GewinnGarantiertAktiv = true;
  }
}
void PlayerManager_DeActivateGewinnGarantiert(void)
{
  if (P1_AmZug)
  {
    P1_GewinnGarantiertAktiv = false;
  }
  else
  {
    P2_GewinnGarantiertAktiv = false;
  }
}
bool PlayerManager_IsGewinnGarantiertAcive(void)
{
  if (P1_AmZug)
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
void PlayerManager_ActivateEinsatzSetzen(void)
{
  if (P1_AmZug)
  {
    P1_EinsatztSetzenAktiv = true;
  }
  else
  {
    P2_EinsatztSetzenAktiv = true;
  }
}
void PlayerManager_DeActivateEinsatzSetzen(void)
{
  if (P1_AmZug)
  {
    P1_EinsatztSetzenAktiv = false;
  }
  else
  {
    P2_EinsatztSetzenAktiv = false;
  }
}
bool PlayerManager_IsEinsatzSetzenAcive(void)
{
  if (P1_AmZug)
  {
    if (P1_EinsatztSetzenAktiv)
    {
      return true;
    }
  }
  else
  {
    if (P2_EinsatztSetzenAktiv)
    {
      return true;
    }
  }
}

// Aussetzen: Hier wird auf den Passiven Spieler gesetzt
// Und der Aktive zurückgesetzt.
void PlayerManager_ActivateAussetzen(void)
{
  if (P1_AmZug)
  {
    P2_AussetzenAktiv = true;
  }
  else
  {
    P1_AussetzenAktiv = true;
  }
}
void PlayerManager_DeActivateAussetzen(void)
{
  if (P1_AmZug)
  {
    P1_AussetzenAktiv = false;
  }
  else
  {
    P2_AussetzenAktiv = false;
  }
}
bool PlayerManager_IsAussetzenAcive(void)
{
  if (P1_AmZug)
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
