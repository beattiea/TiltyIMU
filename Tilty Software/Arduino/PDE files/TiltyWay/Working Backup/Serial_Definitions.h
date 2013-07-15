#define myPort Serial2

/*  Serial commands  */
#define SET_COMMAND '|'
#define READ_COMMAND ']'
#define SAVE_COMMAND '='
#define LOAD_SAVED_COMMAND '_'
#define STREAMING_COMMAND '}'
#define PING ')'
#define CONFIRM '*'

/*  Serial data indicators  */
/*  These are sent from the computer to indicate what variable to act upon  */
#define VARIABLE_kP 'p'//  Set kP value
#define VARIABLE_kI 'i'//  Set kI value
#define VARIABLE_kD 'd'//  Set kD value
#define VARIABLE_P 'P'//  Read P value
#define VARIABLE_I 'I'//  Read I value
#define VARIABLE_D 'D'//  Read D value
#define VARIABLE_kS 's'//  Set kS value
#define VARIABLE_SOFFSET 'q'//  Set steering offset value      Not yet implemented
#define VARIABLE_S 'S'//  Read steering value
#define VARIABLE_ANGLE 'A'//  Read pitch angle
#define VARIABLE_ROLL 'R'//  Read roll angle
#define VARIABLE_YAW 'Y'//  Read yaw angle
#define VARIABLE_OFFSET 'o'//  Set angle offset value
#define VARIABLE_LOOP 't'//  Set fixed loop time (in milliseconds)
#define VARIABLE_SPEED 'l'//  Set speed limit %
#define VARIABLE_KICK  'k'//  Set speed limit kick back
#define VARIABLE_TRIM 'T'//  Read trim pot values

#define TRUE '1'
#define FALSE '0'

/*  Variables to control data streaming  */
boolean STREAM_DATA = false;//  Global streaming controller
boolean STREAM_ANGLE = false;
boolean STREAM_P = false;
boolean STREAM_I = false;
boolean STREAM_D = false;
boolean STREAM_S = false;
boolean STREAM_LOOP = false;
