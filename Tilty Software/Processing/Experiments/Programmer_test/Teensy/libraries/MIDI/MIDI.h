/*
  MIDI.h - Library for Arduino MIDI I/O communications.
  Created by Francois Best, January 2, 2009.
  Released into the public domain.
  Version 2.6: Minor changes by Paul Stoffregen, February 2011
*/

#ifndef MIDI_h
#define MIDI_h


#include <inttypes.h> 

/*! The basic baudrate for MIDI communications. */
#define MIDI_rate 31250
#define MIDI_BAUDRATE 31250
/*! Message type Note Off (equivalent to a NoteOn with null velocity)*/
#define NoteOff 0
/*! Message type Note On			*/
#define NoteOn 1
/*! Message type AfterTouch Poly	*/
#define ATPoly 2
#define AfterTouchPoly 2
/*! Message type Control Change		*/
#define CC 3
#define ControlChange 3
/*! Message type Program Change		*/
#define PC 4
#define ProgramChange 4
/*! Message type AfterTouch Channel	*/
#define ATCanal 5
#define AfterTouchChannel 5
/*! Message type Pitch Bend			*/
#define	PitchBend 6
/*! Message type System Exclusive 	*/
#define SysEx 7
#define SystemExclusive 7

/*#define MIDI_THRU_ON 128
#define MIDI_OPTO_EXT 64
#define MIDI_OPTO_ON 32*/

#define MIDI_FILTER_OFF			0
#define MIDI_FILTER_FULL		1
#define MIDI_FILTER_CANAL		2
#define MIDI_FILTER_ANTICANAL	3

#define MIDI_CHANNEL_OMNI 0
#define MIDI_CHANNEL_OFF 17


#define MIDI_SYSEX_ARRAY_SIZE	256

#define MANUFACTURER_ID_H	0x7D	// Non-Commercial

/*! Type definition for practical use (because "unsigned char" is a bit long to write.. )*/
typedef uint8_t byte;

/*! This structure contains decoded data of a MIDI message read from the serial port with read() or thru(). \n */
struct midimsg {
	/*! The MIDI channel on which the message was recieved. \n Value goes from 1 to 16. */
	byte channel; 
	/*! The type of the message (see the define section for types reference) */
	byte type;
	/*! The first data byte.\n Value goes from 0 to 127.\n If the message is SysEx, this byte contains the array length. */
	byte data1;
	/*! The second data byte. If the message is only 2 bytes long, this one is null.\n Value goes from 0 to 127. */
	byte data2;
	/*! System Exclusive dedicated byte array. \n Array length is stocked in data1. */
	byte sysex_array[MIDI_SYSEX_ARRAY_SIZE];
	/*! This boolean indicates if the message is valid or not. There is no channel consideration here, validity means the message respects the MIDI norm. */
	bool OK;
};


class MIDI_Class {
public:
	MIDI_Class(); // Constructeurs
	~MIDI_Class(); // Destructeur
	
	void begin(byte inChannel = 1);
	
	// Input methods
	bool read();
	bool read(byte channel);

	// Output methods
	void send(byte type, byte param1, byte param2, byte canal);
	
	void sendNoteOn(byte NoteNumber,byte Velocity,byte Channel);
	void sendNoteOff(byte NoteNumber,byte Velocity,byte Channel);
	void sendProgramChange(byte ProgramNumber,byte Channel);
	void sendControlChange(byte ControlNumber, byte ControlValue,byte Channel);
	void sendPitchBend(int PitchValue,byte Channel);
	void sendPolyPressure(byte NoteNumber,byte Pressure,byte Channel);
	void sendAfterTouch(byte Pressure,byte Channel);
	void sendSysEx(byte length, byte * array);
	
	// Thru
	void turnThruOn();
	void turnThruOff();
	void turnThru(bool state);
	
	// Getters
	byte getType();
	byte getChannel();
	byte getData1();
	byte getData2();
	byte * getSysExArray();
	bool check();
	byte getInputChannel() { return mInputChannel; }
	byte getFilterMode() { return mFilterMode; }
	bool getThruState() { return mThruActivated; }
	
	// Setters
	void setDeviceID(byte sysID);
	void delMsg();
	void delSysEx();
	void setInputChannel(byte channel);
	void setFilter(byte filter);
	
	
private:
	byte genctrl(byte canal, byte type);
	void filter(byte channel);
	void setType(byte type);
	void setChannel(byte channel);
	void setData1(byte data);
	void setData2(byte data);
	void setStatus(bool status);
	bool parse(byte channel);
	
	// Class access only
	byte mInputChannel;
	byte mFilterMode;
	byte sysex_ID;
	byte mRunningStatus_TX;
	byte mRunningStatus_RX;
	midimsg mMessage;
	bool mThruActivated;
};


extern MIDI_Class MIDI;

#endif // MIDI_h
