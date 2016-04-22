#include  "Colorled.h"
#include  "track.h"

#define pir_pin 10

#define switch_led A0
#define switch_track A1
#define switch_speed A2

int speed_track = 175;

boolean pir_track;

unsigned long train_time = 0;

int switchSet (int pin)
{
  if (analogRead(pin) <= 30)
    return 1;
  else if (analogRead(pin) >= 1000)
    return 2;
  else
    return 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(pir_pin, INPUT);
  pinMode(switch_led, INPUT_PULLUP);
  pinMode(switch_track, INPUT_PULLUP);
  pinMode(switch_speed, INPUT_PULLUP);
  pinMode(OUT1A, OUTPUT);
  pinMode(PWM1A, OUTPUT);
  strip.begin();
}

void loop() {
  //Serial.println(analogRead(A6));
  //--------pir---------//
  if (digitalRead(pir_pin))
  {
    pir_track = true;
    train_time = millis();
    colorSet(strip.Color(100, 100, 100), 3);
  }
  else
    colorSet(strip.Color(0, 0, 0), 3);

  //--------switch track-------//
  if (switchSet(switch_track) == 0)
  {
    pir_track = false;
    stop();
  }
  else
  {
    if (pir_track)
    {
      if (switchSet(switch_track) == 1 )
        car_run(1, speed_track);
      else if (switchSet(switch_track) == 2 )
        car_run(2, speed_track);
    }
    else
      stop();
    if (millis() < train_time) train_time = millis();
    if (millis() - train_time > 10 * 1000) {
      pir_track = false;
      train_time = millis();
    }
    Serial.println(pir_track);
  }
  //--------switch speed-------//
  if (switchSet(switch_speed) == 0)
    speed_track = 200;
  else if (switchSet(switch_speed) == 1)
    speed_track = 255;
  else if (switchSet(switch_speed) == 2)
    speed_track = 170;

  //--------switch colorled-------//
  if (switchSet(switch_led) == 0)//关
  {
    colorSet(strip.Color(0, 0, 0), 0);
    colorSet(strip.Color(0, 0, 0), 1);
    colorSet(strip.Color(0, 0, 0), 2);
  }
  else if (switchSet(switch_led) == 1)
  {
    colorSet(strip.Color(255, 0, 0), 0);
    colorSet(strip.Color(0, 255, 0), 1);
    colorSet(strip.Color(0, 0, 255), 2);
  }
  else if (switchSet(switch_led) == 2)
  {
    breath(255, 255, 0, 0);
    breath(0, 255, 255, 1);
    breath(255, 0, 255, 2);
  }
  //delay(10);
}
