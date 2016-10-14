#include "colorled.h"

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.begin(9600);
  strip.begin();//初始化彩灯，开始控制彩灯
  strip.setBrightness(BRIGHT_MAX);
  for (int i = 0; i < 11; i++)
  {
    setAllLed(i);
    delay(1000);
  }
  for (int i = 0; i < 1000; i++)
  {
    ledRainbow(10);
    delay(10);
  }
  for (int i = 0; i < 600; i++)
  {
    ledBreath(COLOR_YELLOW, 2);
    delay(10);
  }
}
