#include <Adafruit_NeoPixel.h>  //调用LED彩灯的库文件

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量


int state; //定义一个整数变量state

void setup()
{
  ColorLED.begin();
  pinMode(A0, INPUT); //设置光敏传感器引脚为输入状态
  Serial.begin(9600); //设置串口波特率为9600
}
void loop()
{
  state = analogRead(A0);
  Serial.print("state:");
  Serial.println(state);
  delay(100);
  if (state < 50) { //当state的值小于50时，亮红灯
    ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0));  //设置彩灯颜色为红色
    ColorLED.show();  //显示彩灯效果
  } else { //否则，关灯
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));  //设置彩灯颜色为红色
    ColorLED.show();  //显示彩灯效果
  }
}
