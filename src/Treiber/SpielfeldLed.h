#ifndef SPIELFELDLED_H
#define SPIELFELDLED_H

#include <inttypes.h>
#include "GlobalTypes.h"

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


// Daten mit den Anzahl Schritten in den Teilsegmenten
struct SpielfeldData {
  int Steps;       // Schritte im Segment
  int StartID;     // LED Start ID des Segments
};


struct FigureData {
  int NewPos;                   // Neue Position, wird vom Spiel verwaltet
  int ActPos;                   // Wird für die Schritte verwendet
  GlobalTypes_Farbe_t Farbe;    // Farbe der Figur
  int Helligkeit;               // Helligkeit der Figur
  bool BranchOn1;               // Branch 1 ist aktiv
  bool BranchOn2;               // Branch 2 ist aktiv
  bool BranchOn3;               // Branch 3 ist aktiv
  int  ActLEDid;                // ID des aktuellen LED's. Nur im Modul "SpielfeldLed.cpp" verwenden
};


// Funktion muss beim Start einmal aufgerufen werden
// Funktion ist "blockierend"
void SF_InitData(void);


// Grundbeleuchtung einschalten
// Funktion ist "blockierend"
// "Helligkeit" gilt für alle LED's
// Return true, wenn abgeschlossen
bool SF_StartDim(uint8_t Helligkeit);


// Lauflicht über alle LED's auf dem Spielfeld
// Funktion startet das Lauflicht mit der angegebenen Farbe und Helligkeit
// Mit SF_LauflichtEnded() kann das Ende abgefragt werden
void SF_StartLauflicht(GlobalTypes_Farbe_t farbe, uint8_t helligkeit);


// Lauflicht über alle LED's auf dem Spielfeld
// Return true, wenn noch am Laufen
// Return false, wenn kein Lauflicht aktiv
bool SF_LauflichtAmLaufen(void);


// Die Figur eines Spielers wird auf dem Spielfeld auf den Anfang gesetzt.
// Vor einem neuen Spiel muss diese Funktion für jeden Spieler und jede
// Figur einmal aufgerufen werden (also 4 x).
// Spieler: "Nummer" des Spielers
// Figur: "Nummer" der Figur
// Farbe: Farbe dieser Figur
// Helligkeit: Helligkeit dieser Figur
void SF_FiguresSetToStart(GlobalTypes_Spieler_t Spieler,
                          GlobalTypes_Figur_t Figur,
                          GlobalTypes_Farbe_t Farbe,
                          int Helligkeit);


// Eine Figur eines Spielers wird von der alten zur neuen Position verschoben.
// Die entsprechenden Daten müssen an die Funktion übergeben werden
// Spieler: "Nummer" des Spielers
// Figur: "Nummer" der Figur
// NewPos: Neue Position der Figur
// BranchOn1: true oder false
// BranchOn2: true oder false
// BranchOn3: true oder false
void SF_MovePlayerFigure(GlobalTypes_Spieler_t Spieler,
                         GlobalTypes_Figur_t Figur,
                         int NewPos,
                         bool BranchOn1,
                         bool BranchOn2,
                         bool BranchOn3);


// Abfrage ob die Figur eines Spielers die neue Position erreicht hat
// Return true, wenn die neue Position erreicht ist
// Return false, wenn die neue Position noch nicht erreicht ist
bool SF_PlayerFigureHasMoved(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur);


// Funktion muss im Main-Loop laufend aufgerufen werden
// Die Funktion ist nicht blockierend
void SF_OperateSpielfeld_Main(void);


// Funktion berechnet auf Grund der "FigureData" den neuen Weg
// Die Funktion darf nur im Modul "SpielfeldLed.cpp" aufgerufen werden
void SF_CalcPlayerWay(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur);

#endif
