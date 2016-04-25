#define nRF_DEBUG

#define NUM 3  //节点数

#include <Adafruit_NeoPixel.h>
#define PIN A4
#define led_team 14
#define led_NUM 15
Adafruit_NeoPixel strip = Adafruit_NeoPixel(led_team*led_NUM, PIN, NEO_GRB + NEO_KHZ800);


uint32_t color[14] = {
  strip.Color(250, 94, 59),
  strip.Color(240, 59, 44),
  strip.Color(210, 43, 47),
  strip.Color(252, 142, 48),
  strip.Color(251, 164, 81),
  strip.Color(252, 208, 110),
  strip.Color(110, 181, 114),
  strip.Color(96, 215, 234),
  strip.Color(73, 148, 206),
  strip.Color(65, 59, 61),
  strip.Color(75, 89, 146),
  strip.Color(166, 107, 209),
  strip.Color(204, 101, 207),
  strip.Color(238, 129, 217),
};

//rf=======================================
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// nRF24L01(+) radio attached using Getting Started board
RF24 radio(9, 10);
RF24Network network(radio);
const int this_node = 0;  //设置本机ID

#define interval_rf  100   //nrf请求时序间隔
#define interval_debug  2000  //节点查错间隔
#define interval_oled  1000  //节点查错间隔

unsigned long time_xuan = 0, time_oled = 0; //定时器

//debug--------------------------
boolean node_clock_error[NUM];  //节点响应状态
unsigned long time_debug = 0; //定时器

unsigned long node_clock[NUM], node_clock_debug[NUM], node_clock_cache = 0; //节点运行时间、节点响应检查时间、节点时间缓存

int sensor_val[NUM];

//--------------------------------
struct send_a  //发送
{
  uint32_t ms;
};

struct receive_a  //接收
{
  uint32_t node_ms;   //节点运行时间
  uint32_t rf_sensor_sta;       //STA
};

void colormodule( int _led , int led_ , int wait)
{
  for (uint16_t i = _led / 2; i < _led; i++) {
    for (uint16_t j = 0; j < led_; j++) {
      strip.setPixelColor(i * led_ + j, color[i]);
      strip.setPixelColor((_led - 1 - i) * led_ + j, color[_led - 1 - i]);
      strip.show();
    }
    delay(wait);
  }
}

void colorset(uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  SPI.begin();    //初始化SPI总线
  radio.begin();
  network.begin(/*channel*/ 110, /*node address*/ this_node);

  strip.begin();
  colorset(strip.Color(0, 200, 200));
  delay(1000);
  colorset(strip.Color(0, 0, 0));
}

void loop() {
  // put your main code here, to run repeatedly:
  //nRF通讯---------------------------------
  if (millis() < time_xuan) time_xuan = millis();
  if (millis() - time_xuan > interval_rf)
  {
    vonrf();
    vodebug();
    time_xuan = millis();
  }
  if (sensor_val[0])
    colormodule( led_team, led_NUM , 100);
  else
    colorset(strip.Color(0, 0, 0));
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
        millis()
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

          node_clock[a] = rec.node_ms;  //运行时间赋值
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
#ifdef nRF_DEBUG
        Serial.print(a + 1);
        Serial.println(" is failed.");
#endif
      }
    }
  }
}


void vodebug()
{
  if (time_debug > millis()) time_debug = millis();
  if (millis() - time_debug > interval_debug)
  {
    for (int a = 0; a < NUM; a++)
    {
      node_clock_error[a] = boolean(node_clock[a] == node_clock_debug[a]); //一定时间内，节点返回的运行时间若不变则有问题
      Serial.print("DEBUG:");
      Serial.print(a + 1);
      Serial.print("=");
      Serial.println(node_clock_error[a]);
      node_clock_debug[a] = node_clock[a];
    }
    time_debug = millis();
  }
}
