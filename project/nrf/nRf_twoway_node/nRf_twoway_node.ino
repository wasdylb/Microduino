#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 4, NEO_GRB + NEO_KHZ800);
#include <Microduino_Key.h>
Key KeyA(6, INPUT);

#define NUM 1    //节点序号

// rf == == == == == == == == == == == == == == == == == == == =
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// nRF24L01(+) radio attached using Getting Started board
RF24 radio(9, 10);
RF24Network network(radio);

const int id_host = 0;  //设置本机ID

boolean switch_key;
boolean switch_result;

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
  strip.begin();
  Serial.println("Hello Microduino");
  SPI.begin();    //初始化SPI总线
  radio.begin();
  network.begin(110, NUM);
}

void loop() {
  if (KeyA.read() == SHORT_PRESS)
    switch_key = !switch_key;

  if (switch_result)
    strip.setPixelColor(0, strip.Color(255, 0, 0));
  else
    strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();

  // put your main code here, to run repeatedly:
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
        switch_key
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
