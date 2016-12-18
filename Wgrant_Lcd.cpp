
#include "Arduino.h"
#include "Wgrant_Lcd.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"

Wgrant_Lcd::Wgrant_Lcd(Adafruit_RGBLCDShield *lcd) {
    _lcd = lcd;
}

void Wgrant_Lcd::print(int line, String message) {
  static String msg[2];
  if (!msg[line].equals(message)) {
    _lcd->setCursor(0,line);
    _lcd->print("                ");
    _lcd->setCursor(0, line);
    msg[line] = message;
    _lcd->print(message);
  }
}
void Wgrant_Lcd::begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS){
  _lcd->begin(cols, rows, charsize);
}

void Wgrant_Lcd::setBacklight(uint8_t status){
  _lcd->setBacklight(status);
}