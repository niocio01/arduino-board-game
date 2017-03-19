
#include "Treiber/LcdTreiber.h"
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR1    0x27
#define I2C_ADDR2    0x26
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C  lcd1(I2C_ADDR1,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
LiquidCrystal_I2C  lcd2(I2C_ADDR2,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

bool LcdTreiber_Startup(void)
{
  lcd1.begin (16,2);
  lcd2.begin (16,2);

  lcd1.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd1.setBacklight(HIGH);
  lcd1.home (); // go home
  lcd2.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd2.setBacklight(HIGH);
  lcd2.home (); // go home

  return (true);
}

void LcdTreiber_DisplayMessage(GlobalTypes_Spieler_t spieler, char * zeileEins, char * zeileZwei)
{
  if (spieler == SpielerEins)
  {
    lcd1.clear();
    lcd1.print(zeileEins);
    lcd1.setCursor(0,1);
    lcd1.print(zeileZwei);
  }
  else
  {
    lcd2.clear();
    lcd2.print(zeileEins);
    lcd2.setCursor(0,1);
    lcd2.print(zeileZwei);
  }
}
