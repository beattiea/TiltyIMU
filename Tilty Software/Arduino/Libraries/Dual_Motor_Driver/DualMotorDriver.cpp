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
#include "DualMotorDriver.h"

#ifdef CORE_TEENSY && __arm__
// Teensy class data
#include "i2c_t3.h"

MotorDriver::MotorDriver()
{
	i2c_address = 0x03;
}

MotorDriver::MotorDriver(uint8_t address)
{	
	i2c_address = address;
}

MotorDriver::~MotorDriver() 
{
	// Do nothing
}



/** \brief Initializes the add-on board, reads control registers, etc.
	\param[out] error Returns 0 if everything went ok, 1 if add-on was not detected.
**/
int MotorDriver::init()
{
	Wire.pinConfigure(I2C_PINS_16_17, I2C_PULLUP_EXT);
	
	Wire.beginTransmission(i2c_address);
	if (Wire.endTransmission()) {	return 1;}
	
	Wire.beginTransmission(i2c_address);
	Wire.write(M1_CONTROL);
	Wire.write(updateControlReg(0,0,0,0,1));
	Wire.write(updateControlReg(0,0,0,0,1));
	Wire.endTransmission();
	
	while (Wire.requestFrom((int)i2c_address, 2) != 2) {}
	M1_control_reg = Wire.read();
	M2_control_reg = Wire.read();
}



/** \brief Sets a given motor to a given power level
	\param[in] motor Either 1 or 2 to indicate motor to write to
	\param[in] power Single byte value to indicate motor power
	\param[out] error Returns 0 if everything went ok, 1 if add-on was not detected, and 2 if motor number was out of bounds
**/
uint8_t MotorDriver::setPower(uint8_t motor, uint8_t power)
{
	Wire.pinConfigure(I2C_PINS_16_17, I2C_PULLUP_EXT);

	Wire.beginTransmission(i2c_address);
	if (motor == 1) {	Wire.write(M1_POWER);}
	else if (motor == 2) {	Wire.write(M2_POWER);}
	else
	{
		Wire.endTransmission();
		return 2;
	}
	Wire.write(power);
	return Wire.endTransmission();
}



/** \brief Sets both motor powers
	\param[in] power1 Single byte value to indicate motor 1 power
	\param[in] power2 Single byte value to indicate motor 2 power
	\param[out] error Returns 0 if everything went ok, 1 if add-on was not detected
**/
uint8_t MotorDriver::setPowers(uint8_t power1, uint8_t power2)
{
	Wire.beginTransmission(i2c_address);
	Wire.write(M1_POWER);
	Wire.write(power1);
	Wire.write(power2);
	return Wire.endTransmission();
}



/** \brief Sets a given motor to a given power level
	\param[in] motor Either 1 or 2 to indicate motor to write to
	\param[in] power 255 to -255 value to indicate motor power and direction
	\param[out] error Returns 0 if everything went ok, 1 if add-on was not detected, and 2 if motor number was out of bounds
**/
uint8_t MotorDriver::setMotor(uint8_t motor, int16_t power)
{
	
}



/** \brief Sets both motor powers
	\param[in] power1 255 to -255 value to indicate motor power and direction
	\param[in] power2 255 to -255 value to indicate motor power and direction
	\param[out] error Returns 0 if everything went ok, 1 if add-on was not detected
**/
uint8_t MotorDriver::setMotors(int16_t power1, int16_t power2)
{
	Wire.pinConfigure(I2C_PINS_16_17, I2C_PULLUP_EXT);
	delayMicroseconds(100);
	
	Wire.beginTransmission(i2c_address);
	Wire.write(M1_CONTROL);
	Wire.write(power1 < 0 ? 0 : 1);
	Wire.write(power2 < 0 ? 0 : 1);
	Wire.write(power1 < 0 ? power1 ^ 0xFF : power1 & 0xFF);
	Wire.write(power2 < 0 ? power2 ^ 0xFF : power2 & 0xFF);
	
	uint8_t result = Wire.endTransmission();
	
	delayMicroseconds(100);
	Wire.pinConfigure(I2C_PINS_18_19, I2C_PULLUP_EXT);
	
	return result;
}



/** \brief Returns a byte to send to update the control register of the add-on board
	\param[in] direction Boolean value that decides the direction of the motor
	\param[in] brake Boolean value that indicates if the motor should brake or coast when at 0 speed
	\param[in] control Boolean value to indicate power or RPM control
	\param[in] invert Boolean value to invert a motor's direction settings
	\param[in] encoder Boolean value to indicate if the encoder should be used or not
	\param[out] byte The byte to send the motor driver to update a motor control register
	
**/
uint8_t MotorDriver::updateControlReg(bool dir, bool brake, bool cont, bool inv, bool enc)
{
		Wire.pinConfigure(I2C_PINS_16_17, I2C_PULLUP_EXT);
		
		uint8_t temp_byte;
		
		if (dir) {	temp_byte |= DIRECTION;}
		if (brake) {	temp_byte |= BRAKE;}
		if (cont) {	temp_byte |= SPEED;}
		if (enc) {	temp_byte |= ENC;}
		
		return temp_byte;
}

// End Teensy/Master class information




#else




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
	pinMode(M1, OUTPUT);
	pinMode(M2, OUTPUT);
	
	pinMode(M1A, OUTPUT);
	pinMode(M1B, OUTPUT);
	pinMode(M2A, OUTPUT);
	pinMode(M2B, OUTPUT);
	
	pinMode(LED, OUTPUT);
	
	pinMode(ENC1A, INPUT);
	pinMode(ENC1B, INPUT);
	pinMode(ENC2A, INPUT);
	pinMode(ENC2B, INPUT);
	
	//Set up Timer2 to automatically update currents and encoders!!!!!!!!!!!!!!
    TCCR2B = 0x00;        //Disbale Timer2 while we set it up
    TCNT2  = 130;         //Reset Timer Count to 130 out of 255
    TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
    TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
    TCCR2A = 0x00;        //Timer2 Control Reg A: Normal port operation, Wave Gen Mode normal
    TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128
	
	
	// Initialize the status and control registers
	data_reg[0] = 0x0B;
	data_reg[1] = 0x0B;
	for (int i = 0x02; i < REGISTER_SIZE; i++) {	data_reg[i] = 0x00;}
	
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);// Setup pins 5 and 6 for fast PWM
	TCCR0B = _BV(CS00);// Set PWM frequency to 62.5kHz (fastest possible)
	#ifndef MOTOR_DRIVER_I2C_ADDRESS
		char I2C_ADDRESS = EEPROM.read(MOTOR_DRIVER_I2C_EEPROM_ADDRESS);
		if (I2C_ADDRESS == 255)
		{
			I2C_ADDRESS = DEFAULT_MOTOR_DRIVER_I2C_ADDRESS;
			EEPROM.write(MOTOR_DRIVER_I2C_EEPROM_ADDRESS, I2C_ADDRESS);
		}
	#else
		I2C_ADDRESS = DEFAULT_MOTOR_DRIVER_I2C_ADDRESS;
	#endif
	TWBR = 400000L;// Set up I2C for 400kHz
	Wire.begin(0x03); // Begin I2C at slave address I2C_ADDRESS (defaults to 0x03)
}


/** \brief Takes incoming I2C data into the rxBuffer
	\param[in] bytes The number of incoming bytes
	\param[out] error Returns 0 if register overflows, 1 if data is successfully transferred
**/
int MotorDriver::getData(int bytes)
{
	active_reg = Wire.read();

	if (active_reg == M1_CURRENT)	{ updateM1Current();}
	else if (active_reg == M2_CURRENT)	{ updateM2Current();}
	
	while (Wire.available())
	{
		if (active_reg >= REGISTER_SIZE) {	active_reg = active_reg % REGISTER_SIZE; return 0;}
		
		else if (active_reg == M1_ENCODER) {	updateEnc1Reg();}
		else if (active_reg == M2_ENCODER) {	updateEnc2Reg();}
		
		else if (active_reg == M1_RATE) {	updateMotor1Rate();}
		else if (active_reg == M2_RATE) {	updateMotor2Rate();}
		
		else 
		{
			data_reg[active_reg] = checkReadOnly(Wire.read());
			active_reg++;
		}
	}
	
	update();
	return 1;
}



/** \brief Sends requested I2C data
**/
void MotorDriver::sendData()
{	
	byte temp[REGISTER_SIZE - active_reg];
	for (int i = 0; i < REGISTER_SIZE - active_reg; i++)
	{
		temp[i] = data_reg[active_reg + i];
	}
	Wire.write(temp, REGISTER_SIZE - active_reg);
}



/** \brief Parses data in rxBuffer and updates encoder values
**/
int MotorDriver::update()
{
	updateMotor1();
	updateMotor2();
}



/** \brief Updates Motor 1 based on control register bit settings
**/
void MotorDriver::updateMotor1()
{
	if (data_reg[M1_POWER] == 0) 
	{
		if (data_reg[M1_CONTROL] & BRAKE) 
		{
			digitalWrite(M1A, HIGH);
			digitalWrite(M1B, HIGH);
			digitalWrite(M1, HIGH);
		}
		else {	digitalWrite(M1, LOW);}
	}
	else if (!(data_reg[M1_CONTROL] & SPEED))
	{
		bool dir = data_reg[M1_CONTROL] & DIRECTION;
		digitalWrite(M1A, dir);
		digitalWrite(M1B, !dir);
		analogWrite(M1, data_reg[M1_POWER]);
	}
}



/** \brief Updates Motor 2 based on control register bit settings
**/
void MotorDriver::updateMotor2()
{
	if (data_reg[M2_POWER] == 0) 
	{
		if (data_reg[M2_CONTROL] & BRAKE) 
		{
			digitalWrite(M2A, HIGH);
			digitalWrite(M2B, HIGH);
			digitalWrite(M2, HIGH);
		}
		else {	digitalWrite(M2, LOW);}
	}
	
	else if (!(data_reg[M2_CONTROL] & SPEED))
	{
		bool dir = data_reg[M2_CONTROL] & DIRECTION;
		digitalWrite(M2A, !dir);
		digitalWrite(M2B, dir);
		analogWrite(M2, data_reg[M2_POWER]);
	}
}



/** \brief Updates the encoder 1 data registers with the encoder 1 value as a 4 byte array or writes received values to encoder.
	Also updates RPS registers with rotations/cycle
**/
void MotorDriver::updateEnc1Reg()
{
	if (Wire.available() >= 4 && active_reg == M1_ENCODER) 
	{
		for (int i = 0; i < 4; i++)
		{
			enc_union.bytes[i] = Wire.read();
			active_reg++;
		}
		m1Encoder.write(enc_union.int32);
		data_reg[M1_CONTROL] ^= ENCD;
	}
	
	else if (data_reg[M1_CONTROL] & ENC)
	{
		long old_enc = M1_encoder;
		
		M1_encoder = m1Encoder.read();
		enc_union.int32 = M1_encoder;
		
		//rot_union.flt = ((M1_encoder - old_enc) / (TICKS_PER_REV * GEAR_RATIO)) * REFRESH_FREQ;
		
		for (int i = 0; i < 4; i++)
		{
			data_reg[M1_ENCODER + i] = enc_union.bytes[i];
			//if (!data_reg[M1_CONTROL] & SPEED) {	data_reg[M1_RPS + i] = rot_union.bytes[i];}
		}
		
		enc_union.int32 = (enc_union.int32 - old_enc);// * REFRESH_FREQ;
		M1_speed_actual = enc_union.int32;
		for (int i = 0; i < 4; i++) {
			data_reg[M1_RATE + i] = enc_union.bytes[i];
		}
		
		if (data_reg[M1_CONTROL] & SPEED) {	updateMotor1Rate();}
		
		data_reg[M1_CONTROL] |= ENCD;
	}
}

/** \brief Updates the encoder 2 data registers with the encoder 2 value as a 4 byte array or writes received values to encoder.
	Also updates RPS registers with rotations/cycle
**/
void MotorDriver::updateEnc2Reg()
{
	if (Wire.available() >= 4 && active_reg == M2_ENCODER)
	{
		for (int i = 0; i < 4; i++)
		{
			enc_union.bytes[i] = Wire.read();
			active_reg++;
		}
		m2Encoder.write(enc_union.int32);
		data_reg[M2_CONTROL] &= !ENCD;
	}
	
	else if (data_reg[M2_CONTROL] & ENC)
	{
		long old_enc = M2_encoder;
		
		M2_encoder = m2Encoder.read();
		enc_union.int32 = M2_encoder;
		
		rot_union.flt = ((M2_encoder - old_enc) / (TICKS_PER_REV * GEAR_RATIO)) * REFRESH_FREQ;
		
		for (int i = 0; i < 4; i++)
		{
			data_reg[M2_ENCODER + i] = enc_union.bytes[i];
			if (!data_reg[M2_CONTROL] & SPEED) {	data_reg[M2_RATE + i] = rot_union.bytes[i];}
		}
		
		data_reg[M2_CONTROL] |= ENCD;
	}
}



/** \brief 
**/
void MotorDriver::updateMotor1Rate() {
	if (Wire.available() >= 4 && active_reg == M1_RATE) 
	{
		for (int i = 0; i < 4; i++)
		{
			enc_union.bytes[i] = Wire.read();
			data_reg[active_reg] = enc_union.bytes[i];
			active_reg++;
		}
		M1_speed = enc_union.int32;
	}
	else
	{
		bool dir = M1_speed > 0 ? true : false;
		digitalWrite(M1A, dir);
		digitalWrite(M1B, !dir);
		
		int16_t diff = M1_speed - M1_speed_actual;
		PID_P1 = data_reg[PID_KP] * diff;
		PID_I1 += data_reg[PID_KI] * diff;
		PID_D1 = 0;//												DERIVATIVE VALUE NOT IMPLEMENTED
		data_reg[M1_POWER] = constrain(PID_P1 + PID_I1 + PID_D1, 0, 255);
		
		analogWrite(M1, data_reg[M1_POWER]);
	}
}

/** \brief 
**/
void MotorDriver::updateMotor2Rate() {
	if (Wire.available() >= 4 && active_reg == M2_RATE) 
	{
		for (int i = 0; i < 4; i++)
		{
			data_reg[active_reg] = Wire.read();
			active_reg++;
		}
	}
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



/** \brief Checks to make sure that current data register is not read-only before writing
	\param[in] Value to write
	\param[out] Value to actually be written
**/
uint8_t MotorDriver::checkReadOnly(uint8_t val)
{
	if (active_reg < 21) {	return val;}
	else {	return data_reg[active_reg];}
}

// End add-on class information
#endif