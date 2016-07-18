#define nRF_DEBUG

#define NUM 4  //节点数

//rf=======================================
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// nRF24L01(+) radio attached using Getting Started board
RF24 radio(9, 10);
RF24Network network(radio);
const int this_node = 0;  //设置本机ID

int sensor_val[NUM];
int result_val[NUM];

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
  SPI.begin();    //初始化SPI总线
  radio.begin();
  network.begin(110, this_node);
}

void loop() {
  // put your main code here, to run repeatedly:
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
        result_val[a]
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

        network.update();
        // If it's time to send a message, send it!
        while ( network.available() )
        {
          // If so, grab it and print it out
          RF24NetworkHeader header;
          receive_a rec;
          network.read(header, &rec, sizeof(rec));

          sensor_val[a] = rec.rf_sensor_sta;
          result_val[a] = sensor_val[a];
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
#ifdef nRF_DEBUG
        Serial.print(a + 1);
        Serial.println(" is failed.");
#endif
      }
    }
  }
}

