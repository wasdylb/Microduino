#include <Microduino_Key.h>
#include <Adafruit_NeoPixel.h>
#define PIN 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIN, NEO_GRB + NEO_KHZ800);

Key KeyA(6, INPUT_PULLUP);

boolean led_off;

#define val_max 255
#define val_min 0
#define servo_max 78//off
#define servo_min 53//on

#define servo_ball_max 130//off
#define servo_ball_min 40//on

#define servo_pin 8
#define servo_ball_pin 10

#define servo_sensor A0
#define light_sensor A2

boolean light_start;

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

int tmStep()
{
  if (analogRead(servo_sensor ) < 500)
  {
    delay(10);
    if (analogRead(servo_sensor ) < 500)
      return 1;
  }
  if (analogRead(light_sensor) < 500)
  {
    delay(10);
    if (analogRead(light_sensor) < 500)
      return 2;
  }
  return 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(servo_sensor, INPUT_PULLUP);
  pinMode(light_sensor, INPUT_PULLUP);
  pinMode(servo_pin, OUTPUT);
  pinMode(servo_ball_pin, OUTPUT);
  strip.begin();
  delay(100);
  colorSet(strip.Color(0, 0, 0));
  delay(500);
  servopulse(servo_pin, servo_max);
  servopulse(servo_ball_pin, servo_ball_max);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(servo_sensor));
  Serial.print(" , ");
  Serial.print(analogRead(light_sensor));
  Serial.print(" , ");
  Serial.print(tmStep());
  Serial.print(" , ");
  Serial.println(led_off);

  if (KeyA.read() == SHORT_PRESS)
  {
    led_off = true;
    servopulse(servo_pin, servo_max);
    delay(20);
  }
  if (tmStep() == 1)
    servopulse(servo_pin, servo_min);
  if (tmStep() == 2 && !led_off)
  {
    colorSet(strip.Color(0, 100, 100));
    led_off = true;
    servopulse(servo_ball_pin, servo_ball_min);
  }
  if (tmStep() == 0 && led_off)
  {
    servopulse(servo_ball_pin, servo_ball_max);
    colorSet(strip.Color(0, 0, 0));
    led_off = false;
  }
  delay(15);
}

void colorSet(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}


