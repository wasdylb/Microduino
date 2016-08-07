#define nRF_DEBUG 1
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 4, NEO_GRB + NEO_KHZ800);
#include <Microduino_Key.h>
Key KeyA(6, INPUT);

#define NUM 4  //节点数
#define TIME_OUT 5000

//rf=======================================
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// nRF24L01(+) radio attached using Getting Started board
RF24 radio(9, 10);
RF24Network network(radio);
const int this_node = 0;  //设置本机ID

boolean switch_key;
int sensor_val[NUM];

long time1;

//--------------------------------
struct send_a  //发送
{
  int rf_sensor_result;
};

struct receive_a  //接收
{
  int rf_sensor_sta;       //STA
};

void setup() {
  Serial.begin(9600);
  strip.begin();
  delay(1000);
  SPI.begin();    //初始化SPI总线
  radio.begin();
  network.begin(110, this_node);
  Serial.println("Hello Microduino");
}

void loop() {
  if (KeyA.read() == SHORT_PRESS)
  {
    switch_key = true;
    time1 = millis();
  }

  if (millis() - time1 > TIME_OUT)
  {
    switch_key = false;
    time1 = millis();
  }

  //nRF通讯---------------------------------
  vonrf();
}

void vonrf()
{
  {
#ifdef nRF_DEBUG
    Serial.println("Sending...");
#endif
    for (int a = 0; a < NUM; a++)
    {
      send_a sen = {
        switch_key
      };    //把这些数据发送出去，对应前面的发送数组
      RF24NetworkHeader header(a + 1);
      bool ok = network.write(header, &sen, sizeof(sen));

      if (ok)
      {
        delay(50);
#ifdef nRF_DEBUG
        Serial.print(a + 1);
        Serial.print(" is ok.");
#endif
        if (sensor_val[a])
          strip.setPixelColor(a, strip.Color(0, 50, 0));
        else
          strip.setPixelColor(a, strip.Color(0, 10, 10));
        strip.show();

        network.update();
        // If it's time to send a message, send it!
        while ( network.available() )
        {
          // If so, grab it and print it out
          RF24NetworkHeader header;
          receive_a rec;
          network.read(header, &rec, sizeof(rec));

          sensor_val[a] = rec.rf_sensor_sta;
        }
#ifdef nRF_DEBUG
        Serial.print("  Sensor_val[");
        Serial.print(a + 1);
        Serial.print("]:");
        Serial.print(sensor_val[a]);
        Serial.println("");
#endif
      }
      else
      {
        strip.setPixelColor(a, strip.Color(0, 0, 0));
        strip.show();
#ifdef nRF_DEBUG
        Serial.print(a + 1);
        Serial.println(" is failed.");
#endif
      }
    }
  }
  delay(15);
}

