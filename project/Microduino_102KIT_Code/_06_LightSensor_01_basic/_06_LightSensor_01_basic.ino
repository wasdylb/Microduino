int state; //定义一个整数变量state

void setup()
{
  pinMode(A0, INPUT); //设置光敏传感器引脚为输入状态
  Serial.begin(9600); //设置串口波特率为9600
}
void loop()
{
  state = analogRead(A0); //将光敏传感器引脚的值赋给变量state
  Serial.print("state:"); //在串口监视器里打印文字 state：
  Serial.println(state); //在串口监视器里打印变量state的值，并换行
  delay(100); //延时100毫秒打印
}
