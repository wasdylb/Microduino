#include <Wire.h>
#include <Rtc_Pcf8563.h>

Rtc_Pcf8563 rtc;//初始化实时时钟

#define Duan1 1
#define Duan2 4
#define Duan3 5
#define Duan4 7
#define h 10

#define time_see 5

int timehourg, timehours, timeming, timemins;

long  data[10] =
{
  // 0xfc, 0x60, 0xDA, 0xf2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6
  0xfc, 0x60, 0xda, 0xf2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6
};

void setup()
{
  // Serial.begin(115200);
  for (int x = 1; x < 13; x++)
    pinMode(x, OUTPUT);

  // vosettime();
}
void loop()
{
  rtc.formatDate();
  rtc.formatTime();

  timehours = rtc.getHour() / 10;
  timehourg = rtc.getHour() % 10;
  timemins = rtc.getMinute() / 10;
  timeming = rtc.getMinute() % 10;

  daytime();

  /*
    Serial.print("TIME:");
    Serial.print("20");
    Serial.print(rtc.getYear());
    Serial.print("/");
    Serial.print(rtc.getMonth());
    Serial.print("/");
    Serial.println(rtc.getDay());
    Serial.print(rtc.getHour());
    Serial.print(":");
    Serial.print(rtc.getMinute());
    Serial.print(":");
    Serial.println(rtc.getSecond());
    delay(1000);
  */
}
void daytime()
{
  digitalWrite(Duan1, LOW);
  digitalWrite(Duan2,  LOW);
  digitalWrite(Duan3,  LOW);
  digitalWrite(Duan4,  LOW);
  for (int i = 0; i < 10; i++)
  {
    leddisplay(data[i]);
    delay(1000);
  }
  /*
    duanma(1);
    leddisplay(data[timehours]);
    delay(time_see);

    duanma(2);
    leddisplay(data[timehourg]);
    delay(time_see);

    duanma(3);
    leddisplay(data[timemins]);
    delay(time_see);

    duanma(4);
    leddisplay(data[timeming]);
    delay(time_see);

    if (rtc.getSecond() % 2 == 0)
    digitalWrite(h, HIGH);
    else
    digitalWrite(h, LOW);
  */
}

//=======================初始化设置时间函数===========================//
void vosettime()
{
  // rtc.initClock();
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  rtc.setDate(1, 1, 8, 0, 16);
  //hr, min, sec
  rtc.setTime(10, 30, 50);
}

void leddisplay(int num)    // 将花样字模对应到端口显示
{
  /*=====================================================================
    先将16进制数向右移x位（num>>x），x代表了microduinoI/O口对应16进制的某位，
    0是最低位，7是最高位。再将移的数据与0x01按位与，就可以得到16进制数某位的
    数据（0或1），再将其值赋值给microduino的I/O就行。
    ======================================================================*/
  //digitalWrite(10, ((num >> 0) & 0x01));//h
  digitalWrite(8, ((num >> 1) & 0x01));//g
  digitalWrite(3, ((num >> 2) & 0x01));//f
  digitalWrite(12, ((num >> 3) & 0x01));//e
  digitalWrite(11, ((num >> 4) & 0x01));//d
  digitalWrite(9, ((num >> 5) & 0x01));//c
  digitalWrite(6, ((num >> 6) & 0x01));//b
  digitalWrite(2, ((num >> 7) & 0x01));//a
}
void duanma(int x)
{
  switch (x)
  {
    case 1:
      {
        digitalWrite(Duan1, LOW);
        digitalWrite(Duan2, HIGH);
        digitalWrite(Duan3, HIGH);
        digitalWrite(Duan4, HIGH);
      }
      break;
    case 2:
      {
        digitalWrite(Duan1, HIGH);
        digitalWrite(Duan2, LOW);
        digitalWrite(Duan3, HIGH);
        digitalWrite(Duan4, HIGH);
      }
      break;
    case 3:
      {
        digitalWrite(Duan1, HIGH);
        digitalWrite(Duan2, HIGH);
        digitalWrite(Duan3, LOW);
        digitalWrite(Duan4, HIGH);
      }
      break;
    case 4:
      {
        digitalWrite(Duan1, HIGH);
        digitalWrite(Duan2, HIGH);
        digitalWrite(Duan3, HIGH);
        digitalWrite(Duan4, LOW);
      }
      break;
  }
}
