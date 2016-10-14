void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  relay_ON(8);
  delay(1000);
  relay_OFF(8);
  delay(1000);
}

void relay_ON(int pin)
{
  digitalWrite(pin, LOW);
  delay(10);
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}

void relay_OFF(int pin)
{
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
  delay(10);
  digitalWrite(pin, HIGH);
}

