#include "LEDs.h";

/* Body LEDS */
byte BodyLEDSCount = 240;
byte groundLightsStatus = 0;
byte groundLightsRGB[3] = {255, 0, 0};

Adafruit_NeoPixel BodyLEDS = Adafruit_NeoPixel(BodyLEDSCount, 32, NEO_GRB + NEO_KHZ800);

void LEDSetup() {
  BodyLEDS.begin(); // This initializes the NeoPixel library.
  BodyLEDS.setBrightness(185); // max 255y
  
  for(int i=0;i<BodyLEDSCount;i++) {
    BodyLEDS.setPixelColor(i, BodyLEDS.Color(0,75,200)); 
  }
  
  BodyLEDS.show(); // This sends the updated pixel color to the hardware.   
}
