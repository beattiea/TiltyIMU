//================= Setup and Connection Settings =================//
#define STEERING_TYPE 0  // 0 = Arcade style control (1 signal is speed, 1 signal is steering)
                         // 1 = Tank style control (1 signal controls each motor)

// Part connection selection. Can be a pin # (ex: 2, 5, etc.) or a servo header (ex: SERVO_HEADER_1)
#define STEERING_SENSE_PIN SERVO_HEADER_3  // Pin or header connected to steering potentiometer
#define RESET_PIN SERVO_HEADER_4           // Pin or header to connect reset button to (High = reset)
//=================================================================//



//================= Control and Behavior Settings =================//
#define TILT_DIRECTION REVERSE // Motor directions to balance. FORWARD/REVERSE reverse motor directions
#define TURN_DIRECTION FORWARD // Motor directions to turn. FORWARD/REVERSE reverse motor directions

/* Soft Control Limits
Exceeding these will cause the program to try to force slowing by overcompensating for inputs*/
#define POWER_LIMIT 0.75  // Percentage of MAX_POWER that causes overcompensation to force slowing

/* Hard Cutoff Limits
Exceeding these values will cause the program to stop and throw an error code*/
#define MAX_PITCH 40    // Maximum forward and backwards tilt from balanced position
#define MAX_ROLL 45     // Maximum side-to-side roll from level ground
#define MAX_POWER 0.85  // Percentage of maximum power allowed (ex: 0.90 = 90% of max power)

/* Startup Control Values
These settings control both initialization and restarting after an error*/
#define STARTING_PITCH 0.0        // Pitch angle required to start balancing
#define STARTING_PITCH_RANGE 1.0  // Pitch must be within STARTING_PITCH +-  STARTING_PITCH_RANGE
#define REQUIRED_TIME 50          // Milliseconds for which pitch must meet starting pitch requirements
//#define STEERING_RANGE
//=================================================================//



//================= IMU Settings =================//
/* IMU angle array positions. 
These are based on the Tilty pointing forward (USB away from the user
and being mounted upright (logo is visible from above) */
#define YAW 0
#define PITCH 2
#define ROLL 1

#define IMU_REFRESH_RATE 200   // IMU data refresh rate in Hz. Max of 200 hz, which may give noisy data.
                               // Should not go below 100 Hz for balancing
                               // Valid values: 200, 100, 67, 50, 40, 33, 29, 25

#define IMU_READ_ERROR_LIMIT 3 // Maximum consecutive IMU read errors before SOS is triggered
//================================================//



//================= PID Control Settings =================//
#define TILT_kP 17            // Proportional PID scalar. Scales with tilt.
#define TILT_kI 0.25            // Integral PID scalar. Scales with time and tilt.
#define TILT_kD 25            // Derivative PID scalar. Scales with rate of tilt.
#define MAX_PID 255  // Maximum value allowed for P + I + D.
//========================================================//




//================= Constant Settings	DO NOT CHANGE =================//

// Voltage Sensing
#define VOLTAGE_SENSE_PIN 14
#define VOLTAGE_DIVIDER 0.05061465

// Pin Settings
#define LED 13
#define SERVO_HEADER_1 2
#define SERVO_HEADER_2 3
#define SERVO_HEADER_3 22
#define SERVO_HEADER_4 23