#include "Karten/Buffs/AktiveBuffsAnzeigen.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/TasterLed.h"
#include "Treiber/PotiLed.h"
#include "Treiber/PotiTreiber.h"
#include <arduino.h>
#include "PlayerManager.h"
#include <inttypes.h>
#include "Messages.h"

Messages_values leer5;

static bool SchildAktiv_P1;
static bool SpeedAktiv_P1;
static bool GewinnGarantiertAktiv_P1;
static bool EinsatzSetzenAktiv_P1;
static bool AussetzenAktiv_P1;

static bool SchildAktiv_P2;
static bool SpeedAktiv_P2;
static bool GewinnGarantiertAktiv_P2;
static bool EinsatzSetzenAktiv_P2;
static bool AussetzenAktiv_P2;

static bool MSGShown;
static bool MSGBestaetigt_P1;
static bool MSGBestaetigt_P2;
static bool BuffsBestaetigt_P1;
static bool BuffsBestaetigt_P2;
static bool BuffanzeigeFertig = true;

uint8_t aktuelleAuswahl_P1;
uint8_t aktuelleAuswahl_P2;


bool AktiveBuffsAnzeigen_fertig(void)
{
  if (BuffanzeigeFertig == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void AktiveBuffsAnzeigen_Run(void)
{
  if (!MSGShown)
  {
    BuffanzeigeFertig = false;
    MSGShown = true;
    Messages_ZeigeNachricht(SpielerEins, MSG_AktiveBuffsAnzeigen, &leer5);
    Messages_ZeigeNachricht(SpielerZwei, MSG_AktiveBuffsAnzeigen, &leer5);
    TasterLed_Setzen(SpielerEins, LedEins, Gruen);
    TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
  }

  /*----------------------------------------------------------------------------
  Spieler Eins */
  if (!MSGBestaetigt_P1)
  {
    if (TasterHandler_Klick(SpielerEins, TasterEins))
    {
      MSGBestaetigt_P1 = true;
      PotiLed_Setzen(SpielerEins, Gruen);
    }
  }
  else
  {
    aktuelleAuswahl_P1 = map(PotiTreiber_Get_Val(SpielerEins), 0, 255, 1, 5);

    switch (aktuelleAuswahl_P1)
    {
      case 1:
      if (PlayerManager_IsShieldActive(SpielerEins))
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Schild_Aktiv, &leer5);
      }
      break;

      case 2:
      if (PlayerManager_IsSpeedActive(SpielerEins))
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Speed_Aktiv, &leer5);
      }
      break;

      case 3:
      if (PlayerManager_IsGewinnGarantiertActive(SpielerEins))
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Gewinn_Aktiv, &leer5);
      }
      break;

      case 4:
      if (PlayerManager_IsEinsatzSetzenActive(SpielerEins))
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_EinsatzSetzen_Aktiv, &leer5);
      }
      break;

      case 5:
      if (PlayerManager_IsAussetzenActive(SpielerEins))
      {
        Messages_ZeigeNachricht(SpielerEins, MSG_Buff_Aussetzen_Aktiv, &leer5);
      }
      break;
    }
  }
  if (!BuffsBestaetigt_P1)
  {
    if (TasterHandler_Klick(SpielerEins, TasterEins))
    {
      BuffsBestaetigt_P1 = true;
      PotiLed_Setzen(SpielerEins, Schwarz);
      TasterLed_Setzen(SpielerEins, LedEins, Schwarz);
    }
  }


/*------------------------------------------------------------------------------
Spieler Zwei */
  if (!MSGBestaetigt_P2)
  {
    if (TasterHandler_Klick(SpielerZwei, TasterEins))
    {
      MSGBestaetigt_P2 = true;
      PotiLed_Setzen(SpielerZwei, Gruen);
    }
  }
  else
  {
    aktuelleAuswahl_P2 = map(PotiTreiber_Get_Val(SpielerZwei), 0, 255, 1, 5);

    switch (aktuelleAuswahl_P2)
    {
      case 1:
      if (PlayerManager_IsShieldActive(SpielerZwei))
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Schild_Aktiv, &leer5);
      }
      break;

      case 2:
      if (PlayerManager_IsSpeedActive(SpielerZwei))
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Speed_Aktiv, &leer5);
      }
      break;

      case 3:
      if (PlayerManager_IsGewinnGarantiertActive(SpielerZwei))
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Gewinn_Aktiv, &leer5);
      }
      break;

      case 4:
      if (PlayerManager_IsEinsatzSetzenActive(SpielerZwei))
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_EinsatzSetzen_Aktiv, &leer5);
      }
      break;

      case 5:
      if (PlayerManager_IsAussetzenActive(SpielerZwei))
      {
        Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Aussetzen_Aktiv, &leer5);
      }
      break;
    }
  }
  if (!BuffsBestaetigt_P2)
  {
    if (TasterHandler_Klick(SpielerZwei, TasterEins))
    {
      BuffsBestaetigt_P2 = true;
      PotiLed_Setzen(SpielerZwei, Schwarz);
      TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
    }
  }

  /*------------------------------------------------------------------------------
  Final check und Reset */
  if (BuffsBestaetigt_P1 and BuffsBestaetigt_P2)
  {
    BuffsBestaetigt_P1 = false;
    BuffsBestaetigt_P2 = false;
    MSGShown = false;
    MSGBestaetigt_P1 = false;
    MSGBestaetigt_P2 = false;
    BuffanzeigeFertig = true;
  }
}
