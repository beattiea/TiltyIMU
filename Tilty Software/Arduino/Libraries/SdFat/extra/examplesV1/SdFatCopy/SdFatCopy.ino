/*
 * Copy Example - only runs on chips with 2K or more RAM
 *
 * This sketch copies the file APPEND.TXT, created by the
 * SdFatAppend.pde example, to the file ACOPY.TXT.
 */
#include <SdFat.h>
#include <SdFatUtil.h> // use functions to print strings from flash memory

const uint8_t SD_CHIP_SELECT = SS;

// file system
SdFat sd;

SdFile from; // read file
SdFile copy; // write file

char* fromName = "APPEND.TXT";
char* toName = "ACOPY.TXT";

// large buffer to test for bugs. 512 bytes runs much faster.
char buf[600];

// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))
//------------------------------------------------------------------------------
void setup(void) {
  Serial.begin(9600);
  while (!Serial) {}  // wait for Leonardo
  PgmPrintln("Type any character to start");
  while (Serial.read() <= 0) {}
  delay(200);  // Catch Due reset problem
  
  PgmPrint("FreeRam: ");
  Serial.println(FreeRam());
  
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
  if (!sd.begin(SD_CHIP_SELECT, SPI_HALF_SPEED)) sd.initErrorHalt();

  // open for read
  if (!from.open(fromName, O_READ)) {
    PgmPrint("Can't open "); 
    Serial.println(fromName);
    PgmPrintln("Run the append example to create the file.");
    error("from.open failed");
  }
  // create if needed, truncate to zero length, open for write
  if (!copy.open(toName, O_CREAT | O_TRUNC | O_WRITE)) {
    error("copy.open failed");
  }
  // count for printing periods
  uint16_t p = 0;
  int16_t n;  
  while ((n = from.read(buf, sizeof(buf))) > 0) {
    if (copy.write(buf, n) != n) error("write failed");
    // print progress periods
    if (!(p++ % 25)) Serial.write('.');
    if (!(p % 500)) Serial.println();
  }
  Serial.println();
  if (n != 0) error ("read");
  // force write of directory entry and last data
  if (!copy.close()) error("copy.close failed");
  PgmPrintln("Copy done.");
}

void loop(void) {}
