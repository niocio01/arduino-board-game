#ifndef MESSAGES_H
#define MESSAGES_H

#include "GlobalTypes.h"

struct Messages_values {
  int AnzFelder;          // Anzeige Anzahl Felder vorwärts
  char MiniGameName[16];  // Name eines Minigames zum Anzeigen
  int  ValEinsatz;      // Gewählter Einsatz für das Minigames
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
  MSG_Minigame_Reaktion,
  MSG_Minigame_Simon,
  MSG_Minigame_ToneMaster,
  MSG_Minigame_QuickFinger,
  MSG_Minigame_FastCounter,
  MSG_Minigame_Timing,
  MSG_Startup_Taster_Fail,
  MSG_Einsatz_waehlen,
  MSG_Gegner_bestimmt_Einsatz,
  MSGxx_Einsatz_Punkte,
  MSGxx_Einsatz_Punkte_FuerGegner,
  MSG_Einsatz_fuer_Gegner,
  MSG_Win,
  MSG_Lose,
  MSG_Tie,
  MSG_Next_Round,
  MSG_Sequenz,
  MSG_Sequenz_Fehler,
  MSG_GegnerSpielt,
  MSG_Rot_Licht_druecken,
  MSG_Zuhoeren,
  MSG_Gegner_hoert_zu,
  MSG_Frequenz,
  MSG_Schnell_druecken,
  MSGxx_Countdown,
  MSG_20_schnell_druecken,
  MSG_Taster_BL_bestaetigen,
  MSG_Stopp_Licht,
  MSGxx_Start_in,
  MSGxx_Endet_in,
  MSG_AktiveBuffsAnzeigen,
  MSG_KeineBuffsAktiv,
  MSG_Buff_Schild_Aktiv,
  MSG_Buff_Speed_Aktiv,
  MSG_Buff_Gewinn_Aktiv,
  MSG_Buff_EinsatzSetzen_Aktiv,
  MSG_Buff_Aussetzen_Aktiv
  } Messages_Nachrichten_t;

/*
 void Messages_ZeigeNachricht(
      GlobalTypes_Spieler_t spieler,                // Spieler Eins oder Zwei
      Messages_Nachrichten_t nachricht);            // Code für die Nachricht (siehe oben)
*/
void Messages_ZeigeNachricht(
    GlobalTypes_Spieler_t spieler,                  // Spieler Eins oder Zwei
    Messages_Nachrichten_t nachricht,               // Code für die Nachricht (siehe oben)
    Messages_values *MessageVal);   // Zusätzliche Werte gemäss obiger Struktur

#endif
