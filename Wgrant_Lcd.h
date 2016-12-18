#ifndef Wgrant_Lcd_h
#define Wgrant_Lcd_h

#include "Arduino.h"
#include "Adafruit_RGBLCDShield.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"

class Wgrant_Lcd
{
  public:
    Wgrant_Lcd(Adafruit_RGBLCDShield *lcd);
    void print(int line, String message);
    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
    void setBacklight(uint8_t status); 

  private:
    Adafruit_RGBLCDShield *_lcd;
};

#endif