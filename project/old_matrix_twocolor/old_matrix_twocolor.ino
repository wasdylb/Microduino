#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

static uint8_t __attribute__ ((progmem)) smile1_bmp[] = {0x3C, 0x42, 0xA9, 0x85, 0x85, 0xA9, 0x42, 0x3C};
static uint8_t __attribute__ ((progmem)) smile2_bmp[] = {0x3C, 0x42, 0x89, 0x85, 0x85, 0x89, 0x42, 0x3C};
static uint8_t __attribute__ ((progmem)) smile3_bmp[] = {0x3C, 0x42, 0xA1, 0x85, 0x85, 0xA1, 0x42, 0x38};
static uint8_t __attribute__ ((progmem)) love1_bmp[] = {0x38, 0x7C, 0x7E, 0x3F, 0x3F, 0x7E, 0x7C, 0x38};
static uint8_t __attribute__ ((progmem)) love2_bmp[] = {0x38, 0x44, 0x42, 0x21, 0x21, 0x42, 0x44, 0x38};
static uint8_t __attribute__ ((progmem)) logo_bmp[] = {0x50, 0xA8, 0xA8, 0xA8, 0x00, 0x00, 0x00, 0x00};

long time;

int color_led;

int add;
int tempI = 0;
int tempJ = 0;
bool up = true;
bool left = true;

void setup() {
  Serial.begin(9600);

  matrix.begin(0x70);
}

void loop() {

  if (millis() - time > 300)
  {
    color_led++;
    if (color_led > 2)
      color_led = 0;
    time = millis();
  };

  logo_move();
  clean(1000);

  vosetlcd("Hello Microduino!", -6 * 17 , LED_GREEN, 150);
  vosetimg(smile1_bmp, LED_GREEN, 100);
  

  for (int i = 0; i < 6; i++)
  {
    vosetimg(smile1_bmp, LED_GREEN, 100);
    vosetimg(smile2_bmp, LED_GREEN, 100);
  }

  for (int i = 0; i < 6; i++)
  {
    vosetimg(smile1_bmp, LED_GREEN, 800);
    clean(500);
  }

  clean(100);

  for (int x = 0; x <= 8; x++)
  {
    for (int j = 0; j <= 8; j++)
      vosetimge(love2_bmp, LED_YELLOW, 50, 0, 0, x, 8 );
  }
  for (int i = 0; i < 6; i++)
  {
    vosetimg(love2_bmp, LED_YELLOW, 800);
    clean(500);
  }

  for (int x = 0; x <= 8; x++)
  {
    for (int j = 0; j <= 8; j++)
      vosetimge(love1_bmp, LED_RED, 50, 0, 0, x, 8 );
  }
  for (int i = 0; i < 6; i++)
  {
    vosetimg(love1_bmp, LED_RED, 800);
    clean(500);
  }
}

void logo_move()
{
  for (int i = 0; i < 8; i++)
  {
    matrix.setRotation(1);
    matrix.drawBitmap(tempJ, tempI, logo_bmp, 8, 8, LED_RED);
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
}

void vosetlcd(char* wd, int x, int Color, int time)
{
  for (int n = 7; n >= x; n--)
  {
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setRotation(1);
    matrix.setTextColor(Color);
    matrix.clear();
    matrix.setCursor(n, 0);
    matrix.print(wd);
    matrix.writeDisplay();
    delay(time);
  }
}

void vosetimg(const uint8_t *bitmap, int Color, int time)
{
  matrix.clear();
  matrix.setRotation(2);
  matrix.drawBitmap(0, 0, bitmap, 8, 8, Color);
  matrix.writeDisplay();
  delay(time);
}

void vosetimge(const uint8_t *bitmap, int Color, int time, int x1, int x2, int y1, int y2)
{
  matrix.setRotation(2);
  matrix.drawBitmap(x1, x2, bitmap, y1, y2, Color);
  matrix.writeDisplay();
  delay(time);
}

void clean(int time)
{
  matrix.clear();
  matrix.writeDisplay();
  delay(time);
}
