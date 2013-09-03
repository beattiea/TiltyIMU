/*
This file contains the flash memory structure used by the TiltyIMU control boards. Each #define is the address of
that specific piece of data. Each address is the previous address plus the size of the variable for the previous address.
*/

#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#define BOARD_TYPE 0
	#define TILTY_DUO 0
	#define TILTY_QUAD 1
	#define TILTY_OMNI 2

#define VOLTAGE_SENSE_PIN 14

#endif