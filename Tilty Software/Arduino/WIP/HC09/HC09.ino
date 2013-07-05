#define _key 15

int _bauds[] = {9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  //int baud = findBaud();
  //Serial.println(baud);
  init(findBaud());
  setBaud(460800);
}

void loop() {
  
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+UART?\r\n");
  delay(20);
  digitalWrite(_key, LOW);
  
  if (Serial1.available()) {
    while (Serial1.available())
    {  Serial.print(char(Serial1.read()));}
    Serial.println();
  }
  delay(500);
}


void init() {
  Serial1.begin(findBaud());
}

void init(int _baud) {
  Serial1.begin(_baud);
}



//  Sets the baud rate of the bluetooth module
boolean setBaud(int _baud) {
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+UART=");
  Serial1.print(_baud);
  Serial1.write(",0,0\r\n");
  delay(20);
  digitalWrite(_key, LOW);
  
  if (Serial1.available()) {
    while (Serial1.available())//  Empty the serial buffer. It's enough to know we received data, it doesn't need to be read.
    {  Serial1.read();}
  }
  
  reset();//  Reset the bluetooth module
  delay(250);//  Wait for the bluetooth module to reboot
  Serial1.end();
  Serial1.begin(_baud);
}



//  Finds and returns the set baud rate of the bluetooth module since it will only communicate at that rate
int findBaud() {
  pinMode(_key, OUTPUT);
  
  for (int i = 0; i < sizeof(_bauds) / 4; i++)
  {
    digitalWrite(_key, HIGH);
    delay(50);
    Serial1.begin(_bauds[i]);
    Serial1.write("AT\r\n");
    delay(50);
    digitalWrite(_key, LOW);
    
    if (Serial1.available()) 
    {
      while (Serial1.available())//  Empty the serial buffer. It's enough to know we received data, it doesn't need to be read.
      {  Serial1.read();}
      return _bauds[i];//  return the correct baud rate
    }
    
    Serial1.end();
  }
  return 0;
}




//  Resets the bluetooth module and waits for it to reconnect
void reset() {
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+RESET\r\n");
  delay(50);
  digitalWrite(_key, LOW);
  Serial1.end();
}

//  Resets the bluetooth module and waits for it to reconnect, DOESN'T WORK
void reset(boolean _wait) {
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+RESET\r\n");
  delay(50);
  digitalWrite(_key, LOW);
  
  if (Serial1.available()) {
    while (Serial1.available())
    {  Serial.print(char(Serial1.read()));}
    Serial.println();
  }
  
  if (_wait)
  {
    Serial.println("Waiting...");
    while (!Serial1.available()) {}
    Serial.println("Reset");
    Serial1.end();
    Serial1.begin(findBaud());
    Serial.println("hello!");
  }
}
