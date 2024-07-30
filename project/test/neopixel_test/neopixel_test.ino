#include <Adafruit_NeoPixel.h>

#define pin 15
#define nums 15

Adafruit_NeoPixel ex_str = Adafruit_NeoPixel(nums, pin, NEO_GRB+NEO_KHZ800);

void setup() {
  ex_str.begin();
  ex_str.show();
}

void loop() {
  for(int i = 0;i < nums;i++){
    ex_str.setPixelColor(i, 255, 0, 255);
  }
  ex_str.show();
  delay(3000);
}
