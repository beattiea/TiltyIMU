#ifndef _avr_functions_h_
#define _avr_functions_h_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void eeprom_initialize(void);
uint8_t eeprom_read_byte(const uint8_t *addr) __attribute__ ((pure));
uint16_t eeprom_read_word(const uint16_t *addr) __attribute__ ((pure));
uint32_t eeprom_read_dword(const uint32_t *addr) __attribute__ ((pure));
float eeprom_read_float(const float *addr) __attribute__ ((pure));
void eeprom_read_block(void *buf, const void *addr, uint32_t len); // TODO: implement
void eeprom_write_byte(uint8_t *addr, uint8_t value);
void eeprom_write_word(uint16_t *addr, uint16_t value);
void eeprom_write_dword(uint32_t *addr, uint32_t value);
void eeprom_write_float(float *addr, float value); // TODO: inline call
void eeprom_write_block(const void *buf, void *addr, uint32_t len); // TODO: implement
void eeprom_update_byte(uint8_t *addrp, uint8_t value); // TODO: inline call
void eeprom_update_word(uint16_t *addrp, uint16_t value); // TODO: inline call
void eeprom_update_dword(uint32_t *addrp, uint32_t value); // TODO: inline call
void eeprom_update_float(float *addr, float __value); // TODO: inline call
void eeprom_update_block(const void *buf, void *addr, uint32_t len); // TODO: inline call

char * ultoa(unsigned long val, char *buf, int radix);
char * ltoa(long val, char *buf, int radix);
static inline char * utoa(unsigned int val, char *buf, int radix) __attribute__((always_inline, unused));
static inline char * utoa(unsigned int val, char *buf, int radix) { return ultoa(val, buf, radix); }
static inline char * itoa(int val, char *buf, int radix) __attribute__((always_inline, unused));
static inline char * itoa(int val, char *buf, int radix) { return ltoa(val, buf, radix); }


#ifdef __cplusplus
}
#endif
#endif
