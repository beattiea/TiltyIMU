#ifndef _avr_emulation_h_
#define _avr_emulation_h_

#include "mk20dx128.h"
#include "core_pins.h"
#include "pins_arduino.h"

#ifdef __cplusplus

class PORTDemulation
{
public:
	inline PORTDemulation & operator = (int val) __attribute__((always_inline)) {
		digitalWriteFast(0, (val & (1<<0)));
		digitalWriteFast(1, (val & (1<<1)));
		digitalWriteFast(2, (val & (1<<2)));
		digitalWriteFast(3, (val & (1<<3)));
		digitalWriteFast(4, (val & (1<<4)));
		digitalWriteFast(5, (val & (1<<5)));
		digitalWriteFast(6, (val & (1<<6)));
		digitalWriteFast(7, (val & (1<<7)));
		return *this;
	}
	inline PORTDemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) digitalWriteFast(0, HIGH);
		if (val & (1<<1)) digitalWriteFast(1, HIGH);
		if (val & (1<<2)) digitalWriteFast(2, HIGH);
		if (val & (1<<3)) digitalWriteFast(3, HIGH);
		if (val & (1<<4)) digitalWriteFast(4, HIGH);
		if (val & (1<<5)) digitalWriteFast(5, HIGH);
		if (val & (1<<6)) digitalWriteFast(6, HIGH);
		if (val & (1<<7)) digitalWriteFast(7, HIGH);
		return *this;
	}
	inline PORTDemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) digitalWriteFast(0, LOW);
		if (!(val & (1<<1))) digitalWriteFast(1, LOW);
		if (!(val & (1<<2))) digitalWriteFast(2, LOW);
		if (!(val & (1<<3))) digitalWriteFast(3, LOW);
		if (!(val & (1<<4))) digitalWriteFast(4, LOW);
		if (!(val & (1<<5))) digitalWriteFast(5, LOW);
		if (!(val & (1<<6))) digitalWriteFast(6, LOW);
		if (!(val & (1<<7))) digitalWriteFast(7, LOW);
		return *this;
	}
};
extern PORTDemulation PORTD;

class PINDemulation
{
public:
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		if ((val & (1<<0)) && digitalReadFast(0)) ret |= (1<<0);
		if ((val & (1<<1)) && digitalReadFast(1)) ret |= (1<<1);
		if ((val & (1<<2)) && digitalReadFast(2)) ret |= (1<<2);
		if ((val & (1<<3)) && digitalReadFast(3)) ret |= (1<<3);
		if ((val & (1<<4)) && digitalReadFast(4)) ret |= (1<<4);
		if ((val & (1<<5)) && digitalReadFast(5)) ret |= (1<<5);
		if ((val & (1<<6)) && digitalReadFast(6)) ret |= (1<<6);
		if ((val & (1<<7)) && digitalReadFast(7)) ret |= (1<<7);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		if (digitalReadFast(0)) ret |= (1<<0);
		if (digitalReadFast(1)) ret |= (1<<1);
		if (digitalReadFast(2)) ret |= (1<<2);
		if (digitalReadFast(3)) ret |= (1<<3);
		if (digitalReadFast(4)) ret |= (1<<4);
		if (digitalReadFast(5)) ret |= (1<<5);
		if (digitalReadFast(6)) ret |= (1<<6);
		if (digitalReadFast(7)) ret |= (1<<7);
		return ret;
	}
};
extern PINDemulation PIND;

class PORTBemulation
{
public:
	inline PORTBemulation & operator = (int val) __attribute__((always_inline)) {
		digitalWriteFast(8, (val & (1<<0)));
		digitalWriteFast(9, (val & (1<<1)));
		digitalWriteFast(10, (val & (1<<2)));
		digitalWriteFast(11, (val & (1<<3)));
		digitalWriteFast(12, (val & (1<<4)));
		digitalWriteFast(13, (val & (1<<5)));
		return *this;
	}
	inline PORTBemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) digitalWriteFast(8, HIGH);
		if (val & (1<<1)) digitalWriteFast(9, HIGH);
		if (val & (1<<2)) digitalWriteFast(10, HIGH);
		if (val & (1<<3)) digitalWriteFast(11, HIGH);
		if (val & (1<<4)) digitalWriteFast(12, HIGH);
		if (val & (1<<5)) digitalWriteFast(13, HIGH);
		return *this;
	}
	inline PORTBemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) digitalWriteFast(8, LOW);
		if (!(val & (1<<1))) digitalWriteFast(9, LOW);
		if (!(val & (1<<2))) digitalWriteFast(10, LOW);
		if (!(val & (1<<3))) digitalWriteFast(11, LOW);
		if (!(val & (1<<4))) digitalWriteFast(12, LOW);
		if (!(val & (1<<5))) digitalWriteFast(13, LOW);
		return *this;
	}
};
extern PORTBemulation PORTB;

class PINBemulation
{
public:
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		if ((val & (1<<0)) && digitalReadFast(8)) ret |= (1<<0);
		if ((val & (1<<1)) && digitalReadFast(9)) ret |= (1<<1);
		if ((val & (1<<2)) && digitalReadFast(10)) ret |= (1<<2);
		if ((val & (1<<3)) && digitalReadFast(11)) ret |= (1<<3);
		if ((val & (1<<4)) && digitalReadFast(12)) ret |= (1<<4);
		if ((val & (1<<5)) && digitalReadFast(13)) ret |= (1<<5);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		if (digitalReadFast(8)) ret |= (1<<0);
		if (digitalReadFast(9)) ret |= (1<<1);
		if (digitalReadFast(10)) ret |= (1<<2);
		if (digitalReadFast(11)) ret |= (1<<3);
		if (digitalReadFast(12)) ret |= (1<<4);
		if (digitalReadFast(13)) ret |= (1<<5);
		return ret;
	}
};
extern PINBemulation PINB;

class PORTCemulation
{
public:
	inline PORTCemulation & operator = (int val) __attribute__((always_inline)) {
		digitalWriteFast(14, (val & (1<<0)));
		digitalWriteFast(15, (val & (1<<1)));
		digitalWriteFast(16, (val & (1<<2)));
		digitalWriteFast(17, (val & (1<<3)));
		digitalWriteFast(18, (val & (1<<4)));
		digitalWriteFast(19, (val & (1<<5)));
		return *this;
	}
	inline PORTCemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) digitalWriteFast(14, HIGH);
		if (val & (1<<1)) digitalWriteFast(15, HIGH);
		if (val & (1<<2)) digitalWriteFast(16, HIGH);
		if (val & (1<<3)) digitalWriteFast(17, HIGH);
		if (val & (1<<4)) digitalWriteFast(18, HIGH);
		if (val & (1<<5)) digitalWriteFast(19, HIGH);
		return *this;
	}
	inline PORTCemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) digitalWriteFast(14, LOW);
		if (!(val & (1<<1))) digitalWriteFast(15, LOW);
		if (!(val & (1<<2))) digitalWriteFast(16, LOW);
		if (!(val & (1<<3))) digitalWriteFast(17, LOW);
		if (!(val & (1<<4))) digitalWriteFast(18, LOW);
		if (!(val & (1<<5))) digitalWriteFast(19, LOW);
		return *this;
	}
};
extern PORTCemulation PORTC;

class PINCemulation
{
public:
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		if ((val & (1<<0)) && digitalReadFast(8)) ret |= (1<<0);
		if ((val & (1<<1)) && digitalReadFast(9)) ret |= (1<<1);
		if ((val & (1<<2)) && digitalReadFast(10)) ret |= (1<<2);
		if ((val & (1<<3)) && digitalReadFast(11)) ret |= (1<<3);
		if ((val & (1<<4)) && digitalReadFast(12)) ret |= (1<<4);
		if ((val & (1<<5)) && digitalReadFast(13)) ret |= (1<<5);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		if (digitalReadFast(8)) ret |= (1<<0);
		if (digitalReadFast(9)) ret |= (1<<1);
		if (digitalReadFast(10)) ret |= (1<<2);
		if (digitalReadFast(11)) ret |= (1<<3);
		if (digitalReadFast(12)) ret |= (1<<4);
		if (digitalReadFast(13)) ret |= (1<<5);
		return ret;
	}
};
extern PINCemulation PINC;


#if 0
extern "C" {
void serial_print(const char *p);
void serial_phex(uint32_t n);
void serial_phex16(uint32_t n);
void serial_phex32(uint32_t n);
}
#endif


// SPI Control Register ­ SPCR
#define SPIE	7	// SPI Interrupt Enable - not supported
#define SPE	6	// SPI Enable
#define DORD	5	// DORD: Data Order
#define MSTR	4	// MSTR: Master/Slave Select
#define CPOL	3	// CPOL: Clock Polarity
#define CPHA	2	// CPHA: Clock Phase
#define SPR1	1	// Clock: 3 = 125 kHz, 2 = 250 kHz, 1 = 1 MHz, 0->4 MHz
#define SPR0	0
// SPI Status Register ­ SPSR
#define SPIF	7	// SPIF: SPI Interrupt Flag
#define WCOL	6	// WCOL: Write COLlision Flag - not implemented
#define SPI2X	0	// SPI2X: Double SPI Speed Bit
// SPI Data Register ­ SPDR

class SPCRemulation;
class SPSRemulation;
class SPDRemulation;

class SPCRemulation
{
public:
	inline SPCRemulation & operator = (int val) __attribute__((always_inline)) {
		uint32_t ctar, mcr, sim6;
		//serial_print("SPCR=");
		//serial_phex(val);
		//serial_print("\n");
		sim6 = SIM_SCGC6;
		if (!(sim6 & SIM_SCGC6_SPI0)) {
			//serial_print("init1\n");
			SIM_SCGC6 = sim6 | SIM_SCGC6_SPI0;
			SPI0_CTAR0 = SPI_CTAR_FMSZ(7) | SPI_CTAR_PBR(1) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
		}
		if (!(val & (1<<SPE))) {
			SPI0_MCR |= SPI_MCR_MDIS; // TODO: use bitband for atomic access
		}
		ctar = SPI_CTAR_FMSZ(7) | SPI_CTAR_PBR(1);
		if (val & (1<<DORD))  ctar |= SPI_CTAR_LSBFE;
		if (val & (1<<CPOL))  ctar |= SPI_CTAR_CPOL;
		if (val & (1<<CPHA)) {
			ctar |= SPI_CTAR_CPHA;
			if ((val & 3) == 0) {
				ctar |= SPI_CTAR_BR(1) | SPI_CTAR_ASC(1);
			} else if ((val & 3) == 1) {
				ctar |= SPI_CTAR_BR(4) | SPI_CTAR_ASC(4);
			} else if ((val & 3) == 2) {
				ctar |= SPI_CTAR_BR(6) | SPI_CTAR_ASC(6);
			} else {
				ctar |= SPI_CTAR_BR(7) | SPI_CTAR_ASC(7);
			}
		} else {
			if ((val & 3) == 0) {
				ctar |= SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
			} else if ((val & 3) == 1) {
				ctar |= SPI_CTAR_BR(4) | SPI_CTAR_CSSCK(4);
			} else if ((val & 3) == 2) {
				ctar |= SPI_CTAR_BR(6) | SPI_CTAR_CSSCK(6);
			} else {
				ctar |= SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(7);
			}
		}
		ctar |= (SPI0_CTAR0 & SPI_CTAR_DBR);
		update_ctar(ctar);
		mcr = SPI_MCR_DCONF(0);
		if (val & (1<<MSTR)) mcr |= SPI_MCR_MSTR;
		if (val & (1<<SPE)) {
			mcr &= ~(SPI_MCR_MDIS | SPI_MCR_HALT);
			SPI0_MCR = mcr;
			enable_pins();
		} else {
			mcr |= (SPI_MCR_MDIS | SPI_MCR_HALT);
			SPI0_MCR = mcr;
			disable_pins();
		}
		//serial_print("MCR:");
		//serial_phex32(SPI0_MCR);
		//serial_print(", CTAR0:");
		//serial_phex32(SPI0_CTAR0);
		//serial_print("\n");
		return *this;
	}
	inline SPCRemulation & operator |= (int val) __attribute__((always_inline)) {
		uint32_t sim6;
		//serial_print("SPCR |= ");
		//serial_phex(val);
		//serial_print("\n");
		sim6 = SIM_SCGC6;
		if (!(sim6 & SIM_SCGC6_SPI0)) {
			//serial_print("init2\n");
			SIM_SCGC6 = sim6 | SIM_SCGC6_SPI0;
			SPI0_CTAR0 = SPI_CTAR_FMSZ(7) | SPI_CTAR_PBR(1) | SPI_CTAR_BR(1);
		}
		if (val & ((1<<DORD)|(1<<CPOL)|(1<<CPHA)|3)) {
			uint32_t ctar = SPI0_CTAR0;
			if (val & (1<<DORD)) ctar |= SPI_CTAR_LSBFE; // TODO: use bitband
			if (val & (1<<CPOL)) ctar |= SPI_CTAR_CPOL;
			if ((val & 3) == 1) {
				// TODO: implement - is this ever really needed
			} else if ((val & 3) == 2) {
				// TODO: implement - is this ever really needed
			} else if ((val & 3) == 3) {
				// TODO: implement - is this ever really needed
			}
			if (val & (1<<CPHA) && !(ctar & SPI_CTAR_CPHA)) {
				ctar |= SPI_CTAR_CPHA;
				// TODO: clear SPI_CTAR_CSSCK, set SPI_CTAR_ASC
			}
			update_ctar(ctar);
		}
		if (val & (1<<MSTR)) SPI0_MCR |= SPI_MCR_MSTR;
		if (val & (1<<SPE)) {
			SPI0_MCR &= ~(SPI_MCR_MDIS | SPI_MCR_HALT);
			enable_pins();
		}
		//serial_print("MCR:");
		//serial_phex32(SPI0_MCR);
		//serial_print(", CTAR0:");
		//serial_phex32(SPI0_CTAR0);
		//serial_print("\n");
		return *this;
	}
	inline SPCRemulation & operator &= (int val) __attribute__((always_inline)) {
		//serial_print("SPCR &= ");
		//serial_phex(val);
		//serial_print("\n");
		SIM_SCGC6 |= SIM_SCGC6_SPI0;
		if (!(val & (1<<SPE))) {
			SPI0_MCR |= (SPI_MCR_MDIS | SPI_MCR_HALT);
			disable_pins();
		}
		if ((val & ((1<<DORD)|(1<<CPOL)|(1<<CPHA)|3)) != ((1<<DORD)|(1<<CPOL)|(1<<CPHA)|3)) {
			uint32_t ctar = SPI0_CTAR0;
			if (!(val & (1<<DORD))) ctar &= ~SPI_CTAR_LSBFE; // TODO: use bitband
			if (!(val & (1<<CPOL))) ctar &= ~SPI_CTAR_CPOL;
			if ((val & 3) == 0) {
				// TODO: implement - is this ever really needed
			} else if ((val & 3) == 1) {
				// TODO: implement - is this ever really needed
			} else if ((val & 3) == 2) {
				// TODO: implement - is this ever really needed
			}
			if (!(val & (1<<CPHA)) && (ctar & SPI_CTAR_CPHA)) {
				ctar &= ~SPI_CTAR_CPHA;
				// TODO: set SPI_CTAR_ASC, clear SPI_CTAR_CSSCK
			}
			update_ctar(ctar);
		}
		if (!(val & (1<<MSTR))) SPI0_MCR &= ~SPI_MCR_MSTR;
		return *this;
	}
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		//serial_print("SPCR & ");
		//serial_phex(val);
		//serial_print("\n");
		if ((val & (1<<DORD)) && (SPI0_CTAR0 & SPI_CTAR_LSBFE)) ret |= (1<<DORD);
		if ((val & (1<<CPOL)) && (SPI0_CTAR0 & SPI_CTAR_CPOL)) ret |= (1<<CPOL);
		if ((val & (1<<CPHA)) && (SPI0_CTAR0 & SPI_CTAR_CPHA)) ret |= (1<<CPHA);
		if ((val & 3) == 3) {
			uint32_t dbr = SPI0_CTAR0 & 15;
			if (dbr <= 1) {
			} else if (dbr <= 4) {
				ret |= (1<<SPR0);
			} else if (dbr <= 6) {
				ret |= (1<<SPR1);
			} else {
				ret |= (1<<SPR1)|(1<<SPR0);
			}
		} else if ((val & 3) == 1) {
			// TODO: implement - is this ever really needed
		} else if ((val & 3) == 2) {
			// TODO: implement - is this ever really needed
		}
		if (val & (1<<SPE) && (!(SPI0_MCR & SPI_MCR_MDIS))) ret |= (1<<SPE);
		if (val & (1<<MSTR) && (SPI0_MCR & SPI_MCR_MSTR)) ret |= (1<<MSTR);
		//serial_print("ret = ");
		//serial_phex(ret);
		//serial_print("\n");
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		if ((SIM_SCGC6 & SIM_SCGC6_SPI0)) {
			int ctar = SPI0_CTAR0;
			if (ctar & SPI_CTAR_LSBFE) ret |= (1<<DORD);
			if (ctar & SPI_CTAR_CPOL) ret |= (1<<CPOL);
			if (ctar & SPI_CTAR_CPHA) ret |= (1<<CPHA);
			ctar &= 15;
			if (ctar <= 1) {
			} else if (ctar <= 4) {
				ret |= (1<<SPR0);
			} else if (ctar <= 6) {
				ret |= (1<<SPR1);
			} else {
				ret |= (1<<SPR1)|(1<<SPR0);
			}
			int mcr = SPI0_MCR;
			if (!(mcr & SPI_MCR_MDIS)) ret |= (1<<SPE);
			if (mcr & SPI_MCR_MSTR) ret |= (1<<MSTR);
		}
		return ret;
	}
	friend class SPSRemulation;
private:
	static inline void update_ctar(uint32_t ctar) __attribute__((always_inline)) {
		if (SPI0_CTAR0 == ctar) return;
		uint32_t mcr = SPI0_MCR;
		if (mcr & SPI_MCR_MDIS) {
			SPI0_CTAR0 = ctar;
		} else {
			SPI0_MCR = mcr | SPI_MCR_MDIS | SPI_MCR_HALT;
			SPI0_CTAR0 = ctar;
			SPI0_MCR = mcr;
		}
	}
	inline void enable_pins(void) __attribute__((always_inline)) {
		//serial_print("enable_pins\n");
		CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);
		CORE_PIN12_CONFIG = PORT_PCR_MUX(2);
		CORE_PIN13_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);
	}
	inline void disable_pins(void) __attribute__((always_inline)) {
		//serial_print("disable_pins\n");
		CORE_PIN11_CONFIG = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		CORE_PIN12_CONFIG = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		CORE_PIN13_CONFIG = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	}
};
extern SPCRemulation SPCR;

class SPSRemulation
{
public:
	inline SPSRemulation & operator = (int val) __attribute__((always_inline)) {
		//serial_print("SPSR=");
		//serial_phex(val);
		//serial_print("\n");
		uint32_t ctar = SPI0_CTAR0;
		if (val & (1<<SPI2X)) {
			ctar |= SPI_CTAR_DBR;
		} else {
			ctar &= ~SPI_CTAR_DBR;
		}
		SPCRemulation::update_ctar(ctar);
		//serial_print("MCR:");
		//serial_phex32(SPI0_MCR);
		//serial_print(", CTAR0:");
		//serial_phex32(SPI0_CTAR0);
		//serial_print("\n");
		return *this;
	}
	inline SPSRemulation & operator |= (int val) __attribute__((always_inline)) {
		//serial_print("SPSR |= ");
		//serial_phex(val);
		//serial_print("\n");
		if (val & (1<<SPI2X)) SPCRemulation::update_ctar(SPI0_CTAR0 |= SPI_CTAR_DBR);
		return *this;
	}
	inline SPSRemulation & operator &= (int val) __attribute__((always_inline)) {
		//serial_print("SPSR &= ");
		//serial_phex(val);
		//serial_print("\n");
		if (!(val & (1<<SPI2X))) SPCRemulation::update_ctar(SPI0_CTAR0 &= ~SPI_CTAR_DBR);
		return *this;
	}
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		//serial_print("SPSR & ");
		//serial_phex(val);
		//serial_print("\n");
		// TODO: using SPI_SR_TCF isn't quite right.  Control returns to the
		// caller after the final edge that captures data, which is 1/2 cycle
		// sooner than AVR returns.  At 500 kHz and slower SPI, this can make
		// a difference when digitalWrite is used to manually control the CS
		// pin, and perhaps it could matter at high clocks if faster register
		// access is used?  But does it really matter?  Do any SPI chips in
		// practice really perform differently if CS negates early, after the
		// final bit is clocked, but before the end of the whole clock cycle?
		if ((val & (1<<SPIF)) && (SPI0_SR & SPI_SR_TCF)) ret = (1<<SPIF);
		if ((val & (1<<SPI2X)) && (SPI0_CTAR0 & SPI_CTAR_DBR)) ret |= (1<<SPI2X);
		//delayMicroseconds(50000);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		//serial_print("SPSR (int)\n");
		if (SPI0_SR & SPI_SR_TCF) ret = (1<<SPIF);
		if (SPI0_CTAR0 & SPI_CTAR_DBR) ret |= (1<<SPI2X);
		return ret;
	}
};
extern SPSRemulation SPSR;

class SPDRemulation
{
public:
	inline SPDRemulation & operator = (int val) __attribute__((always_inline)) {
		//serial_print("SPDR = ");
		//serial_phex(val);
		//serial_print("\n");
		SPI0_MCR |= SPI_MCR_CLR_RXF; // discard any received data
		SPI0_SR = SPI_SR_TCF;
		//SPI0_SR = SPI_SR_EOQF;
		//SPI0_PUSHR = (val & 255) | SPI0_PUSHR_EOQ;
		SPI0_PUSHR = (val & 255);
		return *this;
	}
	operator int () const __attribute__((always_inline)) {
		uint32_t val;
		val = SPI0_POPR & 255;
		//serial_print("SPDR (int) ");
		//serial_phex(val);
		//serial_print("\n");
		return val;
	}
};
extern SPDRemulation SPDR;


class SREGemulation
{
public:
	operator int () const __attribute__((always_inline)) {
		uint32_t primask;
		asm volatile("mrs %0, primask\n" : "=r" (primask)::);
		if (primask) return 0;
		return (1<<7);
	}
	inline SREGemulation & operator = (int val) __attribute__((always_inline)) {
		if (val & (1<<7)) {
			__enable_irq();
		} else {
			__disable_irq();
		}
		return *this;
	}
};
extern SREGemulation SREG;



#endif // __cplusplus

#endif
