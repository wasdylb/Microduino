#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int add;

int direction = 0; //1-up. 2-down. 3-left. 4-right. default-not move, which means no direction
int Speed = 1; //the speed of the snack, will increase after eat 5 more food
int foodX, foodY, snackX, snackY; //location of the food the the head of the snack
int snack[64][2];//the location of each body part of the snack. We have 64 points total, each has 2 coordinate.

int sLength = 3; //the length of the snack, will increase after eat 3 more food
int num = 0; //number of food have eaten; also can be the score

static uint8_t PROGMEM m_logo[8] = {0x0A, 0x15, 0x15, 0x15, 0x00, 0x00, 0x00, 0x00};

unsigned long time1, time2;

void randFood() {//generate random food location
  foodX = random(0, 8); foodY = random(0, 8);
  for (int i = 0; i < sLength; i++) {//food can't be on the snack
    if (snack[i][0] == foodX && snack[i][1] == foodY) {
      foodX = random(0, 8); foodY = random(0, 8);
      i = 0;
    }
  }
  matrix.drawPixel(foodX, foodY, LED_ON);
  matrix.writeDisplay();
}

void gameOver() {
  direction = 0;
  Serial.println("GAME OVER!");
  Serial.print("score: ");
  Serial.println(num);
  matrix.clear();
  matrix.setTextColor(LED_ON); //设定LED颜色
  for (int8_t x = 7; x >= -39; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print(num);
    matrix.writeDisplay();
    delay(70);
  }
  matrix.clear();
  direction = 0;// default-not move, which means no direction
  Speed = 1;
  snack[0][0] = 0;
  snack[0][1] = 4;
  snack[1][0] = 1;
  snack[1][1] = 4;
  snack[2][0] = 2;
  snack[2][1] = 4;
  snackX = snack[2][0];
  snackY = snack[2][1];
  sLength = 3;
  num = 0;
  matrix.clear();;
  for (int i = 0; i < sLength; i++) {
    matrix.drawPixel(snack[i][0], snack[i][1], LED_ON); //snack
    matrix.writeDisplay();
  }
  randFood();//generate random food location
}

void updateSnack() {
  matrix.drawPixel(snack[0][0], snack[0][1], LED_OFF);//关掉最后一位
  matrix.writeDisplay();
  snack[sLength][0] = snackX;
  snack[sLength][1] = snackY;
  matrix.drawPixel(snackX, snackY, LED_ON);//开前一位
  matrix.writeDisplay();
  for (int j = 0; j < sLength; j++) {
    snack[j][0] = snack[j + 1][0];//x坐标
    snack[j][1] = snack[j + 1][1];//y坐标
  }
}

void led_blink(int timeF)
{
  for (int t = 1; t <= timeF; t++)
  {
    matrix.drawPixel(foodX, foodY, LED_OFF);
    matrix.writeDisplay();
    time2 = millis();
    while (millis() - time2 < 50)
      read_button();
    matrix.drawPixel(foodX, foodY, LED_ON);
    matrix.writeDisplay();
    time1 = millis();
    while (millis() - time1 < 50)
      read_button();
  }
}

void read_button()
{
  if (800 < analogRead(A0) && analogRead(A0) < 900 && direction != 2)
  {
    delay(100);
    if (800 < analogRead(A0) && analogRead(A0) < 900 && direction != 2)
      direction = 1;
  }
  else if (600 < analogRead(A0) && analogRead(A0) < 750 && direction != 4 && direction != 0)
  {
    delay(100);
    if (600 < analogRead(A0) && analogRead(A0) < 750 && direction != 4 && direction != 0)
      direction = 3;
  }
  else if (480 < analogRead(A0) && analogRead(A0) < 650 && direction != 1)
  {
    delay(100);
    if (480 < analogRead(A0) && analogRead(A0) < 650 && direction != 1)
      direction = 2;
  }
  else if (250 < analogRead(A0) && analogRead(A0) < 450 && direction != 3)
  {
    delay(100);
    direction = 4;
  }
  Serial.println(direction);
}

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);
  matrix.clear();
  matrix.drawBitmap(-1, 2, m_logo, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(3000);
  matrix.clear();;
  randomSeed(analogRead(0));
  snack[0][0] = 0;
  snack[0][1] = 4;
  snack[1][0] = 1;
  snack[1][1] = 4;
  snack[2][0] = 2;
  snack[2][1] = 4;
  snackX = snack[2][0]; snackY = snack[2][1];
  for (int i = 0; i < 3; i++) {
    matrix.drawPixel(snack[i][0], snack[i][1], LED_ON);
    matrix.writeDisplay();
  }
  randFood();//generate random food location
}

void loop() {
  switch (direction)
  {
    case 1:
      snackY = snackY - 1;
      break;
    case 2:
      snackY = snackY + 1;
      break;
    case 3:
      snackX = snackX - 1;
      break;
    case 4:
      snackX = snackX + 1;
      break;
  }

  if (direction != 0) {
    if (snackX > 7 || snackX < 0 || snackY > 7 || snackY < 0) {//if out of range
      gameOver();
    }
    else if (snackX == foodX && snackY == foodY) { //if eat the food
      num++;
      if (num % 5 == 0) {//add speed of the snack
        Speed++;
      }
      delay(100);
      if (num % 2 == 0) {//add length to the snack
        sLength++;
        snack[sLength - 1][0] = snackX; snack[sLength - 1][1] = snackY;
      }
      else {
        updateSnack();
      }
      randFood();
    }
    else {
      for (int i = 0; i < sLength; i++) {
        if (snack[i][0] == snackX && snack[i][1] == snackY) {//check if it hit itself
          gameOver();
        }
      }
      if (direction != 0) { //if not then update the snack position
        updateSnack();
      }
    }
  }
  if (Speed > 5)
    led_blink(3);
  else
    led_blink(8 - Speed);
  /*
  if (Speed < 4) {
    time1 = millis();
    while (millis() - time1 < 800 - 100 * Speed)
      read_button();
  }
  else {
    time2 = millis();
    while (millis() - time2 < 300)
      read_button();
  }
  */
}
