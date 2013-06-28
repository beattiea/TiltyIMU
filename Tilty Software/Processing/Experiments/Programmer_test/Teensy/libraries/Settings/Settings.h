#ifndef Settings_h
#define Settings_h

#include <Arduino.h>
#include <EEPROM.h>

class Settings {
  public:
    /*  Variable stored in Settings data  */
    boolean saved = true;
    int address;
    
    float kP;//  P Scalar
    float kI;//  I Scalar
    float kD;//  D Scalar
    float kS;//  Steering Scalar (percent of maximum speed, 0-100)
    float angleOffset;//  Angle offset value
    int loopTime;//  constant loop time for code
    int speedLimit;//  Speed limit value (127 = 100%)
    int kickback;//  Constant kickback force value. Added to power when speed limit is reached
    float kB;//  Kickback scalar for variable kickback force
    int steeringMin;
    int steeringMax;
    int steeringOffset;
    String name;//  Name of setting
    //String password;//  Password to change settings
    
    /*  Variable address offset values  */
    int KP_ADDRESS = 8;
    int KI_ADDRESS = 12;
    int KD_ADDRESS = 16;
    int KS_ADDRESS = 20;
    int ANGLE_OFFSET_ADDRESS = 24;
    int LOOP_TIME_ADDRESS = 28;
    int SPEED_LIMIT_ADDRESS = 32;
    int KICKBACK_ADDRESS = 36;
    int kB_ADDRESS = 40;
    int STEER_MIN_ADDRESS = 44;
    int STEER_MAX_ADDRESS = 48;
    int STEER_OFFSET_ADDRESS = 52;
    int NAME_ADDRESS = 56;
    
    /*  Functions for handling settings  */
    void savekP(float value);
    void savekP();
    void savekI(float value);
    void savekI();
    void savekD(float value);
    void savekD();
    void savekS(int value);
    void savekS();
    void saveAngleOffset(float value);
    void saveAngleOffset();
    void saveLoopTime(int value);
    void saveLoopTime();
    void saveSpeedLimit(int value);
    void saveSpeedLimit();
    void saveKickback(int value);
    void saveKickback();
    void savekB(float value);
    void savekB();
    void saveSteeringMin(int value);
    void saveSteeringMin();
    void saveSteeringMax(int value);
    void saveSteeringMax();
    void saveSteeringOffset(int value);
    void saveSteeringOffset();
    void saveName(String value);
    void saveName();
    
    float loadkP();
    float loadkI();
    float loadkD();
    float loadkS();
    float loadAngleOffset();
    int loadLoopTime();
    int loadSpeedLimit();
    int loadKickback();
    float loadkB();
    int loadSteeringMin();
    int loadSteeringMax();
    int loadSteeringOffset();
    void loadName();
    
  private:
    
};




/*  EEPROM read and write anything functions  */
template <class T> int save(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int load(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

#endif
