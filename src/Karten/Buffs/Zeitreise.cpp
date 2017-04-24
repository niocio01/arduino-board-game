#include <inttypes.h>
#include "PlayerManager.h"
#include "Karten/Minigames/EinsatzSetzen.h"



const uint8_t anzahlSpeicherstaende = 20;
const uint8_t anzahlDatenTypen = 13; // + 1 wegen check stelle
const uint8_t anzahlSchritteZurueck = 5;

uint8_t Speicherstand_P1[anzahlSpeicherstaende][anzahlDatenTypen];
uint8_t Speicherstand_P2[anzahlSpeicherstaende][anzahlDatenTypen];



const uint8_t ArrayPosMitDatenGefuellt = 0;
const uint8_t Figur1Pos = 1;
const uint8_t Figur2Pos = 2;
const uint8_t FallePos = 3;
const uint8_t EinsatzDepot = 4;
const uint8_t Umweg1Aktiv = 5;
const uint8_t Umweg2Aktiv = 6;
const uint8_t Umweg3Aktiv = 7;
const uint8_t SchildAktiv = 8;
const uint8_t SpeedAktiv = 9;
const uint8_t AussetzenAktiv = 10;
const uint8_t EinsatzSetzenAktiv = 11;
const uint8_t GewinnGarantiertAktiv = 12;



static uint8_t P1_Figur1Pos;
static uint8_t P1_Figur2Pos;
static uint8_t P1_FallePos;
static uint8_t P1_EinsatzDepot;
static bool P1_Umweg1Aktiv;
static bool P1_Umweg2Aktiv;
static bool P1_Umweg3Aktiv;
static bool P1_SchildAktiv;
static bool P1_SpeedAktiv;
static bool P1_AussetzenAktiv;
static bool P1_EinsatzSetzenAktiv;
static bool P1_GewinnGarantiertAktiv;

static uint8_t P2_Figur1Pos;
static uint8_t P2_Figur2Pos;
static uint8_t P2_FallePos;
static uint8_t P2_EinsatzDepot;
static bool P2_Umweg1Aktiv;
static bool P2_Umweg2Aktiv;
static bool P2_Umweg3Aktiv;
static bool P2_SchildAktiv;
static bool P2_SpeedAktiv;
static bool P2_AussetzenAktiv;
static bool P2_EinsatzSetzenAktiv;
static bool P2_GewinnGarantiertAktiv;



void Zeitreise_FillInNewSpielzug(void)
{
  if (PlayerManager_SpielerEinsAmZug())
  {
    for (uint8_t i = anzahlSpeicherstaende; 0; i--) //i ist der spielschritt
    {
      if (i != 0)
      {
        if (Speicherstand_P1[i-1][0] == true)
        {
          for (uint8_t j = 0; anzahlDatenTypen; j++) // j sind die eigentlichen Daten.
          {
            Speicherstand_P1[i][j] = Speicherstand_P1[i-1][j];
          }
        }
      }
      else // bei Array[0] neue Daten Einfüllen
      {
        for (uint8_t j = 0; anzahlDatenTypen; j++)
        {
          if (j == ArrayPosMitDatenGefuellt)
          {
            Speicherstand_P1[i][j] = true; // Setzte wariable um herauszufinden wieviele ebenen bereits gefüllt worden sind.
          }
          else if (j == Figur1Pos)
          {
            //Speicherstand_P1[i][j] =   // getFigurPos.
          }
          else if (j == Figur2Pos)
          {
            //Speicherstand_P1[i][j] =
          }
          else if (j == FallePos)
          {
            //Speicherstand_P1[i][j] =
          }
          else if (j == EinsatzDepot)
          {
            Speicherstand_P1[i][j] = EinsatzSetzen_GetEinsatzDepot(SpielerEins);
          }
          else if (j == Umweg1Aktiv)
          {
            //  Speicherstand_P1[i][j] =
          }
          else if (j == Umweg2Aktiv)
          {
            //  Speicherstand_P1[i][j] =
          }
          else if (j == Umweg3Aktiv)
          {
            //  Speicherstand_P1[i][j] =
          }
          else if (j == SchildAktiv)
          {
            Speicherstand_P1[i][j] = PlayerManager_IsShieldActive(SpielerEins);
          }
          else if (j == SpeedAktiv)
          {
            Speicherstand_P1[i][j] = PlayerManager_IsSpeedActive(SpielerEins);
          }
          else if (j == AussetzenAktiv)
          {
            Speicherstand_P1[i][j] = PlayerManager_IsAussetzenActive(SpielerZwei); // fragt gegenspieler ab
          }
          else if (j == EinsatzSetzenAktiv)
          {
            Speicherstand_P1[i][j] = PlayerManager_IsEinsatzSetzenActive(SpielerEins);
          }
          else if (j == GewinnGarantiertAktiv)
          {
            Speicherstand_P1[i][j] = PlayerManager_IsGewinnGarantiertActive(SpielerEins);
          }
        }
      }
    }
  }



  else // Spieler Zwei
  {
    for (uint8_t i = anzahlSpeicherstaende; 0; i--) //i ist der spielschritt
    {
      if (i != 0)
      {
        if (Speicherstand_P2[i-1][0] == true)
        {
          for (uint8_t j = 0; anzahlDatenTypen; j++) // j sind die eigentlichen Daten.
          {
            Speicherstand_P2[i][j] = Speicherstand_P2[i-1][j];
          }
        }
      }
      else // bei Array[0] neue Daten Einfüllen
      {
        for (uint8_t j = 0; anzahlDatenTypen; j++)
        {
          if (j == ArrayPosMitDatenGefuellt)
          {
            Speicherstand_P2[i][j] = true; // Setzte wariable um herauszufinden wieviele ebenen bereits gefüllt worden sind.
          }
          else if (j == Figur1Pos)
          {
            //Speicherstand_P2[i][j] =   // getFigurPos.
          }
          else if (j == Figur2Pos)
          {
            //Speicherstand_P2[i][j] =
          }
          else if (j == FallePos)
          {
            //Speicherstand_P2[i][j] =
          }
          else if (j == EinsatzDepot)
          {
            Speicherstand_P2[i][j] = EinsatzSetzen_GetEinsatzDepot(SpielerZwei);
          }
          else if (j == Umweg1Aktiv)
          {
            //  Speicherstand_P2[i][j] =
          }
          else if (j == Umweg2Aktiv)
          {
            //  Speicherstand_P2[i][j] =
          }
          else if (j == Umweg3Aktiv)
          {
            //  Speicherstand_P2[i][j] =
          }
          else if (j == SchildAktiv)
          {
            Speicherstand_P2[i][j] = PlayerManager_IsShieldActive(SpielerZwei);
          }
          else if (j == SpeedAktiv)
          {
            Speicherstand_P2[i][j] = PlayerManager_IsSpeedActive(SpielerZwei);
          }
          else if (j == AussetzenAktiv)
          {
            Speicherstand_P2[i][j] = PlayerManager_IsAussetzenActive(SpielerEins); // fragt gegenspieler ab
          }
          else if (j == EinsatzSetzenAktiv)
          {
            Speicherstand_P2[i][j] = PlayerManager_IsEinsatzSetzenActive(SpielerZwei);
          }
          else if (j == GewinnGarantiertAktiv)
          {
            Speicherstand_P2[i][j] = PlayerManager_IsGewinnGarantiertActive(SpielerZwei);
          }
        }
      }
    }
  }
}



void Zeitreise_BuffAnwenden(void)
{
  /* Array verschieben, um augelesen zu werden
  ----------------------------------------------------------------------------------*/

  uint8_t anzahlGefuellt;
  for (uint8_t i= 0; anzahlSpeicherstaende-1; i++)
  {
    if (Speicherstand_P1[i][0] == true)
    {
      anzahlGefuellt ++ ;
    }

  }
  if (anzahlGefuellt < anzahlSchritteZurueck)
  {
    for (uint8_t k = 0; anzahlGefuellt-1 ; k++) // von null bis zur letzten gefüllten zeile
    {
      for (uint8_t j = 0; anzahlDatenTypen; j++) // Alle Daten von Speicherstand i-1 in (i-1)+k schreiben
      {
        Speicherstand_P1[k][j] = Speicherstand_P1[(anzahlGefuellt-1)+k][j];
      }
    }
  }
  else // wenn alle Zeilen gefüllt sind
  {
    for (uint8_t i = 0; anzahlGefuellt-1; i++)
    {
      for (uint8_t j = 0; anzahlDatenTypen; j++)
      {
        Speicherstand_P1[i][j] = Speicherstand_P1[i+(anzahlSchritteZurueck-1)][j];
      }
    }
  }

  /* Array auslesen und Spielstände den entsprechenden Modulen mitteilen.
  ----------------------------------------------------------------------------------*/

  for (uint8_t j = 0;anzahlDatenTypen; j++) // array auslesen
  {
    if (j == Figur1Pos)
    {
      P1_Figur1Pos = Speicherstand_P1[0][j];
      P2_Figur1Pos = Speicherstand_P2[0][j];
    }
    else if (j == Figur2Pos)
    {
      P1_Figur2Pos = Speicherstand_P1[0][j];
      P2_Figur2Pos = Speicherstand_P2[0][j];
    }
    else if (j == FallePos)
    {
      P1_FallePos = Speicherstand_P1[0][j];
      P2_FallePos = Speicherstand_P2[0][j];
    }
    else if (j == EinsatzDepot)
    {
      P1_EinsatzDepot = Speicherstand_P1[0][j];
      P2_EinsatzDepot = Speicherstand_P2[0][j];
      EinsatzSetzen_SetEinsatzDepot(SpielerEins, P1_EinsatzDepot);
      EinsatzSetzen_SetEinsatzDepot(SpielerZwei, P2_EinsatzDepot);
    }
    else if (j == Umweg1Aktiv)
    {
      P1_Umweg1Aktiv = Speicherstand_P1[0][j];
      P2_Umweg1Aktiv = Speicherstand_P2[0][j];
    }
    else if (j == Umweg2Aktiv)
    {
      P1_Umweg2Aktiv = Speicherstand_P1[0][j];
      P2_Umweg2Aktiv = Speicherstand_P2[0][j];
    }
    else if (j == Umweg3Aktiv)
    {
      P1_Umweg3Aktiv = Speicherstand_P1[0][j];
      P2_Umweg3Aktiv = Speicherstand_P2[0][j];
    }

    else if (j == SchildAktiv)
    {
      P1_SchildAktiv = Speicherstand_P1[0][j];
      if (P1_SchildAktiv)
      {
        PlayerManager_ActivateShield(SpielerEins);
      }
      else
      {
        PlayerManager_DeActivateShield(SpielerEins);
      }

      P2_SchildAktiv = Speicherstand_P2[0][j];
      if (P2_SchildAktiv)
      {
        PlayerManager_ActivateShield(SpielerZwei);
      }
      else
      {
        PlayerManager_DeActivateShield(SpielerZwei);
      }
    }

    else if (j == SpeedAktiv)
    {
      P1_SpeedAktiv = Speicherstand_P1[0][j];
      if (P1_SpeedAktiv)
      {
        PlayerManager_ActivateSpeed(SpielerEins);
      }
      else
      {
        PlayerManager_DeActivateSpeed(SpielerEins);
      }

      P2_SpeedAktiv = Speicherstand_P2[0][j];
      if (P2_SpeedAktiv)
      {
        PlayerManager_ActivateSpeed(SpielerZwei);
      }
      else
      {
        PlayerManager_DeActivateSpeed(SpielerZwei);
      }
    }

    else if (j == AussetzenAktiv)
    {
      P1_AussetzenAktiv = Speicherstand_P1[0][j];
      if (P1_AussetzenAktiv)
      {
        PlayerManager_ActivateAussetzen(SpielerZwei); // setzt für gegenspieler
      }
      else
      {
        PlayerManager_DeActivateAussetzen(SpielerZwei); // setzt für gegenspieler
      }

      P2_AussetzenAktiv = Speicherstand_P2[0][j];
      if (P2_AussetzenAktiv)
      {
        PlayerManager_ActivateAussetzen(SpielerEins); // setzt für gegenspieler
      }
      else
      {
        PlayerManager_DeActivateAussetzen(SpielerEins); // setzt für gegenspieler
      }
    }
    else if (j == EinsatzSetzenAktiv)
    {
      P1_EinsatzSetzenAktiv = Speicherstand_P1[0][j];
      if (P1_EinsatzSetzenAktiv)
      {
        PlayerManager_ActivateEinsatzSetzen(SpielerEins);
      }
      else
      {
        PlayerManager_DeActivateEinsatzSetzen(SpielerEins);
      }

      P2_EinsatzSetzenAktiv = Speicherstand_P2[0][j];
      if (P2_EinsatzSetzenAktiv)
      {
        PlayerManager_ActivateEinsatzSetzen(SpielerZwei);
      }
      else
      {
        PlayerManager_DeActivateEinsatzSetzen(SpielerZwei);
      }
    }
    else if (j == GewinnGarantiertAktiv)
    {
      P1_GewinnGarantiertAktiv = Speicherstand_P1[0][j];
      if (P1_GewinnGarantiertAktiv)
      {
        PlayerManager_ActivateGewinnGarantiert(SpielerEins);
      }
      else
      {
        PlayerManager_DeActivateGewinnGarantiert(SpielerEins);
      }

      P2_GewinnGarantiertAktiv = Speicherstand_P2[0][j];
      if (P2_GewinnGarantiertAktiv)
      {
        PlayerManager_ActivateGewinnGarantiert(SpielerZwei);
      }
      else
      {
        PlayerManager_DeActivateGewinnGarantiert(SpielerZwei);
      }
    }
  }


}
