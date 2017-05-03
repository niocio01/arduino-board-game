#ifndef SPIELFELDLED_H
#define SPIELFELDLED_H

#include <inttypes.h>
#include "GlobalTypes.h"

// Typendefinitionen (der global bekannten Daten)
typedef struct FigureData_tag
{
  int NewPos;                   // Neue Position, wird vom Spiel verwaltet
  int ActPos;                   // Wird für die Schritte verwendet
  GlobalTypes_Farbe_t Farbe;    // Farbe der Figur
  int Helligkeit;               // Helligkeit der Figur
  bool BranchOn1;               // Branch 1 ist aktiv
  bool BranchOn2;               // Branch 2 ist aktiv
  bool BranchOn3;               // Branch 3 ist aktiv
  int  ActLEDid;                // ID des aktuellen LED's. Nur im Modul "SpielfeldLed.cpp" verwenden
} FigureData_t;


// Funktion muss vor dem Start einmal aufgerufen werden
void SF_InitData(void);


// Grundbeleuchtung einschalten
// "Helligkeit" gilt für alle LED's
void SF_StartDim(uint8_t Helligkeit);


// Lauflicht über alle LED's auf dem Spielfeld
// Funktion startet das Lauflicht mit der angegebenen Farbe und Helligkeit
// Mit SF_LauflichtEnded() kann das Ende abgefragt werden
void SF_StartLauflicht(GlobalTypes_Farbe_t farbe, uint8_t helligkeit);


// Lauflicht über alle LED's auf dem Spielfeld
// Return true, wenn noch am Laufen
// Return false, wenn kein Lauflicht aktiv
bool SF_LauflichtAmLaufen(void);


// Beide Figuren beider Spieler werden auf dem Spielfeld auf den Anfang gesetzt
// Vor dem Aufruf der Funktion müssen die "FigureData_t" beider Spieler initialisiert werden
// SF_Player1/2_Figure1.NewPos = 0;
// SF_Player1/2_Figure1.Farbe = ....;
// SF_Player1/2_Figure1.Helligkeit = ...;
// SF_Player1/2_Figure1.BranchOn1 = false;
// SF_Player1/2_Figure1.BranchOn2 = false;
// SF_Player1/2_Figure1.BranchOn3 = false;
void SF_FiguresSetToStart(void);


// Eine Figur eines Spielers wird von der alten zur neuen Position verschoben
// Vorgängig müssen die entsprechenden "FigureData_t" gesetzt werden
// SF_Player1_Figure1.NewPos = ??;
// SF_Player1_Figure1.BranchOn1 = ??;
// SF_Player1_Figure1.BranchOn2 = ??;
// SF_Player1_Figure1.BranchOn3 = ??;
void SF_MovePlayerFigure(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur);


// Abfrage ob die Figur eines Spielers die neue Position erreicht hat
// Return true, wenn die neue Position erreicht ist
// Return false, wenn die neue Position noch nicht erreicht ist
bool SF_PlayerFigureHasMoved(GlobalTypes_Spieler_t Spieler, GlobalTypes_Figur_t Figur);


// Funktion muss im Main-Loop laufend aufgerufen werden
// Die Funktion ist nicht blockierend
void SF_OperateSpielfeld_Main(void);

#endif
