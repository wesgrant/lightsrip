#include "Arduino.h"
#include "Adafruit_DotStar.h"
#include <SPI.h>
#include "Wgrant_Lcd.h"
#include "Wgrant_DotStar_Pattern.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"

Wgrant_DotStar_Pattern::Wgrant_DotStar_Pattern(Adafruit_DotStar *strip, int pixel_count, int width, int strip_brightness, Wgrant_Lcd *lcd)
{
  _strip = strip;
  _pixel_count = pixel_count;
  _width = width;
  _strip_brightness = strip_brightness;
  _lcd = lcd;
}

void Wgrant_DotStar_Pattern::begin() {
  _strip->begin(); // Initialize pins for output
  _strip->show();  // Turn all LEDs off ASAP
  _strip->setBrightness(_strip_brightness);
  
  _lcd->begin(16, 2);
  _lcd->setBacklight(0x7);
  _lcd->print(1, "Brightness = " + (String)_strip_brightness);
}

bool Wgrant_DotStar_Pattern::antsMarching(int width, bool reverse, bool sweep, int del) {
  static int j = reverse ? width : 0;
  uint32_t color1 = 0xFF0000, color2 = 0x002200;
  
  _lcd->print(0, "Ants Marching");

  for(int i = 0; i < _pixel_count + 1; i++) {
    if(i % width == j) {
      if(reverse) {
        _strip->setPixelColor(i, color1);
        _strip->setPixelColor(i + 1, color2);
      } else {
        _strip->setPixelColor(i, color1);
        _strip->setPixelColor(i - 1, color2);
      }
    }
  }
  _strip->show();
  
  if(sweep) delay(del + j); else delay(del);
  
  if(reverse) {
    j--;
    if(j < 0) j = width; 
  }  else {
    j++;
    if(j > width) j = 0;
  }

  return j == 0;
}

bool Wgrant_DotStar_Pattern::christmasCane(int width, int del) {
  static int j = 0;
  static bool directionUp = true;
  uint32_t color1 = 0x00FF00, color2 = 0xFF0000;

  _lcd->print(0, "Christmas Cane");

  for(int i = 0; i < _pixel_count; i++) {
    if(i % width == j) _strip->setPixelColor(i, directionUp ? color1 : color2);
  }
  _strip->show();
  delay(del + j);
  
  j = (directionUp ? j + 1 : j - 1);

  if(j == 0 || j ==  width) directionUp = !directionUp;
  return j == 0;
}

bool Wgrant_DotStar_Pattern::christmasSquares() {
  static int j = 0;
  static bool toggle = true;

  uint32_t color1 = 0x00FF00, color2 = 0xFF0000;

  _lcd->print(0, "Christmas Squares");

  for(int i = 0; i < _pixel_count; i++) {
    if((i + 30) % _width == j) _strip->setPixelColor(i,  color1);
    if((i) % _width == j) _strip->setPixelColor(i, color2);
  }
  _strip->show();
  delay(50);
  
  //j = (directionUp ? j + 1 : j - 1);
  j++;

  if(j == _width) {
    toggle = !toggle;
    j = 0;
  } 
  return j == 0;
}

bool Wgrant_DotStar_Pattern::christmasSweep() {
  static int j = 0;
  static bool directionUp = true;
  static uint32_t color;

  _lcd->print(0, "Christmas Sweep");

  color = (color == 0xFF0000 ? 0x00FF00 : 0xFF0000);
  
  for(int i = 0; i < _pixel_count; i++) {
    _strip->setPixelColor(i, (i == j ? color : 0x000000));
  }
  _strip->show();  
  j = (directionUp ? j + 1 : j - 1);

  if(j == 0 || j ==  _pixel_count) {
    directionUp = !directionUp;
  }
  if(j == 0) delay(200);
  return j == 0;
}

bool Wgrant_DotStar_Pattern::lightningFlashes(int flashes) {
  static int j = 0;

  _lcd->print(0, "Lightning Flash");

  for(int i = 0; i < _pixel_count; i++) {
    _strip->setPixelColor(i, (j % 2 == 0 ? 0xFFFFFF : 0x000000));
  }
  _strip->show();
  
  if(j == flashes) { // end
    delay(500); 
    j = 0;
  } else if(j % 2 == 0) { // on
    delay(10);
    j++;
  } else {  // off
    delay(100);
    j++;
  }
  return j == 0;
}

bool Wgrant_DotStar_Pattern::randomDots() {
  static int i;  // so we can give some concept of 'done'
  uint32_t colors[] = {
    // 0xFF0000,
    // 0x110000,
    // 0x110000,
    // 0x110000,
    // 0x110000, 
    // 0x00FF00,
    // 0x001100,
    // 0x001100,
    // 0x001100,
    // 0x001100, 
    // 0x000000,
    // 0x000000,
    // 0x000000,
    // 0x000000,
    // 0x000000,
    // 0xFFFFFF,
    0x0000FF
  };
  int sizeOfColors = sizeof(colors) / sizeof(uint32_t);
  int pixel, color;

  pixel = random(0, _pixel_count + 1);
  _strip->setPixelColor(pixel, 0x0000FF);
  for(int j = 0; j <= 74; j++) {
    color = 0x0000FF ;
    _strip->setPixelColor(pixel, 0x00004B - j);
    _strip->show();
    delay(5);
  }
  _lcd->print(0, "Random Dots");

  //_strip->setPixelColor(random(0, _pixel_count + 1), colors[random(0, sizeOfColors + 1)]); 
  delay(0);
  if(i > _pixel_count) i = 0;
  return (i++ == _pixel_count);
}

bool Wgrant_DotStar_Pattern::runningDot() {
  static int j = 0;
  static bool directionUp = true;
  static uint32_t color = 0xFF0000;

  _lcd->print(0, "Running Dot");

  for(int i = 0; i < _pixel_count; i++) {
    _strip->setPixelColor(i, (i == j ? color : 0x000000));
  }
  _strip->show();  
  delay(10);
  j = (directionUp ? j + 1 : j - 1);

  if(j == 0 || j ==  _pixel_count) {
    directionUp = !directionUp;
    color = (color == 0xFF0000 ? 0x00FF00 : 0xFF0000);
  }
  return j == 0;
}