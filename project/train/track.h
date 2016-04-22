//控制1A的电机
#define OUT1A 13 //12
#define PWM1A 11  //3

void car_run(int num,  int i)
{
  if (num == 1)
  {
    digitalWrite(OUT1A, HIGH);
    analogWrite(PWM1A, i);
  }
  else if (num == 2)
  {
    digitalWrite(OUT1A, LOW);
    analogWrite(PWM1A, i);
  }
}

void stop()
{
  digitalWrite(OUT1A, LOW);
  analogWrite(PWM1A, LOW);
}
