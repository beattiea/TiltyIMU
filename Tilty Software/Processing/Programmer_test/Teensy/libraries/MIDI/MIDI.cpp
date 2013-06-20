/*
 MIDI.cpp - Library for Arduino MIDI I/O communications.
 Created by Francois Best, January 2, 2009.
 Released into the public domain.
 Last update:	10/06/2009
 Version 2.6: Minor changes by Paul Stoffregen, February 2011
*/ 

#include <stdlib.h>
#include "MIDI.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "HardwareSerial.h"
#define Channel_Refused 0

/*! to ATmega 644p users: this library uses the serial port #1 for MIDI. */
#if defined(__AVR_ATmega644P__)
#undef UART
#define UART Serial1
/*! to Teensy/Teensy++ users: this library uses the Tx & Rx pins (the USB is not used) */
#elif defined(CORE_TEENSY)
#undef UART
HardwareSerial UART = HardwareSerial();
#else
/*! to any other ATmega users: this library uses the serial port #0 for MIDI (if you have more than one UART).*/
#undef UART
#define UART Serial
#endif


/*! Main instance (the class comes pre-instantiated). */
MIDI_Class MIDI;


/*! Default constructor for MIDI_Class. */
MIDI_Class::MIDI_Class() { }
/*! Default destructor for MIDI_Class.\n
	This is not really useful for the Arduino, as it is never called...
 */
MIDI_Class::~MIDI_Class() { }


/*! Call the begin method in the setup() function of the Arduino.
	All parameters are set to their default values:
	- Full thru mirroring
	- Input channel set to 1 if no value specified
 */
void MIDI_Class::begin(byte inChannel) {
	// All default values loaded
	UART.begin(MIDI_rate);				
	delMsg();
	sysex_ID = MANUFACTURER_ID_H;						// Default ID = non commercial
	mInputChannel = inChannel;
	mThruActivated = true;
	mFilterMode = MIDI_FILTER_FULL;
	mRunningStatus_TX = Channel_Refused;
	mRunningStatus_RX = Channel_Refused;
	return;
}

/*! Internal method, don't care about this one.. \n It generates a status byte over a channel and a type, by bitshifting. */
byte MIDI_Class::genctrl(byte canal, byte type) {
	byte result = 128;
	result += ((type & 0x07)<<4) & 0x70;
	result += ((canal-1) & 0x0F);
	return result;
}


/*! Generate and send a custom MIDI mMessage.
	\param type		The message type (see type defines for reference)
	\param data1	The first data byte
	\param data2	The second data byte (if the message contains only 1 data byte, set this one to 0)
	\param channel	The output channel on which the message will be sent
 */
void MIDI_Class::send(byte type, byte data1, byte data2, byte channel) {
	//if (channel > 16) return; // Not cool, but handled by MIDI_CHANNEL_OFF
	data1 &= 0x7F;
	data2 &= 0x7F;
	if (channel >= MIDI_CHANNEL_OFF) {
		mRunningStatus_TX = Channel_Refused;
		return; // Don't send anything
	}
	if (mRunningStatus_TX == genctrl(channel,type)) {
		// Send only data bytes
		if (type == PC || type == ATCanal) {
			UART.write(data1);
		}
		else if (type == SysEx) {
			// Use sendSysEx...
		}
		else {
			UART.write(data1);
			UART.write(data2);
		}
	}
	else {
		// New message
		if (type == PC || type == ATCanal) {
			UART.write(genctrl(channel,type));
			UART.write(data1);
		}
		else if (type == SysEx) {
			UART.print(genctrl(channel,type));
		}
		else {
			UART.write(genctrl(channel,type));
			UART.write(data1);
			UART.write(data2);
		}
		mRunningStatus_TX = genctrl(channel,type);
	}
	return;
}

/*! Send a Note On message */
void MIDI_Class::sendNoteOn(byte NoteNumber,byte Velocity,byte Channel) { send(NoteOn,NoteNumber,Velocity,Channel); }
/*! Send a Note Off message (a real Note Off, not a Note On with null velocity) */
void MIDI_Class::sendNoteOff(byte NoteNumber,byte Velocity,byte Channel) { send(NoteOff,NoteNumber,Velocity,Channel); }
/*! Send a Program Change message */
void MIDI_Class::sendProgramChange(byte ProgramNumber,byte Channel) { send(PC,ProgramNumber,0,Channel); }
/*! Send a Control Change message */
void MIDI_Class::sendControlChange(byte ControlNumber, byte ControlValue,byte Channel) { send(CC,ControlNumber,ControlValue,Channel); }
/*! Polyphonic AfterTouch (carries the information of pressure of the given key/note) */
void MIDI_Class::sendPolyPressure(byte NoteNumber,byte Pressure,byte Channel) { send(ATPoly,NoteNumber,Pressure,Channel); }
/*! Monophonic AfterTouch */
void MIDI_Class::sendAfterTouch(byte Pressure,byte Channel) { send(ATCanal,Pressure,0,Channel); }
/*! Generate and send a System Exclusive frame.
	\param length	The size of the array to send
	\param array	The byte array containing the data to send\n
	Don't put F0 or F7 (start & stop SysEx codes), but put destination device's Manufacturer's ID and/or Device ID in the buffer array.
 */
void MIDI_Class::sendSysEx(byte length, byte * array) {
	UART.write(0xF0);
	//for (byte i=0;i<length;i++) UART.print(array[i],BYTE);
	UART.write(array, length);
	UART.write(0xF7);
}
/* Getters */
/*! Getter method: access to the message type stored in the structure. */
byte MIDI_Class::getType() { return mMessage.type; }
/*! Getter method: access to the channel of the message stored in the structure. */
byte MIDI_Class::getChannel() { return mMessage.channel; }
/*! Getter method: access to the first data byte of the message stored in the structure. \n If the message is SysEx, the length of the array is stocked there. */
byte MIDI_Class::getData1() { return mMessage.data1; }
/*! Getter method: access to the second data byte of the message stored in the structure. */
byte MIDI_Class::getData2() { return mMessage.data2; }
/*! Getter method: access to the System Exclusive byte array. Array length is stocked in Data1. */
byte * MIDI_Class::getSysExArray() { return mMessage.sysex_array; }
/*! Check if a valid message is stored in the structure. */
bool MIDI_Class::check() { return mMessage.OK; }

/* Setters */
/*! Use this method to delete the message stored in the structure. */
void MIDI_Class::delMsg() {
	setChannel(0);
	setType(0);
	setData1(0);
	setData2(0);
	setStatus(false);
	delSysEx();
	return;
}
void MIDI_Class::delSysEx() { 
	for (int i=0;i<MIDI_SYSEX_ARRAY_SIZE;i++) mMessage.sysex_array[i] = 0;
}
/*! Set the System Exclusive Device ID (for listening to SysEx messages) */
void MIDI_Class::setDeviceID(byte sysID) { sysex_ID = sysID; }
/*! Set the value for the input MIDI channel 
 \param channel the channel value. Valid values are 1 to 16, 
 MIDI_CHANNEL_OMNI if you want to listen all channels, and MIDI_CHANNEL_OFF to disable MIDI input.
 */
void MIDI_Class::setInputChannel(byte channel) { mInputChannel = channel; }
/*! Set the filter for thru mirroring
 \param filter a filter mode:
 - MIDI_FILTER_FULL			Every incoming message is mirrored.
 - MIDI_FILTER_CANAL		Every message matching the input channel is mirrored.
 - MIDI_FILTER_ANTICANAL	Every message non-matching the input channel is mirrored.
 */
void MIDI_Class::setFilter(byte filter) { mFilterMode = filter; }

/*! Setter method: turn message mirroring on. */
void MIDI_Class::turnThruOn() { mThruActivated = true; }
/*! Setter method: turn message mirroring off. */
void MIDI_Class::turnThruOff() { mThruActivated = false; }
/*! Setter method: set message mirroring to the specified value. */
void MIDI_Class::turnThru(bool val) { mThruActivated = val; }


void MIDI_Class::setType(byte type) { mMessage.type = type; }
void MIDI_Class::setChannel(byte channel) { mMessage.channel = channel; }
void MIDI_Class::setData1(byte D) { mMessage.data1 = D; }
void MIDI_Class::setData2(byte D) { mMessage.data2 = D; }
void MIDI_Class::setStatus(bool ok) { mMessage.OK = ok; }


bool MIDI_Class::parse(byte inChannelFilter) {
	if (inChannelFilter >= MIDI_CHANNEL_OFF) return false;	// MIDI input disabled
	byte tStatus=0,tChannel=0,tType=0,tData1=0,tData2=0;
	delMsg();	// Cleanup
	if (UART.available() == 128) { UART.flush(); };	
	if (UART.available() > 0) { // do we have something to read?
		tStatus = UART.read();
		if (tStatus > 127) {
			tChannel = (tStatus&0x0F)+1;
			tType = ((tStatus&0x70)>>4)&0x07;
			if (tChannel == inChannelFilter || inChannelFilter == MIDI_CHANNEL_OMNI || tType == SysEx) {
				if (tType == PC || tType == ATCanal) {
					// 2 bytes long message
					if(UART.available() > 0) {
						tData1 = UART.read();
						if (tData1 < 128) {
							// Saving to struct
							setChannel(tChannel);
							setType(tType);
							setData1(tData1);
							setData2(0);
							setStatus(true);
							mRunningStatus_RX = tStatus;
						}
					}
					else {
						// Data on next turn
						mRunningStatus_RX = tStatus;
						return false;
					}
				}
				else if (tType == SysEx) { // Handle all system messages
					if (tStatus == 0xF0) {
						mMessage.sysex_array[0] = tStatus;
						unsigned length;
						for (length=1;length<MIDI_SYSEX_ARRAY_SIZE;length++) {
							while(!UART.available()) {};
							tData1 = UART.read();
							mMessage.sysex_array[length] = tData1;
							if (tData1 == 0xF7) {
								length++;
								break;
							}
						}
						setType(SysEx);
						setData1(length);
						setStatus(true);
						mRunningStatus_RX = Channel_Refused; // No running status with SysEx
					} else {
						// ignore the other system messages
						return false;
					}
				}
				else {
					// 3 bytes message
					if(UART.available() > 0) {
						tData1 = UART.read();
						if (tData1 < 128) {
							// Wait for the third byte
							while(!UART.available()) {};
							if(UART.available() > 0) {
								tData2 = UART.read();
								if (tData2 < 128) {
									// Saving
									setChannel(tChannel);
									setType(tType);
									setData1(tData1);
									setData2(tData2);
									setStatus(true);
									mRunningStatus_RX = tStatus;
								}
							}
						}
						else {
							// We were expecting for a data byte
							return false;
						}
					}
					else {
						// Data on next turn
						mRunningStatus_RX = tStatus;
						return false;
					}
				}
			}
			else {
				// Channel refused
				mRunningStatus_RX = Channel_Refused;
				return false;
			}
		}
		else {
			// Running status?
			// data matching the previous control byte
			if (mRunningStatus_RX == Channel_Refused) {
				return false;
			}
			else {
				tChannel = (mRunningStatus_RX&0x0F)+1;
				tType = ((mRunningStatus_RX&0x70)>>4)&0x07;
				if (tType == PC || tType == ATCanal) {
					// Saving	
					setChannel(tChannel);
					setType(tType);
					setData1(tStatus);
					setData2(0);
					setStatus(true);
				}
				else if (tType == SysEx) {
					// Normally not possible (as we don't recognize SysEx as a Running Status
					mRunningStatus_RX = Channel_Refused;
				}
				else {
					// 3 bytes
					while(!UART.available()) {};
					if(UART.available() > 0) {
						tData2 = UART.read();
						if (tData2 < 128) {
							// Saving
							setChannel(tChannel);
							setType(tType);
							setData1(tStatus);
							setData2(tData2);
							setStatus(true);
						}
					}
				}
			}
		}
	}
	else return false;
	return check();
}


/*! Read a MIDI message from the serial port using the main input channel (see setInputChannel() for reference). \n
 Returned value: true if any valid message has been stored in the structure, false if not.
 A valid message is a message that matches the input channel. \n\n
 If the Thru is enabled and the messages matches the filter, it is sent back on the MIDI output.
 */
bool MIDI_Class::read() {
	return read(mInputChannel);
}
/*! Reading/mirroring method, the same as read() with a given input channel to read on. */
bool MIDI_Class::read(byte channel) {
	if (parse(MIDI_CHANNEL_OMNI)) {
		if (channel >= MIDI_CHANNEL_OFF && getType() != SysEx) { // Input disabled
			delMsg(); 
			return false; 
		} 
		if (mThruActivated) filter(channel); // Filter and send (if thru enabled)
		if (getChannel() == channel || channel == MIDI_CHANNEL_OMNI || getType() == SysEx)	return true;
		else { 
			delMsg(); 
			return false; 
		}
	} else {
		return false;
	}
}

void MIDI_Class::filter(byte channel) { // Mirroring filter
	// MIDI message validity already checked by thru
	switch (mFilterMode) {
		case MIDI_FILTER_FULL:
			// All pass
			send(getType(),getData1(),getData2(),getChannel());
			break;
		case MIDI_FILTER_CANAL:
			// Same channel
			if (channel >= MIDI_CHANNEL_OFF) return;
			if (getChannel() == channel || channel == MIDI_CHANNEL_OMNI) send(getType(),getData1(),getData2(),getChannel());
			break;
		case MIDI_FILTER_ANTICANAL:
			// Different channel
			if (channel == MIDI_CHANNEL_OMNI) return;
			if (getChannel() != channel || channel >= MIDI_CHANNEL_OFF) send(getType(),getData1(),getData2(),getChannel());
			break;
		default:
			break;
	}
	return;
}
	





