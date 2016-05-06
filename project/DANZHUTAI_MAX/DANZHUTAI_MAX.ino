//#include <Servo.h>
//Servo myservo;  // create servo object to control a servo
int servo_pos = 0;    // variable to store the servo position
int servo_num = 1;
unsigned long servo_time = 0;

//get sensor vol/////////////////////////////
#include <TimerOne.h>

#define Dead 0
#define Left 1
#define Curve 2
#define LeftTop 3
#define Top 4

#define VOL_MIN 600
#define VOL_MAX 1000

int sensor_pin[5] = {
  A0, A1, A2, A3, A6
};
int sensor_Value_def[5] = {
  770, 700, 700, 820, 710
};
boolean activate[5] = {
  0, 0, 0, 0, 0
};

boolean sensor_sta[5] = {
  0, 0, 0, 0, 0
};
boolean sensor_sta_cache[5] = {
  0, 0, 0, 0, 0
};
#define T_STA 400 //消抖时间
unsigned long time_sta = 0; //消抖时间
void timerIsr() {
  int sensor_Value[5];
  for (int a = 0; a < 5; a++) {
    sensor_sta_cache[a] = sensor_sta[a];
    sensor_Value[a] = constrain(analogRead(sensor_pin[a]), VOL_MIN, VOL_MAX);
    sensor_sta[a] = (boolean) (sensor_Value[a] < sensor_Value_def[a]);
    if (sensor_sta[a] && !sensor_sta_cache[a]) {
      activate[a] = true;
      time_sta = millis();
    }
    //    sensor_Value_min[a] = min(sensor_Value[a], sensor_Value_min[a]);
    //    sensor_Value_max[a] = min(sensor_Value[a], sensor_Value_max[a]);
  }
}

//Score/life/////////////////////////
#include <EEPROM.h>

#define S_VOL_A  4
#define S_VOL_B  6
#define S_VOL_C  8

unsigned long Score = 0;
unsigned long Score_cache = 0;
unsigned long Score_Top = 0;
int Life = 1;

//LEDMATRIX////////////////////////////////
#include "Microduino_Matrix.h"

uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {
  { 64, 63}
};

Matrix display = Matrix(Addr);

int display_sta = 0;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  Wire.begin();
  //getDeviceAddr
  for (int a = 0; a < display.getMatrixNum(); a++) {
    Serial.print(display.getDeviceAddr(a));
    Serial.print(" ");
  }
  Serial.println("");

  //setLedColor
  for (int y = 0; y < display.getHeight() * 8; y++) {
    for (int x = 0; x < display.getWidth() * 8; x++) {
      randomSeed(analogRead(A7));
      display.setLedColor(x, y, random(0, 255), random(0, 255), random(0, 255));   //x, y, r, g, b
      delay(5);
    }
  }
  delay(1000);
  display.clearDisplay();
  display_sta = 1;

  EEPROM.get(0, Score_Top);

  Timer1.initialize(5000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

  //pinMode(6, OUTPUT); //设定舵机接口为输出接口
  //  myservo.attach(6);
}

String _buffer_data;
char buffer_data[128];
// the loop routine runs over and over again forever:
void loop() {
  //  if (millis() < time_sensor) time_sensor = millis();
  //  if (millis() - time_sensor > 4) {
  //    timerIsr();
  //
  //    time_sensor = millis();
  //  }

  if (Life <= 0) {
    //EEPROM;
    if (Score > Score_Top) {
      Serial.print("You got the Top Score:");
      Serial.println(Score);
      Score_Top = Score;
      EEPROM.put(0, Score_Top);
      display_sta = 101;
    }
    else {
      Serial.print("You Score:");
      Serial.print(Score);
      Serial.print(",The Top Score:");
      Serial.println(Score_Top);
      display_sta = 100;
    }
    Score_cache = Score;
    Life = 1;
    Score = 0;
  }
  else {
    if (millis() - time_sta > T_STA) {
      if (activate[Left]) {
        activate[Left] = false;
        Life++;

        Life = constrain(Life, 0, 16);
        Serial.print("Life:");
        Serial.print(Life);
        Serial.println("");

        display_sta = 201;
      }
      if (activate[Dead]) {
        activate[Dead] = false;
        Life--;

        Life = constrain(Life, 0, 16);
        Serial.print("Life:");
        Serial.print(Life);
        Serial.println("");

        display_sta = 200;
      }
      if (activate[LeftTop]) {
        activate[LeftTop] = false;
        Score += S_VOL_A;
        Serial.print("Score:");
        Serial.print(Score);
        Serial.println("");

        display_sta = 301;
      }
      if (activate[Top]) {
        activate[Top] = false;
        Score += S_VOL_B;
        Serial.print("Score:");
        Serial.print(Score);
        Serial.println("");

        display_sta = 302;
      }
      if (activate[Curve]) {
        activate[Curve] = false;
        Score += S_VOL_C;
        Serial.print("Score:");
        Serial.print(Score);
        Serial.println("");

        display_sta = 303;
      }
    }
  }

  if (display_sta) {
    display.clearDisplay();
    if (display_sta == 1) {
      display.setColor(255, 0, 255);
      //writeString H
      display.setCursor(0, 0);   //x, y
      display.print("GO!"); //string, MODE, time ,y
      display_sta = 0;
    }
    else if (display_sta == 100) {
      _buffer_data =  "Score:";
      _buffer_data += String(Score_cache);
      for (int a = 0; a < 128; a++) buffer_data[a] = NULL;
      for (int a = 0; a < _buffer_data.length(); a++) buffer_data[a] = _buffer_data[a];
      display.setColor(0, 255, 0);
      display.writeString(buffer_data, MODE_H, 20, 0); //string, MODE, time ,y
      display_sta = 1;
    }
    else if (display_sta == 101) {
      _buffer_data =  "Top Score:";
      _buffer_data += String(Score_cache);
      for (int a = 0; a < 128; a++) buffer_data[a] = NULL;
      for (int a = 0; a < _buffer_data.length(); a++) buffer_data[a] = _buffer_data[a];
      display.setColor(255, 0, 0);
      display.writeString(buffer_data, MODE_H, 20, 0); //string, MODE, time ,y
      display_sta = 1;
    }
    else {
      display.setColor(0, 255, 0);
      display.setFontMode(MODE_H);
      display.setCursor(0, 0);   //x, y
      display.print(Score); //string, MODE, time ,y
      display.setColor(0, 0, 255);
      display.drawLine(0, 7, Life - 1, 7);
      display_sta = 0;
    }
  }

  if (millis() < servo_time) servo_time = millis();
  if (millis() - servo_time > 10) {
    servo_pos += servo_num;
    if (servo_pos > 180 || servo_pos < 0) {
      servo_num = -servo_num;
    }
    //    myservo.write(servo_pos);
    //myservo.detach();
    servo_time = millis();
  }
}
