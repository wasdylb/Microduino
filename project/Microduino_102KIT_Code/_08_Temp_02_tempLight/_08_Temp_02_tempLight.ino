#include <Adafruit_NeoPixel.h>  //调用LED彩灯的库文件

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel (2, 6, NEO_GRB + NEO_KHZ800);//定义彩灯引脚以及数量

#include <Wire.h>

#include <lm75.h>

TempI2C_LM75 termo = TempI2C_LM75(0x48, TempI2C_LM75::nine_bits);



void setup()
{
  Serial.begin(9600);
  ColorLED.begin();
}

void loop()
{
  Serial.print(termo.getTemp());
  Serial.println(" oC");
  delay(1000);
  
  float temp = termo.getTemp();

  if (temp > 28) {
    ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0));  //设置彩灯颜色为红色
    ColorLED.show();  //显示彩灯效果
    ColorLED.setPixelColor(1, ColorLED.Color(0, 0, 0));  //设置彩灯颜色为红色
    ColorLED.show();  //显示彩灯效果
  } else {
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));  //设置彩灯颜色为红色
    ColorLED.show();  //显示彩灯效果
    ColorLED.setPixelColor(1, ColorLED.Color(0, 0, 255));  //设置彩灯颜色为红色
    ColorLED.show();  //显示彩灯效果
  }

}
