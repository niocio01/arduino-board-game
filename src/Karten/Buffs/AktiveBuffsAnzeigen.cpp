#include "Karten/Buffs/AktiveBuffsAnzeigen.h"
#include "Treiber/TasterHandler.h"
#include "Treiber/TasterLed.h"
#include "Treiber/PotiLed.h"
#include "Treiber/PotiTreiber.h"
#include <arduino.h>
#include "PlayerManager.h"
#include <inttypes.h>
#include "Messages.h"
#include "Karten/KartenManager.h"

const uint16_t updateIntervall = 100;
static uint32_t lastUpdateTime;

Messages_values leer5;

uint8_t AktiveBuffs_P1[5];
uint8_t AktiveBuffs_P2[5];


const uint8_t Schild = 1;
const uint8_t Speed = 2;
const uint8_t GewinnGarantiert = 3;
const uint8_t EinsatzSetzen = 4;
const uint8_t Aussetzen = 5;

static uint8_t AnzahlAktiveBuffs_P1 = 0;
static uint8_t AnzahlAktiveBuffs_P2 = 0;

static uint8_t displayBuffNr_P1 = 0;
static uint8_t displayBuffNr_P2 = 0;

static bool MSGShown = false;
static bool MSGBestaetigt_P1 = false;
static bool MSGBestaetigt_P2 = false;
static bool BuffsBestaetigt_P1 = false;
static bool BuffsBestaetigt_P2 = false;

uint8_t aktuelleAuswahl_P1;
uint8_t aktuelleAuswahl_P2;


void AktiveBuffsAnzeigen_Run(void)
{
  if (!MSGShown)
  {
    MSGShown = true;
    Messages_ZeigeNachricht(SpielerEins, MSG_AktiveBuffsAnzeigen, &leer5);
    Messages_ZeigeNachricht(SpielerZwei, MSG_AktiveBuffsAnzeigen, &leer5);
    TasterLed_Setzen(SpielerEins, LedEins, Gruen);
    TasterLed_Setzen(SpielerZwei, LedEins, Gruen);

    /*----------------------------------------------------------------------------
    Buffs auslesen
    Jeden buff prüfen und fals dieser aktiv ist in das Array in die nächste position schreiben */


    // Spieler Zwei
    if (PlayerManager_IsShieldActive(SpielerZwei))
    {
      AktiveBuffs_P2[AnzahlAktiveBuffs_P2] = Schild;
      AnzahlAktiveBuffs_P2 ++;
    }
    if (PlayerManager_IsSpeedActive(SpielerZwei))
    {
      AktiveBuffs_P2[AnzahlAktiveBuffs_P2] = Speed;
      AnzahlAktiveBuffs_P2 ++;
    }
    if (PlayerManager_IsGewinnGarantiertActive(SpielerZwei))
    {
      AktiveBuffs_P2[AnzahlAktiveBuffs_P2] = GewinnGarantiert;
      AnzahlAktiveBuffs_P2 ++;
    }
    if (PlayerManager_IsEinsatzSetzenActive(SpielerZwei))
    {
      AktiveBuffs_P2[AnzahlAktiveBuffs_P2] = EinsatzSetzen;
      AnzahlAktiveBuffs_P2 ++;
    }
    if (PlayerManager_IsAussetzenActive(SpielerZwei))
    {
      AktiveBuffs_P2[AnzahlAktiveBuffs_P2] = Aussetzen;
      AnzahlAktiveBuffs_P2 ++;
    }
  }
  /*------------------------------------------------------------------------------*/

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
    if ((millis() - lastUpdateTime) > updateIntervall)
    {
    lastUpdateTime = millis();
    aktuelleAuswahl_P2 = map(PotiTreiber_Get_Val(SpielerZwei), 0, 255, 0, AnzahlAktiveBuffs_P2-1);

    displayBuffNr_P2 = AktiveBuffs_P2[aktuelleAuswahl_P2]; // display Buff an Array pos. aktuelleAuswahl_P2

    switch (displayBuffNr_P2)
    {
      case 0: // kein buff aktiv
      Messages_ZeigeNachricht(SpielerZwei, MSG_KeineBuffsAktiv, &leer5);
      break;

      case Schild: // 1
      Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Schild_Aktiv, &leer5);
      break;

      case Speed: // 2
      Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Speed_Aktiv, &leer5);
      break;

      case GewinnGarantiert: // 3
      Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Gewinn_Aktiv, &leer5);
      break;

      case EinsatzSetzen: // 4
      Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_EinsatzSetzen_Aktiv, &leer5);
      break;

      case Aussetzen: // 5
      Messages_ZeigeNachricht(SpielerZwei, MSG_Buff_Aussetzen_Aktiv, &leer5);
      break;

    }
  }

    if (!BuffsBestaetigt_P2)
    {
      if (TasterHandler_Klick(SpielerZwei, TasterEins))
      {
      //  BuffsBestaetigt_P2 = true;
        PotiLed_Setzen(SpielerZwei, Schwarz);
        TasterLed_Setzen(SpielerZwei, LedEins, Schwarz);
      }
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
    Kartenmanager_AktiveBuffAnzeigen(false);
  }
}
