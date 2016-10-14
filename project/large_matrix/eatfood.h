int foodX, foodY;
int doudouX, doudouY = 8;
int doudoularge = 9;

int direction;

uint32_t time1, time2;

boolean dou_show;

int score;

void randFood() {//generate random food location
  foodX = random(4, 37); foodY = random(4, 28);
  if ( doudouX <= (foodX + 1) || (foodX - 1) <= (doudouX + doudoularge) || doudouY <= (foodY + 1) ||  (foodY - 1) <= (doudouY + doudoularge)) {
    foodX = random(4, 37); foodY = random(4, 28);
  }
}
void randFoodON() {
  display.setColor(0, 255, 0);
  display.drawFrame(foodX - 1, foodY - 1, 3, 3);
  display.setLedColor(foodX, foodY, 255, 0, 0);
}
void randFoodOFF() {
  display.setColor(0, 0, 0);
  display.drawFrame(foodX - 1, foodY - 1, 3, 3);
  display.setLedColor(foodX, foodY, 0, 0, 0);
}

void doudoudirection(int x, int y, int direc, boolean show)
{
  if (show)
  {
    switch (direc)
    {
      case 0:
        display.drawBMP(x, y, doudouR);
        break;
      case 1:
        display.drawBMP(x, y, doudouL);
        break;
      case 2:
        display.drawBMP(x, y, doudouU);
        break;
      case 3:
        display.drawBMP(x, y, doudouD);
        break;
    }
  }
  else
    display.drawBMP(x, y, doudouB);
}

void read_button()
{
  if (800 < analogRead(A0) && analogRead(A0) < 900 && direction != 2)
  {
    delay(100);
    if (800 < analogRead(A0) && analogRead(A0) < 900 && direction != 2)
      direction = 1;
  }
  else if (600 < analogRead(A0) && analogRead(A0) < 750 && direction != 4 && direction != 0)
  {
    delay(100);
    if (600 < analogRead(A0) && analogRead(A0) < 750 && direction != 4 && direction != 0)
      direction = 3;
  }
  else if (480 < analogRead(A0) && analogRead(A0) < 650 && direction != 1)
  {
    delay(100);
    if (480 < analogRead(A0) && analogRead(A0) < 650 && direction != 1)
      direction = 2;
  }
  else if (250 < analogRead(A0) && analogRead(A0) < 450 && direction != 3)
  {
    delay(100);
    direction = 4;
  }
  else if ( analogRead(A0) < 50)
  {
    delay(100);
    direction = 0;
    dou_show = true;
  }
  // Serial.println(direction);
}

void gameover()
{
  display.clearDisplay();
  randFoodOFF();
  doudouX = 0;
  doudouY = 8;
  direction = 0;

  display.setColor(0, 255, 255);
  display.setCursor(2, 6);
  display.print("SCORE:");

  display.setColor(255, 0, 255);
  display.setCursor(14, 16);
  if (score < 10)
    display.print("0");
  display.print(score);

  delay(4000);
  display.clearDisplay();
  score=0;
  randFood();
  randFoodON();
  doudoudirection(doudouX, doudouY, 0, true);
}

void winfood()
{
  score++;
  randFoodOFF();
  randFood();
  randFoodON();
}

void food_blink(int timeF)
{
  for (int t = 1; t <= timeF; t++)
  {
    randFoodON();
    time2 = millis();
    while (millis() - time2 < 50)
      read_button();
    randFoodOFF();
    time1 = millis();
    while (millis() - time1 < 50)
      read_button();
  }
  dou_show = !dou_show;
}

