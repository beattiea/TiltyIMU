#include <nbwire.h>
/*
call this version 1.0

Offhand, the only funky part that I can think of is in nbrequestFrom, where the buffer
length and index are set *before* the data is actually read. The problem is that these
are variables local to the TwoWire object, and by the time we actually have read the
data, and know what the length actually is, we have no simple access to the object's 
variables. The actual bytes read *is* given to the callback function, though.

The ISR code for a slave receiver is commented out. I don't have that setup, and can't
verify it at this time. Save it for 2.0!

The handling of the read and write processes here is much like in the demo sketch code: 
the process is broken down into sequential functions, where each registers the next as a
callback, essentially.

For example, for the Read process, twi_read00 just returns if TWI is not yet in a 
ready state. When there's another interrupt, and the interface *is* ready, then it
sets up the read, starts it, and registers twi_read01 as the function to call after
the *next* interrupt. twi_read01, then, just returns if the interface is still in a
"reading" state. When the reading is done, it copies the information to the buffer,
cleans up, and calls the user-requested callback function with the actual number of 
bytes read.

The writing is similar.

Questions, comments and problems can go to Gene@Telobot.com.

Thumbs Up!
Gene Knight

*/

TwoWire Wire;

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;

uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;

//uint8_t TwoWire::transmitting = 0;
void (*TwoWire::user_onRequest)(void);
void (*TwoWire::user_onReceive)(int);

static volatile uint8_t twi_transmitting ;
static volatile uint8_t twi_state;
static uint8_t twi_slarw;
static volatile uint8_t twi_error;
static uint8_t twi_masterBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_masterBufferIndex;
static uint8_t twi_masterBufferLength;
static uint8_t twi_rxBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_rxBufferIndex;
//static volatile uint8_t twi_Interrupt_Continue_Command ;
static volatile uint8_t twi_Return_Value ;
static volatile uint8_t twi_Done ;
void (*twi_cbendTransmissionDone)(int);
void (*twi_cbreadFromDone)(int);

void twi_init () {
  // initialize state
   twi_state = TWI_READY ;
    // activate internal pull-ups for twi
    // as per note from atmega8 manual pg167
    sbi(PORTC, 4);
    sbi(PORTC, 5);
  // initialize twi prescaler and bit rate
  cbi(TWSR, TWPS0); // TWI Status Register - Prescaler bits
  cbi(TWSR, TWPS1);
  /* twi bit rate formula from atmega128 manual pg 204
  SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
  note: TWBR should be 10 or higher for master mode
  It is 72 for a 16mhz Wiring board with 100kHz TWI */
  TWBR = ((CPU_FREQ / TWI_FREQ) - 16) / 2; // bitrate register
  // enable twi module, acks, and twi interrupt
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
  /* TWEN - TWI Enable Bit
  TWIE - TWI Interrupt Enable
  TWEA - TWI Enable Acknowledge Bit
  TWINT - TWI Interrupt Flag
  TWSTA - TWI Start Condition
  */
}

typedef struct {
uint8_t address ;
uint8_t* data ;
uint8_t length ;
uint8_t wait ;
uint8_t i;
} twi_Write_Vars;

twi_Write_Vars *ptwv = 0 ;
static void (*fNextInterruptFunction)(void) = 0;

void twi_Finish (byte bRetVal) {
	if (ptwv) {
		free (ptwv) ;
		ptwv = 0 ;
	}
	twi_Done = 0xFF ;
	twi_Return_Value = bRetVal ;
	fNextInterruptFunction = 0 ;
}

uint8_t twii_WaitForDone () {
	while (!twi_Done) continue ;
	return twi_Return_Value ;
}

void twii_SetState (uint8_t ucState) {
  twi_state = ucState;
}

void twii_SetError (uint8_t ucError) {
  twi_error = ucError ;
}

void twii_InitBuffer (uint8_t ucPos, uint8_t ucLength) {
  twi_masterBufferIndex = 0;
  twi_masterBufferLength = ucLength;
}

void twii_CopyToBuf (uint8_t* pData, uint8_t ucLength) {
uint8_t i ;
  for(i = 0; i < ucLength; ++i){
    twi_masterBuffer[i] = pData[i];
  }
}

void twii_CopyFromBuf (uint8_t *pData, uint8_t ucLength) {
uint8_t i ;
  for(i = 0; i < ucLength; ++i){
    pData[i] = twi_masterBuffer[i] ;
  }
}

void twii_SetSlaRW (uint8_t ucSlaRW) {
  twi_slarw = ucSlaRW ;
}

void twii_SetStart () {
	  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);
}

void twi_write01 () {
	if (TWI_MTX == twi_state) return ; // blocking test
	twi_transmitting = 0 ;
  if (twi_error == 0xFF)
    twi_Finish (0);	// success
  else if (twi_error == TW_MT_SLA_NACK)
    twi_Finish (2);	// error: address send, nack received
  else if (twi_error == TW_MT_DATA_NACK)
    twi_Finish (3);	// error: data send, nack received
  else
    twi_Finish (4);	// other twi error
  if (twi_cbendTransmissionDone) return twi_cbendTransmissionDone (twi_Return_Value) ;
	return ;
}


void twi_write00 () {
	if (TWI_READY != twi_state) return ; // blocking test
	if(TWI_BUFFER_LENGTH < ptwv->length){
		twi_Finish (1) ; // end write with error 1
		return ;
	}
	twi_Done = 0x00 ; // show as working
	twii_SetState (TWI_MTX) ; // to transmitting
	twii_SetError (0xFF) ; // to No Error
	twii_InitBuffer (0, ptwv->length) ; // pointer and length
	twii_CopyToBuf (ptwv->data, ptwv->length) ; // get the data
	twii_SetSlaRW ((ptwv->address << 1) | TW_WRITE) ; // write command
	twii_SetStart () ; // start the cycle
	fNextInterruptFunction = twi_write01 ; // next routine
	return twi_write01 () ;
}

void twi_writeTo (uint8_t address, uint8_t* data, uint8_t length, uint8_t wait) {
  uint8_t i;
	ptwv = (twi_Write_Vars *)malloc (sizeof (twi_Write_Vars)) ;
	ptwv->address = address ;
	ptwv->data = data ;
	ptwv->length = length ;
	ptwv->wait = wait ;
	fNextInterruptFunction = twi_write00 ;
	return twi_write00 () ;
}

void twi_read01 () {
	if (TWI_MRX == twi_state) return ; // blocking test
	if (twi_masterBufferIndex < ptwv->length)
		ptwv->length = twi_masterBufferIndex;
	twii_CopyFromBuf (ptwv->data, ptwv->length) ;
	twi_Finish (ptwv->length) ;
  if (twi_cbreadFromDone) return twi_cbreadFromDone (twi_Return_Value) ;
	return ;
}

void twi_read00 () {
	if (TWI_READY != twi_state) return ; // blocking test
	if (TWI_BUFFER_LENGTH < ptwv->length) twi_Finish (0) ; // error return
	twi_Done = 0x00 ; // show as working
	twii_SetState (TWI_MRX) ; // reading
	twii_SetError (0xFF) ; // reset error
	twii_InitBuffer (0, ptwv->length - 1) ; // init to one less than length
	twii_SetSlaRW ((ptwv->address << 1) | TW_READ) ; // read command
	twii_SetStart () ; // start cycle
	fNextInterruptFunction = twi_read01 ;
	return twi_read01 () ;
}


void twi_readFrom(uint8_t address, uint8_t* data, uint8_t length) {
  uint8_t i;

	ptwv = (twi_Write_Vars *)malloc (sizeof (twi_Write_Vars)) ;
	ptwv->address = address ;
	ptwv->data = data ;
	ptwv->length = length ;
	fNextInterruptFunction = twi_read00 ;
	return twi_read00 () ;
}


void twi_reply(uint8_t ack) {
  // transmit master read ready signal, with or without ack
  if(ack){
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
  }else{
	  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT);
  }
}

void twi_stop(void) {
  // send stop condition
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

  // wait for stop condition to be exectued on bus
  // TWINT is not set after a stop condition!
  while(TWCR & _BV(TWSTO)){
    continue;
  }

  // update twi state
  twi_state = TWI_READY;
}

void twi_releaseBus(void) {
  // release bus
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);

  // update twi state
  twi_state = TWI_READY;
}


SIGNAL(TWI_vect) {
  switch(TW_STATUS){
    // All Master
    case TW_START:     // sent start condition
    case TW_REP_START: // sent repeated start condition
      // copy device address and r/w bit to output register and ack
      TWDR = twi_slarw;
      twi_reply(1);
      break;

    // Master Transmitter
    case TW_MT_SLA_ACK:  // slave receiver acked address
    case TW_MT_DATA_ACK: // slave receiver acked data
      // if there is data to send, send it, otherwise stop 
      if(twi_masterBufferIndex < twi_masterBufferLength){
        // copy data to output register and ack
        TWDR = twi_masterBuffer[twi_masterBufferIndex++];
        twi_reply(1);
      }else{
        twi_stop();
      }
      break;
    case TW_MT_SLA_NACK:  // address sent, nack received
      twi_error = TW_MT_SLA_NACK;
      twi_stop();
      break;
    case TW_MT_DATA_NACK: // data sent, nack received
      twi_error = TW_MT_DATA_NACK;
      twi_stop();
      break;
    case TW_MT_ARB_LOST: // lost bus arbitration
      twi_error = TW_MT_ARB_LOST;
      twi_releaseBus();
      break;

    // Master Receiver
    case TW_MR_DATA_ACK: // data received, ack sent
      // put byte into buffer
      twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
    case TW_MR_SLA_ACK:  // address sent, ack received
      // ack if more bytes are expected, otherwise nack
      if(twi_masterBufferIndex < twi_masterBufferLength){
        twi_reply(1);
      }else{
        twi_reply(0);
      }
      break;
    case TW_MR_DATA_NACK: // data received, nack sent
      // put final byte into buffer
      twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
    case TW_MR_SLA_NACK: // address sent, nack received
      twi_stop();
      break;
    // TW_MR_ARB_LOST handled by TW_MT_ARB_LOST case

    // Slave Receiver
//  case TW_SR_SLA_ACK:   // addressed, returned ack
//  case TW_SR_GCALL_ACK: // addressed generally, returned ack
//  case TW_SR_ARB_LOST_SLA_ACK:   // lost arbitration, returned ack
//  case TW_SR_ARB_LOST_GCALL_ACK: // lost arbitration, returned ack
//    // enter slave receiver mode
//    twi_state = TWI_SRX;
//    // indicate that rx buffer can be overwritten and ack
//    twi_rxBufferIndex = 0;
//    twi_reply(1);
//    break;
//  case TW_SR_DATA_ACK:       // data received, returned ack
//  case TW_SR_GCALL_DATA_ACK: // data received generally, returned ack
//    // if there is still room in the rx buffer
//    if(twi_rxBufferIndex < TWI_BUFFER_LENGTH){
//      // put byte in buffer and ack
//      twi_rxBuffer[twi_rxBufferIndex++] = TWDR;
//      twi_reply(1);
//    }else{
//      // otherwise nack
//      twi_reply(0);
//    }
//    break;
//  case TW_SR_STOP: // stop or repeated start condition received
//    // put a null char after data if there's room
//    if(twi_rxBufferIndex < TWI_BUFFER_LENGTH){
//      twi_rxBuffer[twi_rxBufferIndex] = '\0';
//    }
//    // sends ack and stops interface for clock stretching
//    twi_stop();
//    // callback to user defined callback
//    twi_onSlaveReceive(twi_rxBuffer, twi_rxBufferIndex);
//    // since we submit rx buffer to "wire" library, we can reset it
//    twi_rxBufferIndex = 0;
//    // ack future responses and leave slave receiver state
//    twi_releaseBus();
//    break;
//  case TW_SR_DATA_NACK:       // data received, returned nack
//  case TW_SR_GCALL_DATA_NACK: // data received generally, returned nack
//    // nack back at master
//    twi_reply(0);
//    break;
    
//  // Slave Transmitter
//  case TW_ST_SLA_ACK:          // addressed, returned ack
//  case TW_ST_ARB_LOST_SLA_ACK: // arbitration lost, returned ack
//    // enter slave transmitter mode
//    twi_state = TWI_STX;
//    // ready the tx buffer index for iteration
//    twi_txBufferIndex = 0;
//    // set tx buffer length to be zero, to verify if user changes it
//    twi_txBufferLength = 0;
//    // request for txBuffer to be filled and length to be set
//    // note: user must call twi_transmit(bytes, length) to do this
//    twi_onSlaveTransmit();
//    // if they didn't change buffer & length, initialize it
//    if(0 == twi_txBufferLength){
//      twi_txBufferLength = 1;
//      twi_txBuffer[0] = 0x00;
//    }
//    // transmit first byte from buffer, fall
//  case TW_ST_DATA_ACK: // byte sent, ack returned
//    // copy data to output register
//    TWDR = twi_txBuffer[twi_txBufferIndex++];
//    // if there is more to send, ack, otherwise nack
//    if(twi_txBufferIndex < twi_txBufferLength){
//      twi_reply(1);
//    }else{
//      twi_reply(0);
//    }
//    break;
//  case TW_ST_DATA_NACK: // received nack, we are done 
//  case TW_ST_LAST_DATA: // received ack, but we are done already!
//    // ack future responses
//    twi_reply(1);
//    // leave slave receiver state
//    twi_state = TWI_READY;
//    break;

    // All
    case TW_NO_INFO:   // no state information
      break;
    case TW_BUS_ERROR: // bus error, illegal stop/start
      twi_error = TW_BUS_ERROR;
      twi_stop();
      break;
  }
if (fNextInterruptFunction) return fNextInterruptFunction () ;
}



TwoWire::TwoWire()
{
}

void TwoWire::begin(void)
{
  rxBufferIndex = 0;
  rxBufferLength = 0;

  txBufferIndex = 0;
  txBufferLength = 0;

  twi_init();
}

void TwoWire::beginTransmission(int address)
{
//  beginTransmission((uint8_t)address);
  // indicate that we are transmitting
  twi_transmitting = 1;
  // set address of targeted slave
  txAddress = address;
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
}

uint8_t TwoWire::endTransmission(void)
{
  // transmit buffer (blocking)
//  int8_t ret = 
  twi_cbendTransmissionDone = NULL ;
  twi_writeTo(txAddress, txBuffer, txBufferLength, 1);
  int8_t ret = twii_WaitForDone () ;
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
//  // indicate that we are done transmitting
//  twi_transmitting = 0;
  return ret;
}

void TwoWire::nbendTransmission(void (*function)(int))
{
  twi_cbendTransmissionDone = function ;
  twi_writeTo(txAddress, txBuffer, txBufferLength, 1);
  return ;
}

void TwoWire::send(int data)
{
  if(twi_transmitting){
  // in master transmitter mode
    // don't bother if buffer is full
    if(txBufferLength >= BUFFER_LENGTH){
      return;
    }
    // put byte in tx buffer
    txBuffer[txBufferIndex] = data;
    ++txBufferIndex;
    // update amount in buffer   
    txBufferLength = txBufferIndex;
  }else{
  // in slave send mode
    // reply to master
//    twi_transmit(&data, 1);
  }
}

uint8_t TwoWire::receive(void)
{
  // default to returning null char
  // for people using with char strings
  uint8_t value = '\0';
  
  // get each successive byte on each call
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }

  return value;
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  // clamp to buffer length
  if(quantity > BUFFER_LENGTH){
    quantity = BUFFER_LENGTH;
  }
  // perform blocking read into buffer
  twi_cbreadFromDone = NULL ;
  twi_readFrom(address, rxBuffer, quantity);
  uint8_t read = twii_WaitForDone () ;
  // set rx buffer iterator vars
  rxBufferIndex = 0;
  rxBufferLength = read;

  return read;
}

void TwoWire::nbrequestFrom(int address, int quantity, void (*function)(int))
{
  // clamp to buffer length
  if(quantity > BUFFER_LENGTH){
    quantity = BUFFER_LENGTH;
  }
  // perform blocking read into buffer
  twi_cbreadFromDone = function ;
  twi_readFrom(address, rxBuffer, quantity);
//  uint8_t read = twii_WaitForDone () ;
//  // set rx buffer iterator vars
//  rxBufferIndex = 0;
//  rxBufferLength = read;
  rxBufferIndex = 0;
  rxBufferLength = quantity; // this is a hack

  return ; // read;
}

uint8_t TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

