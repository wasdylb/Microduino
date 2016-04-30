#include <Adafruit_NeoPixel.h> //调用LED彩灯的库文件
#include <Microduino_Key.h> //调用开关的库文件

#define LED_PIN 6   //led灯控制引脚
#define LED_NUM 2 //允许接的led灯的个数
#define Key_PIN 4 //定义开关引脚

Key KeyA(Key_PIN, INPUT_PULLUP); //定义开关参数
Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量

boolean sta; //定义布尔变量，初始为假
int i = 0; //定义一个整数变量i


void setup() {
  ColorLED.begin(); //设置彩灯初始状态
  pinMode(Key_PIN, INPUT); //设置开关引脚为输入状态
  
}

void loop() {
  if (KeyA.read()==SHORT_PRESS) { //当读取到开关按下时
    i++; //变量i递增1
    
  }
  if (i == 1) { //当i＝1时，灯亮10%
    ColorLED.setPixelColor(0, ColorLED.Color(25, 25, 25));
    ColorLED.show();
  }
  else if (i == 2) { //当i＝2时，灯亮30%
    ColorLED.setPixelColor(0, ColorLED.Color(75, 75, 75));
    ColorLED.show();
  }
  else if (i == 3) { //当i＝3时，灯亮50%
    ColorLED.setPixelColor(0, ColorLED.Color(150, 150, 150));
    ColorLED.show();
  }
  else if (i == 4) { //当i＝4时，灯亮75%
    ColorLED.setPixelColor(0, ColorLED.Color(200, 200, 200));
    ColorLED.show();
  }
  else if (i == 5) { //当i＝5时，灯亮100%
    ColorLED.setPixelColor(0, ColorLED.Color(255, 255, 255));
    ColorLED.show();
  }
  else if (i == 6) { //当i＝6时，灯灭，i归零
    i = 0;
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));
    ColorLED.show();
  }
  delay(15);
}
