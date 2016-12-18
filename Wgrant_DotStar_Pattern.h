#ifndef Wgrant_DotStar_Pattern_h
#define Wgrant_DotStar_Pattern_h

#include "Arduino.h"
#include "Adafruit_DotStar.h"
#include <SPI.h>
#include "Wgrant_Lcd.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"

class Wgrant_DotStar_Pattern
{
  public:
    Wgrant_DotStar_Pattern(Adafruit_DotStar *strip, int pixel_count, int width, int strip_brightness, Wgrant_Lcd *lcd);
    
    void begin();
    bool antsMarching(int width, bool reverse, bool sweep, int del);
    bool christmasCane(int width, int del);
    bool christmasSquares();
    bool christmasSweep();
    bool lightningFlashes(int flashes);
    bool randomDots();
    bool runningDot();

  private:
    Adafruit_DotStar *_strip;
    int _pixel_count;
    int _width;
    int _strip_brightness;
    Wgrant_Lcd *_lcd;
};

#endif
