/*
*  header file for NXTSound_driver
*  version 1.2
*/

#ifndef __NXTSound_H__
#define __NXTSound_H__

#define NXT_SOUND_TYPE_DB  0x07  /*!< NXT Sound sensor type DB */
#define NXT_SOUND_TYPE_DBA 0x08  /*!< NXT Sound sensor type DBA */

#include "NXShieldAGS.h"

class ClassNXTSound : public NXShieldAGS
{
public:
	bool init(NXShield * shield, SH_BankPort bp, byte type = NXT_SOUND_TYPE_DB);

	int  SoundLevel();
  
  bool SetDB();
  bool SetDBA();
};

#endif