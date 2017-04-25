#include "SpielfeldLed.h"
#include "LedTreiber.h"
#include <arduino.h>
#include "inttypes.h"

// Daten mit den Anzahl Schritten in den Teilsegmenten
struct SpielfeldData SF_dataPlayer1[SF_MaxSegm];
struct SpielfeldData SF_dataPlayer2[SF_MaxSegm];

struct FigureData SF_Player1_Figure1;
struct FigureData SF_Player1_Figure2;
struct FigureData SF_Player2_Figure1;
struct FigureData SF_Player2_Figure2;

int SF_Player1_Kreis[SF_K_Steps];
int SF_Player2_Kreis[SF_K_Steps];

uint16_t SF_LedWeg[SF_MAX_STEPS];

const uint8_t SF_DIM_helligkeit = 5;
const uint32_t SF_UpdateDelayS = 750;    // "Wanderzeit" LEDs im Spiel in ms
const uint32_t SF_UpdateDelayF = 1;     // "Wanderzeit" der LEDs im Lauflicht
uint32_t SF_OldTimeS;
uint32_t SF_OldTimeF;


GlobalTypes_Spieler_t SF_ActSpieler;
GlobalTypes_Figur_t SF_ActFigur;
bool SF_FigureMoving = false;
bool SF_Player1Fig1Aktiv = false;
bool SF_Player2Fig1Aktiv = false;

GlobalTypes_Farbe_t SF_LauflichtFarbe;
uint8_t SF_LauflichtHelligkeit;
bool SF_LauflichtAktiv;
int SF_LauflichtCounter;


// Kommentar siehe Headerfile
// **************************
void SF_InitData(void)
{
  // Spielfeld Teil Spieler 1
  SF_dataPlayer1[SF_SegmVB1].Steps = 11;          // Segment bis Branch 1
  SF_dataPlayer1[SF_SegmVB1].StartID = 0;         // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmIB1].Steps = 4;           // Kürzeres Segment bei Branch 1
  SF_dataPlayer1[SF_SegmIB1].StartID = 11;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmB1].Steps = 8;            // Längeres Segment bei Branch 1
  SF_dataPlayer1[SF_SegmB1].StartID = 161;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmVB2].Steps = 9;           // Segment bis Branch 2
  SF_dataPlayer1[SF_SegmVB2].StartID = 15;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmIB2].Steps = 4;           // Kürzeres Segment bei Branch 2
  SF_dataPlayer1[SF_SegmIB2].StartID = 24;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmB2].Steps = 10;           // Längeres Segment bei Branch 2
  SF_dataPlayer1[SF_SegmB2].StartID = 169;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmVB3].Steps = 11;          // Segment bis Branch 3
  SF_dataPlayer1[SF_SegmVB3].StartID = 28;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmIB3].Steps = 4;           // Kürzeres Segment bei Branch 3
  SF_dataPlayer1[SF_SegmIB3].StartID = 40;        // Start ID Hardware zu LED's oben *** Anstelle 40 vermutlich 39
  SF_dataPlayer1[SF_SegmB3].Steps = 13;           // Längeres Segment bei Branch 3
  SF_dataPlayer1[SF_SegmB3].StartID = 179;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmVK].Steps = 19;           // Segment bis zum Kreis
  SF_dataPlayer1[SF_SegmVK].StartID = 44;         // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmK].Steps = SF_K_Steps;    // Segment im Kreis

  // Spielfeld Teil Spieler 2
  SF_dataPlayer2[SF_SegmVB1].Steps = 9;           // Segment bis Branch 1
  SF_dataPlayer2[SF_SegmVB1].StartID = 62;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmIB1].Steps = 5;           // Kürzeres Segment bei Branch 1
  SF_dataPlayer2[SF_SegmIB1].StartID = 71;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmB1].Steps = 14;           // Längeres Segment bei Branch 1
  SF_dataPlayer2[SF_SegmB1].StartID = 124;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmVB2].Steps = 6;           // Segment bis Branch 2
  SF_dataPlayer2[SF_SegmVB2].StartID = 76;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmIB2].Steps = 7;           // Kürzeres Segment bei Branch 2
  SF_dataPlayer2[SF_SegmIB2].StartID = 82;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmB2].Steps = 11;           // Längeres Segment bei Branch 2
  SF_dataPlayer2[SF_SegmB2].StartID = 138;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmVB3].Steps = 9;           // Segment bis Branch 3
  SF_dataPlayer2[SF_SegmVB3].StartID = 89;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmIB3].Steps = 6;           // Kürzeres Segment bei Branch 3
  SF_dataPlayer2[SF_SegmIB3].StartID = 98;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmB3].Steps = 12;           // Längeres Segment bei Branch 3
  SF_dataPlayer2[SF_SegmB3].StartID = 149;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmVK].Steps = 20;           // Segment bis zum Kreis
  SF_dataPlayer2[SF_SegmVK].StartID = 104;        // Start ID Hardware zu LED's oben
  SF_dataPlayer2[SF_SegmK].Steps = SF_K_Steps;    // Segment im Kreis

  // Spielfeld Teil Kreis
  SF_Player1_Kreis[0] = 240;
  SF_Player1_Kreis[1] = 239;
  SF_Player1_Kreis[2] = 238;
  SF_Player1_Kreis[3] = 237;
  SF_Player1_Kreis[4] = 236;
  SF_Player1_Kreis[5] = 235;
  SF_Player1_Kreis[6] = 234;
  SF_Player1_Kreis[7] = 233;
  SF_Player1_Kreis[8] = 232;
  SF_Player1_Kreis[9] = 231;
  SF_Player1_Kreis[10] = 230;
  SF_Player1_Kreis[11] = 214;
  SF_Player1_Kreis[12] = 202;
  SF_Player1_Kreis[13] = 203;
  SF_Player1_Kreis[14] = 204;
  SF_Player1_Kreis[15] = 205;
  SF_Player1_Kreis[16] = 206;
  SF_Player1_Kreis[17] = 196;
  SF_Player1_Kreis[18] = 192;

  SF_Player2_Kreis[0] = 252;
  SF_Player2_Kreis[1] = 251;
  SF_Player2_Kreis[2] = 250;
  SF_Player2_Kreis[3] = 249;
  SF_Player2_Kreis[4] = 248;
  SF_Player2_Kreis[5] = 247;
  SF_Player2_Kreis[6] = 246;
  SF_Player2_Kreis[7] = 245;
  SF_Player2_Kreis[8] = 244;
  SF_Player2_Kreis[9] = 243;
  SF_Player2_Kreis[10] = 242;
  SF_Player2_Kreis[11] = 222;
  SF_Player2_Kreis[12] = 208;
  SF_Player2_Kreis[13] = 209;
  SF_Player2_Kreis[14] = 210;
  SF_Player2_Kreis[15] = 211;
  SF_Player2_Kreis[16] = 212;
  SF_Player2_Kreis[17] = 200;
  SF_Player2_Kreis[18] = 192;

  SF_OldTimeS = millis();
  SF_OldTimeF = millis();
}


// Kommentar siehe Headerfile
// **************************
bool SF_StartDim(uint8_t Helligkeit)
{
  int Segment;
  int i;
  uint16_t id;

  // Alle LED's Player 1 auf StartDim setzen
  for (Segment = 0; Segment < SF_MaxSegm; Segment++)
  {
    for (id = SF_dataPlayer1[Segment].StartID, i = 0; i < SF_dataPlayer1[Segment].Steps; i++, id++)
    {
      LedTreiber_LedSetzen(id, Weiss, Helligkeit);
    }
    //LedTreiber_LedAnzeigen();
  }

  // Alle LED's Player 2 auf StartDim setzen
  for (Segment = 0; Segment < SF_MaxSegm; Segment++)
  {
    for (id = SF_dataPlayer2[Segment].StartID, i = 0; i < SF_dataPlayer2[Segment].Steps; i++, id++)
    {
      LedTreiber_LedSetzen(id, Weiss, Helligkeit);
    }
    //LedTreiber_LedAnzeigen();
  }

  // Alle LED's des Kreises setzen
  for (id = SF_K_StartID, i = 0; i < SF_K_TotSteps; i++, id++)
  {
    LedTreiber_LedSetzen(id, Weiss, Helligkeit);
  }

  LedTreiber_LedAnzeigen();
  return(true);
}


// Kommentar siehe Headerfile
// **************************
void SF_StartLauflicht(GlobalTypes_Farbe_t farbe, uint8_t helligkeit)
{
  SF_LauflichtFarbe = farbe;
  SF_LauflichtHelligkeit = helligkeit;
  SF_LauflichtCounter = 0;
  SF_LauflichtAktiv = true;

}// end of SF_StartLauflicht()


// Kommentar siehe Headerfile
// **************************
bool SF_LauflichtAmLaufen(void)
{
  return(SF_LauflichtAktiv);
}// end of SF_LauflichtEnded()


// Kommentar siehe Headerfile
// **************************
void SF_FiguresSetToStart(void)
{
  SF_Player1_Figure1.ActPos = 0;
  SF_Player1_Figure1.NewPos = 0;
  SF_Player1_Figure1.ActLEDid = SF_dataPlayer1[0].StartID;
  SF_Player1_Figure2.ActPos = 0;
  SF_Player1_Figure2.NewPos = 0;
  SF_Player1_Figure2.ActLEDid = SF_dataPlayer1[0].StartID;

  SF_Player2_Figure1.ActPos = 0;
  SF_Player2_Figure1.NewPos = 0;
  SF_Player2_Figure1.ActLEDid = SF_dataPlayer2[0].StartID;
  SF_Player2_Figure2.ActPos = 0;
  SF_Player2_Figure2.NewPos = 0;
  SF_Player2_Figure2.ActLEDid = SF_dataPlayer2[0].StartID;
}// end of SF_FiguresSetToStart()


// Kommentar siehe Headerfile
// **************************
void SF_MovePlayerFigure(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur)
{
  SF_ActSpieler = Spieler;
  SF_ActFigur = Figur;
  SF_FigureMoving = false;

  if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureEins)) {
    if (SF_Player1_Figure1.NewPos > SF_Player1_Figure1.ActPos) {
      SF_FigureMoving = true;
    }
  }
  if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureZwei)) {
    if (SF_Player1_Figure2.NewPos > SF_Player1_Figure2.ActPos) {
      SF_FigureMoving = true;
    }
  }
  if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureEins)) {
    if (SF_Player2_Figure1.NewPos > SF_Player2_Figure1.ActPos) {
      SF_FigureMoving = true;
    }
  }
  if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureZwei)) {
    if (SF_Player2_Figure2.NewPos > SF_Player2_Figure2.ActPos) {
      SF_FigureMoving = true;
    }
  }

  if(SF_FigureMoving == true)
  {
    SF_CalcPlayerWay(SF_ActSpieler, SF_ActFigur);
  }
}// end of SF_MovePlayerFigure()


// Kommentar siehe Headerfile
// **************************
bool SF_PlayerFigureHasMoved(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur)
{
  bool RetVal = false;

  if ((Spieler == SpielerEins) && (Figur == FigureEins)) {
    if (SF_Player1_Figure1.NewPos == SF_Player1_Figure1.ActPos) {
      RetVal = true;
    }
  }
  if ((Spieler == SpielerEins) && (Figur == FigureZwei)) {
    if (SF_Player1_Figure2.NewPos == SF_Player1_Figure2.ActPos) {
      RetVal = true;
    }
  }
  if ((Spieler == SpielerZwei) && (Figur == FigureEins)) {
    if (SF_Player2_Figure1.NewPos == SF_Player2_Figure1.ActPos) {
      RetVal = true;
    }
  }
  if ((Spieler == SpielerZwei) && (Figur == FigureZwei)) {
    if (SF_Player2_Figure2.NewPos == SF_Player2_Figure2.ActPos) {
      RetVal = true;
    }
  }

  return(RetVal);
}// end of SF_PlayerFigureHasMoved()


// Kommentar siehe Headerfile
// **************************
void SF_OperateSpielfeld_Main(void)
{

  // LED im Spielfeld abhängig von Spieler und Figur anzeigen
  // Update erfolgt alle SF_UpdateDelayS ms
  if ((millis() - SF_OldTimeS) > SF_UpdateDelayS)
  {
    SF_OldTimeS = millis();

    if(SF_FigureMoving)
    {
      // Alte Position löschen
      // ---------------------
      if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureEins)) {
        LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid, Weiss, SF_DIM_helligkeit);
      }
      if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureZwei)) {
        LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid, Weiss, SF_DIM_helligkeit);
      }
      if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureEins)) {
        LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid, Weiss, SF_DIM_helligkeit);
      }
      if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureZwei)) {
        LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid, Weiss, SF_DIM_helligkeit);
      }

      // Neue Position setzten
      // ---------------------
      if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureEins))
      {
        SF_Player1_Figure1.ActPos++;
        SF_Player1_Figure1.ActLEDid = SF_LedWeg[SF_Player1_Figure1.ActPos];
        SF_Player1Fig1Aktiv = true;
      }
      if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureZwei))
      {
        SF_Player1_Figure2.ActPos++;
        SF_Player1_Figure2.ActLEDid = SF_LedWeg[SF_Player1_Figure2.ActPos];
        SF_Player1Fig1Aktiv = false;
      }
      if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureEins))
      {
        SF_Player2_Figure1.ActPos++;
        SF_Player2_Figure1.ActLEDid = SF_LedWeg[SF_Player2_Figure1.ActPos];
        SF_Player2Fig1Aktiv = true;
      }
      if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureZwei))
      {
        SF_Player2_Figure2.ActPos++;
        SF_Player2_Figure2.ActLEDid = SF_LedWeg[SF_Player2_Figure2.ActPos];
        SF_Player2Fig1Aktiv = false;
      }

      // Kontrolle ob Moving abgeschlossen
      // ---------------------------------
      if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureEins))
      {
        if(SF_Player1_Figure1.ActPos >= SF_Player1_Figure1.NewPos) { SF_FigureMoving = false; }
      }
      if ((SF_ActSpieler == SpielerEins) && (SF_ActFigur == FigureZwei))
      {
        if(SF_Player1_Figure2.ActPos >= SF_Player1_Figure2.NewPos) { SF_FigureMoving = false; }
      }
      if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureEins))
      {
        if(SF_Player2_Figure1.ActPos >= SF_Player2_Figure1.NewPos) { SF_FigureMoving = false; }
      }
      if ((SF_ActSpieler == SpielerZwei) && (SF_ActFigur == FigureZwei))
      {
        if(SF_Player2_Figure2.ActPos >= SF_Player2_Figure2.NewPos) { SF_FigureMoving = false; }
      }
    }// end of if(SF_FigureMoving)


    // Anzeige LED Player 1
    // ------------------------------------------------
    if(SF_Player1_Figure1.ActLEDid == SF_Player1_Figure2.ActLEDid)
    {
      if(SF_Player1Fig1Aktiv == true)
      {
        SF_Player1Fig1Aktiv = false;
        LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid,
          SF_Player1_Figure1.Farbe,
          SF_Player1_Figure1.Helligkeit);
        }
        else
        {
          SF_Player1Fig1Aktiv = true;
          LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid,
            SF_Player1_Figure2.Farbe,
            SF_Player1_Figure2.Helligkeit);
          }
        }
        else
        {
          LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid,
            SF_Player1_Figure1.Farbe,
            SF_Player1_Figure1.Helligkeit);

            LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid,
              SF_Player1_Figure2.Farbe,
              SF_Player1_Figure2.Helligkeit);
            }


            // Anzeige LED Player 2
            // ------------------------------------------------
            if(SF_Player2_Figure1.ActLEDid == SF_Player2_Figure2.ActLEDid)
            {
              if(SF_Player2Fig1Aktiv == true)
              {
                SF_Player2Fig1Aktiv = false;
                LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid,
                  SF_Player2_Figure1.Farbe,
                  SF_Player2_Figure1.Helligkeit);
                }
                else
                {
                  SF_Player2Fig1Aktiv = true;
                  LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid,
                    SF_Player2_Figure2.Farbe,
                    SF_Player2_Figure2.Helligkeit);
                  }
                }
                else
                {
                  LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid,
                    SF_Player2_Figure1.Farbe,
                    SF_Player2_Figure1.Helligkeit);

                    LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid,
                      SF_Player2_Figure2.Farbe,
                      SF_Player2_Figure2.Helligkeit);
                    }

                    // Wechselanzeige beim Ziel noch regeln
                    // ------------------------------------
                    // ?????????????????????????????

                  }

                  // LED Lauflicht durchlaufen
                  // Update erfolgt alle SF_UpdateDelayF ms
                  if ((millis() - SF_OldTimeF) > SF_UpdateDelayF)
                  {
                    SF_OldTimeF = millis();

                    if(SF_LauflichtAktiv == true)
                    {
                      if(SF_LauflichtCounter >= SF_TOT_LEDS)
                      {
                        LedTreiber_LedSetzen(SF_LauflichtCounter-1, Weiss, SF_DIM_helligkeit);
                        SF_LauflichtAktiv = false;
                      }
                      else
                      {
                        if (SF_LauflichtCounter > 0)
                        {
                          LedTreiber_LedSetzen(SF_LauflichtCounter-1, Weiss, SF_DIM_helligkeit);
                        }
                        LedTreiber_LedSetzen(SF_LauflichtCounter,
                          SF_LauflichtFarbe,
                          SF_LauflichtHelligkeit);
                          SF_LauflichtCounter++;
                        }
                        LedTreiber_LedAnzeigen();
                      }
                    }

                  }// end of SF_OperateSpielfeld_Main()


                  // Kommentar siehe Headerfile
                  // **************************
                  void SF_CalcPlayerWay(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur)
                  {
                    int Pos;
                    int i;
                    bool BranchOn1, BranchOn2, BranchOn3;
                    struct SpielfeldData SF_dataPlayer[SF_MaxSegm];

                    // Daten abhängig ob Spieler 1 oder 2
                    for (i = 0; i < SF_MaxSegm; i++)
                    {
                      if(Spieler == SpielerEins)
                      {
                        SF_dataPlayer[i].Steps = SF_dataPlayer1[i].Steps;
                        SF_dataPlayer[i].StartID = SF_dataPlayer1[i].StartID;
                      }
                      else
                      {
                        SF_dataPlayer[i].Steps = SF_dataPlayer2[i].Steps;
                        SF_dataPlayer[i].StartID = SF_dataPlayer2[i].StartID;
                      }
                    }

                    // Merken ob Branch eingeschaltet ist oder nicht
                    if ((Spieler == SpielerEins) && (Figur == FigureEins)) {
                      BranchOn1 = SF_Player1_Figure1.BranchOn1;
                      BranchOn2 = SF_Player1_Figure1.BranchOn2;
                      BranchOn3 = SF_Player1_Figure1.BranchOn3;
                    }
                    if ((Spieler == SpielerEins) && (Figur == FigureZwei)) {
                      BranchOn1 = SF_Player1_Figure2.BranchOn1;
                      BranchOn2 = SF_Player1_Figure2.BranchOn2;
                      BranchOn3 = SF_Player1_Figure2.BranchOn3;
                    }
                    if ((Spieler == SpielerZwei) && (Figur == FigureEins)) {
                      BranchOn1 = SF_Player2_Figure1.BranchOn1;
                      BranchOn2 = SF_Player2_Figure1.BranchOn2;
                      BranchOn3 = SF_Player2_Figure1.BranchOn3;
                    }
                    if ((Spieler == SpielerZwei) && (Figur == FigureZwei)) {
                      BranchOn1 = SF_Player2_Figure2.BranchOn1;
                      BranchOn2 = SF_Player2_Figure2.BranchOn2;
                      BranchOn3 = SF_Player2_Figure2.BranchOn3;
                    }

                    // Segment vor Branch 1 abfüllen
                    Pos = 0;
                    for (i = 0; i < SF_dataPlayer[SF_SegmVB1].Steps; i++, Pos++)
                    {
                      SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmVB1].StartID + i;
                    }

                    // Segment Branch 1 innen/aussen abfüllen
                    if (BranchOn1 == true)
                    {
                      for (i = 0; i < SF_dataPlayer[SF_SegmB1].Steps; i++, Pos++) {
                        SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmB1].StartID + i;
                      }
                    }
                    else
                    {
                      for (i = 0; i < SF_dataPlayer[SF_SegmIB1].Steps; i++, Pos++) {
                        SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmIB1].StartID + i;
                      }
                    }

                    // Segment vor Branch 2 berechnen
                    for (i = 0; i < SF_dataPlayer[SF_SegmVB2].Steps; i++, Pos++)
                    {
                      SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmVB2].StartID + i;
                    }

                    // Segment Branch2 innen/aussen berechnen
                    if (BranchOn2 == true)
                    {
                      for (i = 0; i < SF_dataPlayer[SF_SegmB2].Steps; i++, Pos++) {
                        SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmB2].StartID + i;
                      }
                    }
                    else
                    {
                      for (i = 0; i < SF_dataPlayer[SF_SegmIB2].Steps; i++, Pos++) {
                        SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmIB2].StartID + i;
                      }
                    }

                    // Segment vor Branch 3 berechnen
                    for (i = 0; i < SF_dataPlayer[SF_SegmVB3].Steps; i++, Pos++)
                    {
                      SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmVB3].StartID + i;
                    }

                    // Segment Branch3 innen/aussen berechnen
                    if (BranchOn3 == true)
                    {
                      for (i = 0; i < SF_dataPlayer[SF_SegmB3].Steps; i++, Pos++) {
                        SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmB3].StartID + i;
                      }
                    }
                    else
                    {
                      for (i = 0; i < SF_dataPlayer[SF_SegmIB3].Steps; i++, Pos++) {
                        SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmIB3].StartID + i;
                      }
                    }

                    // Segment vor Kreis berechnen
                    for (i = 0; i < SF_dataPlayer[SF_SegmVK].Steps; i++, Pos++)
                    {
                      SF_LedWeg[Pos] = SF_dataPlayer[SF_SegmVK].StartID + i;
                    }

                    // Segment im Kreis berechnen
                    for (i = 0; i < SF_dataPlayer[SF_SegmK].Steps; i++, Pos++)
                    {
                      if (Spieler == SpielerEins)
                      {
                        SF_LedWeg[Pos] = SF_Player1_Kreis[i];
                      }
                      else
                      {
                        SF_LedWeg[Pos] = SF_Player2_Kreis[i];
                      }
                    }
                  }// end of SF_CalcPlayerWay()


/*  Beispiel auskommentiert
void beispiel()
{
  int caseVal = 0;
  bool isInit = false;
  const int START = 0;
  const int READY = 10;
  const int WAIT = 20;
  const int MOVE = 30;

  switch(caseVal)
  {
    case START:
      SF_InitData();
      isInit = true;
      casVal = READY;
    break;

    case READY:
      if(Taste ist gedrückt)
      {
        SF_StartLauflicht(Farbe, 25);
        caseVAL = WAIT;
      }
    break;

    case WAIT:
      if(SF_LauflichtAmLaufen == false)
      {
        Player1_Figure1.NewPos = Player1_Figure2.NewPos = Player2_Figure1.NewPos = Player2_Figure2.NewPos =0;
        Player1_Figure1.Farbe = Farbe1;
        Player1_Figure2.Farbe = Farbe2;
        Player2_Figure1.Farbe = Farbe3;
        Player2_Figure2.Farbe = Farbe4;
        Player1_Figure1.Helligkeit = Player1_Figure2.Helligkeit = Player2_Figure1.Helligkeit = Player2_Figure2.Helligkeit = 12;
        Player1_Figure1.BranchOn1 = Player1_Figure2.BranchOn1 = Player2_Figure1.BranchOn1 = Player2_Figure2.BranchOn1 = false;
        Player1_Figure1.BranchOn2 = Player1_Figure2.BranchOn2 = Player2_Figure1.BranchOn2 = Player2_Figure2.BranchOn2 = false;
        Player1_Figure1.BranchOn3 = Player1_Figure2.BranchOn3 = Player2_Figure1.BranchOn3 = Player2_Figure2.BranchOn3 = false;
        SF_FiguresSetToStart();
        caseVal = MOVE;
      }
    break;

    case MOVE:
    {
      if(Figur soll sich bewegen)
      {
        Player1_Figure1.NewPos = 5;
        Player1_Figure1.BranchOn1 = true;
        Player1_Figure1.BranchOn2 = false;
        Player1_Figure1.BranchOn3 = false;
        SF_MovePlayerFigure(Spieler, Figur);
        caseVal = MOVED;
      }
    }

    case MOVED:
      if(SF_PlayerFigureHasMoved(Spieler, Figur) == true)
      {
        caseVAL = .........;
      }
    brake;
  }

if(isInit) SF_OperateSpielfeld_Main();

}*/
