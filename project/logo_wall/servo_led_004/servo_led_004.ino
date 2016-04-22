#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIN, NEO_GRB + NEO_KHZ800);

#define servo_max 180
#define servo_min 90

#define servo_pin 8
#define servo_sensor A0

boolean led_off;

void servopulse(int sp1, int val1) //Define a pulse function
{
  int myangle1 = map(val1, 0, 180, 500, 2480);
  for (int i = 0; i <= 40; i++)
  {
    digitalWrite(sp1, HIGH); //set servo interface HIGH
    delayMicroseconds(myangle1);
    digitalWrite(sp1, LOW); //set servo interface LOW
    delay(20 - val1 / 1000);
  }
}

int tmStep_sevor()
{
  if (analogRead(servo_sensor ) < 700)
  {
    delay(10);
    if (analogRead(servo_sensor ) < 700)
      return 1;
  }
  return 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(servo_sensor, INPUT);
  pinMode(servo_pin, OUTPUT);
  servopulse(servo_pin, servo_min);
  strip.begin();
  delay(500);
  colorSet(strip.Color(0, 0, 0));
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(servo_sensor));
  if (tmStep_sevor())
  {
    servopulse(servo_pin, servo_max);
    delay(6000);
    colorSet(strip.Color(0, 100, 100));
    delay(6000);
    servopulse(servo_pin, servo_min);
  }
  else
    colorSet(strip.Color(0, 0, 0));
}

void colorSet(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
