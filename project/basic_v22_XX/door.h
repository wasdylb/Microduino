#include "arduino.h"

#define DOOR_TIMEOUT 10000  //10s

#define DOOR_SENSOR_PIN A0
#define DOOR_PIN 0

unsigned long time_door;

void Door_begin() {
  pinMode(DOOR_PIN, OUTPUT);
  digitalWrite(DOOR_PIN, LOW);
}

void Door_Open() {
  Serial.println("Door_Open");
  digitalWrite(DOOR_PIN, HIGH);
  //  myservo.write(servo_max);
  //  delay(1000);
}

void Door_Close() {
  Serial.println("Door_Close");
  digitalWrite(DOOR_PIN, LOW);
  //  myservo.write(servo_min);
  //  delay(1000);
}

boolean Door_Check() {
  Serial.println("Door_Check");
  //  //  Serial.print("\nDoor_Check Program IN!");
  //  return digitalRead(DOOR_SENSOR_PIN);
}
