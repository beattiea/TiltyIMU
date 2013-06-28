#include <SoftPWM.h>

const int ledpin = 13;

void setup()
{
  SoftPWMBegin();
  
  SoftPWMSet(ledpin, 0);

  SoftPWMSetFadeTime(ledpin, 1000, 1000);
}

void loop()
{
  SoftPWMSet(ledpin, 255);
  delay(1000);
  SoftPWMSet(ledpin, 0);
  delay(1000);
}
