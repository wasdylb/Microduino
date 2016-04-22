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
#define MAX_THROTTLE 255
#define MAX_STEERING 200
int16_t throttle = 0;
int16_t steering = 0;

#include <Adafruit_NeoPixel.h>
#define PIN A0
Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIN, NEO_GRB + NEO_KHZ800);

#define light_sensor A2

#define speed_max 100
#define speed_min 0

boolean car_run, car_stop;

int tmStep_light()
{
  if (analogRead(light_sensor) < 200)
  {
    delay(10);
    if (analogRead(light_sensor) < 200)
      return 1;
  }
  return 0;
}

void colorSet(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(light_sensor, INPUT);
  MotorLeft.Fix(1);
  MotorRight.Fix(1);
  strip.begin();
  colorSet(strip.Color(0, 100, 100));
  delay(500);
  colorSet(strip.Color(0, 0, 0));
}


void loop()
{
  Serial.print(car_run);
  Serial.print(",");
  Serial.println(analogRead(light_sensor));

  if (tmStep_light())
  {
    colorSet(strip.Color(0, 100, 100));
    for (int i = speed_min; i < speed_max; i++)
    {
      MotorLeft.Driver(MotorLeft.GetData(i, 0, CHAN_LEFT));
      MotorRight.Driver(MotorRight.GetData(i, 0, CHAN_RIGHT));
      delay(15);
      if (i == speed_max-1)
        car_run = true;
    }
  }
  if (car_run)
  {
    MotorLeft.Driver(MotorLeft.GetData(speed_max, 0, CHAN_LEFT));
    MotorRight.Driver(MotorRight.GetData(speed_max, 0, CHAN_RIGHT));
    delay(5000);
    car_run = false;
    car_stop = true;
    colorSet(strip.Color(0, 0, 0));
  }
  if (!tmStep_light() && car_stop)
  {
    for (int i = speed_max; i > speed_min; i--)
    {
      MotorLeft.Driver(MotorLeft.GetData(i, 0, CHAN_LEFT));
      MotorRight.Driver(MotorRight.GetData(i, 0, CHAN_RIGHT));
      delay(15);
      if (i == speed_min + 1)
        car_stop = false;
    }
  }
}
