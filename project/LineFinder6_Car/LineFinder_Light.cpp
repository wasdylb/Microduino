#include <Wire.h>
#include <I2Cdev.h>
#include "LineFinder_Light.h"

LineFinder_Light::LineFinder_Light()
{

}

boolean LineFinder_Light::begin(uint8_t addr)
{
  _i2cAddr = addr;
  Wire.begin ();
  Wire.beginTransmission(_i2cAddr);
  return !Wire.endTransmission();
}

uint8_t LineFinder_Light::getReg8(uint8_t _reg)
{
  uint8_t result8, resultsta;
  resultsta = I2Cdev::readByte(_i2cAddr, _reg, &result8);
  if (resultsta)
    return result8;
  else
    return 0;
}

uint8_t LineFinder_Light::getHandware()
{
  return getReg8(ADDR8_HANDWARE_VERSION);
}

uint8_t LineFinder_Light::getSoftware()
{
  return getReg8(ADDR8_SOFTWARE_VERSION);
}

void LineFinder_Light::getLine(uint16_t *_line) {
  uint8_t num = 0;
  Wire.beginTransmission(_i2cAddr);
  Wire.write(ADDR16_LINE0);
  Wire.endTransmission();
  Wire.requestFrom(_i2cAddr, 12);
  while (Wire.available()) {
    i2cData.data.U8[num] = Wire.read();
    num++;
  }
  if (num == 12) {
    memcpy(_line, i2cData.data.D16, 12);
  }else{
    memset(_line, 0, 12);
  }
}

