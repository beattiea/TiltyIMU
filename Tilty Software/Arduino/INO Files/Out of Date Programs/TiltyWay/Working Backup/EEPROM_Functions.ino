//  FINISHED TRANSFERRING

/*  Checks to see if an address has a saved value  */
boolean checkEEPROMsaved(int address) {
  if (EEPROM.read(address * BLOCK_SIZE + (BLOCK_SIZE - 1)) == SAVED_VALUE) {  return true;}//  Checks last byte of a stored address to see if saved value is true
  else {  return false;}
}



/*  Write a float value to the given EEPROM block  */
void saveFloat(int address, float value) {
  floatUnion.val = value;
  for (int i = 0; i < sizeof(value); i++) {
    EEPROM.write((address * BLOCK_SIZE) + i, floatUnion.bytes[i]);
  }
  EEPROM.write(address * BLOCK_SIZE + (BLOCK_SIZE - 1), 1);//  Writes a 1 to the fifth byte to indicate there is a saved value
}

/*  Writes an integer value to the given EEPROM block  */
void saveInt(int address, int value) {
  intUnion.val = value;
  //Serial.println(intUnion.val);
  for (int i = 0; i < sizeof(value); i++) {
    EEPROM.write((address * BLOCK_SIZE) + i, intUnion.bytes[i]);
  }
  EEPROM.write(address * BLOCK_SIZE + (BLOCK_SIZE - 1), 1);//  Writes a 1 to the fifth byte to indicate there is a saved value
}




/*  Reads a float value from the given EEPROM block  */
float loadFloat(int address) {
  for (int i = 0; i < 4; i++) {
    floatUnion.bytes[i] = EEPROM.read((address * BLOCK_SIZE) + i);
  }
  
  return floatUnion.val;
}

/*  Reads an integer value from the given EEPROM block  */
int loadInt(int address) {
  for (int i = 0; i < 4; i++) {
    intUnion.bytes[i] = EEPROM.read((address * BLOCK_SIZE) + i);
  }
  
  return intUnion.val;
}

