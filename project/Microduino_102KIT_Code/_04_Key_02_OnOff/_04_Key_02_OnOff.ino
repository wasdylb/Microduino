#include <Adafruit_NeoPixel.h> //调用LED彩灯的库文件
#include <Microduino_Key.h> //调用开关的库文件

#define PIN_LED 6   //led灯控制引脚
#define LED_NUM 2 //允许接的led灯的个数
#define PIN_Key 4 //定义开关引脚

Key KeyA(PIN_Key, INPUT_PULLUP); //定义开关参数
Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(LED_NUM, PIN_LED, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量

boolean sta = false; //定义布尔变量为假

void setup() {
  ColorLED.begin(); //设置彩灯初始状态
  pinMode(PIN_Key, INPUT); //设置开关引脚为输入状态
}

void loop() {
  if (KeyA.read()==SHORT_PRESS) { //当读取到开关按下时
    sta = !sta; //反转布尔变量值
  }
  
  if (sta) { //当布尔变量为真时
    ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0)); //彩灯显示红色
    ColorLED.show();  //显示彩灯效果
  } else {
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0)); //彩灯显示黑色（关闭）
    ColorLED.show(); //显示彩灯效果
  } 
  delay(15); //延时15毫秒，防止按键干扰
}
