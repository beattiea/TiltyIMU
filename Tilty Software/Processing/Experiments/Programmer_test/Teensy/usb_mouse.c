#include "usb_dev.h"
#include "usb_mouse.h"
#include "core_pins.h" // for yield()
#include "HardwareSerial.h"
#include <string.h> // for memcpy()

#ifdef MOUSE_INTERFACE // defined by usb_dev.h -> usb_desc.h

// which buttons are currently pressed
uint8_t usb_mouse_buttons_state=0;

// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
uint8_t usb_mouse_protocol=1;


// Set the mouse buttons.  To create a "click", 2 calls are needed,
// one to push the button down and the second to release it
int usb_mouse_buttons(uint8_t left, uint8_t middle, uint8_t right)
{
        uint8_t mask=0;

        if (left) mask |= 1;
        if (middle) mask |= 4;
        if (right) mask |= 2;
        usb_mouse_buttons_state = mask;
        return usb_mouse_move(0, 0, 0);
}


// Maximum number of transmit packets to queue so we don't starve other endpoints for memory
#define TX_PACKET_LIMIT 3

static uint8_t transmit_previous_timeout=0;

// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 30

#if F_CPU == 96000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 596)
#elif F_CPU == 48000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 428)
#elif F_CPU == 24000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 262)
#endif


// Move the mouse.  x, y and wheel are -127 to 127.  Use 0 for no movement.
int usb_mouse_move(int8_t x, int8_t y, int8_t wheel)
{
        uint32_t wait_count=0;
        usb_packet_t *tx_packet;

	//serial_print("move");
	//serial_print("\n");
        if (x == -128) x = -127;
        if (y == -128) y = -127;
        if (wheel == -128) wheel = -127;

        while (1) {
                if (!usb_configuration) {
                        return -1;
                }
                if (usb_tx_packet_count(MOUSE_ENDPOINT) < TX_PACKET_LIMIT) {
                        tx_packet = usb_malloc();
                        if (tx_packet) break;
                }
                if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
                        transmit_previous_timeout = 1;
                        return -1;
                }
                yield();
        }
	transmit_previous_timeout = 0;
	*(tx_packet->buf) = usb_mouse_buttons_state;
	*(tx_packet->buf + 1) = x;
	*(tx_packet->buf + 2) = y;
	*(tx_packet->buf + 3) = wheel;
	tx_packet->len = 4;
	usb_tx(MOUSE_ENDPOINT, tx_packet);
        return 0;
}



#endif // MOUSE_INTERFACE
