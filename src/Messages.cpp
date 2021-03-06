#include "Messages.h"
#include "Treiber/LcdTreiber.h"
#include "stdio.h"
#include "arduino.h"

struct Messages_values MessageValues;
const uint16_t updateIntervall = 20;
static uint32_t lastUpdateTime;



void Messages_ZeigeNachricht(GlobalTypes_Spieler_t spieler, Messages_Nachrichten_t nachricht, struct Messages_values *MessageVal)
{

  char Text1[16];
  char Text2[16];

  switch (nachricht)
  {
    case MSG_Startup_OK:
    LcdTreiber_DisplayMessage(spieler, (char *) "Startup:", (char *) "erfolgreich");
    break;

    case MSG_Startup_RFID_Fail:
    LcdTreiber_DisplayMessage(spieler, (char *) "Startup:", (char *) "Failed");
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
    LcdTreiber_DisplayMessage(spieler, (char *) "Buff:", (char *) "Einsatz setzen");
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

    case MSG_Minigame_Reaktion:
    LcdTreiber_DisplayMessage(spieler, (char *) "Minigame:", (char *) "Reaktion");
    break;

    case MSG_Minigame_Simon:
    LcdTreiber_DisplayMessage(spieler, (char *) "Minigame:", (char *) "Simon");
    break;

    case MSG_Minigame_ToneMaster:
    LcdTreiber_DisplayMessage(spieler, (char *) "Minigame:", (char *) "Tone Master");
    break;

    case MSG_Minigame_QuickFinger:
    LcdTreiber_DisplayMessage(spieler, (char *) "Minigame:", (char *) "Quick Finger");
    break;

    case MSG_Minigame_FastCounter:
    LcdTreiber_DisplayMessage(spieler, (char *) "Minigame:", (char *) "Fast Counter");
    break;

    case MSG_Minigame_Timing:
    LcdTreiber_DisplayMessage(spieler, (char *) "Minigame:", (char *) "Timing");
    break;

    case MSG_Startup_Taster_Fail:
    LcdTreiber_DisplayMessage(spieler, (char *) "Startup:", (char *) "Taster Fail");
    break;

    case MSG_Einsatz_waehlen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Mit Poti", (char *) "Einsatz waehlen");
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

    case MSG_Tie:
    LcdTreiber_DisplayMessage(spieler, (char *) "Unentschieden:", (char *) "nochmal spielen");
    break;

    case MSG_Next_Round:
    LcdTreiber_DisplayMessage(spieler, (char *) "Naechste Runde", (char *) "");
    break;

    case MSG_Sequenz:
    LcdTreiber_DisplayMessage(spieler, (char *) "Sequenz", (char *) "nachmachen");
    break;

    case MSG_Sequenz_Fehler:
    LcdTreiber_DisplayMessage(spieler, (char *) "Fehler", (char *) "gemacht");
    break;

    case MSG_GegnerSpielt:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gegner spielt", (char *) "jetzt");
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
    LcdTreiber_DisplayMessage(spieler, (char *) "Moeglichst", (char *) "schnell druecken");
    break;

    case MSG_20_schnell_druecken:
    LcdTreiber_DisplayMessage(spieler, (char *) "30 x schnell", (char *) "druecken");
    break;

    case MSG_Taster_BL_bestaetigen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Wenn fertig", (char *) "Blau druecken");
    break;

    case MSG_Stopp_Licht:
    LcdTreiber_DisplayMessage(spieler, (char *) "Licht in der", (char *) "Mitte stoppen");
    break;

    case MSG_AktiveBuffsAnzeigen:
    LcdTreiber_DisplayMessage(spieler, (char *) "Aktive Buffs mit", (char *) "Poti ansehen");
    break;

    case MSG_KeineBuffsAktiv:
    LcdTreiber_DisplayMessage(spieler, (char *) "Keine Buffs", (char *) "Aktiv");
    break;

    case MSG_Buff_Schild_Aktiv:
    LcdTreiber_DisplayMessage(spieler, (char *) "Schild", (char *) "");
    break;

    case MSG_Buff_Speed_Aktiv:
    LcdTreiber_DisplayMessage(spieler, (char *) "Speed", (char *) "");
    break;

    case MSG_Buff_Gewinn_Aktiv:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gewinn", (char *) "garantiert");
    break;

    case MSG_Buff_EinsatzSetzen_Aktiv:
    LcdTreiber_DisplayMessage(spieler, (char *) "Einsatz setzen", (char *) "");
    break;

    case MSG_Buff_Aussetzen_Aktiv:
    LcdTreiber_DisplayMessage(spieler, (char *) "Aussetzen", (char *) "");
    break;

    case MSG_Gegner_WaehltFigur:
    LcdTreiber_DisplayMessage(spieler, (char *) "Gegner bewegt", (char *) "seine Figur");
    break;



    case MSGxx_Felder_vorwaerts:
    if ((millis() - lastUpdateTime) > updateIntervall)
    {
      sprintf(Text1, "%d %s", MessageVal->AnzFelder, "Felder vor");
      LcdTreiber_DisplayMessage(spieler, Text1, (char *) "Figur auswaehlen");
      lastUpdateTime = millis();
    }
    break;

    case MSGxx_Einsatz_Punkte:
    if ((millis() - lastUpdateTime) > updateIntervall)
    {
      sprintf(Text1, "%s %d", "Einsatz:", MessageVal->ValEinsatz);
      sprintf(Text2, "%s %d", "Punkte:", MessageVal->ValPunkte);
      LcdTreiber_DisplayMessage(spieler, Text1, Text2);
      lastUpdateTime = millis();
    }
    break;

    case MSGxx_Einsatz_Punkte_FuerGegner:
    if ((millis() - lastUpdateTime) > updateIntervall)
    {
      sprintf(Text1, "%s %d", "Einsatz:", MessageVal->ValEinsatz);
      LcdTreiber_DisplayMessage(spieler, Text1, (char *) "Punkte: XX");
      lastUpdateTime = millis();
    }
    break;

    case MSGxx_Countdown:
    sprintf(Text2, "%d", MessageVal->CountDown);
    LcdTreiber_DisplayMessage(spieler, (char *) "Countdown:", Text2);
    break;

    case MSGxx_Start_in:
    sprintf(Text2, "%d", MessageVal->CountDown);
    LcdTreiber_DisplayMessage(spieler, (char *) "Start in:", Text2);
    break;

    case MSGxx_Endet_in:
    sprintf(Text2, "%d", MessageVal->CountDown);
    LcdTreiber_DisplayMessage(spieler, (char *) "Game endet in:", Text2);
    break;
  }
}
