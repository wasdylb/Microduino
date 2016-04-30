#include <Adafruit_NeoPixel.h>  //调用LED彩灯的库文件

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(2, 6, NEO_GRB + NEO_KHZ800);  //定义彩灯引脚以及数量

int i; //定义整数变量i

void setup() {
  ColorLED.begin();  //设置彩灯初始状态
}

void loop() {
  for (i = 0; i <= 255; i++) {  //设置i初始等于0，i最大为255，i每次的递增值为1
    ColorLED.setPixelColor(0, ColorLED.Color(i, 0, 0));  //彩灯从暗到亮
    ColorLED.show(); //显示彩灯效果
    delay(10); //保持10毫秒
  }
  for (i = 255; i >= 0; i--) { //设置i初始等于255，i最小为0，i每次的递减值为1
    ColorLED.setPixelColor(0, ColorLED.Color(i, 0, 0));  //彩灯从亮到暗
    ColorLED.show(); //显示彩灯效果
    delay(10); //保持10毫秒
  }
}
