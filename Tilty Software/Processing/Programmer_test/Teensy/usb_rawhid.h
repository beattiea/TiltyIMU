#ifndef USBrawhid_h_
#define USBrawhid_h_

#if defined(USB_RAWHID)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
int usb_rawhid_recv(void *buffer, uint32_t timeout);
int usb_rawhid_available(void);
int usb_rawhid_send(const void *buffer, uint32_t timeout);
#ifdef __cplusplus
}
#endif


// C++ interface
#ifdef __cplusplus
class usb_rawhid_class
{
public:
	int available(void) {return usb_rawhid_available(); }
	int recv(void *buffer, uint16_t timeout) { return usb_rawhid_recv(buffer, timeout); }
	int send(const void *buffer, uint16_t timeout) { return usb_rawhid_send(buffer, timeout); }
};

extern usb_rawhid_class RawHID;

#endif // __cplusplus

#endif // USB_HID
#endif // USBrawhid_h_
