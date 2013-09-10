#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Print.h"

#define BAUD2DIV(baud)  (((F_CPU * 2) + ((baud) >> 1)) / (baud))
#define BAUD2DIV3(baud) (((F_BUS * 2) + ((baud) >> 1)) / (baud))

#ifdef __cplusplus
extern "C" {
#endif
void serial_begin(uint32_t divisor);
void serial_end(void);
void serial_putchar(uint8_t c);
void serial_flush(void);
int serial_available(void);
int serial_getchar(void);
int serial_peek(void);
void serial_clear(void);
void serial_print(const char *p);
void serial_phex(uint32_t n);
void serial_phex16(uint32_t n);
void serial_phex32(uint32_t n);

void serial2_begin(uint32_t divisor);
void serial2_end(void);
void serial2_putchar(uint8_t c);
void serial2_flush(void);
int serial2_available(void);
int serial2_getchar(void);
int serial2_peek(void);
void serial2_clear(void);

void serial3_begin(uint32_t divisor);
void serial3_end(void);
void serial3_putchar(uint8_t c);
void serial3_flush(void);
int serial3_available(void);
int serial3_getchar(void);
int serial3_peek(void);
void serial3_clear(void);

#ifdef __cplusplus
}
#endif

#define KEY_DELAY 50
#define COMMAND_TIMEOUT 1000

// Bluetooth status return defines
#define BT_INITIALIZED 0
#define BT_READY 1
#define BT_PAIRABLE 2
#define BT_PAIRED 3
#define BT_INQUIRING 4
#define BT_CONNECTING 5
#define BT_CONNECTED 6
#define BT_DISCONNECTED 7
#define BT_UNKNOWN 8

class HC_Bluetooth : public Print
{
	public:
		// Constructors
		HC_Bluetooth();
		~HC_Bluetooth();
		
		// Set up serial port only (HC-06)
		HC_Bluetooth(HardwareSerial& serial);
		HC_Bluetooth(HardwareSerial2& serial);
		HC_Bluetooth(HardwareSerial3& serial);
		
		// Set up serial port and command pin (HC-05)
		HC_Bluetooth(HardwareSerial& serial, uint8_t pin);
		HC_Bluetooth(HardwareSerial2& serial, uint8_t pin);
		HC_Bluetooth(HardwareSerial3& serial, uint8_t pin);
		
		void begin(uint32_t baud)       { serial_number == 1 ? start(BAUD2DIV(baud)) : start(BAUD2DIV3(baud)); }
		void (*end)(void);//                  { serial3_end(); }
		int (*available)(void);//     { return serial3_available(); }
		int (*peek)(void);//          { return serial3_peek(); }
		int (*read)(void);//          { return serial3_getchar(); }
		
		void (*flush)(void);//        { serial3_flush(); }
		void (*clear)(void);//                { serial3_clear(); }
		size_t write(uint8_t c) { put_char(c); return 1; }
		size_t write(unsigned long n)   { return write((uint8_t)n); }
		size_t write(long n)            { return write((uint8_t)n); }
		size_t write(unsigned int n)    { return write((uint8_t)n); }
		size_t write(int n)             { return write((uint8_t)n); }
		using Print::write;
		
		void commandMode();
		int checkOK();
		int getStatus();
		
		int status;
		
	private:
		bool command_mode = false;
		
		char command_start[3] = {'A', 'T', '+'};
		char command_end[2] = {'\r', '\n'};
		
		char AT_OK[4] = {'O', 'K', '\r', '\n'};
		
		int readReturn(char *buffer, uint8_t length);
		int parseQueryReturn(char *char1, char *char2, uint8_t length);

		void (*start)(uint32_t baud);
		void (*put_char)(uint8_t);
		void (*baud_div)(uint32_t baud);
		
		uint8_t serial_number;
		uint8_t command_pin;
		
		void setupSerial1();
		void setupSerial2();
		void setupSerial3();
};






