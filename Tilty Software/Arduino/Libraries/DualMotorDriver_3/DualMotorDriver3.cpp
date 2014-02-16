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


DualMotorDriver MotorDriver;

// Add-on/shield code
DualMotorDriver::DualMotorDriver()
{	
	// Initialize all of the I/O pins
	pinMode(5, OUTPUT);	digitalWrite(5, LOW);// M1
	pinMode(6, OUTPUT);	digitalWrite(6, LOW);// M2
	
	pinMode(7, OUTPUT);	digitalWrite(7, LOW);// M1H
	pinMode(8, OUTPUT);	digitalWrite(8, HIGH);// M1L
	pinMode(4, OUTPUT);	digitalWrite(4, LOW);// M2H
	pinMode(9, OUTPUT);	digitalWrite(9, HIGH);// M2L
	
	pinMode(M1_SENSE, INPUT);
	pinMode(M2_SENSE, INPUT);
	
	pinMode(LED, OUTPUT);	digitalWrite(LED, LOW);
	
	
	pinMode(ENC1A, INPUT);	digitalWrite(ENC1A, HIGH);
	pinMode(ENC1B, INPUT);	digitalWrite(ENC2A, HIGH);
	pinMode(ENC2A, INPUT);	digitalWrite(ENC1B, HIGH);
	pinMode(ENC2B, INPUT);	digitalWrite(ENC2B, HIGH);
	
	// Enable interrupts for encoders
	attachInterrupt(1, readEncoder1, RISING);
	attachInterrupt(0, readEncoder2, RISING);
	EICRA = ENCODER_RESOLUTION;	// Set interrupt for change
	
	
	
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
	OCR2B = OCR2A_VALUE / 2;// Set compare 2 to half compare 1 rate
	TCCR2A = TIMER2A_MODE;	// Timer2 Control Reg A: Set to mode 7, counts from 0x00 to OCR2A
	TCCR2B = TIMER2B_MODE | TIMER2_PRESCALER;// Timer2 Control Reg B: Timer Prescaler set to 1024 and timer mode set to mode 7

	//Setup the I2C bus
	Wire.begin(DEFAULT_DMD_ADDRESS);	// Begin I2C at slave address I2C_ADDRESS (defaults to 0x03)
#if I2C_FREQ == 100000
	TWBR = 72;							// Set up I2C for 100kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#elif I2C_FREQ == 200000
	TWBR = 32;							// Set up I2C for 200kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#else
	TWBR = 12;							// Set up I2C for 400kHz. Forumla is: Bit Rate = 16MHz / (16 + 2 * TWBR)
#endif
	digitalWrite(A4, LOW);				// Disable internal pull-ups
	digitalWrite(A5, LOW);				// Disable internal pull-ups
	
	// Setup pin structs
	M1 = (Pin){(uint8_t*)&PORTD, (uint8_t*)&PIND, 1<<5, 5, 5, 0x02};
	M2 = (Pin){(uint8_t*)&PORTD, (uint8_t*)&PIND, 1<<6, 6, 6, 0x04};
	M1H = (Pin){(uint8_t*)&PORTD, (uint8_t*)&PIND, 1<<7, 7, 7, 0x00};
	M1L = (Pin){(uint8_t*)&PORTB, (uint8_t*)&PINB, 1<<0, 0, 8, 0x00};
	M2H = (Pin){(uint8_t*)&PORTB, (uint8_t*)&PINB, 1<<1, 9, 9, 0x00};
	M2L = (Pin){(uint8_t*)&PORTD, (uint8_t*)&PIND, 1<<4, 4, 4, 0x00};
	
	
	
	// Setup motor structs
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
	motor1.old_enc = 0;
	motor1.OCR0x = (uint8_t*)&OCR0B;
	motor1.COM0x = 0x20;
	motor1.speed_pin = &M1;
	motor1.high_pin = &M1H;
	motor1.low_pin = &M1L;
	
	motor2.control = &M2_control;
	motor2.power = &M2_power;
	motor2.enc_val = &M2_encoder;
	motor2.cur_rate = &M2_rate;
	motor2.cur_pwr = &M2_current_power;
	motor2.scaled_pwr = &M2_scaled_power;
	motor2.targ_rate = &M2_target_rate;
	motor2.PID_P = &PID_P2;
	motor2.PID_I = &PID_I2;
	motor2.PID_D = &PID_D2;
	motor2.old_enc = 0;
	motor2.OCR0x = (uint8_t*)&OCR0A;
	motor2.COM0x = 0x80;
	motor2.speed_pin = &M2;
	motor2.high_pin = &M2H;
	motor2.low_pin = &M2L;
	
	ramping_rate = 5;
	
	M1_control = DEFAULT_M1_CONTROL;
	M2_control = DEFAULT_M2_CONTROL;
	
	min_power = DEFAULT_MIN_POWER;
	PID_kP = DEFAULT_PID_KP;
	PID_kI = DEFAULT_PID_KI;
	PID_kD = DEFAULT_PID_KD;
	
	setTimerB(&motor1);
	setTimerB(&motor2);
	
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
	
	// The below timer setups were placed here cause Arduino screws with them otherwise as they'd usually be used by other functions/libraries
	
	// Setup Timer0 for the PWM pins
	TCCR0B = 0;				// Disable the timer while we set it up
	TCCR0A = 0x03;			// Setup pins 5 and 6 for phase fast PWM
	TCNT0 = 0;
	TCCR0B = 0x01;			// Set PWM prescaler to 1 (lowest possible)
	
	// Set up Timer1 cause why not
	// 64 prescaler, 250 counts per millisecond, Fast PWM mode
	TCCR1B = 0;
	TCCR1A = 0x03;//_BV(WGM11) | _BV(WGM10);
	TCCR1C = 0;
	TCNT1 = 0;
	OCR1A = 250;
	TIMSK1 = 1;
	TCCR1B = 0x1B;//_BV(WGM13) | _BV(WGM12) | _BV(CS11) | _BV(CS10);
}


void DualMotorDriver::saveSettings(uint8_t vals)
{
	eeprom_write_byte((uint8_t*)SAVED_VALS_ADDRESS, vals);
	if (vals & 0x01) eeprom_write_byte((uint8_t*)M1_CONTROL_ADDRESS, M1_control);
	if (vals & 0x02) eeprom_write_byte((uint8_t*)M2_CONTROL_ADDRESS, M2_control);
	if (vals & 0x04) eeprom_write_byte((uint8_t*) MIN_POWER_ADDRESS, min_power);
	if (vals & 0x08) eeprom_write_byte((uint8_t*)RAMPING_RATE_ADDRESS, ramping_rate);
	if (vals & 0x10) eeprom_write_byte((uint8_t*)I2C_ADDR_ADDRESS, TWAR);
	if (vals & 0x20) eeprom_write_block((void*)&PID_kP, (void*)PID_SCALARS_ADDRESS, 12);
}

void DualMotorDriver::loadSettings()
{
	uint8_t vals = EEPROM.read(SAVED_VALS_ADDRESS);
	if (!(vals & 0x80))
	{
		if (vals & 0x01) M1_control = eeprom_read_byte((uint8_t*)M1_CONTROL_ADDRESS);
		if (vals & 0x02) M2_control = eeprom_read_byte((uint8_t*)M2_CONTROL_ADDRESS);
		if (vals & 0x04) min_power = eeprom_read_byte((uint8_t*)RAMPING_RATE_ADDRESS);
		if (vals & 0x10) TWAR = eeprom_read_byte((uint8_t*)I2C_ADDR_ADDRESS);
		if (vals & 0x20) eeprom_read_block((void*)&PID_kP, (void*)PID_SCALARS_ADDRESS, 12);
	}
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
				case M1_CONTROL:	wireToVar(&M1_control);  				updated_vars |= 1 << active_var;	break;
				case M2_CONTROL:	wireToVar(&M2_control);	 				updated_vars |= 1 << active_var;	break;
				case M1_POWER: 		wireToVar(&M1_power); 	 				updated_vars |= 1 << active_var;	break;
				case M2_POWER: 		wireToVar(&M2_power);	 				updated_vars |= 1 << active_var;	break;
				case M1_ENCODER: 	wireToVar(&M1_encoder);					updated_vars |= 1 << active_var;	break;
				case M2_ENCODER: 	wireToVar(&M2_encoder);					updated_vars |= 1 << active_var;	break;
				case M1_RATE: 		wireToVar((uint16_t*)&M1_target_rate);	updated_vars |= 1 << active_var;	break;
				case M2_RATE: 		wireToVar((uint16_t*)&M2_target_rate);	updated_vars |= 1 << active_var;	break;
				case PID_KP: 		wireToVar(&PID_kP);						updated_vars |= 1 << active_var;	break;
				case PID_KI: 		wireToVar(&PID_kI);						updated_vars |= 1 << active_var;	break;
				case PID_KD: 		wireToVar(&PID_kD);						updated_vars |= 1 << active_var;	break;
				case DEVICE_ID: 	TWAR = Wire.read() << 1; 				updated_vars |= 1 << active_var;	break;
				case EEPROM_SAVE: 	saveSettings(Wire.read());				break;
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
		case M2_ENCODER: 	active_var_ptr = &M2_encoder;	break;
		case M1_RATE: 		active_var_ptr = &M1_rate;		break;
		case M2_RATE: 		active_var_ptr = &M2_rate;		break;
		case PID_KP: 		active_var_ptr = &PID_kP;		break;
		case PID_KI: 		active_var_ptr = &PID_kI;		break;
		case PID_KD: 		active_var_ptr = &PID_kD;		break;
		case EEPROM_LOAD: 	loadSettings();
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
			case m1_target_rate: Wire.write((uint8_t*)motor1.targ_rate, 2); break;
			case led: ledToggle(); break;
			case ms: Wire.write((uint8_t*)MS, 4); break;
			case m1_p: Wire.write((uint8_t*)motor1.PID_P, 4); break;
			case m1_i: Wire.write((uint8_t*)motor1.PID_I, 4); break;
			case m1_d: Wire.write((uint8_t*)motor1.PID_D, 4); break;
			
			case m2_scaled_power: Wire.write(motor2.scaled_pwr, 1); break;
			case m2_current_power: Wire.write(motor2.cur_pwr, 1); break;
			case m2_power: Wire.write(motor2.power, 1); break;
			case m2_encoder: Wire.write((uint8_t*)motor2.enc_val, 4); break;
			case m2_rate: Wire.write((uint8_t*)motor2.cur_rate, 4); break;
			case m2_target_rate: Wire.write((uint8_t*)motor2.targ_rate, 2); break;
			case m2_p: Wire.write((uint8_t*)motor2.PID_P, 4); break;
			case m2_i: Wire.write((uint8_t*)motor2.PID_I, 4); break;
			case m2_d: Wire.write((uint8_t*)motor2.PID_D, 4); break;
			
			case pin1s: Wire.write((uint8_t*)&M1, sizeof(M1)); break;
			case pin2s: Wire.write((uint8_t*)&M1, sizeof(M2)); break;
			case pin1H: Wire.write((uint8_t*)&M1, sizeof(M1H)); break;
			case pin1L: Wire.write((uint8_t*)&M1, sizeof(M1L)); break;
			case pin2H: Wire.write((uint8_t*)&M1, sizeof(M2H)); break;
			case pin2L: Wire.write((uint8_t*)&M1, sizeof(M2L)); break;
			
			case read_eeprom: Wire.write(EEPROM.read(SAVED_VALS_ADDRESS)); break;
			
			case 199: Wire.write(*motor1.control & DIRECTION); break;
			case 200: Wire.write(digitalRead(motor1.high_pin->number)); break;
			case 201: Wire.write(digitalRead(motor1.high_pin->number) ^ (*motor1.control & DIRECTION)); break;
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
	if (updated_vars & (1 << M2_CONTROL))	updateMotorControl(&motor2);
	if (updated_vars & (1 << M1_POWER)) 	updateMotor(&motor1);
	if (updated_vars & (1 << M2_POWER)) 	updateMotor(&motor2);
	
	updated_vars = 0;
}


inline void DualMotorDriver::updateMotorControl(Motor *motor)
{
	if (!(*motor->control & SPEED)) setMotorDirection(motor);
	if ((*motor->control & 0x0C) != 12)// If not in RPM mode, reset the PID values and target rate setting
	{
		*motor->PID_P = 0;
		*motor->PID_I = 0;
		*motor->PID_D = 0;
		*motor->targ_rate = 0;
		updateMotor(motor);
	}
	else // If in RPM mode, disable braking and enable the encoder
	{
		*motor->control &= ~BRAKE;
		*motor->control |= ENCODER;
		setMotorDirection(motor);
	}
	
	setTimerB(motor);
}


void DualMotorDriver::updateMotor(Motor *motor)
{
	if (*motor->control & ENCODER)
	{
		updateEncoder(motor);
	}
	
	if (*motor->control & SPEED) 
	{
		if (*motor->control & MODE) { updateMotorRPM(motor);}
		else 
		{ 
			*motor->power ? *motor->scaled_pwr = map(*motor->power, 0, 255, min_power, 255) : *motor->scaled_pwr = 0;
			updateMotorPower(motor);
		}
	}
	else if (*motor->control & MODE)
	{
		*motor->power ? *motor->cur_pwr = map(*motor->power, 0, 255, min_power, 255) : *motor->cur_pwr = 0;
		setMotorPWM(motor);
	}
	else 
	{
		*motor->cur_pwr = *motor->power;
		setMotorPWM(motor);
	}
}


inline void DualMotorDriver::updateMotorRPM(Motor *motor)
{
	float old_rate = *motor->cur_rate;
	//updateEncoder(motor);
	
	*motor->PID_P = PID_kP * *motor->targ_rate;
	*motor->PID_I += PID_kI * (*motor->targ_rate - *motor->cur_rate);
	*motor->PID_D = PID_kD * (old_rate - *motor->cur_rate);
	
	float PID_power = *motor->PID_P + *motor->PID_I + *motor->PID_D;
	
	*motor->cur_pwr = constrain(abs(PID_power), min_power, 255);

	if (PID_power < 0 && !(*motor->control & DIRECTION))
	{
		*motor->control |= DIRECTION;
		setMotorDirection(motor);
	}
	else if (PID_power > 0 && *motor->control & DIRECTION)
	{
		*motor->control &= ~DIRECTION;
		setMotorDirection(motor);
	}
	setMotorPWM(motor);
}


inline void DualMotorDriver::updateMotorPower(Motor *motor)
{
	if (*motor->power) {
		if (!(digitalRead(motor->high_pin->number) ^ (*motor->control & DIRECTION)))// Check to see if motor is turning the same direction as indicated by motor control register.
			//((*motor->high_pin->out_port ^ (*motor->control << motor->high_pin->bit)) & motor->high_pin->bit_mask)// This has potential to be a far cleaner solution, by removing the digitalRead(), but it doesn't work!
		{
			if (*motor->cur_pwr < *motor->scaled_pwr) *motor->cur_pwr = constrain(*motor->cur_pwr + ramping_rate, min_power, *motor->scaled_pwr);
			else if (*motor->cur_pwr > *motor->scaled_pwr) *motor->cur_pwr = constrain(*motor->cur_pwr - ramping_rate, *motor->scaled_pwr, 255);
		}
		else // If motor direction and control direction differ, slow down to minimum power then change direction and continue as normal
		{
			*motor->cur_pwr = constrain(*motor->cur_pwr - ramping_rate, min_power, 255);
			if (*motor->cur_pwr == min_power) setMotorDirection(motor);
		}
	}
	else
	{
		*motor->cur_pwr = 0;
	}
	setMotorPWM(motor);
}


inline void DualMotorDriver::updateEncoder(Motor *motor)
{	
	*motor->cur_rate = ((float)(*motor->enc_val - motor->old_enc) / TICKS_PER_ROT) * REFRESH_FREQ * 60;
	motor->old_enc = *motor->enc_val;
}


// More efficient analogWrite for motor control pins
inline void DualMotorDriver::setMotorPWM(Motor *motor)
{
	switch (*motor->cur_pwr)
	{
		case 0: 	TCCR0A &= ~motor->COM0x; setMotorBraking(motor);				break;
		case 255:	TCCR0A &= ~motor->COM0x; sbi(PORTD, motor->speed_pin->number);	break;
		default: 	TCCR0A |= motor->COM0x;  *motor->OCR0x = *motor->cur_pwr;		break;
	}
}

// More efficent digitalWrite for just the motor direction/braking pins
inline void DualMotorDriver::setMotorDirection(Motor *motor)
{
	if (~(*motor->control & BRAKE))
	{
		if (*motor->control & DIRECTION)
		{
			*motor->high_pin->out_port |= motor->high_pin->bit_mask;
			*motor->low_pin->out_port &= ~motor->low_pin->bit_mask;
		}
		else
		{
			*motor->high_pin->out_port &= ~motor->high_pin->bit_mask;
			*motor->low_pin->out_port |= motor->low_pin->bit_mask;
		}
	}
}

// More efficent digitalWrite for just the motor direction/braking pins
inline void DualMotorDriver::setMotorBraking(Motor *motor)
{
	if (*motor->control & BRAKE)
	{
		//PORTD |= (1 << motor->high_pin) | (1 << motor->speed_pin);
		//digitalWrite(motor->low_pin, HIGH);
		*motor->speed_pin->out_port |= motor->speed_pin->bit_mask;
		*motor->high_pin->out_port |= motor->high_pin->bit_mask;
		*motor->low_pin->out_port |= motor->low_pin->bit_mask;
	}
	else
	{
		//cbi(PORTD, motor->speed_pin);
		*motor->speed_pin->out_port &= ~motor->speed_pin->bit_mask;
		setMotorDirection(motor);
	}
}

// Enables and disables the interrupts that control motor and encoder updates
inline void DualMotorDriver::setTimerB(Motor *motor)
{
	if (*motor->control & (SPEED | ENCODER))// Enable the interrupt routine that updates the given motor
	{
		TCCR2B = 0x00;			// Disbale Timer2 while we set it up
		TIMSK2 |= motor->speed_pin->TIMSK2_mask;
		TCCR2B = TIMER2B_MODE | TIMER2_PRESCALER;// Re-enable Timer2
	}
	else // Disable the interrupts that control motor updates if they are unnecessary
	{
		TCCR2B = 0x00;			// Disbale Timer2 while we set it up
		TIMSK2 &= ~motor->speed_pin->TIMSK2_mask;
		TCCR2B = TIMER2B_MODE | TIMER2_PRESCALER;// Re-enable Timer2
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
	*var = ((int16_t)Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void DualMotorDriver::wireToVar(int32_t *var)
{
	*var = ((int32_t)Wire.read() << 24) | ((int32_t)Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
}

// Takes a pointer to a variable and reads a new value into it from I2C
void DualMotorDriver::wireToVar(float *var)
{
	data_union.bytes[0] = Wire.read();
	data_union.bytes[1] = Wire.read();
	data_union.bytes[2] = Wire.read();
	data_union.bytes[3] = Wire.read();
	//*var = (Wire.read() << 24) | (Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
	*var = data_union.float32;
}
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
void readEncoder1()
{
	PINC & 0x01 ? MotorDriver.M1_encoder++ : MotorDriver.M1_encoder--;
}

void readEncoder2()
{
	PINC & 0x02 ? MotorDriver.M2_encoder-- : MotorDriver.M2_encoder++;
}

void delayMillis(unsigned long time)
{
	short i;
	uint32_t start = MS;
	while (MS - start < time)
	{
		i++;
	}
	return;
}

ISR(WDT_vect)
{
	sbi(PORTB, 4);
}

volatile unsigned long MS = 0;

ISR(TIMER1_OVF_vect)
{
	MS++;
	__asm__ __volatile__ ("wdr");
}

ISR(TIMER2_COMPA_vect)
{
	// Motor 1 updates will go here
	MotorDriver.updateMotor(&MotorDriver.motor1);
}

ISR(TIMER2_COMPB_vect)
{
	// Motor 2 updates will go here
	MotorDriver.updateMotor(&MotorDriver.motor2);
}



#ifdef DEBUG_MOTOR_DRIVER
void ledOn() {	sbi(PORTB, 2);}
void ledOff() {	cbi(PORTB, 2);}
void ledToggle() {	PORTB ^= 0x04;}
#endif