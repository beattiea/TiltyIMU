#include "HC_Bluetooth.h"
#include "inttypes.h"

HC_Bluetooth::HC_Bluetooth()
{
	// Do Nothing
}

HC_Bluetooth::~HC_Bluetooth()
{
	// Do Nothing
}

HC_Bluetooth::HC_Bluetooth(HardwareSerial& serial)
{
	setupSerial1();
}

HC_Bluetooth::HC_Bluetooth(HardwareSerial2& serial)
{
	setupSerial2();
}

HC_Bluetooth::HC_Bluetooth(HardwareSerial3& serial)
{
	setupSerial3();
}



HC_Bluetooth::HC_Bluetooth(HardwareSerial& serial, uint8_t pin)
{
	setupSerial1();
	pinMode(pin, OUTPUT);
	command_pin = pin;
}

HC_Bluetooth::HC_Bluetooth(HardwareSerial2& serial, uint8_t pin)
{
	setupSerial2();
	pinMode(pin, OUTPUT);
	command_pin = pin;
}

HC_Bluetooth::HC_Bluetooth(HardwareSerial3& serial, uint8_t pin)
{
	setupSerial3();
	pinMode(pin, OUTPUT);
	command_pin = pin;
}



void HC_Bluetooth::commandMode()
{
	flush();
	clear();
	pinMode(command_pin, OUTPUT);
	digitalWrite(command_pin, HIGH);
	delayMicroseconds(100);
	command_mode = true;
}

int HC_Bluetooth::checkOK()
{
	digitalWrite(command_pin, !digitalRead(command_pin));
	Serial.print("Class read: ");
	Serial.println(digitalRead(command_pin));
	//delayMicroseconds(100000);
	print("AT\r\n");
	digitalWrite(command_pin, LOW);
	long start = millis();
	while (millis() - start < COMMAND_TIMEOUT)
	{
		if (available() == 4)
		{
			for (int i = 0; i < 4; i++)
			{
				char data = read();
				Serial.print(data);
				if (AT_OK[i] != data)
				{
					return false;
				}
			}
			return true;
		}
	}
	return -1;
}

int HC_Bluetooth::getStatus()
{
	if (!command_mode) { commandMode(); }
	// May need a digital write high here anyway
	
	print("AT+STATE?\r\n");
	
	long start = millis();
	char buffer[12];
	
	while (millis() - start < COMMAND_TIMEOUT)
	{
		if (available() == 7)
		{
			char _status_header[7] = {'+', 'S', 'T', 'A', 'T', 'E', ':'};
			// Check that incoming data is actually status data
			for (int i = 0; i < 7; i++)
			{
				if (read() != _status_header[i]) { return 0; }
			}
			
			while (millis() - start < COMMAND_TIMEOUT)
			{
				if (available() >= 5)
				{
					if (read() == 'R')
					{
						char _status[4] = {'E', 'A', 'D', 'Y'};
						char buffer[4];
						readReturn(buffer, 4);
						if (parseQueryReturn(buffer, _status, 4))
						{
							status = BT_READY;
							return BT_READY;
						}
					}
					else if (read() == 'I')
					{
						read();
						if (read() == 'I')
						{
							char _status[8] = {'T', 'I', 'A', 'L', 'I', 'Z', 'E', 'D'};
							while (available() <= 8 && millis() - start < COMMAND_TIMEOUT) { }
							char buffer[8];
							readReturn(buffer, 8);
							if (parseQueryReturn(buffer, _status, 8))
							{
								status = BT_INITIALIZED;
								return BT_INITIALIZED;
							}
						}
						else
						{
							char _status[6] = {'U', 'I', 'R', 'I', 'N', 'G'};
							while (available() <= 6 && millis() - start < COMMAND_TIMEOUT) { }
							char buffer[6];
							readReturn(buffer, 8);
							if (parseQueryReturn(buffer, _status, 8))
							{
								status = BT_INQUIRING;
								return BT_INQUIRING;
							}
						}
					}
				}
			}
		}
	}
}


// Takes a buffer character array and a length and reads length characters into the array
int HC_Bluetooth::readReturn(char *buffer, uint8_t length)
{
	for (int i = 0; i < length; i++)
	{
		buffer[i] = read();
	}
}

// Compares two given arrays and returns if they are equal
int HC_Bluetooth::parseQueryReturn(char *char1, char *char2, uint8_t length)
{
	for (int i = 0; i < length; i++)
	{
		if (char1[i] != char2[i]) { return 0; }
	}
	return true;
}

void HC_Bluetooth::setupSerial1()
{
	start = serial_begin;
	end = serial_end;
	available = serial_available;
	peek = serial_peek;
	read = serial_getchar;
	flush = serial_flush;
	clear = serial_clear;
	put_char = serial_putchar;
	
	serial_number = 1;
}

void HC_Bluetooth::setupSerial2()
{
	start = serial2_begin;
	end = serial2_end;
	available = serial2_available;
	peek = serial2_peek;
	read = serial2_getchar;
	flush = serial2_flush;
	clear = serial2_clear;
	put_char = serial2_putchar;
	
	serial_number = 1;
}

void HC_Bluetooth::setupSerial3()
{
	start = serial3_begin;
	end = serial3_end;
	available = serial3_available;
	peek = serial3_peek;
	read = serial3_getchar;
	flush = serial3_flush;
	clear = serial3_clear;
	put_char = serial3_putchar;
	
	serial_number = 3;
}