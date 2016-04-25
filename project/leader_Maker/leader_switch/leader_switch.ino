#include <Microduino_Key.h>

Key KeyA(A6, INPUT_PULLUP);

#define NUM 1    //节点序号

// rf == == == == == == == == == == == == == == == == == == == =
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// nRF24L01(+) radio attached using Getting Started board
RF24 radio(9, 10);
RF24Network network(radio);

const int id_host = 0;  //设置本机ID

struct send_a  //发送
{
  uint32_t node_ms;   //节点运行时间
  uint32_t rf_sensor_sta;
};

unsigned long last_sent = 0; //定时器

//--------------------------------
struct receive_a  //接收
{
  uint32_t ms;      //主机运行时间
  uint32_t rf_type;   //节点类型
};

unsigned long clock;  //

boolean sta;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello Microduino");
  SPI.begin();    //初始化SPI总线
  radio.begin();
  network.begin(110, NUM);
}

void loop() {
  if (KeyA.read(0, 30) == SHORT_PRESS)
    sta = true;
  // put your main code here, to run repeatedly:
  network.update();
  // Is there anything ready for us?
  while ( network.available() )
  {
    // If so, grab it and print it out
    RF24NetworkHeader header;
    receive_a rec;
    network.read(header, &rec, sizeof(rec));

    clock = rec.ms;      //接收主机运行时间赋值
    {

      Serial.print("Sending...");
      Serial.print(NUM);
      send_a sen = {
        millis(), sta
      };  //把这些数据发送出去，对应前面的发送数组

      RF24NetworkHeader header(id_host);
      boolean ok = network.write(header, &sen, sizeof(sen));
      if (ok)
        Serial.println("...ok.");
      else
        Serial.println("failed.");
    }
  }
}
