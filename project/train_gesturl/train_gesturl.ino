#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <Adafruit_NeoPixel.h>
#include <Microduino_Motor.h>

#define LEDPIN 12

SparkFun_APDS9960 apds = SparkFun_APDS9960();
Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, LEDPIN, NEO_GRB + NEO_KHZ800);

#if defined(__AVR_ATmega32U4__) || (__AVR_ATmega1284P__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define motor_pin0A 8  //PWM
#define motor_pin0B 6
#define motor_pin1A 7  //PWM 
#define motor_pin1B 5
#else
#define motor_pin0A 6  //PWM
#define motor_pin0B 8
#define motor_pin1A 5  //PWM
#define motor_pin1B 7
#endif

Motor MotorLeft(motor_pin0A, motor_pin0B);
Motor MotorRight(motor_pin1A, motor_pin1B);

#define MAX_THROTTLE 255 //最大油门 100~255
#define MAX_STEERING 200 //最大转向 100~512

#define MAX_SPEED_PLUS 255
#define MAX_SPEED_NEGATIVE -255
#define MIN_SPEED 0

#define SPEED_CHANGETIME 5

int train_speed;
int mode = 4, mode_old = 4;

unsigned timer1;

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  MotorLeft.Fix(1);
  MotorRight.Fix(1);
  delay(2000);

  strip.begin();
  strip.show();
  colorWipe(strip.Color(255, 0, 0));
  delay(500);
  colorWipe(strip.Color(0, 255, 0));
  delay(500);
  colorWipe(strip.Color(0, 0, 255));
  delay(500);
  colorWipe(strip.Color(0, 0, 0));
}

void loop() {
  handleGesture();
  if (mode == 3)
  {
    mode_old = 3;
    colorWipe(strip.Color(255, 0, 255));
    if (millis() - timer1 > SPEED_CHANGETIME)
    {
      train_speed--;
      timer1 = millis();
      if (train_speed < MAX_SPEED_NEGATIVE)
        train_speed = MAX_SPEED_NEGATIVE;
    }
  }
  else if (mode == 4)
  {
    mode_old = 4;
    if (millis() - timer1 > SPEED_CHANGETIME)
    {
      train_speed++;
      timer1 = millis();
      if (train_speed > MAX_SPEED_PLUS)
        train_speed = MAX_SPEED_PLUS;
    }
    colorWipe(strip.Color(0, 255, 255));
  }
  else if (mode == 1)
  {
    if (mode_old == 3)
    {
      if (millis() - timer1 > SPEED_CHANGETIME)
      {
        train_speed++;
        timer1 = millis();
        if (train_speed > MIN_SPEED)
          train_speed = MIN_SPEED;
      }
    }
    else if (mode_old == 4)
    {
      if (millis() - timer1 > SPEED_CHANGETIME)
      {
        train_speed--;
        timer1 = millis();
        if (train_speed < MIN_SPEED)
          train_speed = MIN_SPEED;
      }
    }
    colorWipe(strip.Color(0, 0, 0));
  }
  Serial.println(train_speed);
  MotorLeft.Driver(train_speed);
  MotorRight.Driver(train_speed);
}

void handleGesture() {
  if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        {
          Serial.println("UP");
          mode = 1;
        }
        break;
      case DIR_DOWN:
        {
          Serial.println("DOWN");
          mode = 2;
        }
        break;
      case DIR_LEFT:
        {
          Serial.println("LEFT");
          mode = 3;
        }
        break;
      case DIR_RIGHT:
        {
          Serial.println("RIGHT");
          mode = 4;
        }
        break;
      case DIR_FAR:
        {
          Serial.println("FAR");
          mode = 5;
        }
        break;
      default:
        Serial.println("NONE");
    }
    timer1 = millis();
  }
}

void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
