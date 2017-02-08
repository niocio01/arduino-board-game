#include <StatusLed.h>


void StatusLed(StatusLed_Spieler_t Spieler,
  StatusLed_StatusLedName_t StatusledName,
  StatusLed_LedZustand_t LedZustand)
  {
    switch (Spieler)
    {
    case eins:
      switch (StatusLedName)
      {
        case AmZug:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(1, grün);
          break;

          case aus:
          LedTreiber_LedSchalten(1, aus);
          break;
        }
        break;

        case RFID:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(2, grün);
          break;

          case aus:
          LedTreiber_LedSchalten(2, aus);
          break;
        }
        break;

        case Minigame:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(3, grün);
          break;

          case aus:
          LedTreiber_LedSchalten(3, aus);
          break;
        }
        break;
      }
    }
    case zwei:
      switch(StatusLedName)
      {
        case AmZug:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(10, grün);
          break;

          case aus:
          LedTreiber_LedSchalten(10, aus);
          break;
        }
        break;

        case RFID:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(11, grün);
          break;

          case aus:
          LedTreiber_LedSchalten(11, aus);
          break;
        }
        break;

        case Minigame:
        switch (LedZustand)
        {
          case ein:
          LedTreiber_LedSchalten(12, grün);
          break;

          case aus:
          LedTreiber_LedSchalten(12, aus);
          break;
        }
        break;

  }
