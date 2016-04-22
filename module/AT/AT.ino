#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX (D5与电机冲突 屏蔽 只用RX)

#define my_Serial mySerial
//#define my_Serial Serial1 //定义CoreUSB与BT串口
 
void setup()
{
  Serial.begin(9600);//串口监视器通讯波特率
  my_Serial.begin(9600);//BT通讯波特率
}
 
void loop()
{
  if (Serial.available())//监视到串口监视器的数据
    my_Serial.write(Serial.read());//将数据写入BT
  if (my_Serial.available())//监视到BT串口的数据
    Serial.write(my_Serial.read());//将数据在串口监视器打印出来
}
