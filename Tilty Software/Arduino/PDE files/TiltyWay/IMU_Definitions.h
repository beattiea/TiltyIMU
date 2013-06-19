/*  Board Type Definition  */
//#define GEN_MPU6050  // Defines the TeensyWay as a generic MPU6050 IMU board

/*  Defines whether the TeensyWay has the compass module  
Uncomment the below lines if the compass is installed  */
//#define HAS_HMC5883L() true
//#define IS_9DOM() true
//define IS_6DOM() false

/*  Setup the IMU objects  */
FreeIMU IMU = FreeIMU();
MPU60X0 mpu6050 = MPU60X0();

/*  IMU Function Definitions  */
void checkIMUconnection();
void startIMU();

/*  Yaw, Pitch, and Roll Array Indexes  */
#define YAW 0
#define PITCH 2
#define ROLL 1

/*  IMU Variable Declarations  */
float val[9], q[4], ypr[3];// float arrays to retrieve IMU data fro freeIMU
float yaw_offset, pitch_offset = -0.5, roll_offset;
