#include <inttypes.h>
#include "PlayerManager.h"
#include "Karten/Minigames/EinsatzSetzen.h"
#include "Treiber/LedTreiber.h"

// Lokale Definitionen
const uint8_t anzahlSpeicherstaende = 10U;
const uint8_t anzahlSchritteZurueck = 5U;
// ACHTUNG: 'anzahlSpeicherstaende' muss immer mindestens doppelt so gross sein wie
//          'anzahlSchritteZurueck' da sonst das "Zurücksetzen" in der Funktion
//          'Zeitreise_BuffAnwenden()' nicht korrekt funktioniert (dieser Fall ist nicht abgefangen!)

// Lokale Typendefinitionen
typedef struct ZeitreiseDaten_tag
{
  bool SpielschrittGefuellt = false;
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
static void speicherstandEinfuellen_P1(void);
static void speicherstandEinfuellen_P2(void);
static void aktuelleSpielstaendeWeitergeben(void);


/* Alle Daten des aktuellen Spielers einen Arrayplatz "nach oben" verschieben
und den nun freien Arrayplatz[0] mit den aktuellen Spielerdaten füllen
----------------------------------------------------------------------------------*/
void Zeitreise_FillInNewSpielzug(void)
{
  uint8_t spielSchritt;

  if (PlayerManager_SpielerEinsAmZug())
  {
    // Alle Spielerdaten jeweils um einen Arrayplatz "nach oben" verschieben
    for (spielSchritt = (anzahlSpeicherstaende - 1U); spielSchritt > 1U; spielSchritt--)
    {
	  // Spielerdaten um einem Arrayplatz "nach oben" verschieben ([n-1]->[n], [n-2]->[n-1] bis [0]->[1])
	  // Hinweis: Gefüllter oder nicht gefüllter Spielschritt spielt hier keine Rolle!
	  speicherstandKopieren_P1(spielSchritt, (spielSchritt - 1U));
    }
    // Neue Spielerdaten einfüllen (immer auf Arrayplatz[0])
    speicherstandEinfuellen_P1();
  }

  if (PlayerManager_SpielerZweiAmZug())
  {
    // Alle Spielerdaten jeweils um einen Arrayplatz "nach oben" verschieben
    for (spielSchritt = (anzahlSpeicherstaende - 1U); spielSchritt > 1U; spielSchritt--)
    {
	  // Spielerdaten um einem Arrayplatz "nach oben" verschieben ([n-1]->[n], [n-2]->[n-1] bis [0]->[1])
	  // Hinweis: Gefüllter oder nicht gefüllter Spielschritt spielt hier keine Rolle!
	  speicherstandKopieren_P2(spielSchritt, (spielSchritt - 1U));
    }
    // Neue Spielerdaten einfüllen (immer auf Arrayplatz[0])
    speicherstandEinfuellen_P2();
  }
}

/* Prüft zuerst, wie viele gefüllte Spielschritte vorhanden sind welche "zurückgesetzt" werden können.
   Danach Spielerdaten um die Anzahl möglichen Arrayplätze "nach unten" verschieben und
   alle nicht definierten (neuen) Arrayplätze löschen, d.h. auf "nicht gefüllt" setzen.
   Zuletzt den aktuellen (veränderten) Spielstand auf Arrayplatz[0] den jeweiligen Modulen mitteilen.
----------------------------------------------------------------------------------*/
void Zeitreise_BuffAnwenden(void)
{
  uint8_t spielSchritt;
  uint8_t anzahlSchritteGefuellt;

  if (    (PlayerManager_SpielerEinsAmZug())
       || (PlayerManager_SpielerZweiAmZug())
     )
  {
    // Spieler 1: Anzahl gefüllte Spielschritte zählen und begrenzen
	anzahlSchritteGefuellt = 0U;
    for (spielSchritt = 0U; spielSchritt < (anzahlSpeicherstaende - 1U); spielSchritt++)
    {
      if (Speicherstand_P1[spielSchritt].SpielschrittGefuellt == true)
      {
        if (anzahlSchritteGefuellt < anzahlSchritteZurueck)
		{
          anzahlSchritteGefuellt++;
		}
      }
    }

	// Spieler 1: Spielerdaten "nach unten" verschieben
    for (spielSchritt = 0U; spielSchritt < (anzahlSpeicherstaende - 1U); spielSchritt++)
    {
	  if (spielSchritt < (anzahlSpeicherstaende - anzahlSchritteGefuellt))
	  {
	    // Spielerdaten um 'anzahlSchritteGefuellt' "nach unten" verschieben
        speicherstandKopieren_P1(spielSchritt, (spielSchritt + anzahlSchritteGefuellt));
	  }
	  else
	  {
	    // Restliche (nicht verschobene) Spielerdaten auf "nicht gefüllt" setzen
	    Speicherstand_P1[spielSchritt].SpielschrittGefuellt = false;
	  }
    }

    // Spieler 2: Anzahl gefüllte Spielschritte zählen und begrenzen
	anzahlSchritteGefuellt = 0U;
    for (spielSchritt = 0U; spielSchritt < (anzahlSpeicherstaende - 1U); spielSchritt++)
    {
      if (Speicherstand_P2[spielSchritt].SpielschrittGefuellt == true)
      {
        if (anzahlSchritteGefuellt < anzahlSchritteZurueck)
		{
          anzahlSchritteGefuellt++;
		}
      }
    }

	// Spieler 2: Spielerdaten "nach unten" verschieben
    for (spielSchritt = 0U; spielSchritt < (anzahlSpeicherstaende - 1U); spielSchritt++)
    {
	  if (spielSchritt < (anzahlSpeicherstaende - anzahlSchritteGefuellt))
	  {
	    // Spielerdaten um 'anzahlSchritteGefuellt' "nach unten" verschieben
        speicherstandKopieren_P2(spielSchritt, (spielSchritt + anzahlSchritteGefuellt));
	  }
	  else
	  {
	    // Restliche (nicht verschobene) Spielerdaten auf "nicht gefüllt" setzen
	    Speicherstand_P2[spielSchritt].SpielschrittGefuellt = false;
	  }
    }

    // Aktuelle Zeitreise-Daten an entsprechende Module weitergeben
    aktuelleSpielstaendeWeitergeben();
  }
}

/* Aktuelle Zeitreise-Daten von Spieler 1 vom Quell-Schritt in Ziel-Schritt kopieren
   Hinweis: Kopiert auch nicht gefüllte Spielschritte!
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
   Hinweis: Kopiert auch nicht gefüllte Spielschritte!
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

/* Neue Zeitreise-Daten von Spieler 1 in Arrayplatz[0] einfüllen
----------------------------------------------------------------------------------*/
static void speicherstandEinfuellen_P1(void)
{
  Speicherstand_P1[0U].SpielschrittGefuellt = true;
  Speicherstand_P1[0U].Figur1Pos = 0U;  // TODO getFigurPos
  Speicherstand_P1[0U].Figur2Pos = 0U; // TODO getFigurPos
  Speicherstand_P1[0U].FallePos = 0U; // TODO ... ?
  Speicherstand_P1[0U].EinsatzDepot = EinsatzSetzen_GetEinsatzDepot(SpielerEins);
  Speicherstand_P1[0U].Umweg1Aktiv = false; // TODO ... ?
  Speicherstand_P1[0U].Umweg2Aktiv = false; // TODO ... ?
  Speicherstand_P1[0U].Umweg3Aktiv = false; // TODO ... ?
  Speicherstand_P1[0U].SchildAktiv = PlayerManager_IsShieldActive(SpielerEins);
  Speicherstand_P1[0U].SpeedAktiv = PlayerManager_IsSpeedActive(SpielerEins);
  Speicherstand_P1[0U].AussetzenAktiv = PlayerManager_IsAussetzenActive(SpielerZwei); // fragt gegenspieler ab
  Speicherstand_P1[0U].EinsatzSetzenAktiv = PlayerManager_IsEinsatzSetzenActive(SpielerEins);
  Speicherstand_P1[0U].GewinnGarantiertAktiv = PlayerManager_IsGewinnGarantiertActive(SpielerEins);
}

/* Neue Zeitreise-Daten von Spieler 2 in Arrayplatz[0] einfüllen
----------------------------------------------------------------------------------*/
static void speicherstandEinfuellen_P2(void)
{
  Speicherstand_P2[0U].SpielschrittGefuellt = true;
  Speicherstand_P2[0U].Figur1Pos = 0U;  // TODO getFigurPos
  Speicherstand_P2[0U].Figur2Pos = 0U; // TODO getFigurPos
  Speicherstand_P2[0U].FallePos = 0U; // TODO ... ?
  Speicherstand_P2[0U].EinsatzDepot = EinsatzSetzen_GetEinsatzDepot(SpielerZwei);
  Speicherstand_P2[0U].Umweg1Aktiv = false; // TODO ... ?
  Speicherstand_P2[0U].Umweg2Aktiv = false; // TODO ... ?
  Speicherstand_P2[0U].Umweg3Aktiv = false; // TODO ... ?
  Speicherstand_P2[0U].SchildAktiv = PlayerManager_IsShieldActive(SpielerZwei);
  Speicherstand_P2[0U].SpeedAktiv = PlayerManager_IsSpeedActive(SpielerZwei);
  Speicherstand_P2[0U].AussetzenAktiv = PlayerManager_IsAussetzenActive(SpielerEins); // fragt gegenspieler ab
  Speicherstand_P2[0U].EinsatzSetzenAktiv = PlayerManager_IsEinsatzSetzenActive(SpielerZwei);
  Speicherstand_P2[0U].GewinnGarantiertAktiv = PlayerManager_IsGewinnGarantiertActive(SpielerZwei);
}

/* Aktuelle Zeitreise-Daten an entsprechende Module weitergeben
----------------------------------------------------------------------------------*/
static void aktuelleSpielstaendeWeitergeben(void)
{
  /* TODO Aktuellen Stand weitergeben ???
  Speicherstand_P1[0U].Figur1Pos;
  Speicherstand_P2[0U].Figur1Pos;
  Speicherstand_P1[0U].Figur2Pos;
  Speicherstand_P2[0U].Figur2Pos;
  Speicherstand_P1[0U].FallePos;
  Speicherstand_P2[0U].FallePos;
  */
  //--------------------------------------------------------
  EinsatzSetzen_SetEinsatzDepot(SpielerEins, Speicherstand_P1[0U].EinsatzDepot);
  EinsatzSetzen_SetEinsatzDepot(SpielerZwei, Speicherstand_P2[0U].EinsatzDepot);
  //--------------------------------------------------------
  /* TODO Aktuellen Stand weitergeben ???
  Speicherstand_P1[0U].Umweg1Aktiv;
  Speicherstand_P2[0U].Umweg1Aktiv;
  Speicherstand_P1[0U].Umweg2Aktiv;
  Speicherstand_P2[0U].Umweg2Aktiv;
  Speicherstand_P1[0U].Umweg3Aktiv;
  Speicherstand_P2[0U].Umweg3Aktiv;
  */
  //--------------------------------------------------------
  if (Speicherstand_P1[0U].SchildAktiv)
  {
    PlayerManager_ActivateShield(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateShield(SpielerEins);
  }
  if (Speicherstand_P2[0U].SchildAktiv)
  {
    PlayerManager_ActivateShield(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateShield(SpielerZwei);
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0U].SpeedAktiv)
  {
    PlayerManager_ActivateSpeed(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateSpeed(SpielerEins);
  }
  if (Speicherstand_P2[0U].SpeedAktiv)
  {
    PlayerManager_ActivateSpeed(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateSpeed(SpielerZwei);
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0U].AussetzenAktiv)
  {
    PlayerManager_ActivateAussetzen(SpielerZwei); // setzt für gegenspieler
  }
  else
  {
    PlayerManager_DeActivateAussetzen(SpielerZwei); // setzt für gegenspieler
  }
  if (Speicherstand_P2[0U].AussetzenAktiv)
  {
    PlayerManager_ActivateAussetzen(SpielerEins); // setzt für gegenspieler
  }
  else
  {
    PlayerManager_DeActivateAussetzen(SpielerEins); // setzt für gegenspieler
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0U].EinsatzSetzenAktiv)
  {
    PlayerManager_ActivateEinsatzSetzen(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateEinsatzSetzen(SpielerEins);
  }
  if (Speicherstand_P2[0U].EinsatzSetzenAktiv)
  {
    PlayerManager_ActivateEinsatzSetzen(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateEinsatzSetzen(SpielerZwei);
  }
  //--------------------------------------------------------
  if (Speicherstand_P1[0U].GewinnGarantiertAktiv)
  {
    PlayerManager_ActivateGewinnGarantiert(SpielerEins);
  }
  else
  {
    PlayerManager_DeActivateGewinnGarantiert(SpielerEins);
  }
  if (Speicherstand_P2[0U].GewinnGarantiertAktiv)
  {
    PlayerManager_ActivateGewinnGarantiert(SpielerZwei);
  }
  else
  {
    PlayerManager_DeActivateGewinnGarantiert(SpielerZwei);
  }
}

void Zeitreise_DebugSituationErstellen (void)
{
  for (uint8_t i = 0U; i < (anzahlSpeicherstaende - 1U); i++)
  {
  Speicherstand_P1[i].SpielschrittGefuellt = true;
  Speicherstand_P1[i].Figur1Pos = i * 2;
  Speicherstand_P1[i].Figur2Pos = i;
  Speicherstand_P1[i].FallePos = 0;
  Speicherstand_P1[i].EinsatzDepot = 30-i;
  Speicherstand_P1[i].Umweg1Aktiv = false;
  Speicherstand_P1[i].Umweg2Aktiv = false;
  Speicherstand_P1[i].Umweg3Aktiv = true;
  Speicherstand_P1[i].SchildAktiv = true;
  Speicherstand_P1[i].SpeedAktiv = false;
  Speicherstand_P1[i].AussetzenAktiv = false;
  Speicherstand_P1[i].EinsatzSetzenAktiv = true;
  Speicherstand_P1[i].GewinnGarantiertAktiv = false;

  Speicherstand_P2[i].SpielschrittGefuellt = true;
  Speicherstand_P2[i].Figur1Pos = i +5;
  Speicherstand_P2[i].Figur2Pos = i;
  Speicherstand_P2[i].FallePos = 0;
  Speicherstand_P2[i].EinsatzDepot = 30 - 2*i;
  Speicherstand_P2[i].Umweg1Aktiv = true;
  Speicherstand_P2[i].Umweg2Aktiv = false;
  Speicherstand_P2[i].Umweg3Aktiv = false;
  Speicherstand_P2[i].SchildAktiv = true;
  Speicherstand_P2[i].SpeedAktiv = true;
  Speicherstand_P2[i].AussetzenAktiv = true;
  Speicherstand_P2[i].EinsatzSetzenAktiv = true;
  Speicherstand_P2[i].GewinnGarantiertAktiv = true;
  }
//LedTreiber_LedSchalten(192,Blau);
}
