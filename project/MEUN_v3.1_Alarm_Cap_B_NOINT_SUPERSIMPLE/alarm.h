volatile int alarm_flag=0;
boolean alarm_sta=false;
boolean alarm_switch;
int alarm_hour,alarm_minute;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          

int alarm_tone;
int alarm_vol;

boolean test_audio=false;
boolean test_audio_vol=false;

void do_alarm(int _do_alarm)
{
  audio_choose(_do_alarm);
  audio_play();
}

void end_alarm(int _end_alarm)
{
  audio_pause();
}

void test_alarm(int _test_alarm)
{
  do_alarm(_test_alarm);
}

void test_alarm_vol(int _test_alarm_vol)
{
  audio_vol(_test_alarm_vol);
}
