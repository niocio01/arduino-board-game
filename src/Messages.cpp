#include "Messages.h"
#include "LcdTreiber.h"

void Messages_ZeigeNachricht(GlobalTypes_Spieler_t spieler,
  Messages_Nachrichten_t nachricht)
  {
    if (spieler == SpielerEins)
    {
      switch (nachricht)
      {
        case Startup_OK:
        LcdTreiber_DisplayMessage(SpielerEins, "Startup:", "erfolgreich");
        break;

        case Startup_RFID_Fail:
        LcdTreiber_DisplayMessage(SpielerEins, "Startup:", "RFID Fail");
        break;
      }
    }
    else
    {
      switch (nachricht)
      {
        case Startup_OK:
        LcdTreiber_DisplayMessage(SpielerZwei, "Startup:", "erfolgreich");
        break;

        case Startup_RFID_Fail:
        LcdTreiber_DisplayMessage(SpielerZwei, "Startup:", "RFID Fail");
        break;
      }
    }
  }
