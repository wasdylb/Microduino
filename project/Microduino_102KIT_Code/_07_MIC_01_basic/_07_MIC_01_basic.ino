#define mic_pin A0 //定义光敏传感器引脚为A0
#define PIN 6   //led灯控制引脚
#define PIN_NUM 2  //允许接的led灯的个数

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量

int state; //定义一个整数变量state

void setup() {
  Serial.begin(9600); //设置串口波特率为9600
  pinMode(mic_pin, INPUT); //设置光敏传感器引脚为输入状态
  ColorLED.begin(); //设置彩灯初始状态
}

void loop() {
  state = analogRead(mic_pin); //将光敏传感器引脚的值赋给变量state
  Serial.print("Sound:"); //在串口监视器里打印文字 Sound：
  Serial.println(state); //在串口监视器里打印变量state的值，并换行
  delay(100); //延时100毫秒打印
}
