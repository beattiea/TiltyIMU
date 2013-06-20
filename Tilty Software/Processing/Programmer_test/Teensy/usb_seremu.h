#ifndef USBseremu_h_
#define USBseremu_h_

#if defined(USB_HID) || defined(USB_MIDI) || defined(USB_RAWHID) || defined(USB_FLIGHTSIM)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
int usb_seremu_getchar(void);
int usb_seremu_peekchar(void);
int usb_seremu_available(void);
void usb_seremu_flush_input(void);
int usb_seremu_putchar(uint8_t c);
int usb_seremu_write(const void *buffer, uint32_t size);
void usb_seremu_flush_output(void);
void usb_seremu_flush_callback(void);
extern volatile uint8_t usb_seremu_transmit_flush_timer;
extern volatile uint8_t usb_configuration;
#ifdef __cplusplus
}
#endif


// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_seremu_class : public Stream
{
public:
        void begin(long) { /* TODO: call a function that tries to wait for enumeration */ };
        void end() { /* TODO: flush output and shut down USB port */ };
        virtual int available() { return usb_seremu_available(); }
        virtual int read() { return usb_seremu_getchar(); }
        virtual int peek() { return usb_seremu_peekchar(); }
        virtual void flush() { usb_seremu_flush_output(); }
        virtual size_t write(uint8_t c) { return usb_seremu_putchar(c); }
        virtual size_t write(const uint8_t *buffer, size_t size) { return usb_seremu_write(buffer, size); }
        size_t write(unsigned long n) { return write((uint8_t)n); }
        size_t write(long n) { return write((uint8_t)n); }
        size_t write(unsigned int n) { return write((uint8_t)n); }
        size_t write(int n) { return write((uint8_t)n); }
	using Print::write;
        void send_now(void) { usb_seremu_flush_output(); };
        uint32_t baud(void) { return 9600; }
        uint8_t stopbits(void) { return 1; }
        uint8_t paritytype(void) { return 0; }
        uint8_t numbits(void) { return 8; }
        uint8_t dtr(void) { return 1; }
        uint8_t rts(void) { return 1; }
        operator bool() { return usb_configuration; }
};

extern usb_seremu_class Serial;

#endif // __cplusplus

#endif // USB_HID
#endif // USBseremu_h_
