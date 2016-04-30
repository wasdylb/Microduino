#include <Servo.h>  //调用舵机库文件

Servo myservo;  //定义舵机名称

void setup() {
  myservo.attach(6);  //设置舵机引脚
}

void loop() {
  myservo.write(180);  //舵机旋转角度为180度
  delay(1000);  //保持1秒(1000毫秒)
  myservo.write(0);  //舵机旋转角度为0度
  delay(1000);  //保持1秒(1000毫秒)
}
