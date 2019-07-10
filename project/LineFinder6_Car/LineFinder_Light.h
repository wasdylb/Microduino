#ifndef _LINEFINDERLIGHT_H_
#define _LINEFINDERLIGHT_H_
#include "Arduino.h"

#define IICADDR                 0x09

#define I2C_DATA_SIZE           14

#define ADDR8_HANDWARE_VERSION  0
#define ADDR8_SOFTWARE_VERSION  1
#define ADDR16_LINE0            2
#define ADDR16_LINE1            4
#define ADDR16_LINE2            6
#define ADDR16_LINE3            8
#define ADDR16_LINE4            10
#define ADDR16_LINE5            12

typedef union {
  uint16_t D16[I2C_DATA_SIZE / 2];
  uint8_t U8[I2C_DATA_SIZE];
} data_u;

typedef struct {
  data_u data;
} i2cData_t;

class LineFinder_Light {

  public:
    LineFinder_Light();
    bool begin(uint8_t i2cAddr = IICADDR);
    uint8_t getReg8(uint8_t _reg);
    uint8_t getHandware();
    uint8_t getSoftware();
    void getLine(uint16_t *_line);

  private:
    uint8_t _i2cAddr;
    i2cData_t i2cData;

};

#endif
