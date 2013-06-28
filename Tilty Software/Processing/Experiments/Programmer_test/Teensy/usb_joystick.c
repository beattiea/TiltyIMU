#include "usb_dev.h"
#include "usb_joystick.h"
#include "core_pins.h" // for yield()
#include "HardwareSerial.h"
#include <string.h> // for memcpy()

#ifdef JOYSTICK_INTERFACE // defined by usb_dev.h -> usb_desc.h


uint32_t usb_joystick_data[3];


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




int usb_joystick_send(void)
{
        uint32_t wait_count=0;
        usb_packet_t *tx_packet;

	//serial_print("send");
	//serial_print("\n");
        while (1) {
                if (!usb_configuration) {
			//serial_print("error1\n");
                        return -1;
                }
                if (usb_tx_packet_count(JOYSTICK_ENDPOINT) < TX_PACKET_LIMIT) {
                        tx_packet = usb_malloc();
                        if (tx_packet) break;
                }
                if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
                        transmit_previous_timeout = 1;
			//serial_print("error2\n");
                        return -1;
                }
                yield();
        }
	transmit_previous_timeout = 0;
	memcpy(tx_packet->buf, usb_joystick_data, 12);
        tx_packet->len = 12;
        usb_tx(JOYSTICK_ENDPOINT, tx_packet);
	//serial_print("ok\n");
        return 0;
}




#endif // JOYSTICK_INTERFACE
