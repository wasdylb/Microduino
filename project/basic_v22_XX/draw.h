#include "Arduino.h"

#include "U8glib.h"

//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_courB14r)
#define setFont_M u8g.setFont(u8g_font_6x13)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)

//屏幕类型--------
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

#define init_draw 250	//主界面刷新时间
unsigned long time_draw;
unsigned long time_draw_sleep;
boolean draw_switch = false;

const unsigned char bmp_a[] U8G_PROGMEM =
{
  0x00, 0x00, 0xFC, 0x00, 0xFE, 0x7F, 0xFE, 0x43, 0xFE, 0x43, 0xFE, 0x7F, 0xFE, 0x43, 0xFE, 0x43,
  0xFE, 0x7F, 0xFE, 0x43, 0xFE, 0x43, 0xFE, 0x7F, 0xFE, 0x43, 0xFE, 0x43, 0xFE, 0x7F, 0x00, 0x00
};

const unsigned char bmp_c[] U8G_PROGMEM =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x07, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x00,
  0x00, 0x00, 0xF8, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0x1F, 0xF8, 0x3F, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0x07, 0xE0, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0x03, 0xC0, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x01, 0x80, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFC, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x78, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x3F, 0xFC, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x0F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x0F, 0xF0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xF0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x0F, 0xF0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x3F, 0xFC, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x3F, 0xFE, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char bmp_b[] U8G_PROGMEM =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x07, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x00,
  0x00, 0x00, 0xF8, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0x1F, 0xF8, 0x3F, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0x07, 0xE0, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0x03, 0xC0, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x01, 0x80, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0x80, 0x7F, 0x00, 0x00, 0xFE, 0x00, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x3F, 0xFC, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x0F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x0F, 0xF0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xE0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x07, 0xF0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x0F, 0xF0, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x3F, 0xFC, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0x3F, 0xFE, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char bmp_d[] U8G_PROGMEM =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
  0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
  0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
  0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00,
  0x00, 0xFE, 0xE0, 0x1F, 0xFC, 0x83, 0x3F, 0x00,
  0x00, 0x7E, 0xC0, 0x0F, 0xF8, 0x01, 0x3F, 0x00,
  0x00, 0x7E, 0xC0, 0x0F, 0xF8, 0x01, 0x3F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x7C, 0xC0, 0x0F, 0xF8, 0x01, 0x1F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0x78, 0xC0, 0x0F, 0xF8, 0x01, 0x0F, 0x00,
  0x00, 0xF8, 0xE0, 0x1F, 0xFC, 0x83, 0x0F, 0x00,
  0x00, 0xF8, 0xFB, 0x7F, 0xFF, 0xEF, 0x0F, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00,
  0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00,
  0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00,
  0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//主界面，可自由定义
void drawMain(int _draw_num, boolean _draw_refresh) {
  if (time_draw_sleep > millis()) time_draw_sleep = millis();
  if (millis() - time_draw_sleep > 30000) {
    if (draw_switch) {
      draw_switch = false;
      u8g.sleepOn();
    }
  }
  else {
    if (time_draw > millis()) time_draw = millis();
    if (millis() - time_draw > init_draw || _draw_refresh)
    {
      time_draw = millis();

      u8g.firstPage();
      do {
        switch (_draw_num) {
          case 1:
            setFont_M;
            u8g.setFontRefHeightText();
            u8g.setPrintPos(4, 16);
            u8g.print("Record in ");
            u8g.print(10 - (millis() - uid_time_admin) / 1000);
            u8g.print("s");

            //u8g.setFont(u8g_font_9x15Br);
            //u8g.setFont(u8g_font_9x18Br);
            //u8g.setFont(u8g_font_courB24n);
            u8g.setFontRefHeightText();

            u8g.drawXBMP( 110, 4, 16, 16, bmp_a);

            u8g.setFontRefHeightText();

            u8g.setPrintPos(15 + 40, 50);

            u8g.setDefaultForegroundColor();
            u8g.drawBox(0, 26, 128, 64 - 26);
            u8g.setDefaultBackgroundColor();
            u8g.setPrintPos(4, 42);
            u8g.print("Data:[");
            u8g.print(eeprom_Check(uid_data));
            u8g.print("]:");
            u8g.print(uid_data);

            u8g.setPrintPos(4, 60);
            u8g.print("Num:");
            u8g.print(eeprom_Num());
            u8g.print("/");
            u8g.print(MAX_BANKCARD_NUM);

            u8g.setDefaultForegroundColor();

            break;
          case 0:
            u8g.drawXBMP( 32, 0, 64, 64, bmp_b);
            //            setFont_M;
            //            u8g.setFontRefHeightText();
            //            u8g.setPrintPos(4, 16);
            //            u8g.print("Please login");
            break;
          case 2:
            u8g.drawXBMP( 32, 0, 64, 64, bmp_d);
            //            setFont_M;
            //            u8g.setFontRefHeightText();
            //            u8g.setPrintPos(4, 16);
            //            u8g.print("ALL Card ID Clear!");
            break;
          case 3:
            u8g.drawXBMP( 32, 0, 64, 64, bmp_c);
            //            setFont_M;
            //            u8g.setFontRefHeightText();
            //            u8g.setPrintPos(4, 16);
            //            u8g.print("Open Door!");
            break;
        }
      }
      while ( u8g.nextPage() );
    }
  }
}