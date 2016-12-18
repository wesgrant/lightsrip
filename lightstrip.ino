#include "Wgrant_DotStar_Pattern.h"
#include "Wgrant_Lcd.h"

#define NUMPIXELS 240 // Number of LEDs in strip
#define WIDTH 60
#define PROGRAM_TIME 10000
#define DELAY 0
#define BRIGHTNESS 255 // initial brightness

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BGR);
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

Wgrant_Lcd wlcd = Wgrant_Lcd(&lcd);
Wgrant_DotStar_Pattern pattern = Wgrant_DotStar_Pattern(&strip, NUMPIXELS, WIDTH, BRIGHTNESS, &wlcd);

void setup() {
  pattern.begin();
  //Serial.begin(9600);
}

void loop() {
  static int brightness = BRIGHTNESS;
  uint8_t buttons = lcd.readButtons();
  if(buttons) {
    if(buttons & BUTTON_UP) {
      brightness += 5;
      if(brightness > 255) brightness = 255;
    }
    if(buttons & BUTTON_DOWN) {
      brightness -= 5;
      if(brightness < 0) brightness = 0; 
    }
      strip.setBrightness(brightness);
      wlcd.print(1, "Brightness = " + (String)brightness);
  }
  show();
  //pattern.randomDots();
}

void show() {
  static unsigned long program_start_time = millis();
  unsigned long time_delta = millis() - program_start_time;
  
  if(time_delta < (unsigned long)PROGRAM_TIME) pattern.antsMarching(WIDTH, false, true, DELAY);
  else if(time_delta < (unsigned long)PROGRAM_TIME * 2) pattern.antsMarching(WIDTH, true, false, DELAY);
  else if(time_delta < (unsigned long)PROGRAM_TIME * 3) pattern.runningDot();
  else if(time_delta < (unsigned long)PROGRAM_TIME * 4) pattern.christmasCane(WIDTH, DELAY);
  else if(time_delta < (unsigned long)PROGRAM_TIME * 5) pattern.christmasSweep();
  else if(time_delta < (unsigned long)PROGRAM_TIME * 8) pattern.christmasSquares();
    else if(time_delta < (unsigned long)PROGRAM_TIME * 9) pattern.lightningFlashes(3);
  else if(time_delta < (unsigned long)PROGRAM_TIME * 20) pattern.randomDots();
  else program_start_time = millis();
}
