#ifndef MESSAGES_H
#define MESSAGES_H

#include "GlobalTypes.h"

struct Messages_values {
  int AnzFelder;          // Anzeige Anzahl Felder vorwärts
  char MiniGameName[40];  // Name eines Minigames zum Anzeigen
  int  ValEinsatz;        // Gewählter Einsatz für das Minigames
  int  ValPunkte;         // Noch vorhandene Punkte
  int  CountDown;         // Wert um CountDown anzuzeigen
};

typedef enum {
  MSG_Startup_OK,
  MSG_Startup_RFID_Fail,
  MSG_Welcome,
  MSG_Gegner_am_Zug,
  MSG_Karte_EndGame,
  MSG_Aussetzen,
  MSGxx_Felder_vorwaerts,
  MSG_Falle,
  MSG_Figur_retten,
  MSG_Feld_waehlen,
  MSG_Gegner_Schild,
  MSG_Buff_Falle,
  MSG_Schild_zerbrochen,
  MSG_Buff_Einsatz_bestimmen,
  MSG_Taster_GN_bestaetigen,
  MSG_Buff_Steinschlag,
  MSG_Steinschlag_Gebiet_waehlen,
  MSG_Buff_Speed,
  MSG_Buff_Gewinn,
  MSG_Buff_Aussetzen,
  MSG_Buff_Zeitreise,
  MSG_Buff_Mehr_Einsatz,
  MSG_Einsatz_erhoeht,
  MSG_Buff_Lucky,
  MSG_Buff_Schild,
  MSG_Startup_Taster_Fail,
  MSGxx_MinigameName,
  MSG_Einsatz_waehlen,
  MSG_Gegner_bestimmt_Einsatz,
  MSGxx_Einsatz_Punkte,
  MSG_Einsatz_fuer_Gegner,
  MSG_Win,
  MSG_Lose,
  MSG_Next_Round,
  MSG_Sequenz,
  MSG_Rot_Licht_druecken,
  MSG_Zuhoeren,
  MSG_Gegner_hoert_zu,
  MSG_Frequenz,
  MSG_Schnell_druecken,
  MSGxx_Countdown,
  MSG_20_schnell_druecken,
  MSG_Taster_BL_bestaetigen,
  MSG_Stopp_Licht }Messages_Nachrichten_t;

void Messages_ZeigeNachricht(
    GlobalTypes_Spieler_t spieler,                  // Spieler Eins oder Zwei
    Messages_Nachrichten_t nachricht,               // Code für die Nachricht (siehe oben)
    const struct Messages_values *MessageVal);   // Zusätzliche Werte gemäss obiger Struktur

#endif
