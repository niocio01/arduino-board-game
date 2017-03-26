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
const uint32_t SF_UpdateDelayS = 500;    // "Wanderzeit" LEDs im Spiel in ms
uint32_t SF_OldTime;


GlobalTypes_Spieler_t SF_ActSpieler;
GlobalTypes_Figur_t SF_ActFigur;
bool SF_FigureMoving = false;


// Kommentar siehe Headerfile
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
    SF_dataPlayer1[SF_SegmIB3].StartID = 40;        // Start ID Hardware zu LED's oben
    SF_dataPlayer1[SF_SegmB3].Steps = 13;           // Längeres Segment bei Branch 3
    SF_dataPlayer1[SF_SegmB3].StartID = 179;        // Start ID Hardware zu LED's oben
    SF_dataPlayer1[SF_SegmVK].Steps = 19;           // Segment bis zum Kreis
    SF_dataPlayer1[SF_SegmVK].StartID = 44;         // Start ID Hardware zu LED's oben
    SF_dataPlayer1[SF_SegmK].Steps = SF_K_Steps;    // Segment im Kreis

    // Spielfeld Teil Speiler 2
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
}


// Kommentar siehe Headerfile
// **************************
bool SF_StartDim(void)
{
  int Segment;
  int i;
  uint16_t id;

  // Alle LED's Player 1 auf StartDim setzen
  for (Segment = 0; Segment < SF_MaxSegm; Segment++)
  {
    for (id = SF_dataPlayer1[Segment].StartID, i = 0; i < SF_dataPlayer1[Segment].Steps; i++, id++)
    {
      LedTreiber_LedSchalten(id, Weiss, SF_DIM_helligkeit);
    }
  }

  // Alle LED's Player 2 auf StartDim setzen
  for (Segment = 0; Segment < SF_MaxSegm; Segment++)
  {
    for (id = SF_dataPlayer2[Segment].StartID, i = 0; i < SF_dataPlayer2[Segment].Steps; i++, id++)
    {
      LedTreiber_LedSchalten(id, Weiss, SF_DIM_helligkeit);
    }
  }

  // Alle LED's des Kreises setzen
  for (id = SF_K_StartID, i = 0; i < SF_K_TotSteps; i++, id++)
  {
    LedTreiber_LedSchalten(id, Weiss, SF_DIM_helligkeit);
  }

return(true);
}


// Kommentar siehe Headerfile
bool SF_Lauflicht(void)
{

return(false);
}

// Kommentar siehe Headerfile
void SF_FiguresSetToStart(void)
{

}

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
}


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
}


// Kommentar siehe Headerfile
void SF_OperateSpielfeld(void)
{

  if ((millis() - SF_OldTime) > SF_UpdateDelayS)
  {
    if(SF_FigureMoving)
    {

      // Alte Position löschen

      // Neue Position setzten

      // Kontrolle ob Moving abgeschlossen


    }



  }
}

// Kommentar siehe Headerfile
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

}
