#include <Microduino_Motor.h>
#if defined(__AVR_ATmega32U4__) || (__AVR_ATmega1284P__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define motor_pin0A 8
#define motor_pin0B 6
#define motor_pin1A 7
#define motor_pin1B 5
#else
#define motor_pin0A 6
#define motor_pin0B 8
#define motor_pin1A 5
#define motor_pin1B 7
#endif
Motor MotorLeft(motor_pin0A, motor_pin0B);
Motor MotorRight(motor_pin1A, motor_pin1B);

#define motor_pin0A A0
#define motor_pin0B A1

#define MAX_THROTTLE 255
#define MAX_STEERING 200
int16_t throttle = 0;
int16_t steering = 0;

#define upPin 3
#define downPin 2
#define ledPin A3

boolean run_car, off, on;

#include <Microduino_Protocol_SoftSer.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, -1);
Protocol ProtocolB(&mySerial, TYPE_NUM);
uint16_t Data[8];
void setup()
{
  MotorLeft.Fix(1);
  MotorRight.Fix(-1);
  delay(1000);

  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  ProtocolB.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(upPin) && !digitalRead(downPin))
    off = true;
  else if (!digitalRead(upPin) && digitalRead(downPin))
    on = true;
  else
  {
    off = false;
    on = false;
  }

  int sta = ProtocolB.parse(Data, MODE_WHILE);
  if (sta == P_FINE) {

    for (int a = 0; a < CHANNEL_NUM; a++) {
      Serial.print(Data[a]);
      Serial.print(" ");
    }
    Serial.println("    DATA OK");

    if (Data[3] == 1500 && Data[2] == 1500 && Data[4] == 1000)
      digitalWrite(ledPin, LOW);
    else
      digitalWrite(ledPin, HIGH);
    Serial.print(off);
    Serial.print(",");
    Serial.println(on);

    if (Data[4] == 2000)
      run_car = true;
    else
      run_car = false;

    if (run_car)
    {
      if (off)//OFF
        up();
      if (on)//ON
        down();
      delay(500);
    }
    else if (off || on)
      stop();

    throttle = map(Data[3], 1000, 2000, -255, 255);
    steering = map(Data[2], 1000, 2000, -255, 255);
    MotorLeft.Driver(MotorLeft.GetData(throttle, steering, CHAN_LEFT));
    MotorRight.Driver(MotorRight.GetData(throttle, steering, CHAN_RIGHT));
  }
  delay(10);

}

void up()
{
  digitalWrite(motor_pin0A, HIGH);
  digitalWrite(motor_pin0B, LOW);
}
void down()
{
  digitalWrite(motor_pin0A, LOW);
  digitalWrite(motor_pin0B, HIGH);
}

void stop()
{
  digitalWrite(motor_pin0A, HIGH);
  digitalWrite(motor_pin0B, HIGH);
}

