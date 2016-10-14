#include <IRremote.h>
#define PHOTO 0xB4B8F

IRsend irsend;

unsigned long timer;

#define IR_pin 6  //CoreUSB

void setup() {
  Serial.begin(9600);
  pinMode(IR_pin, OUTPUT);
  delay(1000);
  takePhoto();
}

void loop() {

  if ((millis() - timer) / 1000 > 2 * 60)
  {
    takePhoto();
    timer = millis();
  }
  Serial.println((millis() - timer) / 1000);
}

void takePhoto()
{
  for (int i = 0; i < 3; i++)
  {
    irsend.sendSony(PHOTO, 20); // Sony code
    delay(10);
  }
}
