#include "Karten/Minigames/Simon.h"
#include "globaltypes.h"
#include "PlayerManager.h"
#include "Messages.h"
#include "inttypes.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "arduino.h"

const uint8_t DimHelligkeit = 10;
const uint8_t BrightHelligkeit = 100;
const uint16_t ZeitZwischenFarben = 1000;
const uint16_t AnzeigedauerFarbe = 500;

GlobalTypes_Spieler_t aktiverSpieler;
Messages_values leer6;

const uint8_t keine = 0;
const uint8_t rot = 1;
const uint8_t gruen = 2;
const uint8_t gelb = 3;
const uint8_t blau = 4;


const uint8_t ID_1 = 0;
const uint8_t ID_2 = 1;
const uint8_t ID_3 = 2;
const uint8_t ID_4 = 3;
const uint8_t ID_5 = 4;
const uint8_t ID_6 = 5;
const uint8_t ID_7 = 6;
const uint8_t ID_8 = 7;
const uint8_t ID_9 = 8;
const uint8_t ID_10 = 9;
const uint8_t ID_11 = 10;

uint16_t FeldRot[11];
uint16_t FeldGruen[11];
uint16_t FeldGelb[11];
uint16_t FeldBlau[11];
uint8_t sequence[20];
static uint8_t SequenzLaenge;
static uint8_t aktuellerSequenzZeigeSchritt;
static uint8_t aktuellerSequenzLoeseSchritt;
static uint32_t lastUpdateTime;
static uint32_t lastColorChange;
static uint8_t aktuelleFarbe = 0;
static uint8_t alteFarbe = 0;


static bool MSGShown;
static bool FirstPlayerMSGBestaetigt;
static bool SecondPlayerMSGBestaetigt;
static bool addToSequence = true;
static bool playSequence;


void Simon_InitData(void);
void Simon_ShowColor_Run(void);


void Simon_Run(void)
{
  Simon_ShowColor_Run();
  if (!MSGShown)
  {
    MSGShown = true;
    LedTreiber_ControllsBlack();
    Simon_InitData();

    if (PlayerManager_SpielerEinsAmZug())
    {
      aktiverSpieler = SpielerEins;
      Messages_ZeigeNachricht(SpielerEins, MSG_Sequenz, &leer6);
      Messages_ZeigeNachricht(SpielerZwei, MSG_GegnerSpielt, &leer6);
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
    }
    else
    {
      aktiverSpieler = SpielerZwei;
      Messages_ZeigeNachricht(SpielerZwei, MSG_Sequenz, &leer6);
      Messages_ZeigeNachricht(SpielerEins, MSG_GegnerSpielt, &leer6);
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
    }
  }
  else if(!FirstPlayerMSGBestaetigt)
  {
    if (TasterHandler_Klick(aktiverSpieler, TasterEins))
    {
      TasterLed_Setzen(aktiverSpieler, LedEins, Rot);
      TasterLed_Setzen(aktiverSpieler, LedZwei, Gruen);
      TasterLed_Setzen(aktiverSpieler, LedDrei, Gelb);
      TasterLed_Setzen(aktiverSpieler, LedVier, Blau);
      FirstPlayerMSGBestaetigt = true;
    }
  }
  else if(FirstPlayerMSGBestaetigt)
  {
    if (playSequence)
    {
      if (addToSequence)
      {
        addToSequence = false;
        uint8_t newColor = random(1, 4);
        sequence[SequenzLaenge] = newColor;
        SequenzLaenge ++;
      }
      if (aktuellerSequenzZeigeSchritt <= SequenzLaenge)
      {
        if ((millis() - lastUpdateTime) > ZeitZwischenFarben)
        {
          aktuelleFarbe = sequence[aktuellerSequenzZeigeSchritt];
          aktuellerSequenzZeigeSchritt ++;
        }
      }
      else
      {
        // playSequence = false;
      }

    }
    else // nachmachen
    {
      if (TasterHandler_Klick(aktiverSpieler, TasterEins))
      {
        aktuelleFarbe = rot;
      }
      if (TasterHandler_Klick(aktiverSpieler, TasterZwei))
      {
        aktuelleFarbe = gruen;
      }
      if (TasterHandler_Klick(aktiverSpieler, TasterDrei))
      {
        aktuelleFarbe = gelb;
      }
      if (TasterHandler_Klick(aktiverSpieler, TasterVier))
      {
        aktuelleFarbe = blau;
      }
      if (aktuelleFarbe == sequence[aktuellerSequenzLoeseSchritt])
      {
        aktuellerSequenzLoeseSchritt ++;
        if (aktuellerSequenzLoeseSchritt == SequenzLaenge)
        {
          playSequence = true;
          addToSequence = true;
          if (aktiverSpieler == SpielerEins)
          {
            LedTreiber_LedSchalten(aktuellerSequenzLoeseSchritt -1, Gruen, 100);
          }
          else // P2
          {
            LedTreiber_LedSchalten(aktuellerSequenzLoeseSchritt + 61, Gruen, 100);
          }
        }
      }
    }
  }
}

void Simon_ShowColor_Run(void)
{
  if (((millis() - lastColorChange) > AnzeigedauerFarbe) or aktuelleFarbe != alteFarbe)
  {
    if ((millis() - lastColorChange) > AnzeigedauerFarbe)
    {
      aktuelleFarbe = keine;
      alteFarbe = keine;
    }

    if (aktuelleFarbe != alteFarbe)
    {
      alteFarbe = aktuelleFarbe;
    }

    lastColorChange = millis();

    switch (aktuelleFarbe)
    {

      case keine:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, DimHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, DimHelligkeit);
      }
      break;

      case rot:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, BrightHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, DimHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, DimHelligkeit);
      }
      break;

      case gruen:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, BrightHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, DimHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, DimHelligkeit);
      }
      break;

      case gelb:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, BrightHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, DimHelligkeit);
      }
      break;

      case blau:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, DimHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, BrightHelligkeit);
      }
      break;
    }
    LedTreiber_LedAnzeigen();
  }
}


void Simon_InitData(void)
{
  FeldRot[ID_1] = 200;
  FeldRot[ID_2] = 211;
  FeldRot[ID_3] = 212;
  FeldRot[ID_4] = 226;
  FeldRot[ID_5] = 227;
  FeldRot[ID_6] = 228;
  FeldRot[ID_7] = 248;
  FeldRot[ID_8] = 249;
  FeldRot[ID_9] = 250;
  FeldRot[ID_10] = 251;
  FeldRot[ID_11] = 252;

  FeldGruen[ID_1] = 198;
  FeldGruen[ID_2] = 208;
  FeldGruen[ID_3] = 209;
  FeldGruen[ID_4] = 222;
  FeldGruen[ID_5] = 223;
  FeldGruen[ID_6] = 224;
  FeldGruen[ID_7] = 242;
  FeldGruen[ID_8] = 243;
  FeldGruen[ID_9] = 244;
  FeldGruen[ID_10] = 245;
  FeldGruen[ID_11] = 246;

  FeldGelb[ID_1] = 196;
  FeldGelb[ID_2] = 205;
  FeldGelb[ID_3] = 206;
  FeldGelb[ID_4] = 218;
  FeldGelb[ID_5] = 219;
  FeldGelb[ID_6] = 220;
  FeldGelb[ID_7] = 236;
  FeldGelb[ID_8] = 237;
  FeldGelb[ID_9] = 238;
  FeldGelb[ID_10] = 239;
  FeldGelb[ID_11] = 240;

  FeldBlau[ID_1] = 194;
  FeldBlau[ID_2] = 202;
  FeldBlau[ID_3] = 203;
  FeldBlau[ID_4] = 214;
  FeldBlau[ID_5] = 215;
  FeldBlau[ID_6] = 216;
  FeldBlau[ID_7] = 230;
  FeldBlau[ID_8] = 231;
  FeldBlau[ID_9] = 232;
  FeldBlau[ID_10] = 233;
  FeldBlau[ID_11] = 234;
}
