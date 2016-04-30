#include <Adafruit_NeoPixel.h>  //调用LED彩灯的库文件

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(2, 6, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量

void setup() {
  ColorLED.begin();  //设置彩灯初始状态
}

void loop() {
  ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0));  //设置彩灯颜色为红色
  ColorLED.show();  //显示彩灯效果
  delay(1000);  //保持1秒(1000毫秒)

  ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));  //设置彩灯颜色为红色
  ColorLED.show();  //显示彩灯效果
  delay(1000);  //保持1秒(1000毫秒)
}
