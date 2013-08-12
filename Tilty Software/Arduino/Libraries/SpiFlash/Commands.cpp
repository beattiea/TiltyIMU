#include "Arduino.h"
#include "SpiFlash.h"

//#define DEBUG

// Error code defines
#define PAGE_OVERFLOW 2
#define WRITE_IN_PROGRESS 3
#define BUFFER_OVERFLOW 4
#define MEMORY_OVERFLOW 5

//=======================          Defines for Spansion flash chips          =======================//
// Command defines
#define WRITE_STATUS_REG 0x01
#define PAGE_PROGRAM 0x02
#define READ_DATA 0x03
#define WRITE_DISABLE 0x04
#define READ_STATUS_REG 0x05
#define WRITE_ENABLE 0x06
#define FAST_READ 0x0B // Not actually used as the Teensy can't operate SPI at frequencies beyond the normal read command
#define SECTOR_ERASE 0x20 // Erases a 4kB sector of data (16 pages)
#define FAST_READ_DO 0x3B // Also not necessary as the Teensy isn't set up for dual output fast reading anyways
#define READ_IDENTIFICATION 0x9F // Not necessary as it's mainly for backwards compatibility
#define READ_DEVICE_ID 0xAB // Also used to wake device from deep power down
#define DEEP_POWER_DOWN 0xB9 // Almost useless as it makes a difference of ~3uA in power consumption
#define BLOCK_ERASE 0xBE // Erases a 64kB block of data
#define CHIP_ERASE 0xC7 // Erases the entire chip

// Status Register defines
#define WIP 0x01 // Write In Progress bit
#define WEL 0x02 // Write Enabled Latch bit
#define BP0 0x04 // Block Protect bit 1
#define BP0 0x08 // Block Protect bit 2
#define BP0 0x10 // Block Protect bit 3
#define BP0 0x20 // Block Protect bit 4
#define SRP 0x80 // Status Register Protect bit

// Size value defines for Spansion S25FL204K
#define PAGE_SIZE 256
#define SECTOR_SIZE 4096
#define BLOCK_SIZE 65536
#define CHIP_SIZE 524288


int SpiFlash::write(byte* _buf, long addr, uint16_t _length)
{
	// Below if statement checks that device is ready, address is within device memory, and there won't be a page overflow writing data
	if (!checkWriteInProgress() && _length <= PAGE_SIZE && checkAddress(addr, _length) && checkPageOverflow(addr, _length))
	{
		digitalWriteFast(SS, LOW);
		send(PAGE_PROGRAM);
		send(addr >> 16);
		send(addr >> 8);
		send(addr);
		#ifdef DEBUG
			Serial.println("Writing Data. . .");
		#endif
		for (int i = 0; i < _length; i++)
		{
			send(*_buf);
			#ifdef DEBUG
				//Serial.println(*_buf, BIN);
			#endif
			_buf++;
		}
		digitalWriteFast(SS, HIGH);
		
		writeEnable();
		
		return 1; // returns 1 if ok
	}
	else
	{ // Returns other error codes if something goes wrong
		if (((addr + _length) % PAGE_SIZE) < _length - 1) { return PAGE_OVERFLOW;}
		else if (_length >= PAGE_SIZE) { return BUFFER_OVERFLOW;}
		else if (addr >= capacity) { return MEMORY_OVERFLOW;}
		else if (checkWriteInProgress()) { return WRITE_IN_PROGRESS;}
	}
	
	return -1; // Unknown error
}

int SpiFlash::write(int _data, long addr)
{
	byte _buf[4];
	uint8_t _size = sizeof(int);
	_buf[0] = _data >> 24;
	_buf[1] = _data >> 16;
	_buf[2] = _data >> 8;
	_buf[3] = _data;

	return write(&_buf[0], addr, _size);
}


int SpiFlash::write(float _data, long addr)
{
	uint8_t _size = sizeof(float);
	float_buf.float_value = _data;
	
	#ifdef DEBUG
		for (int i = 0; i < 4; i++){	Serial.println(float_buf.bytes[i], BIN);}
	#endif

	return write(&float_buf.bytes[0], addr, _size);
}


int SpiFlash::write(double _data, long addr)
{
	return write(float(_data), addr);
}


int SpiFlash::bufferData(int _data)
{
	return bufferData((float)_data);
}


int SpiFlash::bufferData(float _data)
{
	uint8_t _size = sizeof(float);
	if (buffer_pos + _size - 1 < sizeof(buffer))
	{
		float_buf.float_value = _data;
		for (int i = 0; i < 4; i++)
		{
			buffer[buffer_pos + i] = float_buf.bytes[i];
		}
		buffer_pos += _size;
	}
	
	if (buffer_pos > PAGE_SIZE - _size)
	{
		#ifdef DEBUG
			Serial.println("Buffer full. Writing data. . .");
		#endif
		int _result = writeBuffer(bufferaddr);
		bufferaddr += PAGE_SIZE;
		buffer_pos = 0;
		return _result;
	}
}


int SpiFlash::bufferData(double _data)
{
	return bufferData((float)_data);
}


int SpiFlash::writeBuffer(long addr)
{
	buffer_pos = 0;
	return write(&buffer[0], addr, sizeof(buffer));
}


byte SpiFlash::read(long addr)
{
	if(!checkWriteInProgress())
	{
		digitalWriteFast(SS, LOW);
		send(READ_DATA);
		send(addr >> 16);
		send(addr >> 8);
		send(addr);
		return receive();
	}
	else
	{
		return 0;
	}
}

int SpiFlash::readInt(long addr)
{
	if(!checkWriteInProgress())
	{
		return readFloat(addr);
	}
	else
	{
		return 0;
	}
}


int16_t SpiFlash::readInt16(long addr)
{
	if(!checkWriteInProgress())
	{
		digitalWriteFast(SS, LOW);
		send(READ_DATA);
		send(addr >> 16);
		send(addr >> 8);
		send(addr);
		int16_t _buf = receive() << 8;
		_buf |= receive();
		digitalWriteFast(SS, HIGH);
		
		return _buf;
	}
	else
	{
		return 0;
	}
}


float SpiFlash::readFloat(long addr)
{	
	if(!checkWriteInProgress())
	{
		digitalWriteFast(SS, LOW);
		send(READ_DATA);
		send(addr >> 16);
		send(addr >> 8);
		send(addr);
		for (int i = 0; i < sizeof(float); i++)
		{
			float_buf.bytes[i] = receive();
		}
		digitalWriteFast(SS, HIGH);
		
		return float_buf.float_value;
	}
	else
	{
		return 0;
	}
}


bool SpiFlash::read(byte* _buf, long addr, uint32_t _length)
{
	if (!checkWriteInProgress() && addr < capacity)
	{
		digitalWriteFast(SS, LOW);
		send(READ_DATA);
		send(addr >> 16);
		send(addr >> 8);
		send(addr);
		for (int i = 0; i < _length; i++)
		{
			*_buf = receive();
			#ifdef DEBUG
				Serial.println(*_buf, BIN);
			#endif
			_buf++;
		}
		digitalWriteFast(SS, HIGH);
		
		return true;
	}
	else
	{
		return false;
	}
}


// Takes an address of 0 to (chip size in bytes / sector size in bytes)
bool SpiFlash::eraseSector(long addr)
{
	if (!checkWriteInProgress())
	{
		digitalWriteFast(SS, LOW);
		send(SECTOR_ERASE);
		addr *= SECTOR_SIZE;
		if (addr >= CHIP_SIZE - SECTOR_SIZE)
		{
			return false;
		}
		send(addr >> 16);
		send(addr >> 8);
		send(addr);
		digitalWriteFast(SS, HIGH);
		
		writeEnable();
		
		return true;
	}
	else
	{
		return false;
	}
}


bool SpiFlash::eraseChip()
{
	if (!checkWriteInProgress())
	{
		digitalWriteFast(SS, LOW);
		send(CHIP_ERASE);
		digitalWriteFast(SS, HIGH);
		
		writeEnable();
		
		return true;
	}
	else
	{
		return false;
	}
}


void SpiFlash::readID()
{
	if (!checkWriteInProgress())
	{
		digitalWriteFast(SS, LOW);
		send(READ_IDENTIFICATION);
		manufacturer = receive();
		type = receive();
		capacity = pow(2, receive());
		digitalWriteFast(SS, HIGH);
	}
}


void SpiFlash::writeEnable()
{
	while (checkWriteInProgress()) {}
	if (!(readStatusReg() & WEL))
	{
		digitalWriteFast(SS, LOW);
		send(WRITE_ENABLE);
		digitalWriteFast(SS, HIGH);
		#ifdef DEBUG
			Serial.println("Enabled write!");
		#endif
	}
	else
	{
		#ifdef DEBUG
			Serial.print("Write already enabled! Status Register: ");
			Serial.println(readStatusReg(), BIN);
		#endif
	}
}


byte SpiFlash::readStatusReg()
{
	digitalWriteFast(SS, LOW);
	send(READ_STATUS_REG);
	byte _status = receive();
	digitalWriteFast(SS, HIGH);
	
	return _status;
}


bool SpiFlash::checkWriteInProgress() 
{
	if (readStatusReg() & WIP) {	return true;}
	else {	return false;}
}


bool SpiFlash::checkAddress(long addr, uint16_t _length) // returns true if address is in acceptable range
{
	if (addr + _length < capacity)
	{
		return true;
	}
	return false;
}

bool SpiFlash::checkPageOverflow(long addr, uint16_t _length)// Returns true if page will not overflow
{
	uint8_t _temp = (addr + _length) % PAGE_SIZE;
	if (_temp >= _length || _temp == 0)
	{
		return true;
	}
	return false;
}