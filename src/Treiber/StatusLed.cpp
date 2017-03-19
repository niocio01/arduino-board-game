#include "Treiber/StatusLed.h"
#include "Treiber/LedTreiber.h"



void StatusLed_Setzen(GlobalTypes_Spieler_t spieler,
  StatusLed_Name_t name,
  StatusLed_Zustand_t zustand)
  {
    if (spieler == SpielerEins)
    {
      switch (name)
      {
        case AmZug_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(1, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(1, Schwarz);
          break;
        }
        break;

        case RFID_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(2, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(2, Schwarz);
          break;
        }
        break;

        case Minigame_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(3, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(3, Schwarz);
          break;
        }
        break;
      }
    }
    else
    {
      switch(name)
      {
        case AmZug_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(10, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(10, Schwarz);
          break;
        }
        break;

        case RFID_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(11, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(11, Schwarz);
          break;
        }
        break;

        case Minigame_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(12, Gruen);
          break;

          case Aus:
          LedTreiber_LedSchalten(12, Schwarz);
          break;
        }
        break;
      }
    }
  }
