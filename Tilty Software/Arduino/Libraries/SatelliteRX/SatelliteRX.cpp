#include <SatelliteRX.h>
/*
// Initialize SatelliteRX with hardware serial port
SatelliteRX::SatelliteRX(HardwareSerial& _serial) : _serialPort(_serial)
{
	_serialPort = HardwareSerial();
}
*/


// Initialize SatelliteRX with hardware serial port
SatelliteRX::SatelliteRX(HardwareSerial3& _serial) : _serialPort(_serial)
{
	// Do nothing
}

/*
// Initialize SatelliteRX with hardware serial port and RX pin
SatelliteRX::SatelliteRX(HardwareSerial _serial, uint8_t _pin)
{
	_serialPort = _serial;
	rx_pin = _pin;
}
*/

/*
// Initialize SatelliteRX with RX pin, auto-determines serial port based on pin number for defined boards
SatelliteRX::SatelliteRX(uint8_t _pin)
{
	rx_pin = _pin;

#ifdef CORE_TEENSY && __arm__ // Definitions for RX pins for Teensy 3.0
	if (_pin == 0) _serialPort = Serial1;
	if (_pin == 9) _serialPort = Serial2;
	if (_pin == 7) _serialPort = Serial3;
#endif

// ToDo: Add pin definitions for other boards
}
*/

SatelliteRX::~SatelliteRX()
{
	_serialPort.end();
}


bool SatelliteRX::init()
{
	_serialPort.begin(115200);
}


bool SatelliteRX::init(bool _bind)
{	
	bool _bound;
	if (_bind) { _bound = bind();}
	_serialPort.begin(115200);
	return _bound;
}


bool SatelliteRX::readData()
{	
	while (_serialPort.available() && !_synced) // Synchronize with start of data packet
	{
		if (_serialPort.read() == 0x03)
		{
			_synced = true;
			_buffer[_buffer_index] = 0x03;
			_buffer_index++;
		}
	}
	
	while (_synced && _serialPort.available() && _buffer_index < 16) // Fill the buffer with data
	{
		_buffer[_buffer_index] = _serialPort.read();
		_buffer_index++;
	}
	
	if (_buffer_index == 16) // If buffer is full, process the data
	{
		#ifdef DEBUG_RX
			for (int i = 0; i < 15; i += 2)
			{
				Serial.print("0x");
				Serial.print(_buffer[i], HEX);
				Serial.print(", ");
				Serial.println(_buffer[i + 1], HEX);
			}
			Serial.println();
		#endif
		
		for (int i = 2; i < 15; i += 2)
		{
			uint16_t temp = _buffer[i] << 8 | _buffer[i + 1];
			uint8_t _channel = temp >> 10;
			channel_data[_channel] = temp & 0x3FF;
		}
		
		updatePointers();
		
		_buffer_index = 0;
		_synced = false;
		
		return true;
	}
	
	return false;
}


bool SatelliteRX::calibrate() // Should read all channels to determine highs and lows and wait till 
{
	/*
	if (channel_data[_channel] > channel_max[_channel]) channel_max[_channel] = channel_data[_channel];
	if (channel_data[_channel] < channel_min[_channel]) channel_min[_channel] = channel_data[_channel];
	*/
}


void SatelliteRX::updatePointers()
{
	if (_set_aileron) { *_aileron = channel_data[AILERON];}
	if (_set_elevator) { *_elevator = channel_data[ELEVATOR];}
	if (_set_rudder) { *_rudder = channel_data[RUDDER];}
	if (_set_throttle) { *_throttle = channel_data[THROTTLE];}
	if (_set_aux1) { *_aux1 = channel_data[AUX1];}
	if (_set_aux2) { *_aux2 = channel_data[AUX2];}
	if (_set_aux3) { *_aux3 = channel_data[AUX3];}
}


void SatelliteRX::setAileron(int* _data) { _set_aileron = true;	_aileron = _data;}
void SatelliteRX::setElevator(int* _data) { _set_elevator= true;	_elevator = _data;}
void SatelliteRX::setRudder(int* _data) { _set_rudder = true;	_rudder = _data;}
void SatelliteRX::setThrottle(int* _data) { _set_throttle = true;	_throttle = _data;}
void SatelliteRX::setAux1(int* _data) { _set_aux1 = true;	_aux1 = _data;}
void SatelliteRX::setAux2(int* _data) { _set_aux2 = true;	_aux2 = _data;}
void SatelliteRX::setAux3(int* _data) { _set_aux3 = true;	_aux3 = _data;}


bool SatelliteRX::bind()
{	
	if (rx_pin != 255)
	{
		pinMode(rx_pin, OUTPUT);
		
		digitalWrite(rx_pin, HIGH);
		delay(100);
		
		for (int i = 0; i < 4; i++) {
			digitalWrite(rx_pin, !digitalRead(rx_pin));
			delayMicroseconds(120);
			
			digitalWrite(rx_pin, !digitalReadFast(rx_pin));
			delayMicroseconds(120); 
		}
	}
}