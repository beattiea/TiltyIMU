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

#if defined(__MK20DX128__)

#include "mk20dx128.h"
#include "core_pins.h"
#include "i2c_t3.h"

#ifdef I2C_DEBUG
    rbuf i2cDebug; // ring buffer for passing diagnostics back to main loop
    uint8_t i2cDebugBuf[32]; // small buffer for moving data to Serial
    size_t i2cDebugBufLen;
    IntervalTimer i2cDebugTimer;

    // print I2C debug - call from main loop to dump diagnostics
    void printI2CDebug(void)
    {
        i2cDebugBufLen = i2cDebug.len();
        if(i2cDebugBufLen)
        {
            i2cDebugBufLen = (i2cDebugBufLen > 32) ? 32 : i2cDebugBufLen; // limit to prevent Serial overflow
            i2cDebug.getBlock(i2cDebugBuf,i2cDebugBufLen);
            Serial.write(i2cDebugBuf,i2cDebugBufLen);
        }
    }
#endif // I2C_DEBUG

//
// Static inits
//
uint8_t i2c_t3::rxBuffer[I2C_RX_BUFFER_LENGTH];
size_t i2c_t3::rxBufferIndex = 0;
size_t i2c_t3::rxBufferLength = 0;
uint8_t i2c_t3::txBuffer[I2C_TX_BUFFER_LENGTH];
size_t i2c_t3::txBufferIndex = 0;
size_t i2c_t3::txBufferLength = 0;
i2c_mode i2c_t3::currentMode = I2C_MASTER;
i2c_pins i2c_t3::currentPins = I2C_PINS_18_19;
i2c_stop i2c_t3::currentStop = I2C_STOP;
volatile i2c_status i2c_t3::currentStatus = I2C_WAITING;
uint8_t i2c_t3::rxAddr = 0;
size_t i2c_t3::reqCount = 0;
uint8_t i2c_t3::irqCount = 0;
void (*i2c_t3::user_onRequest)(void) = NULL;
void (*i2c_t3::user_onReceive)(size_t len) = NULL;

//
// Constructor/Destructor
//
i2c_t3::i2c_t3()
{
}
i2c_t3::~i2c_t3()
{
    #ifdef I2C_DEBUG
        i2cDebugTimer.end();
    #endif
}

//
// Initialize I2C - if config isn't specified, default to master, pins18/19, external pullup, 100kHz
//
void i2c_t3::begin(void)
    { begin(I2C_MASTER, 0, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_100); }

//
// Initialize I2C - if config isn't specified, default to slave, pins18/19, external pullup, 100kHz
//
void i2c_t3::begin(int address)
    { begin((uint8_t)address); }
void i2c_t3::begin(uint8_t address)
    { begin(I2C_SLAVE, address, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_100); }

//
// Initialize I2C - master or single address slave
//
void i2c_t3::begin(i2c_mode mode, uint8_t address, i2c_pins pins, i2c_pullup pullup, i2c_rate rate)
    { begin(mode, address, 0, pins, pullup, rate); }

//
// Initialize I2C
//
void i2c_t3::begin(i2c_mode mode, uint8_t address1, uint8_t address2, i2c_pins pins, i2c_pullup pullup, i2c_rate rate)
{
    SIM_SCGC4 |= SIM_SCGC4_I2C0; // Enable I2C internal clock

    currentMode = mode; // Set mode
    currentStatus = I2C_WAITING; // reset status

    // Set Master/Slave address (zeroed in Master to prevent accidental Rx when setup is changed dynamically)
    if(currentMode == I2C_MASTER)
    {
        I2C0_C2 = I2C_C2_HDRS; // Set high drive select
        I2C0_A1 = 0;
        I2C0_RA = 0;
    }
    else
    {
        I2C0_C2 = (address2) ? (I2C_C2_HDRS|I2C_C2_RMEN)    // Set high drive select and range-match enable
                             : I2C_C2_HDRS;                 // Set high drive select
        // set Slave address, if two addresses are given, setup range and put lower address in A1, higher in RA
        I2C0_A1 = (address2) ? ((address1 < address2) ? (address1<<1) : (address2<<1))
                             : (address1<<1);
        I2C0_RA = (address2) ? ((address1 < address2) ? (address2<<1) : (address1<<1))
                             : 0;
    }

    // Setup pins and options (note: does not "unset" unused pins if dynamically changed, must be done elsewhere)
    // As noted in original TwoWire.cpp, internal pullup is strong (about 190 ohms), but it can work if other
    // devices on bus have strong enough pulldown devices.
    currentPins = pins;
    uint32_t pinConfig = (pullup == I2C_PULLUP_EXT) ? (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE)
                                                    : (PORT_PCR_MUX(2)|PORT_PCR_PE|PORT_PCR_PS);
    if(pins == I2C_PINS_18_19)
    {
        CORE_PIN18_CONFIG = pinConfig;
        CORE_PIN19_CONFIG = pinConfig;
    }
    else
    {
        CORE_PIN16_CONFIG = pinConfig;
        CORE_PIN17_CONFIG = pinConfig;
    }

    // Set rate and filter
    #if F_BUS == 48000000
        switch(rate)                                // Freq  SCL Div
        {                                           // ----  -------
        case I2C_RATE_100:  I2C0_F = 0x27; break;   // 100k    480
        case I2C_RATE_200:  I2C0_F = 0x1F; break;   // 200k    240
        case I2C_RATE_300:  I2C0_F = 0x1D; break;   // 300k    160
        case I2C_RATE_400:  I2C0_F = 0x85; break;   // 400k    120
        case I2C_RATE_600:  I2C0_F = 0x14; break;   // 600k     80
        case I2C_RATE_800:  I2C0_F = 0x45; break;   // 800k     60
        case I2C_RATE_1000: I2C0_F = 0x0D; break;   // 1.0M     48
        case I2C_RATE_1200: I2C0_F = 0x0B; break;   // 1.2M     40
        case I2C_RATE_1500: I2C0_F = 0x09; break;   // 1.5M     32
        case I2C_RATE_2000: I2C0_F = 0x02; break;   // 2.0M     24
        case I2C_RATE_2400: I2C0_F = 0x00; break;   // 2.4M     20
        default:            I2C0_F = 0x27; break;   // 100k    480 (defaults to slowest)
        }
        I2C0_FLT = 4;
    #elif F_BUS == 24000000
        switch(rate)                                // Freq  SCL Div
        {                                           // ----  -------
        case I2C_RATE_100:  I2C0_F = 0x1F; break;   // 100k    240
        case I2C_RATE_200:  I2C0_F = 0x85; break;   // 200k    120
        case I2C_RATE_300:  I2C0_F = 0x14; break;   // 300k     80
        case I2C_RATE_400:  I2C0_F = 0x45; break;   // 400k     60
        case I2C_RATE_600:  I2C0_F = 0x0B; break;   // 600k     40
        case I2C_RATE_800:  I2C0_F = 0x05; break;   // 800k     30
        case I2C_RATE_1000: I2C0_F = 0x02; break;   // 1.0M     24
        case I2C_RATE_1200: I2C0_F = 0x00; break;   // 1.2M     00
        default:            I2C0_F = 0x1F; break;   // 100k    240 (defaults to slowest)
        }
        I2C0_FLT = 2;
    #else
        #error "F_BUS must be 48 MHz or 24 MHz"
    #endif

    // Set config registers
    if(currentMode == I2C_MASTER)
        I2C0_C1 = I2C_C1_IICEN; // Master - enable I2C (hold in Rx mode, intr disabled)
    else
        I2C0_C1 = I2C_C1_IICEN|I2C_C1_IICIE; // Slave - enable I2C and interrupts

    NVIC_ENABLE_IRQ(IRQ_I2C0); // Nested Vec Interrupt Ctrl - enable I2C interrupt

    #ifdef I2C_DEBUG
        if(!Serial) Serial.begin(115200);
        i2cDebugTimer.begin(printI2CDebug, 500); // 2kHz timer
    #endif
}

//
// Configure I2C pins - only works when the bus is in a non-busy state
// return: 1=success, 0=fail (bus busy)
//
uint8_t i2c_t3::pinConfigure(i2c_pins pins, i2c_pullup pullup)
{
    if(I2C0_S & I2C_S_BUSY) return 0; // return immediately if bus busy

    // configure I2C on designated pins, other pin set will be configured as inputs
    currentPins = pins;
    uint32_t i2cConfig = (pullup == I2C_PULLUP_EXT) ? (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE)
                                                    : (PORT_PCR_MUX(2)|PORT_PCR_PE|PORT_PCR_PS);
    uint32_t inputConfig = (pullup == I2C_PULLUP_EXT) ? PORT_PCR_MUX(1)
                                                    : (PORT_PCR_MUX(1)|PORT_PCR_PE|PORT_PCR_PS);
    if(pins == I2C_PINS_18_19)
    {
        *portModeRegister(16) = 0; // input
        CORE_PIN16_CONFIG = inputConfig;
        *portModeRegister(17) = 0; // input
        CORE_PIN17_CONFIG = inputConfig;
        CORE_PIN18_CONFIG = i2cConfig;
        CORE_PIN19_CONFIG = i2cConfig;
    }
    else
    {
        CORE_PIN16_CONFIG = i2cConfig;
        CORE_PIN17_CONFIG = i2cConfig;
        *portModeRegister(18) = 0; // input
        CORE_PIN18_CONFIG = inputConfig;
        *portModeRegister(19) = 0; // input
        CORE_PIN19_CONFIG = inputConfig;
    }
    return 1;
}

//
// Interrupt service routine
//
void i2c0_isr(void)
{
    uint8_t status, c1, data;
    static uint8_t timeoutRxNAK = 0;

    status = I2C0_S;
    c1 = I2C0_C1;
    I2C_DEBUG_STR("I"); I2C_DEBUG_REGS; // interrupt, reg dump
    if(c1 & I2C_C1_MST)
    {
        //
        // Master Mode
        //
        if(c1 & I2C_C1_TX)
        {
            // Continue Master Transmit
            I2C_DEBUG_STR(" MT"); // master transmit
            // check if Master Tx or Rx
            if(i2c_t3::currentStatus == I2C_SENDING)
            {
                // check if slave ACK'd
                if(status & I2C_S_RXAK)
                {
                    I2C_DEBUG_STR(" N"); // NAK
                    if(i2c_t3::txBufferIndex == 0)
                        i2c_t3::currentStatus = I2C_ADDR_NAK; // NAK on Addr
                    else
                        i2c_t3::currentStatus = I2C_DATA_NAK; // NAK on Data
                    // send STOP, change to Rx mode, intr disabled
                    I2C_DEBUG_STR(" STOP");
                    I2C0_C1 = I2C_C1_IICEN;
                }
                else
                {
                    I2C_DEBUG_STR(" A"); // ACK
                    // check if last byte transmitted
                    if(++i2c_t3::txBufferIndex >= i2c_t3::txBufferLength)
                    {
                        // Tx complete, change to waiting state
                        i2c_t3::currentStatus = I2C_WAITING;
                        // send STOP if configured
                        if(i2c_t3::currentStop == I2C_STOP)
                        {
                            // send STOP, change to Rx mode, intr disabled
                            I2C_DEBUG_STR(" STOP");
                            I2C0_C1 = I2C_C1_IICEN;
                        }
                        else
                        {
                            // no STOP, stay in Tx mode, intr disabled
                            I2C0_C1 = I2C_C1_IICEN | I2C_C1_MST | I2C_C1_TX;
                        }
                    }
                    else
                    {
                        // transmit next byte
                        I2C0_D = i2c_t3::txBuffer[i2c_t3::txBufferIndex];
                        I2C_DEBUG_STR(" D:"); I2C_DEBUG_HEX(i2c_t3::txBuffer[i2c_t3::txBufferIndex]); // Tx data
                    }
                }
                I2C_DEBUG_STR("\n");
                I2C0_S = I2C_S_IICIF; // clear intr
                return;
            }
            else if(i2c_t3::currentStatus == I2C_SEND_ADDR)
            {
                // Master Receive, addr sent
                if(status & I2C_S_ARBL)
                {
                    // Arbitration Lost
                    I2C_DEBUG_STR(" ARBL\n"); // arb lost
                    i2c_t3::currentStatus = I2C_ARB_LOST;
                    I2C0_C1 = I2C_C1_IICEN; // change to Rx mode, intr disabled (does this send STOP if ARBL flagged?)
                    I2C0_S = I2C_S_ARBL | I2C_S_IICIF; // clear arbl flag and intr
                    return;
                }
                if(status & I2C_S_RXAK)
                {
                    // Slave addr NAK
                    I2C_DEBUG_STR(" N"); // NAK
                    i2c_t3::currentStatus = I2C_ADDR_NAK; // NAK on Addr
                    // send STOP, change to Rx mode, intr disabled
                    I2C_DEBUG_STR(" STOP");
                    I2C0_C1 = I2C_C1_IICEN;
                }
                else
                {
                    // Slave addr ACK, change to Rx mode
                    I2C_DEBUG_STR(" A"); // ACK
                    i2c_t3::currentStatus = I2C_RECEIVING;
                    if(i2c_t3::reqCount == 1)
                        I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE | I2C_C1_MST | I2C_C1_TXAK; // no STOP, Rx, NAK on recv
                    else
                        I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE | I2C_C1_MST; // no STOP, change to Rx
                    data = I2C0_D; // dummy read
                }
                I2C_DEBUG_STR("\n");
                I2C0_S = I2C_S_IICIF; // clear intr
                return;
            }
            else if(i2c_t3::currentStatus == I2C_TIMEOUT)
            {
                // send STOP if configured
                if(i2c_t3::currentStop == I2C_STOP)
                {
                    // send STOP, change to Rx mode, intr disabled
                    I2C_DEBUG_STR(" STOP\n");
                    I2C_DEBUG_STR("Timeout\n");
                    I2C0_C1 = I2C_C1_IICEN;
                }
                else
                {
                    // no STOP, stay in Tx mode, intr disabled
                    I2C_DEBUG_STR("Timeout\n");
                    I2C0_C1 = I2C_C1_IICEN | I2C_C1_MST | I2C_C1_TX;
                }
                I2C0_S = I2C_S_IICIF; // clear intr
                return;
            }
            else
            {
                // Should not be in Tx mode if not sending
                // send STOP, change to Rx mode, intr disabled
                I2C_DEBUG_STR("WTF\n");
                I2C0_C1 = I2C_C1_IICEN;
                I2C0_S = I2C_S_IICIF; // clear intr
                return;
            }
        }
        else
        {
            // Continue Master Receive
            I2C_DEBUG_STR(" MR"); // master receive
            // check if 2nd to last byte or timeout
            if((i2c_t3::rxBufferLength+2) == i2c_t3::reqCount ||
               (i2c_t3::currentStatus == I2C_TIMEOUT && !timeoutRxNAK))
                I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE | I2C_C1_MST | I2C_C1_TXAK; // no STOP, Rx, NAK on recv
            // if last byte or timeout send STOP
            if((i2c_t3::rxBufferLength+1) >= i2c_t3::reqCount ||
               (i2c_t3::currentStatus == I2C_TIMEOUT && timeoutRxNAK))
            {
                timeoutRxNAK = 0; // clear flag
                if(i2c_t3::currentStatus != I2C_TIMEOUT)
                    i2c_t3::currentStatus = I2C_WAITING; // Rx complete, change to waiting state
                // change to Tx mode
                I2C0_C1 = I2C_C1_IICEN | I2C_C1_MST | I2C_C1_TX;
                // grab last data
                data = I2C0_D;
                I2C_DEBUG_STR(" D:"); I2C_DEBUG_HEX(data); // Rx data
                if(i2c_t3::rxBufferLength < I2C_RX_BUFFER_LENGTH)
                    i2c_t3::rxBuffer[i2c_t3::rxBufferLength++] = data;
                if(i2c_t3::currentStop == I2C_STOP)
                {
                    I2C_DEBUG_STR(" N STOP\n"); // NAK and STOP
                    I2C0_C1 = I2C_C1_IICEN; // send STOP, change to Rx mode, intr disabled
                }
                else
                    I2C_DEBUG_STR(" N\n"); // NAK no STOP
                if(i2c_t3::currentStatus == I2C_TIMEOUT)
                    I2C_DEBUG_STR("Timeout\n"); // timeout
            }
            else
            {
                // grab next data
                data = I2C0_D;
                I2C_DEBUG_STR(" D:"); I2C_DEBUG_HEX(data); // Rx data
                if(i2c_t3::rxBufferLength < I2C_RX_BUFFER_LENGTH)
                    i2c_t3::rxBuffer[i2c_t3::rxBufferLength++] = data;
                I2C_DEBUG_STR(" A\n"); // not last byte, mark as ACK
            }
            if(i2c_t3::currentStatus == I2C_TIMEOUT && !timeoutRxNAK)
                timeoutRxNAK = 1; // set flag to indicate NAK sent
            I2C0_S = I2C_S_IICIF; // clear intr
            return;
        }
    }
    else
    {
        //
        // Slave Mode
        //
        if(status & I2C_S_ARBL)
        {
            // Arbitration Lost
            I2C_DEBUG_STR(" ARBL"); // arb lost
            I2C0_S = I2C_S_ARBL;    // clear arbl flag
            if(!(status & I2C_S_IAAS))
            {
                I2C_DEBUG_STR("\n");
                I2C0_S = I2C_S_IICIF; // clear intr
                return;
            }
        }
        if(status & I2C_S_IAAS)
        {
            // If in Slave Rx already, then RepSTART occured, run callback
            if(i2c_t3::currentStatus == I2C_SLAVE_RX && i2c_t3::user_onReceive != NULL)
            {
                I2C_DEBUG_STR(" RSTART");
                i2c_t3::rxBufferIndex = 0;
                i2c_t3::user_onReceive(i2c_t3::rxBufferLength);
            }
            // Is Addressed As Slave
            if(status & I2C_S_SRW)
            {
                // Begin Slave Transmit
                I2C_DEBUG_STR(" AST"); // addressed slave transmit
                i2c_t3::currentStatus = I2C_SLAVE_TX;
                i2c_t3::txBufferLength = 0;
                if(i2c_t3::user_onRequest != NULL)
                    i2c_t3::user_onRequest(); // load Tx buffer with data
                I2C_DEBUG_STR(" BL:"); I2C_DEBUG_HEX(i2c_t3::txBufferLength >> 8); I2C_DEBUG_HEX(i2c_t3::txBufferLength); // buf len
                if(i2c_t3::txBufferLength == 0)
                    i2c_t3::txBuffer[0] = 0; // send 0's if buffer empty
                I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE;
                i2c_t3::rxAddr = (I2C0_D>>1); // read to get target addr
                I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE | I2C_C1_TX;
                I2C0_D = i2c_t3::txBuffer[0]; // send first data
                i2c_t3::txBufferIndex = 1;
                I2C_DEBUG_STR(" D:"); I2C_DEBUG_HEX(i2c_t3::txBuffer[0]); // Tx data
            }
            else
            {
                // Begin Slave Receive
                I2C_DEBUG_STR(" ASR"); // addressed slave receive
                i2c_t3::irqCount = 0;
                if(i2c_t3::currentPins == I2C_PINS_18_19)
                    attachInterrupt(18, i2c_t3::sda_rising_isr, RISING);
                else
                    attachInterrupt(17, i2c_t3::sda_rising_isr, RISING);
                i2c_t3::currentStatus = I2C_SLAVE_RX;
                i2c_t3::rxBufferLength = 0;
                I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE;
                i2c_t3::rxAddr = (I2C0_D>>1); // read to get target addr
            }
            I2C_DEBUG_STR("\n");
            I2C0_S = I2C_S_IICIF; // clear intr
            return;
        }
        if(c1 & I2C_C1_TX)
        {
            // Continue Slave Transmit
            I2C_DEBUG_STR(" ST"); // slave transmit
            if((status & I2C_S_RXAK) == 0)
            {
                // Master ACK'd previous byte
                I2C_DEBUG_STR(" A"); // ACK
                if(i2c_t3::txBufferIndex < i2c_t3::txBufferLength)
                    data = i2c_t3::txBuffer[i2c_t3::txBufferIndex++];
                else
                    data = 0; // send 0's if buffer empty
                I2C_DEBUG_STR(" D:"); I2C_DEBUG_HEX(data); // Tx data
                I2C0_D = data;
                I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE | I2C_C1_TX;
            }
            else
            {
                // Master did not ACK previous byte
                I2C_DEBUG_STR(" N"); // NAK
                I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE; // switch to Rx mode
                data = I2C0_D; // dummy read
                i2c_t3::currentStatus = I2C_WAITING;
            }
        }
        else
        {
            // Continue Slave Receive
            I2C_DEBUG_STR(" SR"); // slave receive
            i2c_t3::irqCount = 0;
            if(i2c_t3::currentPins == I2C_PINS_18_19)
                attachInterrupt(18, i2c_t3::sda_rising_isr, RISING);
            else
                attachInterrupt(17, i2c_t3::sda_rising_isr, RISING);
            data = I2C0_D;
            I2C_DEBUG_STR(" D:"); I2C_DEBUG_HEX(data); // Rx data
            if(i2c_t3::rxBufferLength < I2C_RX_BUFFER_LENGTH)
                i2c_t3::rxBuffer[i2c_t3::rxBufferLength++] = data;
        }
        I2C_DEBUG_STR("\n");
        I2C0_S = I2C_S_IICIF; // clear intr
    }
}

// Detects the stop condition that terminates a slave receive transfer.
// If anyone from Freescale ever reads this code, please email me at
// paul@pjrc.com and explain how I can respond to the I2C stop without
// inefficient polling or a horrible pin change interrupt hack?!
void i2c_t3::sda_rising_isr(void)
{
    uint8_t status = I2C0_S; // capture status first, can change if ISR is too slow
    I2C_DEBUG_STR2("^ S:"); I2C_DEBUG_HEX2(status); // mark SDA rising edge, dump status
    if(!(status & I2C_S_BUSY))
    {
        I2C_DEBUG_STR(" STOP\n"); // detected STOP
        i2c_t3::currentStatus = I2C_WAITING;
        if(currentPins == I2C_PINS_18_19)
            detachInterrupt(18);
        else
            detachInterrupt(17);
        if(user_onReceive != NULL)
        {
            rxBufferIndex = 0;
            user_onReceive(rxBufferLength);
        }
    }
    else
    {
        if(++irqCount >= 2 || !(currentMode == I2C_SLAVE))
        {
            I2C_DEBUG_STR2(" -x-\n"); // disconnect SDA ISR
            if(currentPins == I2C_PINS_18_19)
                detachInterrupt(18);
            else
                detachInterrupt(17);
        }
        else
            I2C_DEBUG_STR2("\n");
    }
}

//
// Setup Master Transmit - do not call this in the middle of a Tx,
//                         else it will screw up the buffer and status
//
void i2c_t3::beginTransmission(int address) { beginTransmission((uint8_t)address); }
void i2c_t3::beginTransmission(uint8_t address)
{
    txBuffer[0] = (address << 1); // store target addr
    txBufferLength = 1;
    clearWriteError(); // clear any previous write error
    currentStatus = I2C_WAITING; // reset status
}

//
// Master Transmit - blocking function, returns after Tx complete
// return: 0=success, 1=data too long, 2=recv addr NACK, 3=recv data NACK, 4=other error
//
uint8_t i2c_t3::endTransmission(void) { return endTransmission(I2C_STOP, 0); }
uint8_t i2c_t3::endTransmission(i2c_stop sendStop) { return endTransmission(sendStop, 0); }
uint8_t i2c_t3::endTransmission(i2c_stop sendStop, uint32_t timeout)
{
    sendTransmission(sendStop);

    // wait for completion or timeout
    finish(timeout);

    return getError();
}

//
// Send Master Transmit - non-blocking function, it initiates the Tx ISR then returns immediately
//                      - main loop can determine completion via polling done() or using finish()
//                        and success/fail using status()
//
void i2c_t3::sendTransmission(i2c_stop sendStop)
{
    if(txBufferLength)
    {
        // clear the status flags
        I2C0_S = I2C_S_IICIF | I2C_S_ARBL;

        // now take control of the bus...
        if(I2C0_C1 & I2C_C1_MST)
        {
            // we are already the bus master, so send a repeated start
            I2C_DEBUG_STR("RSTART"); // Repeated START
            I2C0_C1 = I2C_C1_IICEN | I2C_C1_MST | I2C_C1_RSTA | I2C_C1_TX;
        }
        else
        {
            // we are not currently the bus master, so wait for bus ready
            while(I2C0_S & I2C_S_BUSY);
            // become the bus master in transmit mode (send start)
            I2C_DEBUG_STR("START"); // START
            currentMode = I2C_MASTER;
            I2C0_C1 = I2C_C1_IICEN | I2C_C1_MST | I2C_C1_TX;
        }

        // send 1st data and enable interrupts
        currentStatus = I2C_SENDING;
        currentStop = sendStop;
        txBufferIndex = 0;
        I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE | I2C_C1_MST | I2C_C1_TX; // enable intr
        I2C_DEBUG_STR(" T:"); I2C_DEBUG_HEX(txBuffer[txBufferIndex]); I2C_DEBUG_STR("\n"); // target addr
        I2C0_D = txBuffer[txBufferIndex];
    }
}

//
// Master Receive - blocking function, returns after Rx complete
// return: #bytes received, 0=fail (0 length request, NAK, timeout, or bus error)
//
size_t i2c_t3::requestFrom(uint8_t addr, size_t len)
    { return requestFrom(addr, len, I2C_STOP, 0); }
size_t i2c_t3::requestFrom(int addr, int len)
    { return requestFrom((uint8_t)addr, (size_t)len, I2C_STOP, 0); }
size_t i2c_t3::requestFrom(uint8_t addr, size_t len, i2c_stop sendStop)
    { return requestFrom(addr, len, sendStop, 0); }
size_t i2c_t3::requestFrom(uint8_t addr, size_t len, i2c_stop sendStop, uint32_t timeout)
{
    // exit immediately if request for 0 bytes
    if(len == 0) return 0;

    sendRequest(addr, len, sendStop);

    // wait for completion or timeout
    if(finish(timeout))
        return rxBufferLength;
    else
        return 0; // NAK, timeout or bus error
}

//
// Start Master Receive - non-blocking function, it initiates the Rx ISR then returns immediately
//                      - main loop can determine completion via polling done() or using finish()
//                        and success/fail using status()
//
void i2c_t3::sendRequest(uint8_t addr, size_t len, i2c_stop sendStop)
{
    // exit immediately if request for 0 bytes
    if(len == 0) return;

    reqCount=len; // store request length
    rxBufferIndex = 0; // reset buffer
    rxBufferLength = 0;

    // clear the status flags
    I2C0_S = I2C_S_IICIF | I2C_S_ARBL;

    // now take control of the bus...
    if(I2C0_C1 & I2C_C1_MST)
    {
        // we are already the bus master, so send a repeated start
        I2C_DEBUG_STR("RSTART"); // Repeated START
        I2C0_C1 = I2C_C1_IICEN | I2C_C1_MST | I2C_C1_RSTA | I2C_C1_TX;
    }
    else
    {
        // we are not currently the bus master, so wait for bus ready
        while(I2C0_S & I2C_S_BUSY);
        // become the bus master in transmit mode (send start)
        I2C_DEBUG_STR("START"); // START
        currentMode = I2C_MASTER;
        I2C0_C1 = I2C_C1_IICEN | I2C_C1_MST | I2C_C1_TX;
    }

    // send 1st data and enable interrupts
    currentStatus = I2C_SEND_ADDR;
    currentStop = sendStop;
    I2C0_C1 = I2C_C1_IICEN | I2C_C1_IICIE | I2C_C1_MST | I2C_C1_TX; // enable intr
    uint8_t target = (addr << 1) | 1; // address + READ
    I2C_DEBUG_STR(" T:"); I2C_DEBUG_HEX(target); I2C_DEBUG_STR("\n"); // target addr
    I2C0_D = target;
}

//
// Return Wire error code
// return: 0=success, 1=data too long, 2=recv addr NACK, 3=recv data NACK, 4=other error
//         (Note: error code 1 (data too long) is only valid after Tx, if it
//                appears after Rx then it was set by a previous Tx)
//
uint8_t i2c_t3::getError(void)
{
    // convert status to Arduino return values (give these a higher priority than buf overflow error)
    switch(currentStatus)
    {
    case I2C_ADDR_NAK: return 2;
    case I2C_DATA_NAK: return 3;
    case I2C_ARB_LOST: return 4;
    case I2C_TIMEOUT:  return 4;
    default: break;
    }
    if(getWriteError()) return 1; // if write_error was set then flag as buffer overflow
    return 0; // no errors
}

//
// Return status
//
i2c_status i2c_t3::status(void)
{
    return currentStatus;
}

//
// Master mode Tx/Rx done check
// return: 1=Tx/Rx complete (with or without errors), 0=still running
//
uint8_t i2c_t3::done(void)
{
    return (currentStatus==I2C_WAITING ||
            currentStatus==I2C_ADDR_NAK ||
            currentStatus==I2C_DATA_NAK ||
            currentStatus==I2C_ARB_LOST);
}

//
// Master mode finish Tx/Rx - loops until timeout, I2C enters waiting state,
//                            or bus error occurs
// return: 1=success (Tx or Rx completed, no error), 0=fail (NAK, timeout or Arb Lost)
//
uint8_t i2c_t3::finish(void) { return finish(0); }
uint8_t i2c_t3::finish(uint32_t timeout)
{
    elapsedMicros deltaT;

    // wait for completion or timeout
    while(!done() && (timeout == 0 || deltaT < timeout));

    // check exit status, if still Tx/Rx then timeout occurred
    if(currentStatus == I2C_SENDING ||
       currentStatus == I2C_SEND_ADDR ||
       currentStatus == I2C_RECEIVING )
        currentStatus = I2C_TIMEOUT; // set to timeout state

    // delay to allow bus to settle (eg. allow STOP to complete and be recognized,
    //                               not just on our side, but on slave side also)
    delayMicroseconds(10);
    if(currentStatus == I2C_WAITING) return 1;
    return 0;
}

//
// Put single data into Tx buffer
// return: #data inserted = success, 0=fail
//
size_t i2c_t3::write(uint8_t data)
{
    if(txBufferLength < I2C_TX_BUFFER_LENGTH)
    {
        txBuffer[txBufferLength++] = data;
        return 1;
    }
    setWriteError();
    return 0;
}

//
// Put data array into Tx buffer
// return: #data inserted = success, 0=fail
//
size_t i2c_t3::write(const uint8_t* data, size_t quantity)
{
    if(txBufferLength < I2C_TX_BUFFER_LENGTH)
    {
        size_t avail = I2C_TX_BUFFER_LENGTH - txBufferLength;
        uint8_t* dest = txBuffer + txBufferLength;

        if(quantity > avail)
        {
            quantity = avail; // truncate to space avail if needed
            setWriteError();
        }
        for(size_t count=quantity; count; count--)
            *dest++ = *data++;
        txBufferLength += quantity;
        return quantity;
    }
    setWriteError();
    return 0;
}

//
// Rx buffer remaining available bytes
// return: #bytes
//
int i2c_t3::available(void)
{
    return rxBufferLength - rxBufferIndex;
}

//
// Read Rx buffer data
// return: data (int), or -1 if buffer empty
//
int i2c_t3::read(void)
{
    if(rxBufferIndex >= rxBufferLength) return -1;
    return rxBuffer[rxBufferIndex++];
}

//
// Peek Rx buffer data
// return: data (int), or -1 if buffer empty
//
int i2c_t3::peek(void)
{
    if(rxBufferIndex >= rxBufferLength) return -1;
    return rxBuffer[rxBufferIndex];
}

//
// Read Rx buffer data
// return: data (uint8_t), or 0 if buffer empty
//
uint8_t i2c_t3::readByte(void)
{
    if(rxBufferIndex >= rxBufferLength) return 0;
    return rxBuffer[rxBufferIndex++];
}

//
// Peek Rx buffer data
// return: data (uint8_t), or 0 if buffer empty
//
uint8_t i2c_t3::peekByte(void)
{
    if(rxBufferIndex >= rxBufferLength) return 0;
    return rxBuffer[rxBufferIndex];
}

//
// Flush not implemented
//
void i2c_t3::flush(void)
{
}

//
// Return Rx Addr (used for Slave with address range)
// return: rxAddr
//
uint8_t i2c_t3::getRxAddr(void)
{
    return rxAddr;
}

//
// set callback function for Slave Rx
//
void i2c_t3::onReceive( void (*function)(size_t len) )
{
    user_onReceive = function;
}

//
// set callback function for Slave Tx
//
void i2c_t3::onRequest( void (*function)(void) )
{
    user_onRequest = function;
}

//
// Instantiate
//
i2c_t3 Wire = i2c_t3();

#endif // __MK20DX128__
