/*
DualDualMotorDriver.cpp - Software library to program and control the TiltyIMU Dual Motor Driver Shield
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
#include "DualDualMotorDriver3.h"


DualMotorDriver MotorDriver;

// Add-on/shield code

DualMotorDriver::DualMotorDriver() : m1Encoder(ENC1A, ENC1B), m2Encoder(ENC2B, ENC2A)
{	
	// Initialize all of the I/O pins
	pinMode(M1, OUTPUT);	digitalWrite(M1, LOW);
	pinMode(M2, OUTPUT);	digitalWrite(M2, LOW);
	
	pinMode(M1A, OUTPUT);	digitalWrite(M1A, LOW);
	pinMode(M1B, OUTPUT);	digitalWrite(M1B, HIGH);
	pinMode(M2A, OUTPUT);	digitalWrite(M2A, LOW);
	pinMode(M2B, OUTPUT);	digitalWrite(M2B, LOW);
	
	pinMode(LED, OUTPUT);	digitalWrite(LED, LOW);
	
	
	pinMode(ENC1A, INPUT);	digitalWrite(ENC1A, HIGH);
	pinMode(ENC1B, INPUT);	digitalWrite(ENC2A, HIGH);
	pinMode(ENC2A, INPUT);
	pinMode(ENC2B, INPUT);
	
	// Enable interrupts for encoders
	EIMSK = 0x03;	// Enable external interrupt INT0
	EICRA = 0x05;	// Set interrupt for change
	
	
	
#ifdef ENABLE_WATCHDOG_TIMER
	// Check for reset problems
	if (MCUSR & (WDRF | BORF)) { }
	MCUSR = 0;
	WDTCSR = _BV(WDCE) | _BV(WDE);
	WDTCSR = _BV(WDIE) | _BV(WDE) | LOW_WDP | HIGH_WDP;
#endif
	
	// Set up Timer2 to automatically update currents and encoders
	// Timer is set up to interrupt every 10ms by default in order to update motors and encoders when necessary
    TCCR2B = 0x00;			// Disbale Timer2 while we set it up
	TCNT2 = 0x00;			// Set initial timer value to 0
	OCR2A = OCR2A_VALUE;	// Set the value to count to for desired refresh rate
	TCCR2A = TIMER2A_MODE;	// Timer2 Control Reg A: Set to mode 7, counts from 0x00 to OCR2A
	TCCR2B = TIMER2B_MODE | TIMER2_PRESCALER;// Timer2 Control Reg B: Timer Prescaler set to 1024 and timer mode set to mode 7
	
	// Set up Timer1 cause why not
	// 64 prescaler, 250 counts per millisecond, Fast PWM mode
	TCCR1B = 0;
	TCCR1A = 0x03;//_BV(WGM11) | _BV(WGM10);
	TCCR1C = 0;
	TCNT1 = 0;
	OCR1A = 250;
	TIMSK1 = 1;
	TCCR1B = 0x1B;//_BV(WGM13) | _BV(WGM12) | _BV(CS11) | _BV(CS10);

	//Setup the I2C bus
	Wire.begin(DEFAULT_DMD_ADDRESS);	// Begin I2C at slave address I2C_ADDRESS (defaults to 0x03)
#if I2C_FREQ == 100000
	TWBR = 72;							// Set up I2C for 100kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#elif I2C_FREQ == 200000
	TWBR = 32;							// Set up I2C for 200kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#else
	TWBR = 12;							// Set up I2C for 400kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#endif
	
	min_power = DEFAULT_MIN_POWER;
	PID_kP = DEFAULT_PID_KP;
	PID_kI = DEFAULT_PID_KI;
	PID_kD = DEFAULT_PID_KD;
	
	// Setup motor structs
	//Motor motor2 = {&M2_control, &M2_power, &M2_encoder, &M2_rate, &M2_current_power, &M2_scaled_power, &m2Encoder, (uint8_t*)&OCR0B, 0x80, M2, M2A, M2B};
	motor1.control = &M1_control;
	motor1.power = &M1_power;
	motor1.enc_val = &M1_encoder;
	motor1.cur_rate = &M1_rate;
	motor1.cur_pwr = &M1_current_power;
	motor1.scaled_pwr = &M1_scaled_power;
	motor1.targ_rate = &M1_target_rate;
	motor1.PID_P = &PID_P1;
	motor1.PID_I = &PID_I1;
	motor1.PID_D = &PID_D1;
	motor1.encoder = &m1Encoder;
	motor1.OCR0x = (uint8_t*)&OCR0B;
	motor1.COM0x = 0x20;
	motor1.speed_pin = M1;
	motor1.high_pin = M1A;
	motor1.low_pin = M1B;
	
	ramping_rate = 5;
	
	M1_control = DEFAULT_M1_CONTROL;
	
	sei();			// Enable global interrupts
}

DualMotorDriver::~DualMotorDriver() 
{
	// Do nothing
}


// Called to initialize the motor driver ISR's
void DualMotorDriver::init()
{
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	
	// Setup Timer0 for the PWM pins, I don't know why this needed to be here, but it wasn't setting correctly in the class constructor
	TCCR0B = 0;				// Disable the timer while we set it up
	TCCR0A = 0x03;			// Setup pins 5 and 6 for phase correct PWM (31.25kHz)
	TCNT0 = 0;
	TCCR0B = 0x01;			// Set PWM prescaler to 1 (lowest possible)
}



// Handles reading in I2C data
uint8_t DualMotorDriver::getData(int bytes)
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
				case M1_RATE: 		wireToVar(&M1_rate);	 updated_vars |= 1 << active_var;	break;	
				case DEVICE_ID: 	TWAR = Wire.read() << 1; updated_vars |= 1 << active_var;	break;
#ifdef DEBUG_MOTOR_DRIVER
				case 50: wireToVar((uint16_t*)&M1_target_rate); break;
#endif
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
		case M1_RATE: 		active_var_ptr = &M1_rate;		break;
	}
	updateVars();
}


void DualMotorDriver::sendData()
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
			case m1_encoder: Wire.write((uint8_t*)motor1.enc_val, 4); break;
			case m1_rate: Wire.write((uint8_t*)motor1.cur_rate, 4); break;
			case m1_target_rate: Wire.write((uint8_t*)motor1.targ_rate, 4); break;
			case led: ledToggle(); break;
			case 127: Wire.write(TCCR2B);
		}
	}
	else
	{
		Wire.write((uint8_t*)active_var_ptr, TX_BUFFER_SIZE);// Holy s**t this worked first try! Pointers FTW!
	}
#else
	Wire.write((uint8_t*)active_var_ptr, TX_BUFFER_SIZE);// Holy s**t this worked first try! Pointers FTW!
#endif
}


// Updates everything based on updated_vars
void DualMotorDriver::updateVars()
{
	if (updated_vars & (1 << M1_CONTROL))	updateMotorControl(&motor1);
	if (updated_vars & (1 << M1_POWER)) 
	{
		M1_power ? M1_scaled_power = map(M1_power, 0, 255, min_power, 255) : M1_scaled_power = 0;
		//if (M1_control & RPM) updateMotorRPM(&motor1);
		updateMotorPower(&motor1);
	}
	
	updated_vars = 0;
}


void DualMotorDriver::updateMotor(Motor *motor)
{
	if (*motor->control & RPM) updateMotorRPM(motor);
	setMotorDirection(motor);
	if (*motor->control & RAMPING) updateMotorPower(motor);
}


inline void DualMotorDriver::updateMotorControl(Motor *motor)
{
	setMotorDirection(motor);
	setTimerB(motor);
}


inline void DualMotorDriver::updateMotorRPM(Motor *motor)
{
	float old_rate = *motor->cur_rate;
	updateEncoder(motor);
	
	*motor->enc_val = motor->encoder->read();
	
	*motor->PID_P = PID_kP * *motor->targ_rate;
	*motor->PID_I += PID_kI * (*motor->targ_rate - *motor->cur_rate);
	*motor->PID_D = PID_kD * (old_rate - *motor->cur_rate);
	
	*motor->cur_pwr = (uint8_t)(*motor->PID_P + *motor->PID_I + *motor->PID_D);
	setMotorPWM(motor);
}


inline void DualMotorDriver::updateMotorPower(Motor *motor)
{
	if (*motor->control & RAMPING)
	{
		if (*motor->cur_pwr < *motor->scaled_pwr) *motor->cur_pwr += ramping_rate;
		else if (*motor->cur_pwr > *motor->scaled_pwr) *motor->cur_pwr -= ramping_rate;
		setMotorPWM(motor);
	}
	else
	{
		*motor->cur_pwr = *motor->scaled_pwr;
		setMotorPWM(motor);
	}
}


inline void DualMotorDriver::updateEncoder(Motor *motor)
{	
	*motor->cur_rate = ((float)(motor->encoder->read() - *motor->enc_val) / TICKS_PER_ROT) * REFRESH_FREQ *682; //		Arbitrary hack job to get reasonably realistic rotation speeds. DO NOT LET THIS BE USED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*motor->enc_val = motor->encoder->read();
}


// More efficient analogWrite for motor control pins
inline void DualMotorDriver::setMotorPWM(Motor *motor)
{
	switch (*motor->cur_pwr)
	{
		case 0: 	TCCR0A &= ~motor->COM0x; setMotorBraking(motor);			break;
		case 255:	TCCR0A &= ~motor->COM0x; sbi(PORTD, motor->speed_pin);		break;
		default: 	TCCR0A |= motor->COM0x;  *motor->OCR0x = *motor->cur_pwr;	break;
	}
}

// More efficent digitalWrite for just the motor direction/braking pins
inline void DualMotorDriver::setMotorDirection(Motor *motor)
{
	if (~(*motor->control & BRAKE) && *motor->cur_pwr != 0)
	{
		if (*motor->control & DIRECTION)
		{
			PORTD |= 1 << motor->high_pin;
			PORTB &= ~(motor->low_pin >> 3);
		}
		else
		{
			PORTD &= ~(1 << motor->high_pin);
			PORTB |= motor->low_pin >> 3;
		}
	}
}

// More efficent digitalWrite for just the motor direction/braking pins
inline void DualMotorDriver::setMotorBraking(Motor *motor)
{
	if (*motor->control & BRAKE)
	{
		PORTD |= (1 << motor->high_pin) | (1 << motor->speed_pin);
		//PORTB |= motor->low_pin >> 3;
		digitalWrite(motor->low_pin, HIGH);
	}
	else
	{
		cbi(PORTD, motor->speed_pin);
	}
}

// Enables and disables the interrupts that control motor and encoder updates
inline void DualMotorDriver::setTimerB(Motor *motor)
{
	if (*motor->control & (RAMPING | RPM))// Enable the interrupt routine that updates the given motor
	{
	    TCCR2B = 0x00;			// Disbale Timer2 while we set it up
		switch (motor->speed_pin)
		{
			case M1: 	TIMSK2 |= 0x02;	break;
			case M2: 	TIMSK2 |= 0x04;	break;
		}
		TCCR2B = TIMER2B_MODE | TIMER2_PRESCALER;// Re-enable Timer2
	}
	else // Disable the interrupts that control motor updates if they are unnecessary
	{
		switch (motor->speed_pin)
		{
			case M1: 	TIMSK2 &= ~0x02;	break;
			case M2: 	TIMSK2 &= ~0x04;	break;
		}
	}
}


// Takes a pointer to a variable and reads a new value into it from I2C
void DualMotorDriver::wireToVar(uint8_t *var)
{
	*var = Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void DualMotorDriver::wireToVar(uint16_t *var)
{
	*var = (Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void DualMotorDriver::wireToVar(int32_t *var)
{
	*var = ((int32_t)Wire.read() << 24) | ((int32_t)Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void DualMotorDriver::wireToVar(float *var)
{
	*var = ((int32_t)Wire.read() << 24) | ((int32_t)Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
}


#ifdef DEBUG_MOTOR_DRIVER
<<<<<<< Local Changes
void DualMotorDriver::ledOn() {	sbi(PORTB, 4);}
void DualMotorDriver::ledOff() {	cbi(PORTB, 4);}
void DualMotorDriver::ledToggle() {	PORTB ^= 0x04;}
#endif=======
void DualMotorDriver::ledOn() {	sbi(PORTB, 4);}
void DualMotorDriver::ledOff() {	cbi(PORTB, 4);}
void DualMotorDriver::ledToggle() {	PORTB ^= 0x04;}
#endif
// ========== End of class ==========

// I2C receive event
void receiveEvent(int bytes) {
	MotorDriver.getData(bytes);
}

// I2C request event
void requestEvent() {
	MotorDriver.sendData();
}

// Interrupt Service Routine attached to INT0 vector
ISR(EXT_INT0_vect)
{
	PINC & 0x02 ? MotorDriver.M1_encoder++ : MotorDriver.M1_encoder--;
	
}

ISR(EXT_INT1_vect)
{
	
}

ISR(WDT_vect)
{
	sbi(PORTB, 4);
}

unsigned long ms;

ISR(TIMER1_OVF_vect)
{
	ms++;
	//PORTB ^= 4;
	//__asm__ __volatile__ ("wdr");
}

ISR(TIMER2_COMPA_vect)
{
	// Motor 1 updates will go here
	MotorDriver.updateMotor(&MotorDriver.motor1);
}

ISR(TIMER2_COMPB_vect)
{
	// Motor 2 updates will go here
}>>>>>>> External Changes
