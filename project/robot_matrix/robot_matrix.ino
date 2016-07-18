#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

const uint8_t PROGMEM anim1[] = {
  B11111111, // 1 frame
  B10011001,
  B10011001,
  B11111111,
  B10000001,
  B11000011,
  B11100111,
  B11111111,
};
const uint8_t PROGMEM anim2[] = {
  B11111111, // 2 frame
  B10011001,
  B10011001,
  B11111111,
  B10111101,
  B10111101,
  B11000011,
  B11111111,
};
const uint8_t PROGMEM anim3[] = {
  B11111111, // 3 frame
  B10011001,
  B10011001,
  B11111111,
  B10000001,
  B11000011,
  B11100111,
  B11111111,
};
const uint8_t PROGMEM anim4[] = {
  B11111111, // 4 frame
  B10011001,
  B10011001,
  B11111111,
  B10111101,
  B10111101,
  B11000011,
  B11111111,
};
const uint8_t PROGMEM anim5[] = {
  B11111111, // 5 frame
  B10011001,
  B10011001,
  B11111111,
  B11111111,
  B11111111,
  B10000001,
  B11111111,
};
const uint8_t PROGMEM anim6[] = {
  B11111111, // 6 frame
  B10011001,
  B10011001,
  B11111111,
  B11100111,
  B11011011,
  B11100111,
  B11111111,
};
const uint8_t PROGMEM anim7[] = {
  B11111111, // 7 frame
  B10111101,
  B00011000,
  B10111101,
  B11100111,
  B11011011,
  B11100111,
  B11111111,
};
const uint8_t PROGMEM anim8[] = {
  B11111111, // 8 frame
  B11111111,
  B00011000,
  B11111111,
  B11100111,
  B11011011,
  B11100111,
  B11111111,
};
const uint8_t PROGMEM anim9[] = {
  B11111111, // 9 frame
  B10111101,
  B00011000,
  B10111101,
  B11100111,
  B11011011,
  B11100111,
  B11111111,
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  matrix.begin(0x70);  // pass in the address
  matrix.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  matrix.clear();
  matrix.drawBitmap(0, 0, anim1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim2, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim3, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim4, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim5, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim6, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim7, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim8, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, anim9, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
}
