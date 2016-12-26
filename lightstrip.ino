#include "Wgrant_DotStar_Pattern.h"
#include "Wgrant_Lcd.h"

#define NUMPIXELS 240 // Number of LEDs in strip
#define WIDTH 60
#define PROGRAM_TIME 10000
#define BRIGHTNESS 255 // initial brightness

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BGR);
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

Wgrant_Lcd wlcd = Wgrant_Lcd(&lcd);
Wgrant_DotStar_Pattern pattern = Wgrant_DotStar_Pattern(&strip, NUMPIXELS, WIDTH, BRIGHTNESS, &wlcd, (unsigned long) PROGRAM_TIME);

void setup() {
  pattern.begin();
  Serial.begin(9600);
}

void loop() {
  byte incomingByte = 0;
  static bool run = true;
  static int run_pattern = 0;
  static int brightness = BRIGHTNESS;
  uint8_t buttons = lcd.readButtons();

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println((char)incomingByte);
  }
  if(buttons || incomingByte > 0) {
    if((buttons & BUTTON_UP) || incomingByte == 'k'){
      brightness += 5;
      if(brightness > 255) brightness = 255;
      Serial.print("Brightness: "); Serial.println((String)brightness);
    }
    if((buttons & BUTTON_DOWN) || incomingByte == 'j') {
      brightness -= 5;
      if(brightness < 0) brightness = 0; 
      Serial.print("Brightness: "); Serial.println((String)brightness);
    }
    if((buttons & BUTTON_RIGHT) || incomingByte == 'l'){
      run_pattern++;
      if(run_pattern > 8) run_pattern = 8;
      delay(200);
    }
    if((buttons & BUTTON_LEFT) || incomingByte == 'h'){
      run_pattern--;
      if(run_pattern < 0) run_pattern = 0;
      delay(200);
    }
    if((buttons & BUTTON_SELECT) || incomingByte == 's'){
      run = !run;
        Serial.println("Resumed");
      if(run) {
        delay(200); 
      } else {
        wlcd.print(0, "--- PAUSED ---");
        Serial.println("PAUSED");
        delay(2000);
      }
    }
      strip.setBrightness(brightness);
      wlcd.print(1, "Brightness = " + (String)brightness);
  }
  if(run) {
    if(run_pattern == 0) {
      pattern.all();
    } else if(run_pattern == 1) {
      pattern.antsMarching();
    } else if(run_pattern == 2) {
      pattern.antsRetreating();
    } else if(run_pattern == 3) {
      pattern.christmasCane();
    } else if(run_pattern == 4) {
      pattern.christmasSquares();
    } else if(run_pattern == 5) {
      pattern.christmasSweep();
    } else if(run_pattern == 6) {
      pattern.lightningFlashes();
    } else if(run_pattern == 7) {
      pattern.randomDots();
    } else if(run_pattern == 8) {
      pattern.runningDot();
    }
  } 
}