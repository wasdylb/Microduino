void setup() {

  pinMode(6, OUTPUT); //定义引脚为输出
}

void loop() {

  tone(6, 800); //蜂鸣器输出频率800
  delay(1000); //延时1秒

  noTone(6); //蜂鸣器关闭
  delay(1000); //延时1秒
}
