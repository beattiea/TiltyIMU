#include "mk20dx128.h"
#include "core_pins.h"
#include "HardwareSerial.h"

void serial1Event() __attribute__((weak));
void serial1Event() {}

void serialEventRun() {
	serial1Event();
}