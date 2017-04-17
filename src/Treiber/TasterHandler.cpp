#include "Treiber/TasterHandler.h"
#include "Treiber/TasterTreiber.h"
#include "Treiber/LedTreiber.h"


static bool LastStateP1T1 = true;
static bool LastStateP1T2 = true;
static bool LastStateP1T3 = true;
static bool LastStateP1T4 = true;

static bool LastStateP2T1 = true;
static bool LastStateP2T2 = true;
static bool LastStateP2T3 = true;
static bool LastStateP2T4 = true;

bool TasterHandler_Klick(GlobalTypes_Spieler_t spieler, TasterHandler_Tasten_t taste)
{
  bool newState;

  if (spieler == SpielerEins)
  {
    switch (taste)
    {
      case TasterEins:
      newState = TasterTreiber_TasteGedrueckt(SPIELER1_TASTE1);
      if (newState != LastStateP1T1)
      {
        LastStateP1T1 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP1T1 = newState;
      return false;

      case TasterZwei:
      newState = TasterTreiber_TasteGedrueckt(SPIELER1_TASTE2);
      if (newState != LastStateP1T2)
      {
        LastStateP1T2 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP1T2 = newState;
      return false;

      case TasterDrei:
      newState = TasterTreiber_TasteGedrueckt(SPIELER1_TASTE3);
      if (newState != LastStateP1T3)
      {
        LastStateP1T3 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP1T3 = newState;
      return false;

      case TasterVier:
      newState = TasterTreiber_TasteGedrueckt(SPIELER1_TASTE4);
      if (newState != LastStateP1T4)
      {
        LastStateP1T4 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP1T4 = newState;
      return false;
    }
  }
  else // Spieler Zwei
  {
    switch (taste)
    {
      case TasterEins:
      newState = TasterTreiber_TasteGedrueckt(SPIELER2_TASTE1);
      if (newState != LastStateP2T1)
      {
        LastStateP2T1 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP2T1 = newState;
      return false;

      case TasterZwei:
      newState = TasterTreiber_TasteGedrueckt(SPIELER2_TASTE2);
      if (newState != LastStateP2T2)
      {
        LastStateP2T2 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP2T2 = newState;
      return false;

      case TasterDrei:
      newState = TasterTreiber_TasteGedrueckt(SPIELER2_TASTE3);
      if (newState != LastStateP2T3)
      {
        LastStateP2T3 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP2T3 = newState;
      return false;

      case TasterVier:
      newState = TasterTreiber_TasteGedrueckt(SPIELER2_TASTE4);
      if (newState != LastStateP2T4)
      {
        LastStateP2T4 = newState;
        if (newState == true)
        {
          return true;
        }
      }
      LastStateP2T4 = newState;
      return false;
    }
  }
}
