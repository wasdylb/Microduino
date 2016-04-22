#include <Adafruit_NeoPixel.h>

#define PIN 8   //led灯控制引脚
#define PIN_NUM 4 //允许接的led灯的个数
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);

int led_pos = 0;
int led_num = 1;

unsigned long led_time = 0;

#define val_max 255
#define val_min 0

void colorSet(uint32_t c, uint32_t i) {
  strip.setPixelColor(i, c);
  strip.show();
}

void breath(int r, int g, int b, int i)
{
  if (millis() < led_time) led_time = millis();
  if (millis() - led_time > 10) {
    led_pos += led_num;
    if (led_pos >= 255 || led_pos <= 0)
      led_num = -led_num;
    led_time = millis();
  }
  colorSet(strip.Color(map(led_pos, val_min, val_max, 0, r), map(led_pos, val_min, val_max, 0, g), map(led_pos, val_min, val_max, 0, b)), i);
}
