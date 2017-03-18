#include "StatusLedSituation.h"
#include "Statusled.h"

void StatusLedSituationSetzten(GlobalTypes_Spieler_t spieler,
  StatusLedSituation_Situation_t situation)
  {
    if (spieler == SpielerEins)
    {
      switch (situation)
      {
        case Spielzug:
        StatusLed_Setzen(SpielerEins,AmZug_Led,Ein);
        StatusLed_Setzen(SpielerEins,RFID_Led,Ein);
        StatusLed_Setzen(SpielerEins,Minigame_Led,Aus);

        StatusLed_Setzen(SpielerZwei,AmZug_Led,Aus);
        StatusLed_Setzen(SpielerZwei,RFID_Led,Aus);
        StatusLed_Setzen(SpielerZwei,Minigame_Led,Aus);

        case Minigame:
        StatusLed_Setzen(SpielerEins,AmZug_Led,Ein);
        StatusLed_Setzen(SpielerEins,RFID_Led,Aus);
        StatusLed_Setzen(SpielerEins,Minigame_Led,Aus);

        StatusLed_Setzen(SpielerZwei,AmZug_Led,Aus);
        StatusLed_Setzen(SpielerZwei,RFID_Led,Aus);
        StatusLed_Setzen(SpielerZwei,Minigame_Led,Aus);
      }
    }
    else
    {
      switch (situation)
      {
        case Spielzug:
        StatusLed_Setzen(SpielerZwei,AmZug_Led,Ein);
        StatusLed_Setzen(SpielerZwei,RFID_Led,Ein);
        StatusLed_Setzen(SpielerZwei,Minigame_Led,Aus);

        StatusLed_Setzen(SpielerEins,AmZug_Led,Aus);
        StatusLed_Setzen(SpielerEins,RFID_Led,Aus);
        StatusLed_Setzen(SpielerEins,Minigame_Led,Aus);

        case Minigame:
        StatusLed_Setzen(SpielerZwei,AmZug_Led,Ein);
        StatusLed_Setzen(SpielerZwei,RFID_Led,Aus);
        StatusLed_Setzen(SpielerZwei,Minigame_Led,Aus);

        StatusLed_Setzen(SpielerEins,AmZug_Led,Aus);
        StatusLed_Setzen(SpielerEins,RFID_Led,Aus);
        StatusLed_Setzen(SpielerEins,Minigame_Led,Aus);
      }
    }
  }
