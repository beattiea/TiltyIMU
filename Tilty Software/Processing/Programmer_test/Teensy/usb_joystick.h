#ifndef USBjoystick_h_
#define USBjoystick_h_

#if defined(USB_HID) || defined(USB_SERIAL_HID)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
int usb_joystick_send(void);
extern uint32_t usb_joystick_data[3];
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class usb_joystick_class
{
        public:
        void begin(void) { }
        void end(void) { }
	void button(uint8_t button, bool val) {
		if (--button >= 32) return;
		if (val) usb_joystick_data[0] |= (1 << button);
		else usb_joystick_data[0] &= ~(1 << button);
		if (!manual_mode) usb_joystick_send();
	}
	void X(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFFFFC00F) | (val << 4);
		if (!manual_mode) usb_joystick_send();
	}
	void Y(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFF003FFF) | (val << 14);
		if (!manual_mode) usb_joystick_send();
	}
	void position(unsigned int x, unsigned int y) {
		if (x > 1023) x = 1023;
		if (y > 1023) y = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFFF00000)
			| (x << 4) | (y << 14);
		if (!manual_mode) usb_joystick_send();
	}
	void Z(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0x00FFFFFF) | (val << 24);
		usb_joystick_data[2] = (usb_joystick_data[2] & 0xFFFFFFFC) | (val >> 8);
		if (!manual_mode) usb_joystick_send();
	}
	void Zrotate(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0xFFFFF003) | (val << 2);
		if (!manual_mode) usb_joystick_send();
	}
	void sliderLeft(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0xFFC00FFF) | (val << 12);
		if (!manual_mode) usb_joystick_send();
	}
	void sliderRight(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0x003FFFFF) | (val << 22);
		if (!manual_mode) usb_joystick_send();
	}
	void slider(unsigned int val) {
		if (val > 1023) val = 1023;
		usb_joystick_data[2] = (usb_joystick_data[2] & 0x00000FFF)
			| (val << 12) | (val << 22);
		if (!manual_mode) usb_joystick_send();
	}
        inline void hat(int dir) {
                uint32_t val;
                if (dir < 0) val = 15;
                else if (dir < 23) val = 0;
                else if (dir < 68) val = 1;
                else if (dir < 113) val = 2;
                else if (dir < 158) val = 3;
                else if (dir < 203) val = 4;
                else if (dir < 245) val = 5;
                else if (dir < 293) val = 6;
                else if (dir < 338) val = 7;
		usb_joystick_data[1] = (usb_joystick_data[1] & 0xFFFFFFF0) | val;
                if (!manual_mode) usb_joystick_send();
        }
	void useManualSend(bool mode) {
		manual_mode = mode;
	}
	void send_now(void) {
		usb_joystick_send();
	}
	private:
	static uint8_t manual_mode;
};
extern usb_joystick_class Joystick;

#endif // __cplusplus

#endif // USB_HID || USB_SERIAL_HID
#endif // USBjoystick_h_

