#include "colorled.h"

#define TOUCH_PIN A0
#define LIGHT_SWITCH 8

unsigned long timer;

int mode;
int num = 1;

boolean relay;

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);
  pinMode(LIGHT_SWITCH, OUTPUT);
  relay_OFF(LIGHT_SWITCH);
  strip.begin();//初始化彩灯，开始控制彩灯
  strip.setBrightness(BRIGHT_MAX);
  delay(1000);
}

void loop() {
  Serial.println(analogRead(TOUCH_PIN));
  if (analogRead(TOUCH_PIN) ==0)
  {
    delay(300);
    if (analogRead(TOUCH_PIN) ==0)
    {
      if (!relay)
      {
        relay_ON(LIGHT_SWITCH);
        relay = true;
      }
      for (uint8_t i = 0; i < strip.numPixels(); i++)//选择所有灯
      {
        setLed(10, i);
        delay(100);
      }
      delay(2000);
      timer = millis();
      mode = random(1, 4);
      while (millis() - timer < 5 * 1000)
      {
        switch (mode)
        {
          case 1:
            setAllLed(num);
            break;
          case 2:
            ledRainbow(10);
            break;
          case 3:
            ledBreath(num, 1);
            break;
        }
        if (millis() % 1000 == 0)
        {
          num++;
          if (num > 8)
            num = 1;
          Serial.println(num);
        }
      }
    }
  }
  else
  {
    setAllLed(COLOR_NONE);
    delay(1000);
    if (relay)
    {
      relay_OFF(LIGHT_SWITCH);
      relay = false;
    }
  }
}

void relay_ON(int pin)
{
  digitalWrite(pin, LOW);
  delay(10);
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}

void relay_OFF(int pin)
{
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
  delay(10);
  digitalWrite(pin, HIGH);
}
