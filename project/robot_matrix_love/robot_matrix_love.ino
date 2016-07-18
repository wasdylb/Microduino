#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

static uint8_t __attribute__ ((progmem)) man1[] = {0x00, 0x66, 0x66, 0x00, 0x00, 0x7E, 0x00, 0x00};//无表情
static uint8_t __attribute__ ((progmem)) women2[] = {0x00, 0x66, 0x66, 0x00, 0x42, 0x7E, 0x00, 0x00};//微笑

static uint8_t __attribute__ ((progmem)) man3[] = {0x00, 0x00, 0x66, 0x00, 0x18, 0x24, 0x18, 0x00}; //惊讶
static uint8_t __attribute__ ((progmem)) women3[] = {0x00, 0x66, 0x66, 0x00, 0x42, 0x7E, 0x00, 0x00};//微笑

static uint8_t __attribute__ ((progmem)) man4[] = {0x00, 0x44, 0xEE, 0x44, 0x00, 0x38, 0x28, 0x38}; //星星眼
static uint8_t __attribute__ ((progmem)) women4[] = {0x00, 0xAA, 0xEE, 0x00, 0x00, 0x44, 0x7C, 0x00}; //害羞眼

static uint8_t __attribute__ ((progmem)) man5[] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}; //示好
static uint8_t __attribute__ ((progmem)) women5[] = {0x00, 0x42, 0xE7, 0x42, 0x00, 0x42, 0x7E, 0x00}; //开心

static uint8_t __attribute__ ((progmem)) man6[] = {0x00, 0x6C, 0x6C, 0x00, 0x00, 0x44, 0x38, 0x00}; //示好
static uint8_t __attribute__ ((progmem)) women6[] = {0x00, 0x66, 0x66, 0x00, 0x00, 0x42, 0x7E, 0x00}; //开心

static uint8_t __attribute__ ((progmem)) man7[] = {0x00, 0x66, 0x66, 0x00, 0x7E, 0x3C, 0x18, 0x00}; //示好
static uint8_t __attribute__ ((progmem)) women7[] = {0x00, 0x66, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18}; //开心

static uint8_t __attribute__ ((progmem)) man8[] = {0x00, 0x66, 0x66, 0x00, 0x7E, 0x3C, 0x18, 0x00}; //示好
static uint8_t __attribute__ ((progmem)) women8[] = {0x00, 0x66, 0x66, 0x00, 0x7E, 0x24, 0x18, 0x00}; //开心

static uint8_t __attribute__ ((progmem)) man9[] = {}; //示好
static uint8_t __attribute__ ((progmem)) women9[] = {}; //开心


void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);
}

void loop() {

//  vosetimg(man1, LED_ON, 3000);
//  vosetimg(man3, LED_ON, 3000);
//  vosetimg(man4, LED_ON, 3000);
//  vosetimg(man5, LED_ON, 3000);
//  vosetimg(man6, LED_ON, 3000);
//  vosetimg(man7, LED_ON, 3000);
//  vosetimg(man8, LED_ON, 3000);

  vosetimg(women2, LED_ON, 3000);
  vosetimg(women3, LED_ON, 3000);
  vosetimg(women4, LED_ON, 3000);
  vosetimg(women5, LED_ON, 3000);
  vosetimg(women6, LED_ON, 3000);
  vosetimg(women7, LED_ON, 3000);
  vosetimg(women8, LED_ON, 3000);

}

void vosetimg(const uint8_t *bitmap, int Color, int time)
{
  matrix.clear();
  matrix.setRotation(0);
  matrix.drawBitmap(0, 0, bitmap, 8, 8, Color);
  matrix.writeDisplay();
  delay(time);
}

void clean(int time)
{
  matrix.clear();
  matrix.writeDisplay();
  delay(time);
}
