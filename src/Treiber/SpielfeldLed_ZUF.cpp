#include "SpielfeldLed.h"
#include "LedTreiber.h"
#include <arduino.h>
#include "inttypes.h"

// Globale Variablen (Daten von andern Moduln mit "extern" sichtbar)
struct FigureData_t SF_Player1_Figure1;
struct FigureData_t SF_Player1_Figure2;
struct FigureData_t SF_Player2_Figure1;
struct FigureData_t SF_Player2_Figure2;

// Lokale Definitionen (TODO: ohne SF_...)
#define  SF_SegmVB1     0       // Segment bis Branch 1
#define  SF_SegmIB1     1       // Kürzeres Segment bei Branch 1
#define  SF_SegmB1      2       // Längeres Segment bei Branch 1
#define  SF_SegmVB2     3       // Segment bis Branch 2
#define  SF_SegmIB2     4       // Kürzeres Segment bei Branch 2
#define  SF_SegmB2      5       // Längeres Segment bei Branch 2
#define  SF_SegmVB3     6       // Segment bis Branch 3
#define  SF_SegmIB3     7       // Kürzeres Segment bei Branch 3
#define  SF_SegmB3      8       // Längeres Segment bei Branch 3
#define  SF_SegmVK      9       // Segment bis zum Kreis
#define  SF_SegmK       10      // Segment im Kreis
#define  SF_MaxSegm     11      // Anzahl der Segemente
#define  SF_K_Steps     18      // Anzahl Schritte pro Spieler im Kreis
#define  SF_K_StartID   192     // ID der ersten LED im Kreis
#define  SF_K_TotSteps  61      // Anzahl Schritte Total im Kreis
#define  SF_MAX_STEPS   100      // Maximale Anzahl Schritte bis zum Ziel
#define  SF_TOT_LEDS    252      // Totale Anzahl LED's

// Lokale Konstanten
const uint8_t dimHelligkeit = 5;
const uint32_t updateDelayS = 750;   // "Wanderzeit" LEDs im Spiel in ms
const uint32_t updateDelayF = 1;     // "Wanderzeit" der LEDs im Lauflicht

// Lokale Typendefinitionen
// Daten mit den Anzahl Schritten in den Teilsegmenten
typedef struct spielfeldData_tag
{
  int Steps;       // Schritte im Segment
  int StartID;     // LED Start ID des Segments
} spielfeldData_t;

// Lokale Variablen
// Daten mit den Anzahl Schritten in den Teilsegmenten
struct spielfeldData_t player1_Data[SF_MaxSegm];
struct spielfeldData_t player2_Data[SF_MaxSegm];

static int player1_Kreis[SF_K_Steps];
static int player2_Kreis[SF_K_Steps];

static uint16_t ledWeg[SF_MAX_STEPS];

static uint32_t oldTimeS;
static uint32_t oldTimeF;

struct GlobalTypes_Spieler_t actSpieler;
struct GlobalTypes_Figur_t actFigur;
static bool figureMoving = false;
static bool player1Fig1Aktiv = false;
static bool player2Fig1Aktiv = false;

static GlobalTypes_Farbe_t lauflichtFarbe;
static uint8_t lauflichtHelligkeit;
static uint8_t lauflichtCounter;
static bool lauflichtAktiv;

// Lokale Funktionen (Prototypen)
static void anzeigeLedPlayer1(void);
static void anzeigeLedPlayer2(void);
static void anzeigeLedLauflicht(void);
static void altePositionLoeschen(void);
static void neuePositionSetzen(void);
static bool kontrolleObMovingAbgeschlossen(void);
static void calcPlayerWay(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur);

// Kommentar siehe Headerfile
// **************************
void SF_InitData(void)
{
  // Spielfeld Teil Spieler 1
  player1_Data[SF_SegmVB1].Steps = 11;          // Segment bis Branch 1
  player1_Data[SF_SegmVB1].StartID = 0;         // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmIB1].Steps = 4;           // Kürzeres Segment bei Branch 1
  player1_Data[SF_SegmIB1].StartID = 11;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmB1].Steps = 8;            // Längeres Segment bei Branch 1
  player1_Data[SF_SegmB1].StartID = 161;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmVB2].Steps = 9;           // Segment bis Branch 2
  player1_Data[SF_SegmVB2].StartID = 15;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmIB2].Steps = 4;           // Kürzeres Segment bei Branch 2
  player1_Data[SF_SegmIB2].StartID = 24;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmB2].Steps = 10;           // Längeres Segment bei Branch 2
  player1_Data[SF_SegmB2].StartID = 169;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmVB3].Steps = 11;          // Segment bis Branch 3
  player1_Data[SF_SegmVB3].StartID = 28;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmIB3].Steps = 4;           // Kürzeres Segment bei Branch 3
  player1_Data[SF_SegmIB3].StartID = 39;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmB3].Steps = 13;           // Längeres Segment bei Branch 3
  player1_Data[SF_SegmB3].StartID = 179;        // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmVK].Steps = 19;           // Segment bis zum Kreis
  player1_Data[SF_SegmVK].StartID = 43;         // Start ID Hardware zu LED's oben
  player1_Data[SF_SegmK].Steps = SF_K_Steps;    // Segment im Kreis

  // Spielfeld Teil Spieler 2
  player2_Data[SF_SegmVB1].Steps = 9;           // Segment bis Branch 1
  player2_Data[SF_SegmVB1].StartID = 62;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmIB1].Steps = 5;           // Kürzeres Segment bei Branch 1
  player2_Data[SF_SegmIB1].StartID = 71;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmB1].Steps = 14;           // Längeres Segment bei Branch 1
  player2_Data[SF_SegmB1].StartID = 124;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmVB2].Steps = 6;           // Segment bis Branch 2
  player2_Data[SF_SegmVB2].StartID = 76;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmIB2].Steps = 7;           // Kürzeres Segment bei Branch 2
  player2_Data[SF_SegmIB2].StartID = 82;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmB2].Steps = 11;           // Längeres Segment bei Branch 2
  player2_Data[SF_SegmB2].StartID = 138;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmVB3].Steps = 9;           // Segment bis Branch 3
  player2_Data[SF_SegmVB3].StartID = 89;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmIB3].Steps = 6;           // Kürzeres Segment bei Branch 3
  player2_Data[SF_SegmIB3].StartID = 98;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmB3].Steps = 12;           // Längeres Segment bei Branch 3
  player2_Data[SF_SegmB3].StartID = 149;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmVK].Steps = 20;           // Segment bis zum Kreis
  player2_Data[SF_SegmVK].StartID = 104;        // Start ID Hardware zu LED's oben
  player2_Data[SF_SegmK].Steps = SF_K_Steps;    // Segment im Kreis

  // Spielfeld Teil Kreis Spieler 1
  player1_Kreis[0] = 240;
  player1_Kreis[1] = 239;
  player1_Kreis[2] = 238;
  player1_Kreis[3] = 237;
  player1_Kreis[4] = 236;
  player1_Kreis[5] = 235;
  player1_Kreis[6] = 234;
  player1_Kreis[7] = 233;
  player1_Kreis[8] = 232;
  player1_Kreis[9] = 231;
  player1_Kreis[10] = 230;
  player1_Kreis[11] = 214;
  player1_Kreis[12] = 202;
  player1_Kreis[13] = 203;
  player1_Kreis[14] = 204;
  player1_Kreis[15] = 205;
  player1_Kreis[16] = 196;
  player1_Kreis[17] = 192;

  // Spielfeld Teil Kreis Spieler 2
  player2_Kreis[0] = 252;
  player2_Kreis[1] = 251;
  player2_Kreis[2] = 250;
  player2_Kreis[3] = 249;
  player2_Kreis[4] = 248;
  player2_Kreis[5] = 247;
  player2_Kreis[6] = 246;
  player2_Kreis[7] = 245;
  player2_Kreis[8] = 244;
  player2_Kreis[9] = 243;
  player2_Kreis[10] = 242;
  player2_Kreis[11] = 222;
  player2_Kreis[12] = 208;
  player2_Kreis[13] = 209;
  player2_Kreis[14] = 210;
  player2_Kreis[15] = 211;
  player2_Kreis[16] = 200;
  player2_Kreis[17] = 192;

  oldTimeS = millis();
  oldTimeF = millis();
}


// Kommentar siehe Headerfile
// **************************
void SF_StartDim(uint8_t Helligkeit)
{
  uint8_t Segment;
  uint16_t i;
  uint16_t id;

  // Alle LED's Player 1 auf StartDim setzen
  for (Segment = 0; Segment < SF_MaxSegm; Segment++)
  {
    id = player1_Data[Segment].StartID;
    for (i = 0; i < player1_Data[Segment].Steps; i++)
    {
      LedTreiber_LedSetzen(id, Weiss, Helligkeit);
      id++;
    }
  }

  // Alle LED's Player 2 auf StartDim setzen
  for (Segment = 0; Segment < SF_MaxSegm; Segment++)
  {
    id = player2_Data[Segment].StartID;
    for (i = 0; i < player2_Data[Segment].Steps; i++)
    {
      LedTreiber_LedSetzen(id, Weiss, Helligkeit);
      id++;
    }
  }

  // Alle LED's Player 1 des Kreises setzen
  for (i = 0; i <= SF_K_Steps ; i++)
  {
    id = player1_Kreis[i];
    LedTreiber_LedSetzen(id, Weiss, Helligkeit);
  }

  // Alle LED's Player 2 des Kreises setzen
  for (i = 0; i <= SF_K_Steps ; i++)
  {
    id = player2_Kreis[i];
    LedTreiber_LedSetzen(id, Weiss, Helligkeit);
  }

  // Alle gesetzten LED's anzeigen
  LedTreiber_LedAnzeigen();
}


// Kommentar siehe Headerfile
// **************************
void SF_StartLauflicht(GlobalTypes_Farbe_t farbe, uint8_t helligkeit)
{
  lauflichtFarbe = farbe;
  lauflichtHelligkeit = helligkeit;
  lauflichtCounter = 0U;
  lauflichtAktiv = true;
}


// Kommentar siehe Headerfile
// **************************
bool SF_LauflichtAmLaufen(void)
{
  return (lauflichtAktiv);
}


// Kommentar siehe Headerfile
// **************************
void SF_FiguresSetToStart(void)
{
  SF_Player1_Figure1.ActPos = 0;
  SF_Player1_Figure1.NewPos = 0;
  SF_Player1_Figure1.ActLEDid = player1_Data[0].StartID;
  SF_Player1_Figure2.ActPos = 0;
  SF_Player1_Figure2.NewPos = 0;
  SF_Player1_Figure2.ActLEDid = player1_Data[0].StartID;

  SF_Player2_Figure1.ActPos = 0;
  SF_Player2_Figure1.NewPos = 0;
  SF_Player2_Figure1.ActLEDid = player2_Data[0].StartID;
  SF_Player2_Figure2.ActPos = 0;
  SF_Player2_Figure2.NewPos = 0;
  SF_Player2_Figure2.ActLEDid = player2_Data[0].StartID;
}


// Kommentar siehe Headerfile
// **************************
void SF_MovePlayerFigure(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur)
{
  actSpieler = Spieler;
  actFigur = Figur;
  figureMoving = false;

  if ((actSpieler == SpielerEins) && (actFigur == FigureEins))
  {
    if (SF_Player1_Figure1.NewPos > SF_Player1_Figure1.ActPos)
    {
      figureMoving = true;
    }
  }
  if ((actSpieler == SpielerEins) && (actFigur == FigureZwei))
  {
    if (SF_Player1_Figure2.NewPos > SF_Player1_Figure2.ActPos)
    {
      figureMoving = true;
    }
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureEins))
  {
    if (SF_Player2_Figure1.NewPos > SF_Player2_Figure1.ActPos)
    {
      figureMoving = true;
    }
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureZwei))
  {
    if (SF_Player2_Figure2.NewPos > SF_Player2_Figure2.ActPos)
    {
      figureMoving = true;
    }
  }

  if (figureMoving == true)
  {
    calcPlayerWay(actSpieler, actFigur);
  }
}


// Kommentar siehe Headerfile
// **************************
bool SF_PlayerFigureHasMoved(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur)
{
  bool retVal = false;

  if ((Spieler == SpielerEins) && (Figur == FigureEins))
  {
    if (SF_Player1_Figure1.NewPos == SF_Player1_Figure1.ActPos)
    {
      retVal = true;
    }
  }
  if ((Spieler == SpielerEins) && (Figur == FigureZwei))
  {
    if (SF_Player1_Figure2.NewPos == SF_Player1_Figure2.ActPos)
    {
      retVal = true;
    }
  }
  if ((Spieler == SpielerZwei) && (Figur == FigureEins))
  {
    if (SF_Player2_Figure1.NewPos == SF_Player2_Figure1.ActPos)
    {
      retVal = true;
    }
  }
  if ((Spieler == SpielerZwei) && (Figur == FigureZwei))
  {
    if (SF_Player2_Figure2.NewPos == SF_Player2_Figure2.ActPos)
    {
      retVal = true;
    }
  }
  return(retVal);
}


// Kommentar siehe Headerfile
// **************************
void SF_OperateSpielfeld_Main(void)
{
  // LED im Spielfeld abhängig von Spieler und Figur anzeigen
  // (Update erfolgt alle updateDelayS ms)
  if ((millis() - oldTimeS) > updateDelayS)
  {
    oldTimeS = millis();
    if (figureMoving)
    {
      altePositionLoeschen();
      neuePositionSetzen();
      figureMoving = kontrolleObMovingAbgeschlossen();
    }
    anzeigeLedPlayer1();
    anzeigeLedPlayer2();

    // Wechselanzeige beim Ziel noch regeln
    // ------------------------------------
    // ?????????????????????????????
  }

  // LED Lauflicht anzeigen (wenn aktiv)
  // (Update erfolgt alle updateDelayF ms)
  if (lauflichtAktiv == true)
  {
    if ((millis() - oldTimeF) > updateDelayF)
    {
      oldTimeF = millis();
      anzeigeLedLauflicht();
    }
  }
  else
  {
    oldTimeF = millis();
  }
}

static void anzeigeLedPlayer1(void)
{
  if (SF_Player1_Figure1.ActLEDid == SF_Player1_Figure2.ActLEDid)
  {
    if (player1Fig1Aktiv == true)
    {
      player1Fig1Aktiv = false;
      LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid, SF_Player1_Figure1.Farbe, SF_Player1_Figure1.Helligkeit);
    }
    else
    {
      player1Fig1Aktiv = true;
      LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid, SF_Player1_Figure2.Farbe, SF_Player1_Figure2.Helligkeit);
      }
    }
  }
  else
  {
    LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid, SF_Player1_Figure1.Farbe, SF_Player1_Figure1.Helligkeit);
    LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid, SF_Player1_Figure2.Farbe, SF_Player1_Figure2.Helligkeit);
  }
}

static void anzeigeLedPlayer2(void)
{
  if (SF_Player2_Figure1.ActLEDid == SF_Player2_Figure2.ActLEDid)
  {
    if (player2Fig1Aktiv == true)
    {
      player2Fig1Aktiv = false;
      LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid, SF_Player2_Figure1.Farbe, SF_Player2_Figure1.Helligkeit);
    }
    else
    {
      player2Fig1Aktiv = true;
      LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid, SF_Player2_Figure2.Farbe, SF_Player2_Figure2.Helligkeit);
    }
  }
  else
  {
    LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid, SF_Player2_Figure1.Farbe, SF_Player2_Figure1.Helligkeit);
    LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid, SF_Player2_Figure2.Farbe, SF_Player2_Figure2.Helligkeit);
  }
}

static void anzeigeLedLauflicht(void)
{
  if (lauflichtCounter >= SF_TOT_LEDS)
  {
    LedTreiber_LedSetzen(lauflichtCounter - 1U, Weiss, dimHelligkeit);
    lauflichtAktiv = false;
  }
  else
  {
    // Alte Lauflicht-LED ausschalten
    if (lauflichtCounter > 0U)
    {
      LedTreiber_LedSetzen(lauflichtCounter - 1U, Weiss, dimHelligkeit);
    }
    // Neue Lauflicht-LED einschalten
    LedTreiber_LedSetzen(lauflichtCounter, lauflichtFarbe, lauflichtHelligkeit);
    LedTreiber_LedAnzeigen();
    lauflichtCounter++;
  }
}

static void altePositionLoeschen(void)
{
  if ((actSpieler == SpielerEins) && (actFigur == FigureEins))
  {
    LedTreiber_LedSchalten(SF_Player1_Figure1.ActLEDid, Weiss, dimHelligkeit);
  }
  if ((actSpieler == SpielerEins) && (actFigur == FigureZwei))
  {
    LedTreiber_LedSchalten(SF_Player1_Figure2.ActLEDid, Weiss, dimHelligkeit);
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureEins))
  {
    LedTreiber_LedSchalten(SF_Player2_Figure1.ActLEDid, Weiss, dimHelligkeit);
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureZwei))
  {
    LedTreiber_LedSchalten(SF_Player2_Figure2.ActLEDid, Weiss, dimHelligkeit);
  }
}

static void neuePositionSetzen(void)
{
  if ((actSpieler == SpielerEins) && (actFigur == FigureEins))
  {
    SF_Player1_Figure1.ActPos++;
    SF_Player1_Figure1.ActLEDid = ledWeg[SF_Player1_Figure1.ActPos];
    player1Fig1Aktiv = true;
  }
  if ((actSpieler == SpielerEins) && (actFigur == FigureZwei))
  {
    SF_Player1_Figure2.ActPos++;
    SF_Player1_Figure2.ActLEDid = ledWeg[SF_Player1_Figure2.ActPos];
    player1Fig1Aktiv = false;
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureEins))
  {
    SF_Player2_Figure1.ActPos++;
    SF_Player2_Figure1.ActLEDid = ledWeg[SF_Player2_Figure1.ActPos];
    player2Fig1Aktiv = true;
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureZwei))
  {
    SF_Player2_Figure2.ActPos++;
    SF_Player2_Figure2.ActLEDid = ledWeg[SF_Player2_Figure2.ActPos];
    player2Fig1Aktiv = false;
  }
}

static bool kontrolleObMovingAbgeschlossen(void)
{
  bool returnWert = false;
  
  if ((actSpieler == SpielerEins) && (actFigur == FigureEins))
  {
    if (SF_Player1_Figure1.ActPos >= SF_Player1_Figure1.NewPos)
    {
      returnWert = true;
    }
  }
  if ((actSpieler == SpielerEins) && (actFigur == FigureZwei))
  {
    if (SF_Player1_Figure2.ActPos >= SF_Player1_Figure2.NewPos)
    {
      returnWert = true;
    }
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureEins))
  {
    if (SF_Player2_Figure1.ActPos >= SF_Player2_Figure1.NewPos)
    {
      returnWert = true;
    }
  }
  if ((actSpieler == SpielerZwei) && (actFigur == FigureZwei))
  {
    if (SF_Player2_Figure2.ActPos >= SF_Player2_Figure2.NewPos)
    {
      returnWert = true;
    }
  }
  return(returnWert);  
}

// Funktion berechnet auf Grund der "FigureData_t" den neuen Weg
static void calcPlayerWay(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur)
{
	int Pos;
	int i;
	bool BranchOn1;
  bool BranchOn2;
  bool BranchOn3;
	spielfeldData_t dataPlayer[SF_MaxSegm];

	// Daten abhängig ob Spieler 1 oder 2
	for (i = 0; i < SF_MaxSegm; i++)
	{
	  if (Spieler == SpielerEins)
	  {
		  dataPlayer[i].Steps = player1_Data[i].Steps;
		  dataPlayer[i].StartID = player1_Data[i].StartID;
	  }
	  else
	  {
		  dataPlayer[i].Steps = player2_Data[i].Steps;
		  dataPlayer[i].StartID = player2_Data[i].StartID;
	  }
	}

	// Merken ob Branch eingeschaltet ist oder nicht
	if ((Spieler == SpielerEins) && (Figur == FigureEins))
  {
	  BranchOn1 = SF_Player1_Figure1.BranchOn1;
	  BranchOn2 = SF_Player1_Figure1.BranchOn2;
	  BranchOn3 = SF_Player1_Figure1.BranchOn3;
	}
	if ((Spieler == SpielerEins) && (Figur == FigureZwei))
  {
	  BranchOn1 = SF_Player1_Figure2.BranchOn1;
	  BranchOn2 = SF_Player1_Figure2.BranchOn2;
	  BranchOn3 = SF_Player1_Figure2.BranchOn3;
	}
	if ((Spieler == SpielerZwei) && (Figur == FigureEins))
  {
	  BranchOn1 = SF_Player2_Figure1.BranchOn1;
	  BranchOn2 = SF_Player2_Figure1.BranchOn2;
	  BranchOn3 = SF_Player2_Figure1.BranchOn3;
	}
	if ((Spieler == SpielerZwei) && (Figur == FigureZwei))
  {
	  BranchOn1 = SF_Player2_Figure2.BranchOn1;
	  BranchOn2 = SF_Player2_Figure2.BranchOn2;
	  BranchOn3 = SF_Player2_Figure2.BranchOn3;
	}

	// Segment vor Branch 1 abfüllen
	Pos = 0;
	for (i = 0; i < dataPlayer[SF_SegmVB1].Steps; i++)
	{
	  ledWeg[Pos] = dataPlayer[SF_SegmVB1].StartID + i;
    Pos++;
	}

	// Segment Branch 1 innen/aussen abfüllen
	if (BranchOn1 == true)
	{
	  for (i = 0; i < dataPlayer[SF_SegmB1].Steps; i++)
    {
		  ledWeg[Pos] = dataPlayer[SF_SegmB1].StartID + i;
      Pos++;
	  }
	}
	else
	{
	  for (i = 0; i < dataPlayer[SF_SegmIB1].Steps; i++)
    {
		  ledWeg[Pos] = dataPlayer[SF_SegmIB1].StartID + i;
      Pos++;
	  }
	}

	// Segment vor Branch 2 berechnen
	for (i = 0; i < dataPlayer[SF_SegmVB2].Steps; i++, Pos++)
	{
	  ledWeg[Pos] = dataPlayer[SF_SegmVB2].StartID + i;
    Pos++;
	}

	// Segment Branch2 innen/aussen berechnen
	if (BranchOn2 == true)
	{
	  for (i = 0; i < dataPlayer[SF_SegmB2].Steps; i++)
    {
		  ledWeg[Pos] = dataPlayer[SF_SegmB2].StartID + i;
      Pos++;
	  }
	}
	else
	{
	  for (i = 0; i < dataPlayer[SF_SegmIB2].Steps; i++)
    {
		  ledWeg[Pos] = dataPlayer[SF_SegmIB2].StartID + i;
      Pos++;
	  }
	}

	// Segment vor Branch 3 berechnen
	for (i = 0; i < dataPlayer[SF_SegmVB3].Steps; i++)
	{
	  ledWeg[Pos] = dataPlayer[SF_SegmVB3].StartID + i;
    Pos++;
	}

	// Segment Branch3 innen/aussen berechnen
	if (BranchOn3 == true)
	{
	  for (i = 0; i < dataPlayer[SF_SegmB3].Steps; i++)
    {
		  ledWeg[Pos] = dataPlayer[SF_SegmB3].StartID + i;
      Pos++;
	  }
	}
	else
	{
	  for (i = 0; i < dataPlayer[SF_SegmIB3].Steps; i++)
    {
		  ledWeg[Pos] = dataPlayer[SF_SegmIB3].StartID + i;
      Pos++;
	  }
	}

	// Segment vor Kreis berechnen
	for (i = 0; i < dataPlayer[SF_SegmVK].Steps; i++)
	{
	  ledWeg[Pos] = dataPlayer[SF_SegmVK].StartID + i;
    Pos++;
	}

	// Segment im Kreis berechnen
	for (i = 0; i < dataPlayer[SF_SegmK].Steps; i++)
	{
	  if (Spieler == SpielerEins)
	  {
		  ledWeg[Pos] = player1_Kreis[i];
	  }
	  else
	  {
		  ledWeg[Pos] = player2_Kreis[i];
	  }
    Pos++;
	}
}

/*  Beispiel auskommentiert
void beispiel(void)
{
  int caseVal = 0;
  bool isInit = false;
  const int START = 0;
  const int READY = 10;
  const int WAIT = 20;
  const int MOVE = 30;

  switch (caseVal)
  {
    case START:
      SF_InitData();
      isInit = true;
      casVal = READY;
      break;

    case READY:
      if (Taste ist gedrückt)
      {
        SF_StartLauflicht(Farbe, 25);
        caseVAL = WAIT;
      }
      break;

    case WAIT:
      if (SF_LauflichtAmLaufen == false)
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
      if (Figur soll sich bewegen)
      {
        Player1_Figure1.NewPos = 5;
        Player1_Figure1.BranchOn1 = true;
        Player1_Figure1.BranchOn2 = false;
        Player1_Figure1.BranchOn3 = false;
        SF_MovePlayerFigure(Spieler, Figur);
        caseVal = MOVED;
      }

    case MOVED:
      if (SF_PlayerFigureHasMoved(Spieler, Figur) == true)
      {
        caseVAL = .........;
      }
      brake;
      
    default:
      break;
  }

  if (isInit)
  {
    SF_OperateSpielfeld_Main();
  }

}*/
