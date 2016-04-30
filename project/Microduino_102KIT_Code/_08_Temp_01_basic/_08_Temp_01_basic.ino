
#include <Wire.h>

#include <lm75.h>

TempI2C_LM75 termo = TempI2C_LM75(0x48,TempI2C_LM75::nine_bits);


void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.print(termo.getTemp());
    Serial.println(" oC");
    delay(1000);
    
}
