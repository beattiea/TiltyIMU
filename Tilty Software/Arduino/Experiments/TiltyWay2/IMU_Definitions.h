/*  Board Type Definition  */
//#define GEN_MPU6050  // Defines the TeensyWay as a generic MPU6050 IMU board

/*  Defines whether the TeensyWay has the compass module  
Uncomment the below lines if the compass is installed  */
//#define HAS_HMC5883L() true
//#define IS_9DOM() true
//define IS_6DOM() false

/*  Setup the IMU objects  */
FreeIMU IMU = FreeIMU();
MPU6050 mpu6050 = MPU6050();

/*  IMU Function Definitions  */
void checkIMUconnection();
void startIMU();

/*  Yaw, Pitch, and Roll Array Indexes  */
#define YAW 0
#define PITCH 2
#define ROLL 1

/*  IMU Variable Declarations  */
float val[9], q[4], ypr[3];// float arrays to retrieve IMU data fro freeIMU
float yaw_offset = 1.221053012 - 0.245624384, pitch_offset = 3.5, roll_offset;

/*  Velocity variables  (derivatives of absolute angles)  */
float dYaw = 0, dYaw_old = 0;
float dPitch = 0.0075, dPitch_old;
float dRoll = 0, dRoll_old = 0;

/*  Acceleration variables (derivatives of angular velocities)  */
float ddPitch = 0, ddPitch_old = 0;
float ddRoll = 0, ddRoll_old = 0;
float ddYaw = 0, ddYaw_old = 0;
