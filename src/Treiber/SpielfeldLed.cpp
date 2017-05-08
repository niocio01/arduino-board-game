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
const uint32_t SF_UpdateDelayS = 200;    // "Wanderzeit" LEDs im Spiel in ms
const uint32_t SF_UpdateDelayF = 25;     // "Wanderzeit" der LEDs im Lauflicht
uint32_t SF_OldTimeS;
uint32_t SF_OldTimeF;

static bool BranchOn1_P1;
static bool BranchOn2_P1;
static bool BranchOn3_P1;
static bool BranchOn1_P2;
static bool BranchOn2_P2;
static bool BranchOn3_P2;


GlobalTypes_Spieler_t SF_ActSpieler;
GlobalTypes_Figur_t SF_ActFigur;
bool SF_FigureMoving = false;
bool SF_Player1Fig1Aktiv = false;
bool SF_Player2Fig1Aktiv = false;

GlobalTypes_Farbe_t SF_LauflichtFarbe;
uint8_t SF_LauflichtHelligkeit;
bool SF_LauflichtAktiv;
bool SF_ShowPlayerAktiv = false;
int SF_LauflichtCounter;
int SF_LastLedCounter = 0;


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
  SF_dataPlayer1[SF_SegmIB3].StartID = 39;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmB3].Steps = 13;           // Längeres Segment bei Branch 3
  SF_dataPlayer1[SF_SegmB3].StartID = 179;        // Start ID Hardware zu LED's oben
  SF_dataPlayer1[SF_SegmVK].Steps = 19;           // Segment bis zum Kreis
  SF_dataPlayer1[SF_SegmVK].StartID = 43;         // Start ID Hardware zu LED's oben
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
  SF_Player1_Kreis[16] = 196;
  SF_Player1_Kreis[17] = 192;

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
  SF_Player2_Kreis[16] = 200;
  SF_Player2_Kreis[17] = 192;

  SF_OldTimeS = millis();
  SF_OldTimeF = millis();
  SF_LastLedCounter = 0;
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
  for (i = 0; i <= SF_K_Steps ; i++)
  {
    id = SF_Player1_Kreis[i];
    LedTreiber_LedSetzen(id, Weiss, Helligkeit);
  }
  for (i = 0; i <= SF_K_Steps ; i++)
  {
    id = SF_Player2_Kreis[i];
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
void SF_FiguresSetToStart(GlobalTypes_Spieler_t Spieler,
                          GlobalTypes_Figur_t Figur,
                          GlobalTypes_Farbe_t Farbe,
                          int Helligkeit)
{

  if((Spieler == SpielerEins) && (Figur == FigureEins))
  {
    SF_Player1_Figure1.ActPos = 0;
    SF_Player1_Figure1.NewPos = 0;
    SF_Player1_Figure1.Farbe = Farbe;
    SF_Player1_Figure1.Helligkeit = Helligkeit;
    SF_Player1_Figure1.BranchOn1 = false;
    SF_Player1_Figure1.BranchOn2 = false;
    SF_Player1_Figure1.BranchOn3 = false;
    SF_Player1_Figure1.ActLEDid = SF_dataPlayer1[0].StartID;
  }
  else if((Spieler == SpielerEins) && (Figur == FigureZwei))
  {
    SF_Player1_Figure2.ActPos = 0;
    SF_Player1_Figure2.NewPos = 0;
    SF_Player1_Figure2.Farbe = Farbe;
    SF_Player1_Figure2.Helligkeit = Helligkeit;
    SF_Player1_Figure2.BranchOn1 = false;
    SF_Player1_Figure2.BranchOn2 = false;
    SF_Player1_Figure2.BranchOn3 = false;
    SF_Player1_Figure2.ActLEDid = SF_dataPlayer1[0].StartID;
  }
  else if((Spieler == SpielerZwei) && (Figur == FigureEins))
  {
    SF_Player2_Figure1.ActPos = 0;
    SF_Player2_Figure1.NewPos = 0;
    SF_Player2_Figure1.Farbe = Farbe;
    SF_Player2_Figure1.Helligkeit = Helligkeit;
    SF_Player2_Figure1.BranchOn1 = false;
    SF_Player2_Figure1.BranchOn2 = false;
    SF_Player2_Figure1.BranchOn3 = false;
    SF_Player2_Figure1.ActLEDid = SF_dataPlayer2[0].StartID;
  }
  else if((Spieler == SpielerZwei) && (Figur == FigureZwei))
  {
    SF_Player2_Figure2.ActPos = 0;
    SF_Player2_Figure2.NewPos = 0;
    SF_Player2_Figure2.Farbe = Farbe;
    SF_Player2_Figure2.Helligkeit = Helligkeit;
    SF_Player2_Figure2.BranchOn1 = false;
    SF_Player2_Figure2.BranchOn2 = false;
    SF_Player2_Figure2.BranchOn3 = false;
    SF_Player2_Figure2.ActLEDid = SF_dataPlayer2[0].StartID;
  }
  SF_ShowPlayerAktiv = true;

}// end of SF_FiguresSetToStart()


// Kommentar siehe Headerfile
// **************************
void SF_SetSpielfeldOff(void)
{
  SF_ShowPlayerAktiv = false;
}// end of SF_SetSpielfeldOff()


// Kommentar siehe Headerfile
// **************************
bool SF_Player1IsWinner(void)
{
  if((SF_Player1_Figure1.ActLEDid == SF_Player1_Kreis[SF_K_Steps-1]) &&
     (SF_Player1_Figure2.ActLEDid == SF_Player1_Kreis[SF_K_Steps-1]))
     return(true);
  else return(false);
}// end of SF_Player1IsWinner()


// Kommentar siehe Headerfile
// **************************
bool SF_Player2IsWinner(void)
{
  if((SF_Player2_Figure1.ActLEDid == SF_Player2_Kreis[SF_K_Steps-1]) &&
     (SF_Player2_Figure2.ActLEDid == SF_Player2_Kreis[SF_K_Steps-1]))
     return(true);
  else return(false);
}// end of SF_Player1IsWinner()





// Kommentar siehe Headerfile
// **************************
void SF_SetBranchPlayer(GlobalTypes_Spieler_t Spieler, SpielfeldLed_Branches_t branch, bool status)
{

  if (Spieler == SpielerEins)
  {
    switch (branch)
    {
      case Branch1:
      BranchOn1_P1 = status;
      break;

      case Branch2:
      BranchOn2_P1 = status;
      break;

      case Branch3:
      BranchOn3_P1 = status;
      break;
    }
  }
  else
  {
    switch (branch)
    {
      case Branch1:
      BranchOn1_P2 = status;
      break;

      case Branch2:
      BranchOn2_P2 = status;
      break;

      case Branch3:
      BranchOn3_P2 = status;
      break;
    }
  }
  SF_SetBranchPlayerFigure(Spieler, FigureEins, BranchOn1_P1, BranchOn2_P1, BranchOn3_P1);
  SF_SetBranchPlayerFigure(Spieler, FigureZwei, BranchOn1_P2, BranchOn2_P2, BranchOn3_P2);

}// end of SF_SetBranchPlayer()


void SF_SetBranchPlayerFigure(GlobalTypes_Spieler_t Spieler,
                              GlobalTypes_Figur_t Figur,
                              bool BranchOn1,
                              bool BranchOn2,
                              bool BranchOn3)
{
  int SegmVB1, SegmIB1, SegmB1, SegmVB2, SegmIB2, SegmB2, SegmVB3;
  int ActPos, CrossingB1, CrossingB2, CrossingB3;
  bool ActBranchOn1, ActBranchOn2;

  if( Spieler == SpielerEins)
  {
    SegmVB1 = SF_dataPlayer1[SF_SegmVB1].Steps;          // Segment bis Branch 1
    SegmIB1 = SF_dataPlayer1[SF_SegmIB1].Steps;          // Kürzeres Segment bei Branch 1
    SegmB1  = SF_dataPlayer1[SF_SegmB1].Steps;           // Längeres Segment bei Branch 1
    SegmVB2 = SF_dataPlayer1[SF_SegmVB2].Steps;          // Segment bis Branch 2
    SegmIB2 = SF_dataPlayer1[SF_SegmIB2].Steps;          // Kürzeres Segment bei Branch 2
    SegmB2  = SF_dataPlayer1[SF_SegmB2].Steps;           // Längeres Segment bei Branch 2
    SegmVB3 = SF_dataPlayer1[SF_SegmVB3].Steps;          // Segment bis Branch 3
    if(Figur == FigureEins)
    {
      ActBranchOn1 = SF_Player1_Figure1.BranchOn1;
      ActBranchOn2 = SF_Player1_Figure1.BranchOn2;
      ActPos = SF_Player1_Figure1.ActPos;
    }
    else
    {
      ActBranchOn1 = SF_Player1_Figure2.BranchOn1;
      ActBranchOn2 = SF_Player1_Figure2.BranchOn2;
      ActPos = SF_Player1_Figure2.ActPos;
    }
  }
  else // Spieler == SpielerZwei
  {
    SegmVB1 = SF_dataPlayer2[SF_SegmVB1].Steps;          // Segment bis Branch 1
    SegmIB1 = SF_dataPlayer2[SF_SegmIB1].Steps;          // Kürzeres Segment bei Branch 1
    SegmB1  = SF_dataPlayer2[SF_SegmB1].Steps;           // Längeres Segment bei Branch 1
    SegmVB2 = SF_dataPlayer2[SF_SegmVB2].Steps;          // Segment bis Branch 2
    SegmIB2 = SF_dataPlayer2[SF_SegmIB2].Steps;          // Kürzeres Segment bei Branch 2
    SegmB2  = SF_dataPlayer2[SF_SegmB2].Steps;           // Längeres Segment bei Branch 2
    SegmVB3 = SF_dataPlayer2[SF_SegmVB3].Steps;          // Segment bis Branch 3
    if(Figur == FigureEins)
    {
      ActBranchOn1 = SF_Player2_Figure1.BranchOn1;
      ActBranchOn2 = SF_Player2_Figure1.BranchOn2;
      ActPos = SF_Player2_Figure1.ActPos;
    }
    else
    {
      ActBranchOn1 = SF_Player2_Figure2.BranchOn1;
      ActBranchOn2 = SF_Player2_Figure2.BranchOn2;
      ActPos = SF_Player2_Figure2.ActPos;
    }
  }

  CrossingB1 = SegmVB1;
  if(ActBranchOn1) CrossingB2 = SegmVB1 + SegmB1 + SegmVB2;
  else CrossingB2 = SegmVB1 + SegmIB1 + SegmVB2;
  if(ActBranchOn2) CrossingB3 = CrossingB2 + SegmB2 + SegmVB3;
  else CrossingB3 = CrossingB2 + SegmIB2 + SegmVB3;

  if(BranchOn1 && (ActPos < CrossingB1))
  {
    if((Spieler == SpielerEins) && (Figur == FigureEins))
      SF_Player1_Figure1.BranchOn1 = true;
    if((Spieler == SpielerEins) && (Figur == FigureZwei))
      SF_Player1_Figure2.BranchOn1 = true;
    if((Spieler == SpielerZwei) && (Figur == FigureEins))
      SF_Player2_Figure1.BranchOn1 = true;
    if((Spieler == SpielerZwei) && (Figur == FigureZwei))
      SF_Player2_Figure2.BranchOn1 = true;
  }

  if(BranchOn2 && (ActPos < CrossingB2))
  {
    if((Spieler == SpielerEins) && (Figur == FigureEins))
      SF_Player1_Figure1.BranchOn2 = true;
    if((Spieler == SpielerEins) && (Figur == FigureZwei))
      SF_Player1_Figure2.BranchOn2 = true;
    if((Spieler == SpielerZwei) && (Figur == FigureEins))
      SF_Player2_Figure1.BranchOn2 = true;
    if((Spieler == SpielerZwei) && (Figur == FigureZwei))
      SF_Player2_Figure2.BranchOn2 = true;
  }

  if(BranchOn3 && (ActPos < CrossingB3))
  {
    if((Spieler == SpielerEins) && (Figur == FigureEins))
      SF_Player1_Figure1.BranchOn3 = true;
    if((Spieler == SpielerEins) && (Figur == FigureZwei))
      SF_Player1_Figure2.BranchOn3 = true;
    if((Spieler == SpielerZwei) && (Figur == FigureEins))
      SF_Player2_Figure1.BranchOn3 = true;
    if((Spieler == SpielerZwei) && (Figur == FigureZwei))
      SF_Player2_Figure2.BranchOn3 = true;
  }

}// end of SF_SetBranchPlayerFigure()


// Kommentar siehe Headerfile
// **************************
void SF_MovePlayerFigure(GlobalTypes_Spieler_t Spieler,
                         GlobalTypes_Figur_t Figur,
                         int Steps)
{
  SF_ActSpieler = Spieler;
  SF_ActFigur = Figur;
  SF_FigureMoving = false;

  if((Spieler == SpielerEins) && (Figur == FigureEins))
  {
    SF_Player1_Figure1.NewPos = SF_Player1_Figure1.ActPos + Steps;
  }
  else if((Spieler == SpielerEins) && (Figur == FigureZwei))
  {
    SF_Player1_Figure2.NewPos = SF_Player1_Figure2.ActPos + Steps;
  }
  else if((Spieler == SpielerZwei) && (Figur == FigureEins))
  {
    SF_Player2_Figure1.NewPos = SF_Player2_Figure1.ActPos + Steps;
  }
  else if((Spieler == SpielerZwei) && (Figur == FigureZwei))
  {
    SF_Player2_Figure2.NewPos = SF_Player2_Figure2.ActPos + Steps;
  }

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
  if (((millis() - SF_OldTimeS) > SF_UpdateDelayS) && SF_ShowPlayerAktiv)
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
        if(SF_Player1_Figure1.ActLEDid != SF_Player1_Kreis[SF_K_Steps-1])
        {
          LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid,
                                 SF_Player1_Figure1.Farbe,
                                 SF_Player1_Figure1.Helligkeit);
        }
      }
      else
      {
        SF_Player1Fig1Aktiv = true;
        if(SF_Player1_Figure2.ActLEDid != SF_Player1_Kreis[SF_K_Steps-1])
        {
          LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid,
                                 SF_Player1_Figure2.Farbe,
                                 SF_Player1_Figure2.Helligkeit);
        }
      }
    }
    else
    {
      if(SF_Player1_Figure1.ActLEDid != SF_Player1_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid,
                               SF_Player1_Figure1.Farbe,
                               SF_Player1_Figure1.Helligkeit);
      }
      if(SF_Player1_Figure2.ActLEDid != SF_Player1_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid,
                               SF_Player1_Figure2.Farbe,
                               SF_Player1_Figure2.Helligkeit);
      }
    }


    // Anzeige LED Player 2
    // ------------------------------------------------
    if(SF_Player2_Figure1.ActLEDid == SF_Player2_Figure2.ActLEDid)
    {
      if(SF_Player2Fig1Aktiv == true)
      {
        SF_Player2Fig1Aktiv = false;
        if(SF_Player2_Figure1.ActLEDid != SF_Player2_Kreis[SF_K_Steps-1])
        {
          LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid,
                                 SF_Player2_Figure1.Farbe,
                                 SF_Player2_Figure1.Helligkeit);
        }
      }
      else
      {
        SF_Player2Fig1Aktiv = true;
        if(SF_Player2_Figure2.ActLEDid != SF_Player2_Kreis[SF_K_Steps-1])
        {
          LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid,
                                 SF_Player2_Figure2.Farbe,
                                 SF_Player2_Figure2.Helligkeit);
        }
      }
    }
    else
    {
      if(SF_Player2_Figure1.ActLEDid != SF_Player2_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid,
                               SF_Player2_Figure1.Farbe,
                               SF_Player2_Figure1.Helligkeit);
      }
      if(SF_Player2_Figure2.ActLEDid != SF_Player2_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid,
                               SF_Player2_Figure2.Farbe,
                               SF_Player2_Figure2.Helligkeit);
      }
    }

    // Wechselanzeige beim Ziel
    // ------------------------
    if(SF_LastLedCounter == 0)
    {
      if(SF_Player1_Figure1.ActLEDid == SF_Player1_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid,
                               SF_Player1_Figure1.Farbe,
                               SF_Player1_Figure1.Helligkeit);
      }
    }
    if(SF_LastLedCounter == 1)
    {
      if(SF_Player1_Figure2.ActLEDid == SF_Player1_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid,
                               SF_Player1_Figure2.Farbe,
                               SF_Player1_Figure2.Helligkeit);
      }
    }
    if(SF_LastLedCounter == 2)
    {
      if(SF_Player2_Figure1.ActLEDid == SF_Player2_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid,
                               SF_Player2_Figure1.Farbe,
                               SF_Player2_Figure1.Helligkeit);
      }
    }
    if(SF_LastLedCounter == 3)
    {
      if(SF_Player2_Figure2.ActLEDid == SF_Player2_Kreis[SF_K_Steps-1])
      {
        LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid,
                               SF_Player2_Figure2.Farbe,
                               SF_Player2_Figure2.Helligkeit);
      }
    }
    SF_LastLedCounter++;
    if(SF_LastLedCounter > 3) SF_LastLedCounter = 0;

  } // end of Teil Anzeige "Spielfiguren"


  // LED Lauflicht durchlaufen
  // Update erfolgt alle SF_UpdateDelayF ms
  if ((millis() - SF_OldTimeF) > SF_UpdateDelayF)
  {
    SF_OldTimeF = millis();

    if(SF_LauflichtAktiv == true)
    {
      LedTreiber_LedSetzen(SF_LauflichtCounter,
                           SF_LauflichtFarbe,
                           SF_LauflichtHelligkeit);
      LedTreiber_LedAnzeigen();
      SF_LauflichtCounter++;

      if(SF_LauflichtCounter >= SF_TOT_LEDS)
      {
        SF_LauflichtAktiv = false;
      }
    }
  }// end of Teil Lauflicht

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
