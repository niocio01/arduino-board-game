#include <inttypes.h>
#include "PlayerManager.h"
#include "Karten/Minigames/EinsatzSetzen.h"

// Lokale Definitionen
const uint8_t anzahlSpeicherstaende = 20;
const uint8_t anzahlSchritteZurueck = 5;

// Lokale Typendefinitionen
typedef struct ZeitreiseDaten_tag
{
  bool SpielschrittGefuellt;
  uint8_t Figur1Pos;
  uint8_t Figur2Pos;
  uint8_t FallePos;
  uint8_t EinsatzDepot;
  bool Umweg1Aktiv;
  bool Umweg2Aktiv;
  bool Umweg3Aktiv;
  bool SchildAktiv;
  bool SpeedAktiv;
  bool AussetzenAktiv;
  bool EinsatzSetzenAktiv;
  bool GewinnGarantiertAktiv;
} ZeitreiseDaten_t;

// Lokale Variablen
static ZeitreiseDaten_t Speicherstand_P1[anzahlSpeicherstaende];
static ZeitreiseDaten_t Speicherstand_P2[anzahlSpeicherstaende];

// Lokale Funktionen (Prototypen)
static void speicherstandKopieren_P1(uint8_t zielSchritt, uint8_t quellSchritt);
static void speicherstandKopieren_P2(uint8_t zielSchritt, uint8_t quellSchritt);
static void speicherstandEinfuellen_P1(uint8_t zielSchritt);
static void speicherstandEinfuellen_P2(uint8_t zielSchritt);
static void aktuelleSpielstaendeWeitergeben(void);


/* Alle Daten des Aktuellen Spielers einen Arrayplatz nach oben verschieben
und den nun freien platz [0] mit den aktuellen daten füllen
----------------------------------------------------------------------------------*/
void Zeitreise_FillInNewSpielzug(void)
{
  uint8_t spielSchritt;

  if (PlayerManager_SpielerEinsAmZug())
  {
    for (spielSchritt = anzahlSpeicherstaende; 0; spielSchritt--)
    {
      if (spielSchritt != 0)
      {
        // Bei Array[!0] bestehende Daten je ein Feld nach oben kopieren
        if (Speicherstand_P1[spielSchritt].SpielschrittGefuellt == true)
        {
          speicherstandKopieren_P1(spielSchritt, spielSchritt-1);
        }
      }
      else
      {
        // Bei Array[0] neue Daten einfüllen
        speicherstandEinfuellen_P1(spielSchritt);
        // Setzte Variable um herauszufinden wieviele Ebenen bereits gefüllt worden sind.
        Speicherstand_P1[spielSchritt].SpielschrittGefuellt = true;
      }
    }
  }

  if (PlayerManager_SpielerZweiAmZug())
  {
    for (spielSchritt = anzahlSpeicherstaende; 0; spielSchritt--)
    {
      if (spielSchritt != 0)
      {
        // Bei Array[>0] bestehende Daten kopieren
        if (Speicherstand_P2[spielSchritt].SpielschrittGefuellt == true)
        {
          speicherstandKopieren_P2(spielSchritt, spielSchritt-1);
        }
      }
      else
      {
        // Bei Array[0] neue Daten einfüllen
        speicherstandEinfuellen_P2(spielSchritt);
        // Setzte Variable um herauszufinden wieviele Ebenen bereits gefüllt worden sind.
        Speicherstand_P1[spielSchritt].SpielschrittGefuellt = true;
      }
    }
  }
}

/* Zerst prüfen, ob 5 spilschritte vorhanden sind, welche zurückgesetzt werden können
falls ja, diese "löschen" und alle daten 5 nach unten verschieben
Falls nein, den höchstmöglichen datensatzt auf platzt [0] verschieben

danach dise neue "alte" Situation auf platz [0] in den jeweiligen Modulen mitteilen.
----------------------------------------------------------------------------------*/
void Zeitreise_BuffAnwenden(void)
{
  /* Array verschieben, um ausgelesen zu werden
  ----------------------------------------------------------------------------------*/
  uint8_t anzahlGefuellt;
  uint8_t spielSchritt;
  // aktuellen Spieler pfüfen, denn dieser
  // hat immer gleichviel oder weniger datenstaende gespichert
  if (PlayerManager_SpielerEinsAmZug())
  {
    // Prüfen, ob alle 5 plätze mit daten gefüllt sind
    for (spielSchritt = 0; anzahlSpeicherstaende-1; spielSchritt++)
    {
      if (Speicherstand_P1[spielSchritt].SpielschrittGefuellt == true)
      {
        anzahlGefuellt++ ;
      }
    }

    // wenn Die anzahl gespeicherter datenstaenden kleiner als "5" (anzahlSchritteZurueck) ist,
    // Ganzes Array (auch Gegner) anazahl gefüllter spielstände (anzahlGefuellt) herunter verschieben.
    if (anzahlGefuellt < anzahlSchritteZurueck)
    {
      for (spielSchritt = 0; anzahlGefuellt-1 ; spielSchritt++) // von null bis zur letzten gefüllten zeile
      {
        speicherstandKopieren_P1(spielSchritt, spielSchritt+(anzahlGefuellt-1));
        speicherstandKopieren_P2(spielSchritt, spielSchritt+(anzahlGefuellt-1));
      }
    }
    else // wenn alle "5" Zeilen gefüllt sind
    {
      for (spielSchritt = 0; anzahlGefuellt-1; spielSchritt++)
      {
        speicherstandKopieren_P1(spielSchritt, spielSchritt+(anzahlSchritteZurueck-1));
        speicherstandKopieren_P2(spielSchritt, spielSchritt+(anzahlSchritteZurueck-1));
      }
    }

    // Aktuelle Zeitreise-Daten an entsprechende Module weitergeben
    aktuelleSpielstaendeWeitergeben();
  }
}

/* Aktuelle Zeitreise-Daten von Spieler 1 vom Quell-Schritt in Ziel-Schritt kopieren
----------------------------------------------------------------------------------*/
static void speicherstandKopieren_P1(uint8_t zielSchritt, uint8_t quellSchritt)
{
  Speicherstand_P1[zielSchritt].SpielschrittGefuellt = Speicherstand_P1[quellSchritt].SpielschrittGefuellt;
  Speicherstand_P1[zielSchritt].Figur1Pos = Speicherstand_P1[quellSchritt].Figur1Pos;
  Speicherstand_P1[zielSchritt].Figur2Pos = Speicherstand_P1[quellSchritt].Figur2Pos;
  Speicherstand_P1[zielSchritt].FallePos = Speicherstand_P1[quellSchritt].FallePos;
  Speicherstand_P1[zielSchritt].EinsatzDepot = Speicherstand_P1[quellSchritt].EinsatzDepot;
  Speicherstand_P1[zielSchritt].Umweg1Aktiv = Speicherstand_P1[quellSchritt].Umweg1Aktiv;
  Speicherstand_P1[zielSchritt].Umweg2Aktiv = Speicherstand_P1[quellSchritt].Umweg2Aktiv;
  Speicherstand_P1[zielSchritt].Umweg3Aktiv = Speicherstand_P1[quellSchritt].Umweg3Aktiv;
  Speicherstand_P1[zielSchritt].SchildAktiv = Speicherstand_P1[quellSchritt].SchildAktiv;
  Speicherstand_P1[zielSchritt].SpeedAktiv = Speicherstand_P1[quellSchritt].SpeedAktiv;
  Speicherstand_P1[zielSchritt].AussetzenAktiv = Speicherstand_P1[quellSchritt].AussetzenAktiv;
  Speicherstand_P1[zielSchritt].EinsatzSetzenAktiv = Speicherstand_P1[quellSchritt].EinsatzSetzenAktiv;
  Speicherstand_P1[zielSchritt].GewinnGarantiertAktiv = Speicherstand_P1[quellSchritt].GewinnGarantiertAktiv;
}

/* Aktuelle Zeitreise-Daten von Spieler 2 vom Quell-Schritt in Ziel-Schritt kopieren
----------------------------------------------------------------------------------*/
static void speicherstandKopieren_P2(uint8_t zielSchritt, uint8_t quellSchritt)
{
  Speicherstand_P2[zielSchritt].SpielschrittGefuellt = Speicherstand_P2[quellSchritt].SpielschrittGefuellt;
  Speicherstand_P2[zielSchritt].Figur1Pos = Speicherstand_P2[quellSchritt].Figur1Pos;
  Speicherstand_P2[zielSchritt].Figur2Pos = Speicherstand_P2[quellSchritt].Figur2Pos;
  Speicherstand_P2[zielSchritt].FallePos = Speicherstand_P2[quellSchritt].FallePos;
  Speicherstand_P2[zielSchritt].EinsatzDepot = Speicherstand_P2[quellSchritt].EinsatzDepot;
  Speicherstand_P2[zielSchritt].Umweg1Aktiv = Speicherstand_P2[quellSchritt].Umweg1Aktiv;
  Speicherstand_P2[zielSchritt].Umweg2Aktiv = Speicherstand_P2[quellSchritt].Umweg2Aktiv;
  Speicherstand_P2[zielSchritt].Umweg3Aktiv = Speicherstand_P2[quellSchritt].Umweg3Aktiv;
  Speicherstand_P2[zielSchritt].SchildAktiv = Speicherstand_P2[quellSchritt].SchildAktiv;
  Speicherstand_P2[zielSchritt].SpeedAktiv = Speicherstand_P2[quellSchritt].SpeedAktiv;
  Speicherstand_P2[zielSchritt].AussetzenAktiv = Speicherstand_P2[quellSchritt].AussetzenAktiv;
  Speicherstand_P2[zielSchritt].EinsatzSetzenAktiv = Speicherstand_P2[quellSchritt].EinsatzSetzenAktiv;
  Speicherstand_P2[zielSchritt].GewinnGarantiertAktiv = Speicherstand_P2[quellSchritt].GewinnGarantiertAktiv;
}

/* Neue Zeitreise-Daten von Spieler 1 in Ziel-Schritt kopieren
----------------------------------------------------------------------------------*/
static void speicherstandEinfuellen_P1(uint8_t zielSchritt)
{
  Speicherstand_P1[zielSchritt].Figur1Pos = 0U;  // TODO getFigurPos
  Speicherstand_P1[zielSchritt].Figur2Pos = 0U; // TODO getFigurPos
  Speicherstand_P1[zielSchritt].FallePos = 0U; // TODO ... ?
  Speicherstand_P1[zielSchritt].EinsatzDepot = EinsatzSetzen_GetEinsatzDepot(SpielerEins);
  Speicherstand_P1[zielSchritt].Umweg1Aktiv = false; // TODO ... ?
  Speicherstand_P1[zielSchritt].Umweg2Aktiv = false; // TODO ... ?
  Speicherstand_P1[zielSchritt].Umweg3Aktiv = false; // TODO ... ?
  Speicherstand_P1[zielSchritt].SchildAktiv = PlayerManager_IsShieldActive(SpielerEins);
  Speicherstand_P1[zielSchritt].SpeedAktiv = PlayerManager_IsSpeedActive(SpielerEins);
  Speicherstand_P1[zielSchritt].AussetzenAktiv = PlayerManager_IsAussetzenActive(SpielerZwei); // fragt gegenspieler ab
  Speicherstand_P1[zielSchritt].EinsatzSetzenAktiv = PlayerManager_IsEinsatzSetzenActive(SpielerEins);
  Speicherstand_P1[zielSchritt].GewinnGarantiertAktiv = PlayerManager_IsGewinnGarantiertActive(SpielerEins);
}

/* Neue Zeitreise-Daten von Spieler 2 in Ziel-Schritt kopieren
----------------------------------------------------------------------------------*/
static void speicherstandEinfuellen_P2(uint8_t zielSchritt)
{
  Speicherstand_P2[zielSchritt].Figur1Pos = 0U;  // TODO getFigurPos
  Speicherstand_P2[zielSchritt].Figur2Pos = 0U; // TODO getFigurPos
  Speicherstand_P2[zielSchritt].FallePos = 0U; // TODO ... ?
  Speicherstand_P2[zielSchritt].EinsatzDepot = EinsatzSetzen_GetEinsatzDepot(SpielerZwei);
  Speicherstand_P2[zielSchritt].Umweg1Aktiv = false; // TODO ... ?
  Speicherstand_P2[zielSchritt].Umweg2Aktiv = false; // TODO ... ?
  Speicherstand_P2[zielSchritt].Umweg3Aktiv = false; // TODO ... ?
  Speicherstand_P2[zielSchritt].SchildAktiv = PlayerManager_IsShieldActive(SpielerZwei);
  Speicherstand_P2[zielSchritt].SpeedAktiv = PlayerManager_IsSpeedActive(SpielerZwei);
  Speicherstand_P2[zielSchritt].AussetzenAktiv = PlayerManager_IsAussetzenActive(SpielerEins); // fragt gegenspieler ab
  Speicherstand_P2[zielSchritt].EinsatzSetzenAktiv = PlayerManager_IsEinsatzSetzenActive(SpielerZwei);
  Speicherstand_P2[zielSchritt].GewinnGarantiertAktiv = PlayerManager_IsGewinnGarantiertActive(SpielerZwei);
}

/* Aktuelle Zeitreise-Daten an entsprechende Module weitergeben
----------------------------------------------------------------------------------*/
static void aktuelleSpielstaendeWeitergeben(void)
{
  /* TODO Aktuellen Stand weitergeben ???
  Speicherstand_P1[0].Figur1Pos;
  Speicherstand_P2[0].Figur1Pos;
  Speicherstand_P1[0].Figur2Pos;
  Speicherstand_P2[0].Figur2Pos;
  Speicherstand_P1[0].FallePos;
  Speicherstand_P2[0].FallePos;
  */
  //--------------------------------------------------------
  EinsatzSetzen_SetEinsatzDepot(SpielerEins, Speicherstand_P1[0].EinsatzDepot);
  EinsatzSetzen_SetEinsatzDepot(SpielerZwei, Speicherstand_P2[0].EinsatzDepot);
  //--------------------------------------------------------
  /* TODO Aktuellen Stand weitergeben ???
  Speicherstand_P1[0].Umweg1Aktiv;
  Speicherstand_P2[0].Umweg1Aktiv;
  Speicherstand_P1[0].Umweg2Aktiv;
  Speicherstand_P2[0].Umweg2Aktiv;
  Speicherstand_P1[0].Umweg3Aktiv;
  Speicherstand_P2[0].Umweg3Aktiv;
  */
  //--------------------------------------------------------
  if (Speicherstand_P1[0].SchildAktiv)
  {
    PlayerManager_ActivateShield(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateShield(SpielerEins);
  }
  if (Speicherstand_P2[0].SchildAktiv)
  {
    PlayerManager_ActivateShield(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateShield(SpielerZwei);
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0].SpeedAktiv)
  {
    PlayerManager_ActivateSpeed(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateSpeed(SpielerEins);
  }
  if (Speicherstand_P2[0].SpeedAktiv)
  {
    PlayerManager_ActivateSpeed(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateSpeed(SpielerZwei);
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0].AussetzenAktiv)
  {
    PlayerManager_ActivateAussetzen(SpielerZwei); // setzt für gegenspieler
  }
  else
  {
    PlayerManager_DeActivateAussetzen(SpielerZwei); // setzt für gegenspieler
  }
  if (Speicherstand_P2[0].AussetzenAktiv)
  {
    PlayerManager_ActivateAussetzen(SpielerEins); // setzt für gegenspieler
  }
  else
  {
    PlayerManager_DeActivateAussetzen(SpielerEins); // setzt für gegenspieler
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0].EinsatzSetzenAktiv)
  {
    PlayerManager_ActivateEinsatzSetzen(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateEinsatzSetzen(SpielerEins);
  }
  if (Speicherstand_P2[0].EinsatzSetzenAktiv)
  {
    PlayerManager_ActivateEinsatzSetzen(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateEinsatzSetzen(SpielerZwei);
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0].GewinnGarantiertAktiv)
  {
    PlayerManager_ActivateGewinnGarantiert(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateGewinnGarantiert(SpielerEins);
  }
  if (Speicherstand_P2[0].GewinnGarantiertAktiv)
  {
    PlayerManager_ActivateGewinnGarantiert(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateGewinnGarantiert(SpielerZwei);
  }
}
