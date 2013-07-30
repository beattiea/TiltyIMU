/*
    ------------------------------------------------------------------------------------------------------
    i2c_t3 - I2C library for Teensy3, derived from Teensy3 TwoWire library

    - Modified 09Jun13 by Brian (nox771 at gmail.com)
        - fixed bug in ISR timeout code in which timeout condition could fail to reset in certain cases
        - fixed bug in Slave mode in sda_rising_isr attach, whereby it was not getting attached on the addr byte
        - moved debug routines so they are entirely defined internal to the library (no end user code req'd)
        - debug routines now use IntervalTimer library
        - added support for range of Slave addresses
        - added getRxAddr() for Slave using addr range to determine its called address
        - removed virtual keyword from all functions (is not a base class)

    - Modified 26Feb13 by Brian (nox771 at gmail.com)
        - Reworked begin function:
            - added option for pins to use (SCL:SDA on 19:18 or 16:17 - note pin order difference)
            - added option for internal pullup - as mentioned in previous code pullup is very strong,
                                                 approx 190 ohms, but is possibly useful for high speed I2C
            - added option for rates - 100kHz, 200kHz, 300kHz, 400kHz, 600kHz, 800kHz, 1MHz, 1.2MHz, <-- 24/48MHz bus
                                       1.5MHz, 2.0MHz, 2.4MHz                                        <-- 48MHz bus only
        - Removed string.h dependency (memcpy)
        - Changed Master modes to interrupt driven
        - Added non-blocking Tx/Rx routines, and status/done/finish routines:
            - sendTransmission() - non-blocking transmit
            - sendRequest() - non-blocking receive
            - status() - reports current status
            - done() - indicates Tx/Rx complete (for main loop polling if I2C is running in background)
            - finish() - loops until Tx/Rx complete or bus error
        - Added readByte()/peekByte() for uint8_t return values (note: returns 0 instead of -1 if buf empty)
        - Added fixes for Slave Rx mode - in short Slave Rx on this part is fubar
          (as proof, notice the difference in the I2Cx_FLT register in the KL25 Sub-Family parts)
            - the SDA-rising ISR hack can work but only detects STOP conditons.
              A slave Rx followed by RepSTART won't be detected since bus remains busy.
              To fix this if IAAS occurs while already in Slave Rx mode then it will
              assume RepSTART occurred and trigger onReceive callback.
        - Separated Tx/Rx buffer sizes for asymmetric devices (adjustable in i2c_t3.h)
        - Changed Tx/Rx buffer indicies to size_t to allow for large (>256 byte) buffers
        - Left debug routines in place (controlled via header defines - default is OFF).  If debug is
            enabled, note that it can easily overrun the Debug queue on large I2C transfers, yielding
            garbage output.  Adjust ringbuf size (in rbuf.h) and possibly PIT interrupt rate to adjust
            data flow to Serial (note also the buffer in Serial can overflow if written too quickly).
        - Added getError() function to return Wire error code
        - Added pinConfigure() function for changing pins on the fly (only when bus not busy)
        - Added timeouts to endTransmission(), requestFrom(), and finish()
    ------------------------------------------------------------------------------------------------------
    TwoWire.cpp - TWI/I2C library for Wiring & Arduino
    Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
    Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
    ------------------------------------------------------------------------------------------------------
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef I2C_T3_H
#define I2C_T3_H

#include <inttypes.h>
#include <stdio.h> // for size_t
#include "Arduino.h"

// Tx/Rx buffer sizes - buffers should be large enough to hold:
//                      Target Addr + Target Command (varies with protocol) + Data payload
//                      Default is 1byte Addr + 2byte Command + 256byte Data
#define I2C_TX_BUFFER_LENGTH 259
#define I2C_RX_BUFFER_LENGTH 259

// Debug controls - these defines control ISR diagnostics.  This is only really necessary for
//                  debugging bus problems, or for devices with no other means of data visibility,
//                  or for ISR development.  When enabled data will output on Serial, so if Serial
//                  already has traffic the result will be a mashup of both streams.
//                  Verbose modes are NOT recommended for anything except ISR devel (they will
//                  easily overrun ring and/or Serial buffers)
//
// I2C_DEBUG - uncomment this to show data transfer, START, STOP, etc.
//#define I2C_DEBUG
// I2C_DEBUG_VERBOSE1 - uncomment this for more verbose diagnostics (not recommended)
//#define I2C_DEBUG_VERBOSE1
// I2C_DEBUG_VERBOSE2 - uncomment this for even more verbose diagnostics (not recommended)
//#define I2C_DEBUG_VERBOSE2

#if defined(I2C_DEBUG) || defined(I2C_DEBUG_VERBOSE1) || defined(I2C_DEBUG_VERBOSE2)
    #include "../rbuf/rbuf.h"
    extern rbuf i2cDebug;
    extern uint8_t i2cDebugBuf[];
    extern size_t i2cDebugBufLen;
    extern IntervalTimer i2cDebugTimer;
    void printI2CDebug(void);

    // Debug Coding - note: for register information refer to Chapter 44: Inter-Integrated Circuit (I2C) - Page 1012
    //
    // Register dump:
    //  A1:   I2C Address Register 1
    //  F:    I2C Frequency Divider register
    //  C1:   I2C Control Register 1
    //  S:    I2C Status register
    //  D:    I2C Data I/O register
    //  C2:   I2C Control Register 2
    //  FLT:  I2C Programmable Input Glitch Filter register
    //
    // Debug Messages
    //  MT       Master Transmit
    //  MR       Master Receive
    //  AST      Addressed Slave Transmit
    //  ST       Slave Transmit
    //  ASR      Addressed Slave Receive
    //  SR       Slave Receive
    //  T        Target Address
    //  N        NAK
    //  A        ACK
    //  START    START
    //  RSTART   Repeated START
    //  STOP     STOP
    //  ARBL     Arbitration Lost
    //  Timeout  Timeout occurred
    //  BL       Buffer Length
    //  ^        SDA Rising-ISR
    //  -x-      SDA Rising-ISR disconnected
    //

    #if defined(I2C_DEBUG_VERBOSE2)
        #define I2C_DEBUG_REGS do          \
        {                                  \
            i2cDebug.putBlock(" A1:", 4);  \
            i2cDebug.putAHex(I2C0_A1);     \
            i2cDebug.putBlock(" F:", 3);   \
            i2cDebug.putAHex(I2C0_F);      \
            i2cDebug.putBlock(" C1:", 4);  \
            i2cDebug.putAHex(I2C0_C1);     \
            i2cDebug.putBlock(" S:", 3);   \
            i2cDebug.putAHex(I2C0_S);      \
            i2cDebug.putBlock(" C2:", 4);  \
            i2cDebug.putAHex(I2C0_C2);     \
            i2cDebug.putBlock(" FLT:", 5); \
            i2cDebug.putAHex(I2C0_FLT);    \
        } while(0)
    #elif defined(I2C_DEBUG_VERBOSE1)
        #define I2C_DEBUG_REGS do          \
        {                                  \
            i2cDebug.putBlock(" C1:", 4);  \
            i2cDebug.putAHex(I2C0_C1);     \
            i2cDebug.putBlock(" S:", 3);   \
            i2cDebug.putAHex(I2C0_S);      \
        } while(0)
    #else
        #define I2C_DEBUG_REGS do{}while(0)
    #endif

    // normal debug strings
    #define I2C_DEBUG_STR(x) i2cDebug.putBlock(x,(sizeof(x)/sizeof(char))-1)
    #define I2C_DEBUG_HEX(x) i2cDebug.putAHex(x)
    // verbose debug strings
    #if defined(I2C_DEBUG_VERBOSE1) || defined(I2C_DEBUG_VERBOSE2)
        #define I2C_DEBUG_STR2(x) i2cDebug.putBlock(x,(sizeof(x)/sizeof(char))-1)
        #define I2C_DEBUG_HEX2(x) i2cDebug.putAHex(x)
    #else
        #define I2C_DEBUG_STR2(x) do{}while(0)
        #define I2C_DEBUG_HEX2(x) do{}while(0)
    #endif
    // wait macro for debug msgs to clear, use this if interleaving with other output on Serial
    #define I2C_DEBUG_WAIT while(i2cDebug.len())
#else
    #define I2C_DEBUG_REGS    do{}while(0)
    #define I2C_DEBUG_STR(x)  do{}while(0)
    #define I2C_DEBUG_STR2(x) do{}while(0)
    #define I2C_DEBUG_HEX(x)  do{}while(0)
    #define I2C_DEBUG_HEX2(x) do{}while(0)
    #define I2C_DEBUG_WAIT    do{}while(0)
#endif

enum i2c_mode   {I2C_MASTER, I2C_SLAVE};
enum i2c_pins   {I2C_PINS_18_19, I2C_PINS_16_17};
enum i2c_pullup {I2C_PULLUP_EXT, I2C_PULLUP_INT};
enum i2c_rate   {I2C_RATE_100,
                 I2C_RATE_200,
                 I2C_RATE_300,
                 I2C_RATE_400,
                 I2C_RATE_600,
                 I2C_RATE_800,
                 I2C_RATE_1000,
                 I2C_RATE_1200,
                 I2C_RATE_1500,
                 I2C_RATE_2000,
                 I2C_RATE_2400};
enum i2c_stop   {I2C_NOSTOP, I2C_STOP};
enum i2c_status {I2C_WAITING,
                 I2C_SENDING,
                 I2C_SEND_ADDR,
                 I2C_RECEIVING,
                 I2C_TIMEOUT,
                 I2C_ADDR_NAK,
                 I2C_DATA_NAK,
                 I2C_ARB_LOST,
                 I2C_SLAVE_TX,
                 I2C_SLAVE_RX};

extern "C" void i2c0_isr(void);

class i2c_t3 : public Stream
{
private:
    static uint8_t rxBuffer[];
    static size_t rxBufferIndex;
    static size_t rxBufferLength;
    static uint8_t txBuffer[];
    static size_t txBufferIndex;
    static size_t txBufferLength;
    static i2c_mode currentMode;
    static i2c_pins currentPins;
    static i2c_stop currentStop;
    static volatile i2c_status currentStatus;
    static uint8_t rxAddr;
    static size_t reqCount;
    static uint8_t irqCount;
    static void (*user_onReceive)(size_t len);
    static void (*user_onRequest)(void);

    friend void i2c0_isr(void);
    static void sda_rising_isr(void);

public:

    i2c_t3();
    ~i2c_t3();
    void begin();
    void begin(int address);
    void begin(uint8_t address);
    void begin(i2c_mode mode, uint8_t address, i2c_pins pins, i2c_pullup pullup, i2c_rate rate);
    void begin(i2c_mode mode, uint8_t address1, uint8_t address2, i2c_pins pins, i2c_pullup pullup, i2c_rate rate);
    uint8_t pinConfigure(i2c_pins pins, i2c_pullup pullup);
    void beginTransmission(int address);
    void beginTransmission(uint8_t address);
    uint8_t endTransmission(void);                                  // blocking
    uint8_t endTransmission(i2c_stop sendStop);                     // blocking
    uint8_t endTransmission(i2c_stop sendStop, uint32_t timeout);   // blocking with timeout
    void sendTransmission(i2c_stop sendStop);                       // non-blocking
    size_t requestFrom(uint8_t addr, size_t len);                   // blocking
    size_t requestFrom(int addr, int len);                          // blocking
    size_t requestFrom(uint8_t addr, size_t len, i2c_stop sendStop);// blocking
    size_t requestFrom(uint8_t addr, size_t len, i2c_stop sendStop, uint32_t timeout);// blocking with timeout
    void sendRequest(uint8_t addr, size_t len, i2c_stop sendStop);  // non-blocking
    uint8_t getError(void);
    i2c_status status(void);
    uint8_t done(void);
    uint8_t finish(void);               // blocking
    uint8_t finish(uint32_t timeout);   // blocking with timeout
    size_t write(uint8_t data);
    size_t write(const uint8_t* data, size_t quantity);
    int available(void);
    int read(void);
    int peek(void);
    uint8_t readByte(void); // returns 0 if empty
    uint8_t peekByte(void); // returns 0 if empty
    void flush(void);
    uint8_t getRxAddr(void);
    void onReceive(void (*user_onReceive)(size_t len));
    void onRequest(void (*user_onRequest)(void));

    #ifdef CORE_TEENSY
        // added by Teensyduino installer, for compatibility
        // with pre-1.0 sketches and libraries
        void send(uint8_t b)               { write(b); }
        void send(uint8_t* s, uint8_t n)   { write(s, n); }
        void send(int n)                   { write((uint8_t)n); }
        void send(char* s)                 { write(s); }
        uint8_t receive(void) {
            int c = read();
            if (c < 0) return 0;
            return c;
        }
    #endif

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n)          { return write((uint8_t)n); }
    inline size_t write(unsigned int n)  { return write((uint8_t)n); }
    inline size_t write(int n)           { return write((uint8_t)n); }
    inline size_t write(const char* str) { return write((const uint8_t*)str, strlen(str)); }
};

extern i2c_t3 Wire;

#endif

