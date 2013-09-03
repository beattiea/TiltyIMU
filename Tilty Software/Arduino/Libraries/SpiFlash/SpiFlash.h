/*
FlashMemory.h - A easy to use interface for the Spansion flash memory chips.
Thanks to William Greiman for the Teensy optimized SdFat library, which this is based off of.
Copyright (C) 2013-2014 Alex Beattie <alexbeattie at tiltyimu dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 2 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.	If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include "Arduino.h"
#include <SPI.h>

#if defined(__arm__) && defined(CORE_TEENSY)
	// Nonzero - use native MK20DX128 SPI
	#define USE_NATIVE_MK20DX128_SPI 1
	#else  // USE_NATIVE_MK20DX128_SPI
	// Zero - don't use native Mk20DX128 SPI
	#define USE_NATIVE_MK20DX128_SPI 0
#endif

class SpiFlash {
	public:
	// Initialize the SPI bus
		void begin(uint8_t _SS, uint8_t sckDivisor);
		
	// Standard SPI flash memory write commands
		int write(byte* _buf, long _addr, uint16_t _length);
		int write(int _data, long _addr);
		int write(float _data, long _addr);
		int write(double _data, long _addr);
		
	// Special SPI flash memory write commands
		// Write data into a buffer until it's full, then it will automatically write to the next page
		int bufferData(int _data);
		int bufferData(float _data);
		int bufferData(double _data);
		int writeBuffer(long _addr);
		
		// Get how far buffered data has been written into the device
		int getWrittenPages();
		
	// Standard SPI flash memory read commands
		// Read a single byte
		byte read(long _addr);
		// Read integers (16 or 32 bit)
		int readInt(long _addr);
		int16_t readInt16(long _addr);
		// Read float values
		float readFloat(long _addr);
		// Read bytes into a buffer
		bool read(byte* _buf, long _addr, uint32_t _length);
		// Read the status register
		byte readStatusReg();
		
	// Standard SPI flash memory erase commands
		// Erase a sector (4kB)
		bool eraseSector(long _addr);
		// Erase a block (64kB)
		bool eraseBlock(long _addr);
		// Erase the entire chip
		bool eraseChip();
		
	// Chip information commands
		// Get device manufacturer
		byte getManufacturer();
		// Get device type
		byte getType();
		// Get device capacity
		unsigned long getCapacity();
		
	private:
		uint8_t SS; // Slave Select pin
		int written_pages = 0;
		
		// Chip data
		byte manufacturer; // Manufacturer ID, not currently used
		byte type; // Memory type, not currently used
		unsigned long capacity; // Total available device memory. _address may not exceed this number
		
		// Buffer only works for full page writes
		uint16_t buffer_pos = 0;
		byte buffer[256];
		long buffer_addr = 0;
		
		// Union to save and load float values
		union floatUnion_t
		{
		  	float float_value;
 			byte bytes[sizeof(float_value)];
		} float_buf;
		
		// Get device specs
		void readID();
		// Enable command and data writing
		void writeEnable();
		// Check that the chip is not in a write cycle
		bool checkWriteInProgress();
		// Check that data is within chip memory
		bool check_address(long _addr, uint16_t _length);
		// check that there won't be a page overflow
		bool checkPageOverflow(long _addr, uint16_t _length);
		// Send a byte.
		void send(uint8_t data);
		 // Send multiple bytes.
		void send(const uint8_t* buf, size_t n);
		// Receive a single byte
		uint8_t receive();
		// Receive multiple bytes.
		uint8_t receive(uint8_t* buf, size_t n);
};


#endif