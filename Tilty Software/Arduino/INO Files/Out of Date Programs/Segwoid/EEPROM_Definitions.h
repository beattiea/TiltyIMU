//  FINISHED TRANSFERING

/*  EEPROM Storage Settings  */
#define BLOCK_SIZE 5  // Number of bytes to assign to each EEPROM storage block
#define SAVED_VALUE true  // Value to indicate if EEPROM block contains saved data

/*  EEPROM Data Address Definitions  */
#define YAW_OFFSET_ADDRESS 1
#define PITCH_OFFSET_ADDRESS 2  // Uses address 1
#define ROLL_OFFSET_ADDRESS 3  // Uses address 2
#define kP_ADDRESS 4  // kP EEPROM address
#define kI_ADDRESS 5  // KI...
#define kD_ADDRESS 6  // KD...
#define STEERING_MIN_ADDRESS 7  // Minimum steering potentiometer value address
#define STEERING_MAX_ADDRESS 8  // Maximum steering potentiometer value address

/*  Custom EEPROM Function Definitions  */
boolean checkEEPROMsaved(int address);
void saveFloat(int address, float value);
void saveInt(int address, int value);
float loadFloat(int address);
int loadInt(int address);

/*  Variables Used By Custom EEPROM Functions  */
union floatUnion_t
{
  float val;
  byte bytes[sizeof(val)];
} floatUnion;

union intUnion_t
{
  int val;
  byte bytes[4];
} intUnion;
