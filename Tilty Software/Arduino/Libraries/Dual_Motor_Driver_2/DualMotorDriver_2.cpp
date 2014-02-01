/*
DualMotorDriver.cpp - Software library to program and control the TiltyIMU Dual Motor Driver Shield
Copyright (C) 2013-2014 Alex Beattie <alexbeattie at tiltyimu dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 2 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"
#include "DualMotorDriver_2.h"


// Add-on/shield code

MotorDriver::MotorDriver() : m1Encoder(ENC1A, ENC1B), m2Encoder(ENC2B, ENC2A)
{	
	// Do nothing
}

MotorDriver::~MotorDriver() 
{
	// Do nothing
}



/** \brief Initializes the add-on board (starts Wire, sets up fast PWM, etc...)
**/
void MotorDriver::init()
{
	pinMode(M1, OUTPUT);	digitalWrite(M1, LOW);
	pinMode(M2, OUTPUT);	digitalWrite(M2, LOW);
	
	pinMode(M1A, OUTPUT);	digitalWrite(M1A, DEFAULT_M1_CONTROL & DIRECTION);
	pinMode(M1B, OUTPUT);	digitalWrite(M1B, !DEFAULT_M1_CONTROL & DIRECTION);
	pinMode(M2A, OUTPUT);	digitalWrite(M2A, DEFAULT_M2_CONTROL & DIRECTION);
	pinMode(M2B, OUTPUT);	digitalWrite(M2B, !DEFAULT_M2_CONTROL & DIRECTION);
	
	pinMode(LED, OUTPUT);	digitalWrite(LED, LOW);
	
	pinMode(ENC1A, INPUT);
	pinMode(ENC1B, INPUT);
	pinMode(ENC2A, INPUT);
	pinMode(ENC2B, INPUT);
	
	// Set up Timer2 to automatically update currents and encoders
	// Timer is set up to interrupt every millisecond (1kHz)
    TCCR2B = 0x00;        //Disbale Timer2 while we set it up
    TCNT2  = 130;         //Reset Timer Count to 130 out of 255
    TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
    TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
    TCCR2A = 0x00;        //Timer2 Control Reg A: Normal port operation, Wave Gen Mode normal
    TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128
	
	// Set all data register values to their defaults except device ID
	// which we'll try to load to be sure we start on the right I2C address
	/*
	if (EEPROM.read(EEPROM_LOAD) != 255 || EEPROM.read(EEPROM_LOAD + 1) != 255 || EEPROM.read(EEPROM_LOAD + 2) != 255)
	{
		data_reg[EEPROM_LOAD] = EEPROM.load(EEPROM_LOAD) << 16;
		data_reg[EEPROM_LOAD + 1] = EEPROM.load(EEPROM_LOAD) << 8;
		data_reg[EEPROM_LOAD + 2] = EEPROM.load(EEPROM_LOAD);
		loadToDataReg();
	}
	*/
	//else {
	data_reg[M1_CONTROL] = DEFAULT_M1_CONTROL;
	data_reg[M2_CONTROL] = DEFAULT_M2_CONTROL;
	data_reg[M1_POWER] = DEFAULT_M1_POWER;
	data_reg[M2_POWER] = DEFAULT_M2_POWER;
	longToDataReg(M1_ENCODER, DEFAULT_M1_ENCODER);
	longToDataReg(M2_ENCODER, DEFAULT_M2_ENCODER);
	data_reg[M1_CURRENT] = DEFAULT_M1_CURRENT;
	data_reg[M2_CURRENT] = DEFAULT_M2_CURRENT;
	longToDataReg(M1_RATE, DEFAULT_M1_RATE);
	longToDataReg(M1_RATE, DEFAULT_M1_RATE);
	floatToDataReg(PID_KP, DEFAULT_PID_KP);
	longToDataReg(M1_RATE, DEFAULT_M1_RATE);
	floatToDataReg(PID_KP, DEFAULT_PID_KP);
	floatToDataReg(PID_KI, DEFAULT_PID_KI);
	floatToDataReg(PID_KD, DEFAULT_PID_KD);
	longToDataReg(TICKS_REV, DEFAULT_TICKS_REV);
	data_reg[LOOP_TIME] = DEFAULT_LOOP_TIME;	loop_frequency = 1000 / data_reg[LOOP_TIME];
	intToDataReg(EEPROM_SAVE, DEFAULT_EEPROM_SAVE);
	intToDataReg(EEPROM_LOAD, DEFAULT_EEPROM_LOAD);
	//}
	
	// Set up the actual PID scalars so we don't need to load them from the data register every time we use them
	PID_kP = DEFAULT_PID_KP;
	PID_kI = DEFAULT_PID_KI;
	PID_kD = DEFAULT_PID_KD;
	
	// Check to see if encoders can be detected, enable them if so, disable them otherwise
	if (digitalRead(ENC1A) || digitalRead(ENC1B)) {	data_reg[M1_CONTROL] |= ENCODER;}
	else {	data_reg[M1_CONTROL] &= !ENCODER;}
	if (digitalRead(ENC2A) || digitalRead(ENC2B)) {	data_reg[M2_CONTROL] |= ENCODER;}
	else {	data_reg[M2_CONTROL] &= !ENCODER;}
	
	// Attempt to load device ID from EEPROM. If loaded value > 127 the default value is used
	uint8_t device_id = EEPROM.read(DEVICE_ID);
	if (device_id & 0x80) {	data_reg[DEVICE_ID] = DEFAULT_DEVICE_ID;}
	else {	data_reg[DEVICE_ID] = device_id;}
	
	// Setup the pwm pins
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);	// Setup pins 5 and 6 for fast PWM
	TCCR0B = _BV(CS00);												// Set PWM frequency to 62.5kHz (fastest possible)
	
	//Setup the I2C bus
	TWBR = 400000L;		// Set up I2C for 400kHz
	Wire.begin(data_reg[DEVICE_ID]);	// Begin I2C at slave address I2C_ADDRESS (defaults to 0x03)
}


/** \brief Takes incoming I2C data into the rxBuffer
	\param[in] bytes The number of incoming bytes
	\param[out] error Returns 0 if register overflows, 1 if data is successfully transferred
**/
uint8_t MotorDriver::getData(int bytes)
{
	active_reg = Wire.read();
	
	if (!Wire.available())// If received byte is just to set active register, run appropriate code for that register
	{
		switch (active_reg)
		{
			case M1_ENCODER: updateM1Encoder(); data_reg[M1_CONTROL] &= !ENCD; break;
			case M2_ENCODER: updateM2Encoder(); data_reg[M2_CONTROL] &= !ENCD; break;
			case M1_CURRENT: updateM1Current(); data_reg[M1_CONTROL] &= !CURD; break;
			case M2_CURRENT: updateM2Current(); data_reg[M2_CONTROL] &= !CURD; break;
			case EEPROM_SAVE: saveDataRegister();
			case EEPROM_LOAD: loadDataRegister();
		}
	}
	
	while (Wire.available())// If more data is available, populate the data register with that data
	{
		switch (active_reg)
		{
			case M1_CONTROL: data_reg[M1_CONTROL] = Wire.read(); active_reg++; break;
			case M2_CONTROL: data_reg[M2_CONTROL] = Wire.read(); active_reg++; break;
			case M1_POWER: data_reg[M1_POWER] = Wire.read(); active_reg++; break;
			case M2_POWER: data_reg[M2_POWER] = Wire.read(); active_reg++; break;
			case M1_ENCODER: wireLongToDataReg(M1_ENCODER); active_reg += 4; break;// CAHNGE ENCODERS TO WRITE TO THE ENCODER ITSELF INSTEAD OF DATA REGISTER
			case M2_ENCODER: wireLongToDataReg(M2_ENCODER); active_reg += 4; break;
			case M1_CURRENT: updateM1Current(); Wire.read(); active_reg++; break;
			case M2_CURRENT: updateM2Current(); Wire.read(); active_reg++; break;
			case M1_RATE: wireLongToDataReg(M1_RATE); active_reg += 4; break;
			case M2_RATE: wireLongToDataReg(M2_RATE); active_reg += 4; break;
			case PID_KP: wireLongToDataReg(PID_KP); active_reg += 4; PID_kP = floatFromDataReg(PID_KP); break;
			case PID_KI: wireLongToDataReg(PID_KI); active_reg += 4; PID_kI = floatFromDataReg(PID_KI); break;
			case PID_KD: wireLongToDataReg(PID_KD); active_reg += 4; PID_kD = floatFromDataReg(PID_KD); break;
			case TICKS_REV: wireLongToDataReg(TICKS_REV); active_reg += 4; break;
			case LOOP_TIME: data_reg[LOOP_TIME] = Wire.read(); active_reg++; loop_frequency = 1000 / data_reg[LOOP_TIME]; break;
			case DEVICE_ID: data_reg[DEVICE_ID] = Wire.read() & 0x7F; active_reg++; break;
			case EEPROM_SAVE: wire3BytesToDataReg(EEPROM_SAVE); break;
			//saveDataRegister((Wire.read() << 16) | (Wire.read() << 8) | Wire.read()); active_reg += 3; break;// Always reads as 0
			case EEPROM_LOAD: wire3BytesToDataReg(EEPROM_LOAD); break;
			//loadDataRegister((Wire.read() << 16) | (Wire.read() << 8) | Wire.read()); active_reg += 3; break;// Always reads as 0
			default: if (active_reg < REGISTER_SIZE) {	data_reg[active_reg] = Wire.read();}; break;// Fills data_reg with received value if it can
		}
	}
}



/** \brief Sends requested I2C data
**/
void MotorDriver::sendData()
{	
	#ifdef DEBUG_MOTOR_DRIVER
	switch (active_reg)
	{
		// Debug code for reading values not in the data register array
		case m1_power: Wire.write(M1_power); break;
		case m1_p: write32(PID_P1); break;
		case m1_i: write32(PID_I1); break;
		//case m1_d: write32(PID_D1); break;
		case m2_power: Wire.write(M2_power); break;
		case m2_p: write32(PID_P2); break;
		case m2_i: write32(PID_I2); break;
		//case m2_d: write32(PID_D2); break;
		case pid_kp: write32(PID_kP); break;
		case pid_ki: write32(PID_kI); break;
		case pid_kd: write32(PID_kD); break;
	}
	
	if (active_reg >= 200) {	Wire.write(EEPROM.read(active_reg - 200));}
	
	return;
	#endif
	
	int temp_size = REGISTER_SIZE - active_reg;
	if (temp_size > BUFFER_SIZE) {	temp_size = 32;}
	Wire.write(&data_reg[active_reg], temp_size);
}



/** \brief Parses data in rxBuffer and updates encoder values
**/
int MotorDriver::update()
{
	count++;
	if (count >= data_reg[LOOP_TIME])
	{
		updateMotor1();
		updateMotor2();
		count = 0;
	}
}



/** \brief Updates Motor 1 based on control register bit settings
**/
void MotorDriver::updateMotor1()
{
	if (data_reg[M1_CONTROL] & SPEED)
	{
		// Speed control code goes here
		/*
		if (data_reg[M1_CONTROL] && ENCODER) {
			updateM1Encoder();
			PID_P1 = (M1_speed - M1_speed_actual) * PID_kP;
			PID_I1 += (M1_speed - M1_speed_actual) * PID_kI;
			//PID_D1 = DERIVATIVE NOT YET IMPLEMENTED
			M1_power += PID_P1 + PID_I1 + PID_D1;
			data_reg[M1_POWER] = M1_power;
			analogWrite(M1, M1_power);
		}
		*/
		
		// (Possibly) Temporary ramping control code instead of actual encoder based version
		if (data_reg[M1_CONTROL] && ENCODER)// Update the encoder if it's enabled
		{
			updateM1Encoder();
		}
		if (M1_power != data_reg[M1_POWER])
		{
			PID_P1 = (data_reg[M1_POWER] - M1_power) * PID_kP;
			PID_I1 += (data_reg[M1_POWER] - M1_power) * PID_kI;
			if (M1_power + PID_P1 + PID_I1 > 256) {	M1_power = 255;}
			else if (M1_power + PID_P1 + PID_I1 < 0) {	M1_power = 0;}
			else {	M1_power += PID_P1 + PID_I1;}
			analogWrite(M1, M1_power);
		}
		if ((data_reg[M1_CONTROL] & DIRECTION) != (M1_control & DIRECTION))// Check for a change of direction
		{
			M1_control = data_reg[M1_CONTROL];
			uint8_t dir = M1_control & DIRECTION;
			digitalWrite(M1A, dir);
			digitalWrite(M1B, !dir);
		}
	}
	else
	{
		if (data_reg[M1_POWER])// Check if motor is running
		{
			if ((data_reg[M1_CONTROL] & DIRECTION) != (M1_control & DIRECTION))// Check for a change of direction
			{
				M1_control = data_reg[M1_CONTROL];
				uint8_t dir = M1_control & DIRECTION;
				digitalWrite(M1A, dir);
				digitalWrite(M1B, !dir);
			}
			if (M1_power != data_reg[M1_POWER])// Check for a new speed
			{
				if (M1_power == 0) {
					uint8_t dir = M1_control & DIRECTION;
					digitalWrite(M1A, dir);
					digitalWrite(M1B, !dir);
				}
				else {
					M1_power = data_reg[M1_POWER];
					analogWrite(M1, data_reg[M1_POWER]);
				}
			}
		}
		else// Check for braking
		{
			uint8_t pin = data_reg[M1_CONTROL] & BRAKE;
			digitalWrite(M1A, pin);
			digitalWrite(M1B, pin);
			digitalWrite(M1, pin);
		}
	}
	if ((data_reg[M1_CONTROL] & ENCODER) && (!data_reg[M1_CONTROL] & SPEED))
	{
		updateM1Encoder();
	}
}



/** \brief Updates Motor 2 based on control register bit settings
**/
void MotorDriver::updateMotor2()
{
	
}



/** \brief Updates the encoder 1 data registers with the encoder 1 value as a 4 byte array.
	Also updates rate registers
**/
void MotorDriver::updateM1Encoder()
{
	if (data_reg[M1_CONTROL] & ENCODER)
	{
		long old_enc = M1_encoder;
		
		M1_encoder = m1Encoder.read();
		data_union.int32 = M1_encoder;
		
		for (int i = 0; i < 4; i++)
		{
			data_reg[M1_ENCODER + i] = data_union.bytes[i];
		}
		
		M1_speed_actual = (data_union.int32 - old_enc) * loop_frequency;
		data_union.float32 = M1_speed_actual;// Gets speed in encoder ticks per second
		/*
		if (!(data_reg[M1_CONTROL] & SPEED))// Only puts the rate value in the register if SPEED control is not being used
		{	
			for (int i = 0; i < 4; i++) 
			{
				data_reg[M1_RATE + i] = data_union.bytes[i];
			}
		}
		*/
		for (int i = 0; i < 4; i++) // Always calculates rate into rate register since encoder speed control isn't implemented
		{
			data_reg[M1_RATE + i] = data_union.bytes[i];
		}
		
		data_reg[M1_CONTROL] |= ENCD;
	}
}

/** \brief Updates the encoder 2 data registers with the encoder 2 value as a 4 byte array or writes received values to encoder.
	Also updates RPS registers with rotations/cycle
**/
void MotorDriver::updateM2Encoder()
{
	
}



/** \brief Updates the register value of motor 1's current draw. The analog reading necessary is slow so this function must be called manually.
**/
void MotorDriver::updateM1Current()
{
	data_reg[M1_CURRENT] = analogRead(M1_SENSE);
	data_reg[M1_CONTROL] |= CURD;
}

/** \brief Updates the register value of motor 2's current draw. The analog reading necessary is slow so this function must be called manually.
**/
void MotorDriver::updateM2Current()
{
	data_reg[M2_CURRENT] = analogRead(M2_SENSE);
	data_reg[M2_CONTROL] |= CURD;
}








uint8_t MotorDriver::intToDataReg(uint8_t reg, uint16_t value)
{
	data_union.int32 = value;
	for (int i = 0; i < 2; i++)
	{
		data_reg[reg + i] = data_union.bytes[i];
	}
}

uint8_t MotorDriver::longToDataReg(uint8_t reg, uint32_t value)
{
	data_union.int32 = value;
	for (int i = 0; i < 4; i++)
	{
		data_reg[reg + i] = data_union.bytes[i];
	}
}

uint8_t MotorDriver::floatToDataReg(uint8_t reg, float value)
{
	data_union.float32 = value;
	for (int i = 0; i < 4; i++)
	{
		data_reg[reg + i] = data_union.bytes[i];
	}
}


uint8_t MotorDriver::wire3BytesToDataReg(uint8_t reg)
{
	for (int i = 0; i < 3; i++)
	{
		data_reg[reg + i] = Wire.read();
	}
}

uint8_t MotorDriver::wireIntToDataReg(uint8_t reg)
{
	for (int i = 0; i < 2; i++)
	{
		data_reg[reg + i] = Wire.read();
	}
}

uint8_t MotorDriver::wireLongToDataReg(uint8_t reg)
{
	for (int i = 0; i < 4; i++)
	{
		data_reg[reg + i] = Wire.read();
	}
}


uint16_t MotorDriver::intFromDataReg(uint8_t reg)
{
	return data_reg[reg] << 8 | data_reg[reg + 1];
}

uint32_t MotorDriver::longFromDataReg(uint8_t reg)
{
	return (data_reg[reg] << 24) | (data_reg[reg + 1] << 16) | (data_reg[reg + 2] << 8) | data_reg[reg + 3];
}

float MotorDriver::floatFromDataReg(uint8_t reg)
{
	for (int i = 0; i < 4; i++)
	{
		data_union.bytes[i] = data_reg[reg + i];
	}
	return data_union.float32;
}






/** \brief Loads and returns an 16 bit value from EEPROM
**/
uint16_t MotorDriver::loadInt(uint16_t address)
{
	return EEPROM.read(address) << 8 | EEPROM.read(address + 1);
}

/** \brief Loads and returns an 32 bit value from EEPROM
**/
uint32_t MotorDriver::loadLong(uint16_t address)
{
	return (EEPROM.read(address) << 24) | (EEPROM.read(address + 1) << 16) | (EEPROM.read(address + 2) << 8) | EEPROM.read(address + 3);
}

/** \brief Loads a 16 bit integer value into the data register
**/
uint8_t MotorDriver::loadIntRegister(uint16_t address, uint8_t reg)
{
	for (int i = 0; i < 2; i++)
	{
		data_reg[reg + i] = EEPROM.read(address + i);
	}
}

/** \brief loads a 24 bit register value from EEPROM
**/
uint8_t MotorDriver::load3ByteRegister(uint16_t address, uint8_t reg) 
{
	for (int i = 0; i < 3; i++) 
	{
		data_reg[reg + i] = EEPROM.read(address + i);
	}
}

/** \brief Loads a 32 bit value into the data register
**/
uint8_t MotorDriver::loadLongRegister(uint16_t address, uint8_t reg)
{
	for (int i = 0; i < 4; i++)
	{
		data_reg[reg + i] = EEPROM.read(address + i);
	}
}

/** \brief Loads data regaister values from EEPROM. Data to load is selected by toggling a bit.
	Ex: to load all registers set EEPROM_LOAD to  0b111111111111111111
	Ex: to leave out encoder, rate, and power registers use 0b111111110011000011
**/
uint8_t MotorDriver::loadDataRegister()
{
	uint32_t values = (data_reg[EEPROM_LOAD] << 16) | (data_reg[EEPROM_LOAD + 1] << 8) | data_reg[EEPROM_LOAD + 2];
	if (values & 0x0001) {	data_reg[M1_CONTROL] = EEPROM.read(M1_CONTROL);}
	if (values & 0x0002) {	data_reg[M2_CONTROL] = EEPROM.read(M2_CONTROL);}
	if (values & 0x0004) {	data_reg[M1_POWER] = EEPROM.read(M1_POWER);}
	if (values & 0x0008) {	data_reg[M2_POWER] = EEPROM.read(M2_POWER);}
	if (values & 0x0010) {	loadLongRegister(M1_ENCODER, M1_ENCODER);}
	if (values & 0x0020) {	loadLongRegister(M2_ENCODER, M2_ENCODER);}
	if (values & 0x0040) {	data_reg[M1_CURRENT] = EEPROM.read(M1_CURRENT);}
	if (values & 0x0080) {	data_reg[M2_CURRENT] = EEPROM.read(M2_CURRENT);}
	if (values & 0x0100) {	loadLongRegister(M1_RATE, M1_RATE);}
	if (values & 0x0200) {	loadLongRegister(M2_RATE, M2_RATE);}
	if (values & 0x0400) {	loadLongRegister(PID_KP, PID_KP);}
	if (values & 0x0800) {	loadLongRegister(PID_KI, PID_KI);}
	if (values & 0x1000) {	loadLongRegister(PID_KD, PID_KD);}
	if (values & 0x2000) {	loadLongRegister(TICKS_REV, TICKS_REV);}
	if (values & 0x4000) {	data_reg[LOOP_TIME] = EEPROM.read(LOOP_TIME); loop_frequency = 1000 / data_reg[LOOP_TIME];}
	if (values & 0x8000) {	data_reg[DEVICE_ID] = EEPROM.read(DEVICE_ID);}
	if (values & 0x010000){	load3ByteRegister(EEPROM_SAVE, EEPROM_SAVE);}
	if (values & 0x020000){	load3ByteRegister(EEPROM_LOAD, EEPROM_LOAD);}
}


/** \brief Saves a 16 bit value to EEPROM
**/
uint8_t MotorDriver::saveInt(uint16_t address, uint32_t value)
{
		EEPROM.write(address, value >> 8);
		EEPROM.write(address, value & 0xFF);
}

/** \brief Saves a 32 bit value to EEPROM
**/
uint8_t MotorDriver::saveLong(uint16_t address, uint32_t value)
{
	EEPROM.write(address, value >> 24 & 0xFF);
	EEPROM.write(address, value >> 16 & 0xFF);
	EEPROM.write(address, value >> 8 & 0xFF);
	EEPROM.write(address, value & 0xFF);
}

/** \brief saves a 16 bit register value into EEPROM
**/
uint8_t MotorDriver::saveIntRegister(uint16_t address, uint8_t reg)
{
	for (int i = 0; i < 2; i++)
	{
		EEPROM.write(address + i, data_reg[reg + i]);
	}
}

/** \brief saves a 24 bit register value into EEPROM
**/
uint8_t MotorDriver::save3ByteRegister(uint16_t address, uint8_t reg) 
{
	for (int i = 0; i < 3; i++) 
	{
		EEPROM.write(address + i, data_reg[reg + i]);
	}
}

/** \brief saves a 32 bit register value into EEPROM
**/
uint8_t MotorDriver::saveLongRegister(uint16_t address, uint8_t reg)
{
	for (int i = 0; i < 4; i++)
	{
		EEPROM.write(address + i, data_reg[reg + i]);
	}
}

/** \brief Saves data regaister values to EEPROM. Data to save is selected by toggling a bit.
	Ex: to save all registers set EEPROM_SAVE to  0b111111111111111111
	Ex: to leave out encoder, rate, and power registers use 0b111111110011000011
**/
uint8_t MotorDriver::saveDataRegister()
{
	uint32_t values = (data_reg[EEPROM_SAVE] << 16) | (data_reg[EEPROM_SAVE + 1] << 8) | data_reg[EEPROM_SAVE + 2]; 
	if (values & 0x01) {	EEPROM.write(M1_CONTROL, data_reg[M1_CONTROL]);}
	if (values & 0x02) {	EEPROM.write(M2_CONTROL, data_reg[M2_CONTROL]);}
	if (values & 0x04) {	EEPROM.write(M1_POWER, data_reg[M1_POWER]);}
	if (values & 0x08) {	EEPROM.write(M2_POWER, data_reg[M2_POWER]);}
	if (values & 0x10) {	saveLongRegister(M1_ENCODER, M1_ENCODER);}
	if (values & 0x20) {	saveLongRegister(M2_ENCODER, M2_ENCODER);}
	if (values & 0x40) {	EEPROM.write(M1_CURRENT, data_reg[M1_CURRENT]);}
	if (values & 0x80) {	EEPROM.write(M2_CURRENT, data_reg[M2_CURRENT]);}
	if (values & 0x0100) {	saveLongRegister(M1_RATE, M1_RATE);}
	if (values & 0x0200) {	saveLongRegister(M2_RATE, M2_RATE);}
	if (values & 0x0400) {	saveLongRegister(PID_KP, PID_KP);}
	if (values & 0x0800) {	saveLongRegister(PID_KI, PID_KI);}
	if (values & 0x1000) {	saveLongRegister(PID_KD, PID_KD);}
	if (values & 0x2000) {	saveLongRegister(TICKS_REV, TICKS_REV);}
	if (values & 0x4000) {	EEPROM.write(LOOP_TIME, data_reg[LOOP_TIME]);}
	if (values & 0x8000) {	EEPROM.write(DEVICE_ID, data_reg[DEVICE_ID]);}
	if (values & 0x010000) {save3ByteRegister(EEPROM_SAVE, EEPROM_SAVE);}
	if (values & 0x020000) {save3ByteRegister(EEPROM_LOAD, EEPROM_LOAD);}
}


#ifdef DEBUG_MOTOR_DRIVER
uint8_t MotorDriver::write32(float val)
{
	data_union.float32 = val;
	Wire.write(data_union.bytes, 4);
}
#endif