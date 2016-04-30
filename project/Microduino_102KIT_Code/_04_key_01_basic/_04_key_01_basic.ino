#include <Adafruit_NeoPixel.h>

#define LED_Pin 6
#define LED_Num 2
#define Key_Pin 8

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(LED_Num, LED_Pin, NEO_GRB + NEO_KHZ800);

void setup() {
  ColorLED.begin();
  pinMode(Key_Pin, INPUT);
}

void loop() {
  int KEY = digitalRead(Key_Pin);
  if (KEY == 0) {
    ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0));
    ColorLED.show();
  } else {
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));
    ColorLED.show();
  }
}
