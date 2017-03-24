#ifndef SPIELFELDLED_H
#define SPIELFELDLED_H

#include "GlobalTypes.h"

// Daten mit den Anzahl Schritten in den Teilsegmenten
struct SpielfeldData {
  int StepsSegmVB1;       // Segment bis Branch 1
  int StepsSegmIB1;       // Kürzeres Segment bei Branch 1
  int StepsSegmB1;        // Längeres Segment bei Branch 1
  int StepsSegmVB2;       // Segment bis Branch 2
  int StepsSegmIB2;       // Kürzeres Segment bei Branch 2
  int StepsSegmB2;        // Längeres Segment bei Branch 2
  int StepsSegmVB3;       // Segment bis Branch 3
  int StepsSegmIB3;       // Kürzeres Segment bei Branch 3
  int StepsSegmB3;        // Längeres Segment bei Branch 3
  int StepsSegmVK;        // Segment bis zum Kreis
  int StepsSegmK;         // Segment im Kreis
};


struct FigureData {
  int NewPos;                   // Neue Position, wird vom Spiel verwaltet
  int ActPos;                   // Wird für die Schritte verwendet
  GlobalTypes_Farbe_t Farbe;    // Farbe der Figur
  bool BranchOn1;               // Branch 1 ist aktiv
  bool BranchOn2;               // Branch 2 ist aktiv
  bool BranchOn3;               // Branch 3 ist aktiv
};


// Grundbeleuchtung einschalten
// Return true, wenn abgeschlossen
// Return false, wenn noch am laufen
bool SF_StartDim(void);


// Lauflicht über alle LED's auf dem Spielfeld
// Return true, wenn abgeschlossen
// Return false, wenn noch am laufen
bool SF_Lauflicht(void);


// Beide Figuren beider Spieler werden auf dem Spielfeld auf den Anfang gesetzt
// Vor dem Aufruf der Funktion müssen die "FigureData" initialisiert werden
// Player1_Figure1.NewPos = 0;
// Player1_Figure1.Farbe = ....;
// Player1_Figure1.BranchOn1 = false;
// Player1_Figure1.BranchOn2 = false;
// Player1_Figure1.BranchOn3 = false;
void SF_FiguresSetToStart(void);


// Eine Figur eines Spielers wird von der alten zur neuen Position verschoben
// Vorgängig müssen die entsprechenden "FigureData" gesetzt werden
// Player1_Figure1.NewPos = ??;
// Player1_Figure1.BranchOn1 = ??;
// Player1_Figure1.BranchOn2 = ??;
// Player1_Figure1.BranchOn3 = ??;
void SF_MovePlayerFigure(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur);

// Abfrage ob die Figur eines Spielers die neue Position erreicht hat
// Return true, wenn die neue Position erreicht ist
// Return false, wenn die neue Position noch nicht erreicht ist
bool SF_PlayerFigureHasMoved(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur);


// Funktion muss im Main-Loop laufend aufgerufen werden
// Die Funktion ist nicht blockierend
void SF_OperateSpielfeld(void);


#endif
