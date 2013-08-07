#define _key 15

int _bauds[] = {9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};


void setup() {
  Serial.begin(115200);
  Serial3.begin(9600);
  while (!Serial) {}
  Serial.println("begin...");
  delay(5);
}

void loop() {
 
  
  if (Serial.available()) {
    while (Serial.available())
    {  Serial3.print(char(Serial.read()));}
    Serial3.print("\r\n");
  }
  
  if (Serial3.available()) {
    while (Serial3.available())
    {  Serial.print(char(Serial3.read()));}
  }
}
