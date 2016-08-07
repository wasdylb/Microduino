//用户自定义部分------------------------
//RTC------------------------
#include <Rtc_Pcf8563.h>
#include <Wire.h>

#include <SoftwareSerial.h>

//EEPROM---------------------
#include <EEPROM.h>

//用户自定义部分------------------------

#include "Micromenu.h"
#include "U8glib.h"

void setup() 
{
  //用户自定义部分========================
  SETUP_begin();
  //用户自定义部分========================

  // u8g.setRot180();  // rotate screen, if required
  osd_smart_init();    //界面条件初始化
}

void loop() 
{  
  uiStep();	//检测输入动作

  updateMenu(type);	//根据输入动作更新菜单项

  if(!menu_level)	//运行主界面
  {
    if(millis() < time_drawMain) time_drawMain=millis();
    if(millis() - time_drawMain > init_drawMain)
    {
      osd_smart_run(false); 

      time_drawMain=millis();
    }
  }
  else if(menu_redraw_required)		//根据输入动作运行菜单
  {
    osd_smart_begin();
    osd_smart_run(true);
    menu_redraw_required = false;
  }


  //用户自定义部分========================

  //任何时候都运行===
  {
    LOOP_priority_1ST();
  }

  //除配置模式，任何时候都运行===
  if(!sta)
  {
    LOOP_priority_2ND();  
  }
  //配置模式运行===
  else
  {
    LOOP_priority_3RD();  
  }

  //仅在主界时运行===
  if(!menu_level)
  {
    LOOP_priority_4TH();  
  }

  //用户自定义部分========================
}
