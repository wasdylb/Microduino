#include <Adafruit_NeoPixel.h>
#define PIN 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(19, PIN, NEO_GRB + NEO_KHZ800);

#include <Microduino_Key.h>
Key KeyA(6, INPUT_PULLUP);

#define speakerPin  4
#define wrt_serial Serial1

int Countdown = 10 * 1000;
int led_on = 18;

int takephotho_num;

unsigned long timer;

String msg = "";

void colorSet(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void colorSet(uint32_t c, uint32_t i) {
  strip.setPixelColor(i, c);
  strip.show();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wrt_serial.begin(9600);
  strip.begin();
  colorSet(strip.Color(0, 100, 100));
  delay(500);
  colorSet(strip.Color(0, 0, 0));
  wrt_serial.println("S0");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (wrt_serial.available() > 0)
  {
    msg = wrt_serial.readStringUntil('\n');
    Serial.println(msg);
  }
  if (msg.length() >= 3 && msg[0] == 'P')
  {
    takephotho_num = (msg[1] - '0') * 10 + msg[2] - '0';
    if (takephotho_num > 0 && takephotho_num % 5 == 0)
    {
      led_int5(strip.Color(0, 255, 255), takephotho_num / 5, 3, 500);
      wrt_serial.println("S0");
    }
    msg = "";
  }
  if (msg == "WA")
  {
    Serial.println("--- WA mode ----");
    led_wa(strip.Color(255, 0, 0), 45);
    led_wa(strip.Color(0, 255, 0), 45);
    led_wa(strip.Color(0, 0, 255), 45);
    led_wa(strip.Color(0, 255, 255), 45);
    colorSet(strip.Color(255, 0, 255));
    delay(1000);
    colorSet(strip.Color(0, 0, 0));
    delay(1000);
    colorSet(strip.Color(255, 0, 255));
    delay(1000);
    colorSet(strip.Color(0, 0, 0));
    delay(1000);
    colorSet(strip.Color(255, 0, 255));
    delay(1000);
    colorSet(strip.Color(0, 0, 0));
    delay(1000);
    wrt_serial.println("S0");
    msg = "";
  }
  if (msg == "W1")
  {
    Serial.println("--- W1 mode ----");
    led_w1(strip.Color(255, 0, 255) , 45);
    led_w1(strip.Color(0, 255, 255) , 45);
    led_w1(strip.Color(255, 255, 255) , 45);
    led_w1(strip.Color(50, 255, 100) , 45);
    led_wa(strip.Color(255, 0, 0), 45);
    led_wa(strip.Color(0, 255, 0), 45);
    led_wa(strip.Color(0, 0, 255), 45);
    led_wa(strip.Color(0, 255, 255), 45);
    wrt_serial.println("S0");
    msg = "";
  }

  if ((KeyA.read()) == SHORT_PRESS)
  {
    Serial.println("takephoto");
    colorSet(strip.Color(255, 0, 0));
    colorSet(strip.Color(0, 0, 0), 0);
    wrt_serial.println("T0");
    if (millis() != timer) timer = millis();
    while (millis() - timer <= Countdown - 1000)
    {
      if (millis() % 1000 == 0)
      {
        tone(speakerPin, 400, 200);
        colorSet(strip.Color(0, 0, 0), led_on);
        colorSet(strip.Color(0, 0, 0), led_on - 1);
        led_on -= 2;
      }
    }
    colorSet(strip.Color(255, 255, 255), 0);
    tone(speakerPin, 800);
    wrt_serial.println("T1");
    delay(80);
    colorSet(strip.Color(0, 0, 0));
    noTone(speakerPin);
    led_on = 18;
  }
  delay(15);
}

void led_wa(uint32_t c , int wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(strip.numPixels() - i, c);
    strip.show();
    delay(wait);
  }
  colorSet(strip.Color(0, 0, 0));
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
  colorSet(strip.Color(0, 0, 0));
}

void led_w1( uint32_t c , int wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(strip.numPixels() / 2 - i, c);
    strip.setPixelColor(strip.numPixels() / 2 + i, c);
    strip.show();
    delay(wait);
  }
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(strip.numPixels() - i, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
  }
}

void led_int5( uint32_t c , int number, int fre , int wait)
{
  for (int j = 0; j < fre; j++)
  {
    for (int i = 0; i < number + 1; i++)
    {
      strip.setPixelColor(strip.numPixels() - i, c);
      strip.show();
    }
    delay(wait);
    for (int i = 0; i < number + 1; i++)
    {
      strip.setPixelColor(strip.numPixels() - i, strip.Color(0, 0, 0));
      strip.show();
    }
    delay(wait);
  }
}

