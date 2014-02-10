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
#include "wiring_private.h"
#include "DualMotorDriver3.h"


// Add-on/shield code

MotorDriver::MotorDriver() : m1Encoder(ENC1A, ENC1B), m2Encoder(ENC2B, ENC2A)
{	
	// Initialize all of the I/O pins
	pinMode(M1, OUTPUT);	digitalWrite(M1, LOW);
	pinMode(M2, OUTPUT);	digitalWrite(M2, LOW);
	
	pinMode(M1A, OUTPUT);	digitalWrite(M1A, LOW);
	pinMode(M1B, OUTPUT);	digitalWrite(M1B, HIGH);
	pinMode(M2A, OUTPUT);	digitalWrite(M2A, LOW);
	pinMode(M2B, OUTPUT);	digitalWrite(M2B, HIGH);
	
	pinMode(LED, OUTPUT);	digitalWrite(LED, LOW);
	
	pinMode(ENC1A, INPUT);
	pinMode(ENC1B, INPUT);
	pinMode(ENC2A, INPUT);
	pinMode(ENC2B, INPUT);
	
	// Set up Timer2 to automatically update currents and encoders
	// Timer is set up to interrupt every 2.5ms to update motors and encoders when necessary
    TCCR2B = 0x00;			// Disbale Timer2 while we set it up
	TCNT2 = 0x00;			// Set initial timer value to 0
	TIMSK2 = TIMER2_IMSK;	// Timer2 INT Reg: Timer2 Capture/Compare A and B enable
	TCCR2A = TIMER2A_MODE;	// Timer2 Control Reg A: Set to mode 7, counts from 0x00 to OCR2A
	OCR2A = OCR2A_VALUE;	// Count from 0-77 -> ~200Hz -> ~0.005 second period
	OCR2B = OCR2A / 2;		// Count to 1/2 of OCR2A to evenly distribute the workload over time
	if (DEFAULT_M1_CONTROL & (RAMPING | RPM) | DEFAULT_M2_CONTROL & (RAMPING | RPM))// Only turns on Timer2 if it's needed
	{
		TCCR2B = TIMER2B_MODE | TIMER2_PRESCALER;// Timer2 Control Reg B: Timer Prescaler set to 1024 and timer mode set to mode 7
	}
	
	// Setup the PWM pins
#ifdef PHASE_CORRECT_PWM
	TCCR0A = 0x01;			// Setup pins 5 and 6 for phase correct PWM (31.25kHz)
#else
	TCCR0A = 0x03;			// Setup pins 5 and 6 for fast PWM (62.5kHz)
#endif
	TCCR0B = 0x01;			// Set PWM prescaler to 1 (lowest possible)

	//Setup the I2C bus
	Wire.begin(DEFAULT_DMD_ADDRESS);	// Begin I2C at slave address I2C_ADDRESS (defaults to 0x03)
#if I2C_FREQ == 100000
	TWBR = 72;							// Set up I2C for 100kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#elif I2C_FREQ == 200000
	TWBR = 32;							// Set up I2C for 200kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#else I2C_FREQ
	TWBR = 12;							// Set up I2C for 400kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#endif
	
	min_power = DEFAULT_MIN_POWER;
	
	// Setup motor structs
	//Motor motor2 = {&M2_control, &M2_power, &M2_encoder, &M2_rate, &M2_current_power, &M2_scaled_power, &m2Encoder, (uint8_t*)&OCR0B, 0x80, M2, M2A, M2B};
	motor1.control = &M1_control;
	motor1.power = &M1_power;
	motor1.enc_val = &M1_encoder;
	motor1.rate = &M1_rate;
	motor1.cur_pwr = &M1_current_power;
	motor1.scaled_pwr = &M1_scaled_power;
	motor1.encoder = &m1Encoder;
	motor1.OCR0x = (uint8_t*)&OCR0B;
	motor1.COM0x = 0x20;
	motor1.speed_pin = M1;
	motor1.high_pin = M1A;
	motor1.low_pin = M1B;
	
	*motor1.cur_pwr = 127;
	motorPWM(&motor1);
}

MotorDriver::~MotorDriver() 
{
	// Do nothing
}



// Handles reading in I2C data
uint8_t MotorDriver::getData(int bytes)
{
	active_var = Wire.read();
	
	if (Wire.available())
	{
		while (Wire.available())
		{
			switch (active_var)
			{
				case M1_CONTROL:	wireToVar(&M1_control);  updated_vars |= 1 << active_var;	break;
				case M2_CONTROL:	wireToVar(&M2_control);	 updated_vars |= 1 << active_var;	break;
				case M1_POWER: 		wireToVar(&M1_power); 	 updated_vars |= 1 << active_var;	break;
				case M2_POWER: 		wireToVar(&M2_power);	 updated_vars |= 1 << active_var;	break;
				case M1_ENCODER: 	wireToVar(&M1_encoder);	 updated_vars |= 1 << active_var;	break;
				case DEVICE_ID: 	TWAR = Wire.read() << 1; updated_vars |= 1 << active_var;	break;
			}
			if (Wire.available()) active_var++;
		}
	}
	
	switch (active_var)
	{
		case M1_CONTROL: 	active_var_ptr = &M1_control;	break;
		case M2_CONTROL: 	active_var_ptr = &M2_control;	break;
		case M1_POWER: 		active_var_ptr = &M1_power;		break;
		case M2_POWER: 		active_var_ptr = &M2_power;		break;
		case M1_ENCODER: 	active_var_ptr = &M1_encoder;	break;
	}
	updateVars();
}


void MotorDriver::sendData()
{
#ifdef DEBUG_MOTOR_DRIVER
	if (active_var > 100)
	{
		switch (active_var)
		{
			// Debug code for reading values not in the data register array
			case m1_scaled_power: Wire.write(motor1.scaled_pwr, 1); break;
			case m1_current_power: Wire.write(motor1.cur_pwr, 1); break;
			case m1_power: Wire.write(motor1.power, 1); break;
			case led: ledToggle(); break;
		}
	}
	else
	{
#endif
	
		Wire.write((uint8_t*)active_var_ptr, TX_BUFFER_SIZE);// Holy s**t this worked first try! Pointers FTW!
#ifdef DEBUG_MOTOR_DRIVER
	}
#endif
}


// Updates everything based on updated_vars
void MotorDriver::updateVars()
{
	if (updated_vars & (1 << M1_POWER)) 
	{
		M1_power ? M1_scaled_power = map(M1_power, 0, 255, min_power, 255) : M1_scaled_power = 0;
		updateMotor(&motor1);
	}
	if (updated_vars & (1 << M1_CONTROL))	updateMotor(&motor1);
}


// Updates a motor based on its control data and power/speed
inline void MotorDriver::updateMotor(Motor *motor)
{
	if (*motor->control & (RPM | RAMPING))
	{
		if (*motor->control & RPM)
		{
			// RPM control code goes here!!!!!!!!!!!
		}
		else
		{
			if (*motor->cur_pwr < *motor->scaled_pwr) *motor->cur_pwr += ramping_rate;
			else if (*motor->cur_pwr > *motor->scaled_pwr) *motor->cur_pwr -= ramping_rate;
		}
	}
	
	else
	{
		*motor->cur_pwr = *motor->scaled_pwr;
		motorPWM(motor);
	}
}

// More efficient analogWrite for motor control pins
inline void MotorDriver::motorPWM(Motor *motor)
{
	switch (*motor->cur_pwr)
	{
		case 0: 	TCCR0A &= ~motor->COM0x; cbi(PORTD, motor->speed_pin);		break;
		case 255:	TCCR0A &= ~motor->COM0x; sbi(PORTD, motor->speed_pin);		break;
		default: 	TCCR0A |= motor->COM0x;  *motor->OCR0x = *motor->cur_pwr;	 break;
	}
}

// Takes a pointer to a variable and an encoder reads the current encoder value into the variable
void encoderToVar(int32_t *var, Encoder *enc)
{
	*var = enc->read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void MotorDriver::wireToVar(uint8_t *var)
{
	*var = Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void MotorDriver::wireToVar(uint16_t *var)
{
	*var = (Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void MotorDriver::wireToVar(int32_t *var)
{
	*var = ((int32_t)Wire.read() << 24) | ((int32_t)Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void MotorDriver::wireToVar(float *var)
{
	*var = ((int32_t)Wire.read() << 24) | ((int32_t)Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
}


void MotorDriver::ledOn() {	digitalWrite(LED, HIGH);}
void MotorDriver::ledOff() {	digitalWrite(LED, LOW);}
void MotorDriver::ledToggle() {	digitalWrite(LED, !digitalRead(LED));}

ISR(TIMER2_OVF_vect) 
{
	//motors.update();
	//count = 0;
	
	TCNT2 = 130;
	TIFR2 = 0x00;
}

ISR(TIMER2_COMPA_vect)
{
	// Motor 1 updates will go here
}

ISR(TIMER2_COMPB_vect)
{
	// Motor 2 updates will go here
}