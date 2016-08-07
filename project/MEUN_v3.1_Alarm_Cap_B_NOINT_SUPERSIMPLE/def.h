#include "Arduino.h"

//debug--------------------------
#define interval_debug  2000	//节点查错间隔
unsigned long time_debug=0;		//定时器

boolean node_clock_error[4];	//节点响应状态
unsigned long node_clock[4],node_clock_debug[4],node_clock_cache=0;		//节点运行时间、节点响应检查时间、节点时间缓存

//rtc--------------------------
#define interval_rtc  500	//间隔
unsigned long time_rtc=0;		//定时器

