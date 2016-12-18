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
  static bool run = true;
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
    if(buttons & BUTTON_SELECT){
      run = !run;
      if(run) {
        delay(200); 
      } else {
        wlcd.print(0, "--- PAUSED ---");
        delay(2000);
      }
    }
      strip.setBrightness(brightness);
      wlcd.print(1, "Brightness = " + (String)brightness);
  }
  if(run) pattern.all();
  //pattern.randomDots();
}