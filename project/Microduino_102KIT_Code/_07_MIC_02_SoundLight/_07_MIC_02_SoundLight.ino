#include <Adafruit_NeoPixel.h>  //调用LED彩灯的库文件

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量

int state; //定义一个整数变量state

void setup() {
  Serial.begin(9600); //设置串口波特率为9600
  pinMode(A0, INPUT); //设置MIC传感器引脚为输入状态
  ColorLED.begin(); //设置彩灯初始状态
}

void loop() {
  state = analogRead(A0); //将MIC传感器引脚的值赋给变量state
  Serial.print("Sound:"); //在串口监视器里打印文字 state：
  Serial.println(state); //在串口监视器里打印变量state的值，并换行
  delay(100); //延时100毫秒打印
 
  if (state > 200) { //当state的值大于200时，亮红灯
    ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0));  //设置彩灯颜色为红色
    ColorLED.show();  //显示彩灯效果
    delay(2000); //持续2秒
  } else { //否则关灯
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));  //设置彩灯颜色为红色
    ColorLED.show(); //显示彩灯效果
  }

}
