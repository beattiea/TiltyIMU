void setup() {
  Serial.begin(115200);
  analogReadRes(10);
}


int r1 = 10000;
int r2 = 680;
float voltage;

void loop() {
  voltage = (analogRead(14) / 1024.0) * 51.8294;
  
  Serial.print("B");
  Serial.println(voltage, 3);
  
  delay(100);
}
