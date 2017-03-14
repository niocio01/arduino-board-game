#include "StatusLed.h"



void StatusLed_Setzen(GlobalLed_Spieler_t Spieler,
  StatusLed_StatusLedName_t StatusledName,
  StatusLed_LedZustand_t LedZustand)
  {
    if (Spieler == spielerEins)
    {
      switch (StatusLedName)
      {
        case AmZug:
          switch (LedZustand)
          {
            case ein:
            LedTreiber_LedSchalten(1, Gruen);
            break;

            case Aus:
            LedTreiber_LedSchalten(1, Aus);
            break;
          }
        break;

        case RFID:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(2, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(2, Aus);
          break;
        }
        break;

        case Minigame:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(3, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(3, Aus);
          break;
        }
        break;
      }
    }
    else
    {
      switch(StatusLedName)
      {
        case AmZug:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(10, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(10, Aus);
          break;
        }
        break;

        case RFID:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(11, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(11, Aus);
          break;
        }
        break;

        case Minigame:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(12, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(12, Aus);
          break;
        }
        break;
      }
  }
