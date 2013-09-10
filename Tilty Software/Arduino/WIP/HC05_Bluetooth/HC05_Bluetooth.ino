#include <HC_Bluetooth.h>

#define _key 15

int _bauds[] = {9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  //int baud = findBaud();
  //Serial.println(baud);
  Serial.println(init());
  Serial.println("begin...");
  delay(5);
  //setBaud(115200);
  pinMode(_key, OUTPUT);
}

void loop() {
  if (Serial.available()) {
	digitalWrite(_key, HIGH);
	delay(50);
	while (Serial.available())
	{  Serial1.print(char(Serial.read()));}
	Serial1.print("\r\n");
	delay(50);
	digitalWrite(_key, LOW);
  }
 
  if (Serial1.available()) {
	while (Serial1.available())
	{  Serial.print(char(Serial1.read()));
	   delay(1);}
	Serial.println();
  }
}



//	Starts the bluetooth module at the buad rate it is recognized as using, this is useful if the setting isn't known
//	Returns true if the bluetooth module is connected and false if no connection was made
//	The bluetooth module must be in command mode for this to work!
boolean init() 
{
  return init(findBaud());
}

//	Starts the bluetooth module at a set baud rate, this will only work if the set rate and the bluetooth module's rate match
//	Returns true if a valid rate is used (either 1-8 or a valid baud rate) and false if the baud rate is invalid
boolean init(int _baud) 
{
  if (_baud < 8 && _baud > 0)
  {
	Serial1.begin(_bauds[_baud - 1]);
	return true;
  }
 
  else if (_baud != -1)
  {
	for (int i = 0; i < sizeof(_bauds) / 4; i++)
	{
	  if (_baud == _bauds[i])
	  {
		Serial1.begin(_bauds[i]);
		return true;
	  }
	}
  }
  return false;
}



//	Sets the baud rate of the bluetooth module
//	The bluetooth module must be in command mode for this to work!
boolean setBaud(int _baud) 
{
  pinMode (_key, OUTPUT);
 
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+UART=");
  Serial1.print(_baud);
  Serial1.write(",0,0\r\n");
  delay(50);
  digitalWrite(_key, LOW);
 
  if (Serial1.available())
  {
	while (Serial1.available())//  Empty the serial buffer. It's enough to know we received data, it doesn't need to be read.
	{  Serial1.read();}
  }
 
  reset();//  Reset the bluetooth module
  delay(250);//	 Wait for the bluetooth module to reboot
  Serial1.end();
  Serial1.begin(_baud);
}



//	Finds and returns the set baud rate of the bluetooth module since it will only communicate at that rate
//	The bluetooth module must be in command mode for this to work!
int findBaud()
{
  pinMode(_key, OUTPUT);
 
  for (int i = 0; i < sizeof(_bauds) / 4; i++)
  {
	digitalWrite(_key, HIGH);
	Serial1.begin(_bauds[i]);
	delay(100);
	Serial1.write("AT\r\n");
	delay(100);
	digitalWrite(_key, LOW);

	if (Serial1.available()) 
	{
	  while (Serial1.available())//	 Empty the serial buffer. It's enough to know we received data, it doesn't need to be read.
	  {	 Serial.print(char(Serial1.read()));}
	  return _bauds[i];//  return the correct baud rate
	}

	Serial1.end();
  }
  return -1;
}



//	Sets the name that the bluetooth module broadcasts
//	The bluetooth module must be in command mode for this to work!
boolean setName(char _name[])
{
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+NAME=");
  Serial1.print(_name);
  Serial1.write("\r\n");
  delay(50);
  digitalWrite(_key, LOW);
 
  if (Serial1.available())
  {
	while (Serial1.available())//  Empty the serial buffer. It's enough to know we received data, it doesn't need to be read.
	{  Serial1.read();}

	return true;
  }
}



//	Resets the bluetooth module and waits for it to reconnect
//	The bluetooth module must be in command mode for this to work!
void reset()
{
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+RESET\r\n");
  delay(50);
  digitalWrite(_key, LOW);
  Serial1.end();
}

//	Resets the bluetooth module and waits for it to reconnect, DOESN'T WORK
//	The bluetooth module must be in command mode for this to work!
void reset(boolean _wait)
{
  digitalWrite(_key, HIGH);
  delay(50);
  Serial1.write("AT+RESET\r\n");
  delay(50);
  digitalWrite(_key, LOW);
 
  if (Serial1.available())
  {
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
