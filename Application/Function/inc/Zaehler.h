#ifndef ZAEHLER_H
#define ZAEHLER_H

#include <inttypes.h>

void Zaehler_Spieler1Figur1Erhoehen(uint8_t wert);
void Zaehler_Spieler1Figur2Erhoehen(uint8_t wert);
void Zaehler_Spieler2Figur1Erhoehen(uint8_t wert);
void Zaehler_Spieler2Figur2Erhoehen(uint8_t wert);

void Zaehler_Spieler1Figur1Erniedrigen(uint8_t wert);
void Zaehler_Spieler1Figur2Erniedrigen(uint8_t wert);
void Zaehler_Spieler2Figur1Erniedrigen(uint8_t wert);
void Zaehler_Spieler2Figur2Erniedrigen(uint8_t wert);

uint8_t Zaehler_Spieler1Figur1ZaehlerStandLesen(void);
uint8_t Zaehler_Spieler1Figur2ZaehlerStandLesen(void);
uint8_t Zaehler_Spieler2Figur1ZaehlerStandLesen(void);
uint8_t Zaehler_Spieler2Figur2ZaehlerStandLesen(void);

void Zaehler_Spieler1ZaehlerStandLoeschen(void);
void Zaehler_Spieler2ZaehlerStandLoeschen(void);

#endif
