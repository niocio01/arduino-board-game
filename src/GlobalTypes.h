#ifndef GLOBALTypes_H
#define GLOBALTypes_H

typedef enum
{
  SpielerEins,
  SpielerZwei
} GlobalTypes_Spieler_t; // def für Spielseite!!

typedef enum
{
  Schwarz,
  Weiss,
  Rot,
  Gruen,
  Blau,
  Gelb,
  Violett
} GlobalTypes_Farbe_t;

typedef enum
{
  AktiverSpieler,
  PassiverSpieler
} GlobalTypes_AktiverSpieler_t;

typedef enum
{
  FigureEins,
  FigureZwei
} GlobalTypes_Figur_t;

#endif
