#include <Adafruit_NeoPixel.h> //调用LED彩灯的库文件

#define PIN_PIR 4 //定义PIR引脚
#define PIN 6  //led灯控制引脚
#define PIN_NUM 2 //允许接的led灯的个数

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量

int state; //定义一个整数变量state

void setup() {
  ColorLED.begin(); //设置彩灯初始状态
  pinMode(PIN_PIR, INPUT); //设置PIR引脚为输入状态
}

void loop() {
  state = digitalRead(PIN_PIR); //将PIR引脚的值赋给变量state
  
  if (state == 1) { //当state的值等于1的时候，亮红灯
    ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0));
    ColorLED.show();
    
    
  } else {  //否则亮黑灯（关灯）
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));
    ColorLED.show();
  }
}
