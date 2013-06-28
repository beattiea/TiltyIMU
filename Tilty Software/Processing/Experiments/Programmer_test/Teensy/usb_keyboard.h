#ifndef USBkeyboard_h_
#define USBkeyboard_h_

#include "keylayouts.h"

#if defined(USB_HID) || defined(USB_SERIAL_HID)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_keyboard_write(uint8_t c);
void usb_keyboard_write_unicode(uint16_t cpoint);
void usb_keyboard_press_keycode(uint16_t n);
void usb_keyboard_release_keycode(uint16_t n);
void usb_keyboard_release_all(void);
int usb_keyboard_press(uint8_t key, uint8_t modifier);
int usb_keyboard_send(void);
extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern uint8_t keyboard_protocol;
extern uint8_t keyboard_idle_config;
extern uint8_t keyboard_idle_count;
extern volatile uint8_t keyboard_leds;
#ifdef __cplusplus
}
#endif



// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_keyboard_class : public Print
{
public:
	void begin(void) { }
	void end(void) { }
	virtual size_t write(uint8_t c) { usb_keyboard_write(c); return 1; }
        size_t write(unsigned long n) { return write((uint8_t)n); }
        size_t write(long n) { return write((uint8_t)n); }
        size_t write(unsigned int n) { return write((uint8_t)n); }
        size_t write(int n) { return write((uint8_t)n); }
	using Print::write;
	void write_unicode(uint16_t n) { usb_keyboard_write_unicode(n); }
	void set_modifier(uint8_t c) { keyboard_modifier_keys = c; }
	void set_key1(uint8_t c) { keyboard_keys[0] = c; }
	void set_key2(uint8_t c) { keyboard_keys[1] = c; }
	void set_key3(uint8_t c) { keyboard_keys[2] = c; }
	void set_key4(uint8_t c) { keyboard_keys[3] = c; }
	void set_key5(uint8_t c) { keyboard_keys[4] = c; }
	void set_key6(uint8_t c) { keyboard_keys[5] = c; }
	void set_media(uint8_t c) { }
	void send_now(void) { usb_keyboard_send(); }
	void press(uint16_t n) { usb_keyboard_press_keycode(n); }
	void release(uint16_t n) { usb_keyboard_release_keycode(n); }
	void releaseAll(void);
};

extern usb_keyboard_class Keyboard;

#endif // __cplusplus

#endif // USB_HID || USB_SERIAL_HID
#endif // USBkeyboard_h_
