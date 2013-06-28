#ifndef USBmouse_h_
#define USBmouse_h_

#if defined(USB_HID) || defined(USB_SERIAL_HID)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
int usb_mouse_buttons(uint8_t left, uint8_t middle, uint8_t right);
int usb_mouse_move(int8_t x, int8_t y, int8_t wheel);
extern uint8_t usb_mouse_buttons_state;
extern uint8_t usb_mouse_protocol;
#ifdef __cplusplus
}
#endif


#define MOUSE_LEFT 1
#define MOUSE_MIDDLE 4
#define MOUSE_RIGHT 2
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

// C++ interface
#ifdef __cplusplus
class usb_mouse_class
{
        public:
        void begin(void) { }
        void end(void) { }
        void move(int8_t x, int8_t y, int8_t wheel=0) { usb_mouse_move(x, y, wheel); }
        void click(uint8_t b = MOUSE_LEFT) {
		usb_mouse_buttons_state = b;
		usb_mouse_move(0, 0, 0);
		usb_mouse_buttons_state = 0;
		usb_mouse_move(0, 0, 0);
	}
        void scroll(int8_t wheel) { usb_mouse_move(0, 0, wheel); }
        void set_buttons(uint8_t left, uint8_t middle=0, uint8_t right=0) {
		usb_mouse_buttons(left, middle, right);
	}
        void press(uint8_t b = MOUSE_LEFT) {
		uint8_t buttons = usb_mouse_buttons_state | (b & MOUSE_ALL);
		if (buttons != usb_mouse_buttons_state) {
			usb_mouse_buttons_state = buttons;
			usb_mouse_move(0, 0, 0);
		}
	}
        void release(uint8_t b = MOUSE_LEFT) {
		uint8_t buttons = usb_mouse_buttons_state & ~(b & MOUSE_ALL);
		if (buttons != usb_mouse_buttons_state) {
			usb_mouse_buttons_state = buttons;
			usb_mouse_move(0, 0, 0);
		}
	}
        bool isPressed(uint8_t b = MOUSE_ALL) {
		return ((usb_mouse_buttons_state & (b & MOUSE_ALL)) != 0);
	}
};
extern usb_mouse_class Mouse;

#endif // __cplusplus

#endif // USB_HID || USB_SERIAL_HID
#endif // USBmouse_h_

