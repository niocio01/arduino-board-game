#include "Messages.h"
#include "Treiber/LcdTreiber.h"
#include "stdio.h"
#include "arduino.h"

struct Messages_values MessageValues;
const uint16_t updateIntervall = 200;
static uint16_t lastUpdateTime;



void Messages_ZeigeNachricht(GlobalTypes_Spieler_t spieler, Messages_Nachrichten_t nachricht)
{
  switch (nachricht)
  {
    case MSG_Startup_OK:
    LcdTreiber_DisplayMessage(spieler, (char *) "Startup:", (char *) "erfolgreich");
    break;

    case MSG_Startup_RFID_Fail:
    LcdTreiber_DisplayMessage(spieler, (char *) "Startup:", (char *) "RFID Fail");
    break;

    case MSG_Welcome:
    LcdTreiber_DisplayMessage(spieler, (char *) "Hallo bitte", (char *) "Taste druecken");
    break;

    case MSG_Gegner_am_Zug:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gegner ist", (char *) "am Zug");
    break;

    case MSG_Karte_EndGame:
    LcdTreiber_DisplayMessage(spieler, (char *) "Karte legen oder", (char *) "Spielzug beenden");
    break;

    case MSG_Aussetzen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Du musst", (char *) "aussetzen");
    break;

    case MSG_Falle:
    LcdTreiber_DisplayMessage(spieler, (char *) "Du bist in eine", (char *) "Falle getappt");
    break;

    case MSG_Figur_retten:
    LcdTreiber_DisplayMessage(spieler, (char *) "Rette deine", (char *) "Figur");
    break;

    case MSG_Feld_waehlen:
    LcdTreiber_DisplayMessage(spieler, (char *) "mit POT", (char *) "Feld wählen");
    break;

    case MSG_Gegner_Schild:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gegner hatte", (char *) "einen Schild");
    break;

    case MSG_Schild_zerbrochen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Schild", (char *) "zerbrochen");
    break;

    case MSG_Buff_Einsatz_bestimmen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Einsatz bestimmen");
    break;

    case MSG_Buff_Falle:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Falle stellen");
    break;

    case MSG_Taster_GN_bestaetigen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Taster(gruen)", (char *) "= bestaetigen");
    break;

    case MSG_Buff_Steinschlag:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Steinschlag");
    break;

    case MSG_Steinschlag_Gebiet_waehlen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gebiet auswaehlen", (char *) "");
    break;

    case MSG_Buff_Speed:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Speed");
    break;

    case MSG_Buff_Gewinn:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Gewinn garantiert");
    break;

    case MSG_Buff_Aussetzen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Aussetzen");
    break;

    case MSG_Buff_Zeitreise:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Zeitreise");
    break;

    case MSG_Buff_Mehr_Einsatz:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Mehr Einsatz");
    break;

    case MSG_Einsatz_erhoeht:
    LcdTreiber_DisplayMessage(spieler, (char *) "10 neue", (char *) "Minigamepunkte");
    break;

    case MSG_Buff_Lucky:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Lucky");
    break;

    case MSG_Buff_Schild:
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Schild");
    break;

    case MSG_Startup_Taster_Fail:
    LcdTreiber_DisplayMessage(spieler, (char *) "Startup:", (char *) "Taster Fail");
    break;

    case MSG_Einsatz_waehlen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Mit POT", (char *) "Einsatz wählen");
    break;

    case MSG_Gegner_bestimmt_Einsatz:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gegner bestimmt", (char *) "Einsatz");
    break;

    case MSG_Einsatz_fuer_Gegner:
    LcdTreiber_DisplayMessage(spieler, (char *) "Einsatz fuer", (char *) "Gegner setzen");
    break;

    case MSG_Win:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gewonnen", (char *) "");
    break;

    case MSG_Lose:
    LcdTreiber_DisplayMessage(spieler, (char *) "Verloren", (char *) "");
    break;

    case MSG_Next_Round:
    LcdTreiber_DisplayMessage(spieler, (char *) "Nächste Runde", (char *) "");
    break;

    case MSG_Sequenz:
    LcdTreiber_DisplayMessage(spieler, (char *) "Sequenz", (char *) "nachmachen");
    break;

    case MSG_Rot_Licht_druecken:
    LcdTreiber_DisplayMessage(spieler, (char *) "Bei rotem", (char *) "Licht druecken");
    break;

    case MSG_Zuhoeren:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gut zuhoeren!", (char *) "");
    break;

    case MSG_Gegner_hoert_zu:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gegner hoert zu", (char *) "");
    break;

    case MSG_Frequenz:
    LcdTreiber_DisplayMessage(spieler, (char *) "Mit POT Frequenz", (char *) "nachbilden");
    break;

    case MSG_Schnell_druecken:
    LcdTreiber_DisplayMessage(spieler, (char *) "Moeglichst schnell", (char *) "druecken in…");
    break;

    case MSG_20_schnell_druecken:
    LcdTreiber_DisplayMessage(spieler, (char *) "20 x schnell", (char *) "druecken in…");
    break;

    case MSG_Taster_BL_bestaetigen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Wenn fertig", (char *) "Blau druecken");
    break;

    case MSG_Stopp_Licht:
    LcdTreiber_DisplayMessage(spieler, (char *) "Licht in der", (char *) "Mitte stoppen");
    break;
  }
}


void Messages_ZeigeNachricht_Wert(GlobalTypes_Spieler_t spieler, Messages_Nachrichten_t nachricht, const struct Messages_values *MessageVal)
{
  if ((millis() - lastUpdateTime) > updateIntervall)
  {
    char Text1[41];
    char Text2[41];

    switch (nachricht)
    {
      case MSGxx_Felder_vorwaerts:
      sprintf(Text1, "%s %d", "es geht", MessageVal->AnzFelder);
      LcdTreiber_DisplayMessage(spieler, Text1, (char *) "Felder vorwaerts");
      break;

      case MSGxx_MinigameName:
      LcdTreiber_DisplayMessage(spieler, (char *) "Minigame:", MessageVal->MiniGameName);
      break;

      case MSGxx_Einsatz_Punkte:
      sprintf(Text1, "%s %d", "Einsatz:", MessageVal->ValEinsatz);
      sprintf(Text2, "%s %d", "Punke:", MessageVal->ValPunkte);
      LcdTreiber_DisplayMessage(spieler, Text1, Text2);
      break;

      case MSGxx_Countdown:
      sprintf(Text2, "%d", MessageVal->CountDown);
      LcdTreiber_DisplayMessage(spieler, (char *) "Countdown:", Text2);
      break;
    }
    lastUpdateTime = millis();
  }
}
