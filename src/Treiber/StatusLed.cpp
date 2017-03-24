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
          LedTreiber_LedSchalten(253, Gruen, 50);
          break;

          case Aus:
          LedTreiber_LedSchalten(253, Rot, 10);
          break;
        }
        break;

        case RFID_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(254, Gruen, 50);
          break;

          case Aus:
          LedTreiber_LedSchalten(254, Rot, 10);
          break;
        }
        break;

        case Minigame_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(255, Gruen, 50);
          break;

          case Aus:
          LedTreiber_LedSchalten(255, Rot, 10);
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
          LedTreiber_LedSchalten(261, Gruen, 50);
          break;

          case Aus:
          LedTreiber_LedSchalten(261, Rot, 10);
          break;
        }
        break;

        case RFID_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(262, Gruen, 50);
          break;

          case Aus:
          LedTreiber_LedSchalten(262, Rot, 10);
          break;
        }
        break;

        case Minigame_Led:
        switch (zustand)
        {
          case Ein:
          LedTreiber_LedSchalten(263, Gruen, 50);
          break;

          case Aus:
          LedTreiber_LedSchalten(263, Rot, 10);
          break;
        }
        break;
      }
    }
  }
