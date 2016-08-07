#include "Arduino.h"

#define BUTTON_KEY A0

//键值定义-------------------
#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4

uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;
uint8_t last_key_code = KEY_NONE;

//检测输入动作---------------
void uiStep(void) {
  uiKeyCodeSecond = uiKeyCodeFirst;
  /*-----------------------Joystick-----------------------*/
  /*
    if (analogRead(A0) < 100)
    uiKeyCodeFirst = KEY_NEXT;
    else if (analogRead(A0) > 900)
    uiKeyCodeFirst = KEY_PREV;
    else if (analogRead(A1) > 900)
    uiKeyCodeFirst = KEY_SELECT;
    else if (analogRead(A1) < 100)
    uiKeyCodeFirst = KEY_BACK;
    else
    uiKeyCodeFirst = KEY_NONE;
  */
  /*-----------------------Audio-----------------------*/
  Serial.println(analogRead(BUTTON_KEY));
  if (analogRead(BUTTON_KEY) > 450 && analogRead(BUTTON_KEY) < 650)
  {
    delay(100);
    uiKeyCodeFirst = KEY_NEXT;
  }
  else if (analogRead(BUTTON_KEY) > 800 && analogRead(BUTTON_KEY) < 950)
  {
    delay(100);
    uiKeyCodeFirst = KEY_PREV;
  }
  else if (analogRead(BUTTON_KEY) < 100)
    uiKeyCodeFirst = KEY_SELECT;
  else
    uiKeyCodeFirst = KEY_NONE;

  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = KEY_NONE;
}
