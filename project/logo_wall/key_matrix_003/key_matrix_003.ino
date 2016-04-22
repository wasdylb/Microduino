#include <Microduino_Key.h>
#include "Microduino_Matrix.h"

uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {
  { 64}
};

Matrix display = Matrix(Addr);

Key KeyA(8, INPUT_PULLUP);

static const uint8_t logoA[] PROGMEM = {   //低位在前 逐行
  0x0A, 0x15, 0x15, 0x15, 0x00, 0x00, 0x00, 0x00
};

int color[8][3] =
{
  {255, 0, 0},
  {255, 255, 0},
  {0, 255, 0},
  {0, 255, 255},
  {0, 0, 255},
  {255, 255, 255},
  {100, 255, 0},
  {0, 255, 100},
};

int tempI = 2;
int tempJ = 2;
bool up = true;
bool left = true;
bool led_sta, move_one;
unsigned long timer1;

void image_move()
{
  for (int i = 0; i < 8; i++)
  {
    display.setColor(color[i][0], color[i][1], color[i][2]);
    display.drawBMP(tempI, tempJ, 8, 8, logoA);
    if (tempI + 4 == 7) {
      left = true;
    }
    else if (tempI == 0) {
      left = false;
    }
    if (tempJ + 3 == 7) {
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
    if (millis() != timer1) timer1 = millis();
    while (millis() - timer1 <= 500)
    {
      if (KeyA.read() == SHORT_PRESS)
        return;
    }
    display.clearDisplay();
  }
  delay(15);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // See the connection status in Serial Monitor
  Wire.begin();
  delay(6000);
  display.clearDisplay();
  image_move();
  display.clearDisplay();
}

void loop() {
  if (KeyA.read() == SHORT_PRESS)
    led_sta = !led_sta;
  if (led_sta)
  {
    rainbowCycle(1);
    move_one = false;
  }
  else if (!led_sta && !move_one)
  {
    display.clearDisplay();
    image_move();
    move_one = true;
  }

  delay(15);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < 64; i++) {
      Wheel(((i * 256 / 64) + j) & 255);
      if (KeyA.read() == SHORT_PRESS)
      {
        led_sta = false;
        return;
      }
    }
    delay(wait);
  }
}

void Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        display.setLedColor(i, j, WheelPos * 3, 255 - WheelPos * 3, 0);
    }
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        display.setLedColor(i, j, 255 - WheelPos * 3, 0, WheelPos * 3);
    }
  } else {
    WheelPos -= 170;
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        display.setLedColor(i, j, 0, WheelPos * 3, 255 - WheelPos * 3);
    }
  }
}
