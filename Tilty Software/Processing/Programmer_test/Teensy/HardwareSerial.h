#ifndef HardwareSerial_h
#define HardwareSerial_h

#include "mk20dx128.h"
#include <inttypes.h>

#define BAUD2DIV(baud)  (((F_CPU * 2) + ((baud) >> 1)) / (baud))
#define BAUD2DIV3(baud) (((F_BUS * 2) + ((baud) >> 1)) / (baud))

// C language implementation
//
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


// C++ interface
//
#ifdef __cplusplus
#include "Stream.h"
class HardwareSerial : public Stream
{
public:
	void begin(uint32_t baud)       { serial_begin(BAUD2DIV(baud)); }
	void end(void)                  { serial_end(); }
	virtual int available(void)     { return serial_available(); }
	virtual int peek(void)          { return serial_peek(); }
	virtual int read(void)          { return serial_getchar(); }
	virtual void flush(void)        { serial_flush(); }
	void clear(void)                { serial_clear(); }
	virtual size_t write(uint8_t c) { serial_putchar(c); return 1; }
	size_t write(unsigned long n)   { return write((uint8_t)n); }
	size_t write(long n)            { return write((uint8_t)n); }
	size_t write(unsigned int n)    { return write((uint8_t)n); }
	size_t write(int n)             { return write((uint8_t)n); }
	using Print::write;
};
extern HardwareSerial Serial1;

class HardwareSerial2 : public HardwareSerial
{
public:
	void begin(uint32_t baud)       { serial2_begin(BAUD2DIV(baud)); }
	void end(void)                  { serial2_end(); }
	virtual int available(void)     { return serial2_available(); }
	virtual int peek(void)          { return serial2_peek(); }
	virtual int read(void)          { return serial2_getchar(); }
	virtual void flush(void)        { serial2_flush(); }
	void clear(void)                { serial2_clear(); }
	virtual size_t write(uint8_t c) { serial2_putchar(c); return 1; }
	size_t write(unsigned long n)   { return write((uint8_t)n); }
	size_t write(long n)            { return write((uint8_t)n); }
	size_t write(unsigned int n)    { return write((uint8_t)n); }
	size_t write(int n)             { return write((uint8_t)n); }
	using Print::write;
};
extern HardwareSerial2 Serial2;

class HardwareSerial3 : public HardwareSerial
{
public:
	void begin(uint32_t baud)       { serial3_begin(BAUD2DIV3(baud)); }
	void end(void)                  { serial3_end(); }
	virtual int available(void)     { return serial3_available(); }
	virtual int peek(void)          { return serial3_peek(); }
	virtual int read(void)          { return serial3_getchar(); }
	virtual void flush(void)        { serial3_flush(); }
	void clear(void)                { serial3_clear(); }
	virtual size_t write(uint8_t c) { serial3_putchar(c); return 1; }
	size_t write(unsigned long n)   { return write((uint8_t)n); }
	size_t write(long n)            { return write((uint8_t)n); }
	size_t write(unsigned int n)    { return write((uint8_t)n); }
	size_t write(int n)             { return write((uint8_t)n); }
	using Print::write;
};
extern HardwareSerial3 Serial3;

#endif
#endif
