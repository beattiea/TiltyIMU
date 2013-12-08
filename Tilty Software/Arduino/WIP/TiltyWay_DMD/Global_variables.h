// IMU variables and objects
#define MPU6050_DMP_FIFO_RATE ((200 / IMU_REFRESH_RATE) - 1)
MPU6050 imu;
// Places to store MPU6050 IMU readings
float ypr[3];			// [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float ypr_offset[3] = {0, 0, 0};	// [yaw, pitch, roll] offset value container for manually adjusting zero angle
float yaw, pitch, roll; // Variables to hold adjusted values (ypr[] - ypr_offset[])


// PID variables and objects
float tilt_power = 0;
PID tiltPID = PID(&ypr[PITCH], &tilt_power, TILT_kP, TILT_kI, TILT_kD, TILT_DIRECTION);


// Motor Driver stuff
MotorDriver motors;