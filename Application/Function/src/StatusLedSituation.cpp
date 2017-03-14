#include "StatusLedSituation.h"
#include "Statusled.h"

void StatusLedSituationSetzten(StatusLedSituation_spieler_t spieler,
StatusLedSituation_Situation_t situation)
{
  if (spieler == SpielerEins)
  {
    switch (situation)
    {
      case Spielzug:
      StatusLed_Setzen(SpielerEins,AmZug,Ein);
      StatusLed_Setzen(SpielerEins,RFID,Ein);
      StatusLed_Setzen(SpielerEins,Minigame,Aus);

      StatusLed_Setzen(SpielerZwei,AmZug,Aus);
      StatusLed_Setzen(SpielerZwei,RFID,Aus);
      StatusLed_Setzen(SpielerZwei,Minigame,Aus);

      case Minigame:
      StatusLed_Setzen(SpielerEins,AmZug,Ein);
      StatusLed_Setzen(SpielerEins,RFID,Aus);
      StatusLed_Setzen(SpielerEins,Minigame,Aus);

      StatusLed_Setzen(SpielerZwei,AmZug,Aus);
      StatusLed_Setzen(SpielerZwei,RFID,Aus);
      StatusLed_Setzen(SpielerZwei,Minigame,Aus);
    }
  }
  else
  {
    switch (situation)
    {
      case Spielzug:
      StatusLed_Setzen(SpielerZwei,AmZug,Ein);
      StatusLed_Setzen(SpielerZwei,RFID,Ein);
      StatusLed_Setzen(SpielerZwei,Minigame,Aus);

      StatusLed_Setzen(SpielerEins,AmZug,Aus);
      StatusLed_Setzen(SpielerEins,RFID,Aus);
      StatusLed_Setzen(SpielerEins,Minigame,Aus);

      case Minigame:
      StatusLed_Setzen(SpielerZwei,AmZug,Ein);
      StatusLed_Setzen(SpielerZwei,RFID,Aus);
      StatusLed_Setzen(SpielerZwei,Minigame,Aus);

      StatusLed_Setzen(SpielerEins,AmZug,Aus);
      StatusLed_Setzen(SpielerEins,RFID,Aus);
      StatusLed_Setzen(SpielerEins,Minigame,Aus);
      }
    }
  }
}
