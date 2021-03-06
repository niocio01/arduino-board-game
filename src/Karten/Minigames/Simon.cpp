#include "Karten/Minigames/Simon.h"
#include "globaltypes.h"
#include "PlayerManager.h"
#include "Messages.h"
#include "inttypes.h"
#include "Treiber/LedTreiber.h"
#include "Treiber/TasterLed.h"
#include "Treiber/TasterHandler.h"
#include "arduino.h"
#include "Pitches.h"
#include "Treiber/SpeakerTreiber.h"
#include "Karten/Minigames/MinigameManager.h"

const uint8_t laengeStartSequenz = 3;
const uint8_t maxSequenzLaenge = 20;
const uint8_t DimHelligkeit = 10; // helligkeit die nicht aktive felder erhalten
const uint8_t BrightHelligkeit = 100; // helligkeit die aktive felder erhalten
const uint16_t ZeitZwischenFarben = 400;
const uint16_t AnzeigedauerFarbe = 200;
const uint16_t ZeitZwischenSequenzen = 1000;
const uint16_t TonDauer = 300;

GlobalTypes_Spieler_t aktiverSpieler;
Messages_values leer6;

const uint8_t keine = 1;
const uint8_t rot = 2;
const uint8_t gruen = 3;
const uint8_t gelb = 4;
const uint8_t blau = 5;

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
uint8_t sequence[maxSequenzLaenge];
static uint8_t SequenzLaenge;
static uint8_t aktuellerSequenzZeigeSchritt;
static uint8_t aktuellerSequenzLoeseSchritt;
static uint32_t currentTime;
static uint32_t lastFarbeTime;
static uint32_t lastColorChange;
static uint8_t aktuelleFarbe = keine;
static uint8_t alteFarbe = 0;
static uint8_t neueFarbe = keine;
static uint8_t score_P1 = 0;
static uint8_t score_P2 = 0;


static bool PlayerDecided;
static bool MSGShown;
static bool MSGBestaetigt;
static bool addToSequence = true;
static bool playSequence = true;
static bool sequenzNachmachen = false;
static bool switchColor = true;
static bool preNextSequenz;
static bool P1_Done = false;
static bool P2_Done = false;

void Simon_InitData(void);
void Simon_ShowColor_Run(void);


void Simon_Run(void)
{
  if (!PlayerDecided)
  {
    if (PlayerManager_SpielerEinsAmZug())
    {
      aktiverSpieler = SpielerEins;
    }
    else
    {
      aktiverSpieler = SpielerZwei;
    }
  }
  Simon_ShowColor_Run();
  if (!MSGShown)
  {
    MSGShown = true;
    LedTreiber_ControllsBlack();
    Simon_InitData();
    neueFarbe = keine;
    Simon_ShowColor_Run();

    if (aktiverSpieler == SpielerEins)
    {
      Messages_ZeigeNachricht(SpielerEins, MSG_Sequenz, &leer6);
      Messages_ZeigeNachricht(SpielerZwei, MSG_GegnerSpielt, &leer6);
      TasterLed_Setzen(SpielerEins, LedEins, Gruen);
    }
    else
    {
      Messages_ZeigeNachricht(SpielerZwei, MSG_Sequenz, &leer6);
      Messages_ZeigeNachricht(SpielerEins, MSG_GegnerSpielt, &leer6);
      TasterLed_Setzen(SpielerZwei, LedEins, Gruen);
    }
  }
  else if(!MSGBestaetigt)
  {
    if (TasterHandler_Klick(aktiverSpieler, TasterEins))
    {
      TasterLed_Setzen(aktiverSpieler, LedEins, Rot);
      TasterLed_Setzen(aktiverSpieler, LedZwei, Gruen);
      TasterLed_Setzen(aktiverSpieler, LedDrei, Blau);
      TasterLed_Setzen(aktiverSpieler, LedVier, Gelb);
      MSGBestaetigt = true;
      lastFarbeTime = currentTime + ZeitZwischenFarben;
    }
  }
  else if(MSGBestaetigt)
  {
    if (addToSequence)
    {
      addToSequence = false;
      playSequence = true;
      aktuellerSequenzZeigeSchritt = 0;
      randomSeed(analogRead(4));
      if (SequenzLaenge == 0)
      {
        for (SequenzLaenge = 0; SequenzLaenge <= laengeStartSequenz-1; SequenzLaenge++)
        {
          uint8_t newColor = random(rot, blau+1);
          sequence[SequenzLaenge] = newColor;
        }
      }
      else
      {
        uint8_t newColor = random(rot, blau+1);
        sequence[SequenzLaenge] = newColor;
        SequenzLaenge ++;
      }
    }

    if (playSequence)
    {
      if (preNextSequenz)
      {
        if (currentTime > lastFarbeTime + ZeitZwischenSequenzen)
        {
          preNextSequenz = false;
          lastFarbeTime = millis();
          neueFarbe = keine;
        }
      }
      else if (aktuellerSequenzZeigeSchritt <= SequenzLaenge)
      {
        if (currentTime > lastFarbeTime + ZeitZwischenFarben)
        {
          lastFarbeTime = currentTime;
          neueFarbe = sequence[aktuellerSequenzZeigeSchritt];
          aktuellerSequenzZeigeSchritt ++;
        }
      }
      else
      {
        playSequence = false;
        sequenzNachmachen = true;
      }
    }

    if (sequenzNachmachen)
    {
      uint8_t aktuelleAuswahl = 0;

      if (TasterHandler_Klick(aktiverSpieler, TasterEins))
      {
        neueFarbe = rot;
        aktuelleAuswahl = rot;
        SpeakerTreiber_PlayTone(NOTE_C4, TonDauer);
      }
      if (TasterHandler_Klick(aktiverSpieler, TasterZwei))
      {
        neueFarbe = gruen;
        aktuelleAuswahl = gruen;
        SpeakerTreiber_PlayTone(NOTE_G3, TonDauer);
      }
      if (TasterHandler_Klick(aktiverSpieler, TasterDrei))
      {
        neueFarbe = blau;
        aktuelleAuswahl = blau;
        SpeakerTreiber_PlayTone(NOTE_C3, TonDauer);
      }
      if (TasterHandler_Klick(aktiverSpieler, TasterVier))
      {
        neueFarbe = gelb;
        aktuelleAuswahl = gelb;
        SpeakerTreiber_PlayTone(NOTE_E3, TonDauer);

      }
      if (aktuelleAuswahl != 0)
      {
        if (aktuelleAuswahl == sequence[aktuellerSequenzLoeseSchritt])
        {
          aktuellerSequenzLoeseSchritt ++;

          if (aktuellerSequenzLoeseSchritt == SequenzLaenge) // sequenz gelöst
          {
            for (uint8_t i = 0; i <= 10 ; i++)
            {
              LedTreiber_LedSetzen(FeldRot[i], Rot, BrightHelligkeit);
              LedTreiber_LedSetzen(FeldGruen[i], Gruen, BrightHelligkeit);
              LedTreiber_LedSetzen(FeldGelb[i], Gelb, BrightHelligkeit);
              LedTreiber_LedSetzen(FeldBlau[i], Blau, BrightHelligkeit);
            }

            playSequence = true;
            addToSequence = true;
            sequenzNachmachen = false;
            aktuellerSequenzLoeseSchritt = 0;
            preNextSequenz = true;
            lastFarbeTime = millis();
            neueFarbe = 0;
            aktuelleFarbe = keine;

            if (aktiverSpieler == SpielerEins)
            {
              LedTreiber_LedSetzen(SequenzLaenge - laengeStartSequenz , Gruen, 100);
            }
            else // P2
            {
              LedTreiber_LedSetzen(SequenzLaenge - laengeStartSequenz + 62, Gruen, 100);
            }
            LedTreiber_LedAnzeigen();
          }
        }
        else // fehler gemacht
        {
          if (aktiverSpieler == SpielerEins)
          {
            score_P1 = SequenzLaenge;
            P1_Done = true;
            aktiverSpieler = SpielerZwei;
          }
          else
          {
            score_P2 = SequenzLaenge;
            P2_Done = true;
            aktiverSpieler = SpielerEins;
          }

          LedTreiber_ControllsBlack();
          aktuelleFarbe = keine;
          neueFarbe = 0;
          SpeakerTreiber_PlayTone(NOTE_A2, 400);

          PlayerDecided = true; // reset for next Player
          MSGShown = false;
          MSGBestaetigt = false;
          addToSequence = true;
          playSequence = false;
          sequenzNachmachen = false;
          preNextSequenz = false;
          aktuellerSequenzZeigeSchritt = 0;
          aktuellerSequenzLoeseSchritt = 0;
          SequenzLaenge = 0;
          for (uint8_t i = 0; i <= maxSequenzLaenge; i++)
          {
            sequence[i] = 0;
          }

          if (P1_Done and P2_Done) // reset the rest and end game
          {
            P1_Done = false;
            P2_Done = false;

            if (score_P1 < score_P2)
            {
              PlayerDecided = false;
              score_P1 = 0;
              score_P2 = 0;
              MinigameManager_GameEnded(Win_SpielerZwei);
            }
            else if (score_P2 < score_P1)
            {
              PlayerDecided = false;
              score_P1 = 0;
              score_P2 = 0;
              MinigameManager_GameEnded(Win_SpielerEins);
            }
            else if (score_P1 == score_P2)
            {
              PlayerDecided = false;
              score_P1 = 0;
              score_P2 = 0;
              MinigameManager_GameEnded(Win_Unentschieden);
            }
          }
        }
      }
    }
  }
}

void Simon_ShowColor_Run(void)
{
  currentTime = millis();

  if (currentTime > (lastColorChange + AnzeigedauerFarbe) and aktuelleFarbe != keine)
  {
    aktuelleFarbe = keine;
    switchColor = true;
  }

  if (neueFarbe != 0) //else
  {
    aktuelleFarbe = neueFarbe;
    neueFarbe = 0;
    switchColor = true;
    lastColorChange = currentTime;
  }

  if (switchColor)
  {
    switchColor = false;
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
      SpeakerTreiber_PlayTone(NOTE_C4, TonDauer);
      break;

      case gruen:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, BrightHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, DimHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, DimHelligkeit);
      }
      SpeakerTreiber_PlayTone(NOTE_G3, TonDauer);
      break;

      case gelb:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, BrightHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, DimHelligkeit);
      }
      SpeakerTreiber_PlayTone(NOTE_E3, TonDauer);
      break;

      case blau:
      for (uint8_t i = 0; i <= 10 ; i++)
      {
        LedTreiber_LedSetzen(FeldRot[i], Rot, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGruen[i], Gruen, DimHelligkeit);
        LedTreiber_LedSetzen(FeldGelb[i], Gelb, DimHelligkeit);
        LedTreiber_LedSetzen(FeldBlau[i], Blau, BrightHelligkeit);
      }
      SpeakerTreiber_PlayTone(NOTE_C3, TonDauer);
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

  FeldGruen[ID_1] = 194;
  FeldGruen[ID_2] = 202;
  FeldGruen[ID_3] = 203;
  FeldGruen[ID_4] = 214;
  FeldGruen[ID_5] = 215;
  FeldGruen[ID_6] = 216;
  FeldGruen[ID_7] = 230;
  FeldGruen[ID_8] = 231;
  FeldGruen[ID_9] = 232;
  FeldGruen[ID_10] = 233;
  FeldGruen[ID_11] = 234;

  FeldGelb[ID_1] = 198;
  FeldGelb[ID_2] = 208;
  FeldGelb[ID_3] = 209;
  FeldGelb[ID_4] = 222;
  FeldGelb[ID_5] = 223;
  FeldGelb[ID_6] = 224;
  FeldGelb[ID_7] = 242;
  FeldGelb[ID_8] = 243;
  FeldGelb[ID_9] = 244;
  FeldGelb[ID_10] = 245;
  FeldGelb[ID_11] = 246;

  FeldBlau[ID_1] = 196;
  FeldBlau[ID_2] = 205;
  FeldBlau[ID_3] = 206;
  FeldBlau[ID_4] = 218;
  FeldBlau[ID_5] = 219;
  FeldBlau[ID_6] = 220;
  FeldBlau[ID_7] = 236;
  FeldBlau[ID_8] = 237;
  FeldBlau[ID_9] = 238;
  FeldBlau[ID_10] = 239;
  FeldBlau[ID_11] = 240;
}
