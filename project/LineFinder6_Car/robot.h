#define FingerShield
//#define Microrobot

#include "LineFinder_Light.h"
#if defined(FingerShield)
#include <Microduino_MotorPlus.h>
MotorPlus motor(MOTOR_ADDR4);
#elif defined(Microrobot)
#include <Microduino_MicroRobot.h>
MicroRobot microRobot;
#endif
#include <Microduino_Matrix.h>

LineFinder_Light LineFinder;
uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {  //1x1
  {48}      //点阵IIC地址
};
Matrix display = Matrix(Addr, TYPE_S2);
#if defined(FingerShield)
#define CHACKSPEED 50
#define MAXSPEED 190
#elif defined(Microrobot)
#define CHACKSPEED 120
#define MAXSPEED 150
#endif


uint16_t lineval[6];
uint16_t value_min[6] = {1023, 1023, 1023, 1023, 1023, 1023};
uint16_t value_max[6] = {0, 0, 0, 0, 0, 0};
uint16_t value[6];

int16_t distance;
int16_t last_proportional;
long integral = 0;

int leftspeed, rightspeed;

void setspeed(int16_t left, int16_t right) {
#if defined(FingerShield)
  if (left != BRAKE)
    motor.setSpeed(-left, right);
  else
    motor.setSpeed(BRAKE, right);
#elif defined(Microrobot)
  microRobot.setSpeed(1, left);
  if (right != BRAKE)
    microRobot.setSpeed(4, -right);
  else
    microRobot.setSpeed(4, BRAKE);
#endif
}

void robotInit() {
  Serial.println("init");
#if defined(FingerShield)
  motor.begin();
#elif defined(Microrobot)
  microRobot.begin();
  microRobot.motorInit(1);
  microRobot.motorInit(4);
#endif
  LineFinder.begin(0x09);
  Wire.begin();
  display.clearDisplay();
  Serial.println("start");
  tone(D7, 600, 150);
  delay(150);
  tone(D7, 800, 150);
  delay(150);
  tone(D7, 1000, 150);
  delay(150);
}

void LineFinderTest() {
  LineFinder.getLine(lineval);
  Serial.print('[');
  for (uint8_t i = 0; i < 6; i++) {
    Serial.print(lineval[i]);
    if (i == 5)
      Serial.print("]\n");
    else
      Serial.print(',');
  }
  delay(5);
}

uint8_t linemin(uint16_t *_line) {
  uint16_t _min = 1500;
  uint8_t num = 0;
  for (uint8_t i = 0; i < 6; i++) {
    if (_line[i] < _min) {
      _min = _line[i];
      num = i + 1;
    }
  }
  return num;
}

uint8_t numcache = 0;
uint8_t positionmin(uint16_t *_line) {
  uint16_t _min = 1500;
  uint8_t num = 0;
  for (uint8_t i = 0; i < 6; i++) {
    if (_line[i] < _min) {
      _min = _line[i];
      num = i + 1;
      if (_min < 900)
        numcache = num;
    }
  }
  if (_min > 900) {
    if (numcache < 3)
      return 0;
    else
      return 7;
  } else {
    return num;
  }
}

uint8_t _numcache;
void autoCalibrateSensor() {
  delay(300);
  uint8_t _num;
  long timer = millis();
  LineFinder.getLine(lineval);
  _num = linemin(lineval);
  while (_num != 6) {
    LineFinder.getLine(lineval);
    for (int i = 0; i < 6; i++) {
      value_min[i] = min(lineval[i], value_min[i]);
      value_max[i] = max(lineval[i], value_max[i]);
    }
    _num = linemin(lineval);
    display.setLed(_num, 3, true);
    if (_numcache != _num) {
      display.setLed(_numcache, 3, false);
      _numcache = _num;
    }
    setspeed(-CHACKSPEED, CHACKSPEED);
    delay(10);
  }
  timer = millis();
  while (millis() - timer < 30) {
    LineFinder.getLine(lineval);
    for (int i = 0; i < 6; i++) {
      value_min[i] = min(lineval[i], value_min[i]);
      value_max[i] = max(lineval[i], value_max[i]);
    }
    _num = linemin(lineval);
    setspeed(-CHACKSPEED, CHACKSPEED);
    delay(10);
  }
  while (_num != 1) {
    LineFinder.getLine(lineval);
    for (int i = 0; i < 6; i++) {
      value_min[i] = min(lineval[i], value_min[i]);
      value_max[i] = max(lineval[i], value_max[i]);
    }
    _num = linemin(lineval);
    display.setLed(_num, 3, true);
    if (_numcache != _num) {
      display.setLed(_numcache, 3, false);
      _numcache = _num;
    }
    setspeed(CHACKSPEED, -CHACKSPEED);
    delay(10);
  }
  timer = millis();
  while (millis() - timer < 30) {
    LineFinder.getLine(lineval);
    for (int i = 0; i < 6; i++) {
      value_min[i] = min(lineval[i], value_min[i]);
      value_max[i] = max(lineval[i], value_max[i]);
    }
    setspeed(CHACKSPEED, -CHACKSPEED);
    delay(10);
  }
  while (_num != 3) {
    LineFinder.getLine(lineval);
    for (int i = 0; i < 6; i++) {
      value_min[i] = min(lineval[i], value_min[i]);
      value_max[i] = max(lineval[i], value_max[i]);
    }
    _num = linemin(lineval);
    display.setLed(_num, 3, true);
    if (_numcache != _num) {
      display.setLed(_numcache, 3, false);
      _numcache = _num;
    }
    setspeed(-CHACKSPEED, CHACKSPEED);
    delay(10);
  }
  for (int i = 0; i < 6; i++) {
    Serial.print("[");
    Serial.print(value_min[i]);
    Serial.print(",");
    Serial.print(value_max[i]);
    Serial.print("]");
    Serial.print(" ");
  }
  Serial.print("\n");
  setspeed(BRAKE, BRAKE);
  delay(300);
  setspeed(0, 0);
}

int16_t getposition() {
  uint8_t point;

  LineFinder.getLine(lineval);
  for (uint8_t i = 0; i < 6; i++) {
    value[i] = map(constrain(lineval[i], value_min[i], value_max[i]), value_min[i], value_max[i], 0, 1000);
  }
  point = positionmin(value);
  display.setLed(point, 3, true);
  if (_numcache != point) {
    display.setLed(_numcache, 3, false);
    _numcache = point;
  }
  /*
    Serial.print("[");
    for (int i = 0; i < 6; i++) {
      Serial.print(value[i]);
      if (i < 5)
        Serial.print(",");
    }
    Serial.print("]  ");
    Serial.print(point);
    Serial.print("   ");
  */
  if (point == 0) {
    distance = -1000;
  } else if (point == 7) {
    distance = 7000;
  } else if (point == 1) {
    distance = value[0] + 1000 - value[1];
  } else if (point == 6) {
    distance = 4000 + value[4] + 1000 - value[5];
  }  else {
    if (value[point - 2] < value[point]) {
      distance = 1000 * (point - 2) + value[point - 2] + value[point - 1];
    } else {
      distance = 1000 * (point - 2) + value[point - 2] + value[point - 1] + 1000 - value[point];
    }
  }
  Serial.println(distance - 3000);
  delay(10);
}

void runRobot() {
  int proportional = distance - 3000;
  int derivative = proportional - last_proportional;
  integral += proportional;

  last_proportional = proportional;
#if defined(FingerShield)
  int power_difference = proportional / 2 + integral / 20000 + derivative * 2 / 1;
#elif defined(Microrobot)
  int power_difference = proportional / 2 + integral / 10000 + derivative;
#endif
  if (power_difference > MAXSPEED)
    power_difference = MAXSPEED;
  if (power_difference < -MAXSPEED)
    power_difference = -MAXSPEED;
  if (power_difference < 0) {
    leftspeed = MAXSPEED + power_difference;
    rightspeed = MAXSPEED;
  }
  else {
    leftspeed = MAXSPEED ;
    rightspeed = MAXSPEED - power_difference;
  }
  /*
    Serial.print(leftspeed);
    Serial.print(" , ");
    Serial.println(rightspeed);
  */
  setspeed(leftspeed, rightspeed);
}
