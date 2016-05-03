#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

static uint8_t PROGMEM  //abcdef
m_logo[] = {
  0x50, 0xA8, 0xA8, 0xA8, 0x00, 0x00, 0x00, 0x00
},
smile_bmp[] = {
  0x3c, 0x42, 0xa5, 0x81, 0xa5, 0x99, 0x42, 0x3c
},
neutral_bmp[] = {
  0x3c, 0x42, 0xa5, 0x81, 0xbd, 0x81, 0x42, 0x3c
},
frown_bmp[] = {
  0x3c, 0x42, 0xa5, 0x81, 0x99, 0xa5, 0x42, 0x3c
};

int add;
int tempI = 0;
int tempJ = 0;
bool up = true;
bool left = true;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  matrix.begin(0x70);  // pass in the address

  matrix.clear();
}


void loop() {
  // put your main code here, to run repeatedly:

  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.writeDisplay();
  delay(500);

  for (int i = 0; i < 8; i++)
  {
    matrix.drawBitmap(tempJ, tempI, m_logo, 8, 8, LED_ON);
    matrix.writeDisplay();
    if (tempI + 4 == 8) {
      left = true;
    }
    else if (tempI == 0) {
      left = false;
    }
    if (tempJ + 3 == 6) {
      up = true;
    }
    else if (tempJ == 0) {
      up = false;
    }
    if (left) {
      tempI--;
    }
    else {
      tempI++;
    }
    if (up) {
      tempJ--;
    }
    else {
      tempJ++;
    }
    delay(500);
    matrix.clear();
  }
  matrix.clear();
  matrix.writeDisplay();
  delay(1000);
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  for (int8_t x = 0; x >= -7 * 16; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Hello Microduino");
    matrix.writeDisplay();
    delay(100);
  }
}
