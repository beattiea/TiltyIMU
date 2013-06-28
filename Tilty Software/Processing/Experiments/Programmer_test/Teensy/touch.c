#include "core_pins.h"
//#include "HardwareSerial.h"

static const uint8_t pin2tsi[] = {
//0    1    2    3    4    5    6    7    8    9
  9,  10, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255,  13,   0,   6,   8,   7,
255, 255,  14,  15, 255,  12, 255, 255, 255, 255,
255, 255,  11,   5
};

// These settings give approx 0.02 pF sensitivity and 1200 pF range
// Lower current, higher number of scans, and higher prescaler
// increase sensitivity, but the trade-off is longer measurement
// time and decreased range.
#define CURRENT   2 // 0 to 15 - current to use, value is 2*(current+1)
#define NSCAN     9 // number of times to scan, 0 to 31, value is nscan+1
#define PRESCALE  2 // prescaler, 0 to 7 - value is 2^(prescaler+1)


// output is approx pF * 50
// time to measure 33 pF is approx 0.25 ms
// time to measure 1000 pF is approx 4.5 ms

int touchRead(uint8_t pin)
{
	uint32_t ch;

	if (pin >= NUM_DIGITAL_PINS) return 0;
	ch = pin2tsi[pin];
	if (ch == 255) return 0;

	*portConfigRegister(pin) = PORT_PCR_MUX(0);
	SIM_SCGC5 |= SIM_SCGC5_TSI;
	TSI0_GENCS = 0;
	TSI0_PEN = (1 << ch);
	TSI0_SCANC = TSI_SCANC_REFCHRG(3) | TSI_SCANC_EXTCHRG(CURRENT);
	TSI0_GENCS = TSI_GENCS_NSCN(NSCAN) | TSI_GENCS_PS(PRESCALE) | TSI_GENCS_TSIEN | TSI_GENCS_SWTS;
	delayMicroseconds(10);
	while (TSI0_GENCS & TSI_GENCS_SCNIP) ; // wait
	delayMicroseconds(1);
	return *((volatile uint16_t *)(&TSI0_CNTR1) + ch);
}




