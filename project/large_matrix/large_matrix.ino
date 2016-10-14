#include "Microduino_Matrix.h"

uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {
  { 60, 61, 62, 63, 64},
  { 59, 58, 57, 56, 55},
  {50, 51, 52, 53, 54},
  {49, 48, 47, 46, 45}
};

Matrix display = Matrix(Addr);

#include "image.h"
#include "eatfood.h"

void setup() {
  Serial.begin(115200); // See the connection status in Serial Monitor
  Wire.begin();

  //display.clearFastMode();

  //getDeviceAddr
  for (int a = 0; a < display.getMatrixNum(); a++) {
    Serial.print(display.getDeviceAddr(a));
    Serial.print(" ");
  }
  Serial.println("mCookie");

  display.clearDisplay();
  //setLedColor
  for (int y = 0; y < display.getHeight() * 8; y++) {
    for (int x = 0; x < display.getWidth() * 8; x++) {
      randomSeed(analogRead(A0));
      display.setLedColor(x, y, random(0, 255), random(0, 255), random(0, 255));   //x, y, r, g, b
      delay(1);
    }
  }
  delay(1000);
  display.clearDisplay();
  display.drawBMP(0, 0, logoB);   //x,y,data
  delay(2000);
  display.clearDisplay();
  randFood();
  randFoodON();
  doudoudirection(doudouX, doudouY, 0, true);
}

void loop() {
  switch (direction)
  {
    case 1:
      doudouX = doudouX + 1;
      break;
    case 2:
      doudouX = doudouX - 1;
      break;
    case 3:
      doudouY = doudouY - 1;
      break;
    case 4:
      doudouY = doudouY + 1;
      break;
  }

  if (direction > 0)
  {
    display.clearDisplay();
    randFoodON();
    doudoudirection(doudouX, doudouY, direction - 1, dou_show);

    if ((direction == 1 && (doudouX + 7) == foodX && foodY == (doudouY + 4)) || (direction == 2 && (doudouX + 1) == foodX && foodY == (doudouY + 4)) || (direction == 3 && (doudouX + 4) == foodX && foodY == (doudouY + 1)) || (direction == 4 && (doudouX + 4) == foodX && foodY == (doudouY + 7)))
      winfood();

    if (doudouX > 31 || doudouX < 0 || doudouY > 23 || doudouY < 0)
      gameover();
  }

  food_blink(4);
}
