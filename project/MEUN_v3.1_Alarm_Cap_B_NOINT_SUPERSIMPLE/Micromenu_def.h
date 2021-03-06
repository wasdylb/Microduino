#include "Arduino.h"

#define null NULL

//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_courB14r)
#define setFont_M u8g.setFont(u8g_font_7x13)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
/*
font:
 u8g_font_7x13
 u8g_font_fixed_v0r
 u8g_font_chikitar
 u8g_font_osb21
 u8g_font_courB14r
 u8g_font_courB24n
 u8g_font_9x18Br
 */

//屏幕类型--------
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

#define init_drawMain 500	//主界面刷新时间

int MENU_FONT = 1;	//初始化字体大小 0：小，1：中，2：大

#define RUN_NONE 0		//配置模式对应量类别
#define RUN_SWITCH 1	//配置模式对应量类别
#define RUN_NUM 2		//配置模式对应量类别

#define MENU_ITEMS1 8	//第1层菜单最大值，可定义
#define MENU_ITEMS2 5	//第2层菜单最大值，可定义
#define MENU_ITEMS3 4	//第3层菜单最大值，可定义

#define TASK_NUM 11		//总任务数，和task_action对应


/*
//---------------------------------------------------------------------------------------------------
 在此添加任务
 添加对应数组即可，类似：
 //////////////////////////////////
 ,
 {
 *num, *num_min, *num_max, *num_type, *lev1_id, *lev2_id, *lev3_id
 }
 //////////////////////////////////
 1.从左至右依次表示：
 	任务变量初始值，任务变量最小值，任务变量最大值，任务变量类型，任务所属一级菜单，任务所属二级菜单，任务所属三级菜单

 2.关于变量类型：
 	设置为"RUN_SWITCH"时，为开关量类型，值范围只会返回"0"或"1"
 	设置为"RUN_NUM"时，为数字量类型，值范围从"num_min"到"num_max"

 3.关于层：
 	"lev1_id"、"lev2_id"、"lev3_id"的值都是从1算起，最大不能超过其所属层的最大值（MENU_ITEMS1、MENU_ITEMS2、MENU_ITEMS3）
 	"lev1_id"不能为0，否则无效
 	"lev2_id"如果设为0，判断为不启用该任务二级菜单，其三级菜单也不会被启用
 	"lev3_id"如果设为0，判断为不启用该任务三级菜单

 4.友情提示：
 	添加新任务时，别忘了增加对应"TASK_NUM"的值
 //---------------------------------------------------------------------------------------------------
 */
int task_action[TASK_NUM][7] =
{
  { //00----------------------
    0, 0, 1, RUN_SWITCH, 1, 1, 0
  }
  ,
  { //01----------------------
    0, 0, 23, RUN_NUM, 1, 2, 1
  }
  ,
  { //02----------------------
    0, 0, 59, RUN_NUM, 1, 2, 2
  }
  ,
  { //03----------------------
    1, 1, 10, RUN_NUM, 2, 0, 0
  }
  ,
  { //04----------------------
    2014, 2014, 2099, RUN_NUM, 3, 1, 1
  }
  ,
  { //05----------------------
    1, 1, 12, RUN_NUM, 3, 1, 2
  }
  ,
  { //06----------------------
    1, 1, 31, RUN_NUM, 3, 1, 3
  }
  ,
  { //07----------------------
    0, 0, 23, RUN_NUM, 3, 2, 1
  }
  ,
  { //08----------------------
    0, 0, 59, RUN_NUM, 3, 2, 2
  }
  ,
  { //09----------------------
    0, 0, 2, RUN_NUM, 4, 1, 0
  }
  ,
  { //10----------------------
    15, 1, 30, RUN_NUM, 4, 2, 0
  }
};


/*
//---------------------------------------------------------------------------------------------------
 在此定义菜单项目
 //////////////////////////////////
 ,
 {
 *num, *num_min, *num_max, *num_type, *lev1_id, *lev2_id, *lev3_id
 }
 //////////////////////////////////
 1.关于菜单名：
 	ID=0的层为指示返回主界面的名称，不包含其他数组
 	第1层菜单名：
 		ID所属第1个子数组的第1项
 	第2层菜单名：
 		ID所属旗下数组的第2项
 	第3层菜单名：
 		第2层菜单名后面的几个项

 2.关于层的有效性：
 	结束菜单的三种方法：
 		1.标注该层为"null"（推荐）
 		2.删除对应层名称即可
 		3.删除对应层及其后面数组即可
 	删除了对应层以后，系统将不会扫描接下来的层
 	比如我只要启用三个一级菜单，只要将ID为4的第1个子数组的第1项标为"null"，第4个及以后的菜单都不会被启用

 3.友情提示：
 	添加更多菜单时，别忘了增加对应"MENU_ITEMS"的值
 //---------------------------------------------------------------------------------------------------
 */
#include  <avr\pgmspace.h>
const char* xjj[MENU_ITEMS1 + 1][MENU_ITEMS2][MENU_ITEMS3 + 2] =
{
  { //ID=0----------------------------------
    {
      "MAIN"
    }
  }
  ,
  { //ID=1----------------------------------
    {
      "Set alarm", "Switch", null,  "b", "c" , "d"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "Time", "hour", "minute", null
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , null,   "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#if (MENU_ITEMS1>=2)
  ,
  { //ID=2----------------------------------
    {
      "Set tone", null, "a", "b", "c" , "d"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "O2", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , "O3",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
#if (MENU_ITEMS1>=3)
  ,  { //ID=3----------------------------------
    {
      "Set clock",  "Set data", "year", "month", "day"
    }
#if (MENU_ITEMS2>=2)
    , {
      null  , "Set time", "hour", "minute"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , null, "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
#if (MENU_ITEMS1>=4)
  ,  { //ID=4----------------------------------
    {
      "System", "Font", null, "b", "c" , "d"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "Sound vol", null,  "b", "c" , "d"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , null,  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
#if (MENU_ITEMS1>=5)
  , { //ID=5----------------------------------
    {
      "About", "Thanks", "tiki", "zcb", "ylb", "xjj"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "Designer", "wasdpkj", null, "d"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , null,  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
#if (MENU_ITEMS1>=6)
  ,  {//ID=6----------------------------------
    {
      null, "01", "a", "b", "c", "d"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "02", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , "03", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
#if (MENU_ITEMS1>=7)
  ,  {//ID=7----------------------------------
    {
      null, "01", "a", "b", "c", "d"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "02", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , "03", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
#if (MENU_ITEMS1>=8)
  ,  { //ID=8----------------------------------
    {
      null, "01", "a", "b", "c", "d"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "02", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , "03", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
#if (MENU_ITEMS1>=9)
  ,  { //ID=9----------------------------------
    {
      null, "01", "a", "b", "c", "d"
    }
#if (MENU_ITEMS2>=2)
    , {
      null   , "02", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=3)
    , {
      null   , "03", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=4)
    , {
      null   , "O4",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=5)
    , {
      null   , "05",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=6)
    , {
      null   , "06",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=7)
    , {
      null   , "07",  "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=8)
    , {
      null   , "08", "a", "b", "c", "d"
    }
#endif
#if (MENU_ITEMS2>=9)
    , {
      null   , "09",  "a", "b", "c", "d"
    }
#endif
  }
#endif
};


