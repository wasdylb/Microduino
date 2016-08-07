#include "JQ6500.h"

//Core和CoreUSB默认使用软串口
SoftwareSerial mySerial(2, 3); // RX, TX
JQ6500 AUDIO(&mySerial);     //音频控制类实例,使用软串口（2，3）
//Core+默认使用Serial1
//JQ6500 Audio(&Serial1);

#define NUM 2    //节点序号

// rf == == == == == == == == == == == == == == == == == == == =
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// nRF24L01(+) radio attached using Getting Started board
RF24 radio(9, 10);
RF24Network network(radio);

const int id_host = 0;  //设置本机ID

boolean switch_result;
boolean switch_change;

struct send_a  //发送
{
  int rf_sensor_sta;
};

struct receive_a  //接收
{
  int rf_sensor_result;   //结果
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AUDIO.init(DEVICE_FLASH, MODE_ONE_STOP, 26);
  AUDIO.choose(1);
  AUDIO.pause();
  delay(1000);
  SPI.begin();    //初始化SPI总线
  radio.begin();
  network.begin(110, NUM);

  Serial.println("Hello Microduino");
}

void loop() {

  if (switch_result && !switch_change)
  {
    AUDIO.play();
    Serial.println("-----play-----");
    switch_change = true;
  }
  else if (!switch_result)
    switch_change = false;

  network.update();
  // Is there anything ready for us?
  while ( network.available() )
  {
    // If so, grab it and print it out
    RF24NetworkHeader header;
    receive_a rec;
    network.read(header, &rec, sizeof(rec));

    switch_result = rec.rf_sensor_result;      //接收主机
    Serial.print(switch_result);
    {
      Serial.print("...Sending..NUM:");
      Serial.print(NUM);
      send_a sen = {
        switch_result
      };  //把这些数据发送出去，对应前面的发送数组

      RF24NetworkHeader header(id_host);
      boolean ok = network.write(header, &sen, sizeof(sen));
      if (ok)
        Serial.println("...ok.");
      else
        Serial.println("failed.");
    }
  }
  delay(15);
}
