#include "robot.h"

boolean runsta;

void setup() {
  Serial.begin(115200);
  delay(2000);
  robotInit();
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
}

void loop() {
  //LineFinderTest();

  if (!digitalRead(D6)) {
    for (uint8_t i = 0; i < 2; i++) {
      autoCalibrateSensor();
    }
    runsta = false;
  }

  if (!digitalRead(D5)) {
    delay(300);
    runsta = !runsta;
  }
  if (runsta) {
    getposition();
    runRobot();
  }

}
