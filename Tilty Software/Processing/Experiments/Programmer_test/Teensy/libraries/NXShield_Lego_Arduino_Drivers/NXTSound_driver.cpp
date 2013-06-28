/*! @addtogroup Lego
 * @{
 * @defgroup legosound Sound Sensor
 * Lego Sound Sensor
 * @{
 */

/** \file NXTSound_driver.h
 * \brief Lego Sound Sensor driver
 *
 * NXTSound_driver.h provides an API for the Lego Sound Sensor.
 *
 * Changelog:
 * - 1.0: - Initial release
 * - 1.1:
 *        - Fixed a sound level calculation error
 * - 1.2:
 *        - Removed the work-around previously needed for DATABIT1
 *        - Added function init, so that it would initialize with either type DB or DBA.
 *        
 * Credits:
 *  - Based on Xander Soldaat's awesome ROBOTC drivers
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * \author Matthew Richardson http://mattallen37.wordpress.com/ (matthewrichardson37_at_gmail.com)
 * \date April 17 2012
 * \version 1.2
 * \example Example_Lego_NXT_Sound.ino
 */

#include "NXTSound_driver.h"

/**
 * Initialize the sound sensor on a certain port, and by default set it to DB
 * @param Shield The NXShield instance
 * @param Port The sensor port it's connected to
 * @param Type Optionally choose to initialize with DBA vs. DB. Default is NXT_SOUND_TYPE_DB
 * @return true if no error occured, otherwise false
 */
 
bool ClassNXTSound::init(NXShield * shield, SH_BankPort bp, byte type)  // default NXT_SOUND_TYPE_DB
{
	NXShieldAGS::init(shield, bp);
  if(type == NXT_SOUND_TYPE_DB){
    return SetDB();
  }
  else if(type == NXT_SOUND_TYPE_DBA){
    return SetDBA();
  }
}

static long RawSound;

/**
 * Read the sound level using the current sound mode
 * @return Sound level in the current mode
 */
  
int ClassNXTSound::SoundLevel()
{
  RawSound = readRaw() - 132;
  RawSound = (RawSound * 100) / 86 * 100 / 1023;
  RawSound = 100 - RawSound;
  if(RawSound>100){
    RawSound = 100;
  } else if (RawSound<0){
    RawSound = 0;
  }

  return RawSound;

/*  RawSound = readRaw();
  if (RawSound >= 132){
    RawSound -= 132;
  }
  else{
    RawSound = 0;
  }

  RawSound = (RawSound * 100) / 86;
  
  if (RawSound > 1023){
    RawSound = 1023;
  }
  RawSound = 1023 - RawSound; 
  
  return (RawSound * 100) / 1023;*/
}

/**
 * Set the sound sensor to DB
 * @return true if no error occured, otherwise false
 */

bool ClassNXTSound::SetDB(){
  return setType(SH_Type_ANALOG | SH_Type_DATABIT0_HIGH);
}

/**
 * Set the sound sensor to DBA
 * @return true if no error occured, otherwise false
 */

bool ClassNXTSound::SetDBA(){
  return setType(SH_Type_ANALOG | SH_Type_DATABIT1_HIGH);
}