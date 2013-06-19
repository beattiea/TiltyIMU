/*  Serial command values  */
final char SET = '|';
final char READ = ']';
final char SAVE = '=';
final char LOAD = '_';
final char STREAM = '}';
final char PING = ')';
final char CONFIRM = '*';

/*  Serial data indicators  */
/*  These are sent from the computer to indicate what variable to act upon  */
final char VARIABLE_kP = 'p';//  Set kP value
final char VARIABLE_kI = 'i';//  Set kI value
final char VARIABLE_kD = 'd';//  Set kD value
final char VARIABLE_P = 'P';//  Read P value
final char VARIABLE_I = 'I';//  Read I value
final char VARIABLE_D = 'D';//  Read D value
final char VARIABLE_kS = 's';//  Set kS value
final char VARIABLE_SOFFSET = 'q';//  Set steering offset
final char VARIABLE_S = 'S';//  Read steering value
final char VARIABLE_ANGLE = 'A';//  Read pitch angle
final char VARIABLE_ROLL = 'R';//  Read roll angle
final char VARIABLE_YAW = 'Y';//  Read yaw angle
final char VARIABLE_OFFSET = 'o';//  Set angle offset value
final char VARIABLE_LOOP = 't';//  Set fixed loop time (in milliseconds)
final char VARIABLE_SPEED = 'l';//  Set speed limit %
final char VARIABLE_KICK  = 'k';//  Set speed limit kick back
final char VARIABLE_TRIM = 'T';//  Read trim pot values

final char TRUE = '1';
final char FALSE = '0';

/*  Variables to control data streaming  */
boolean STREAM_DATA = false;//  Global streaming controller
boolean STREAM_ANGLE = false;
boolean STREAM_P = false;
boolean STREAM_I = false;
boolean STREAM_D = false;
boolean STREAM_PID = false;
boolean STREAM_STEERING = false;
boolean STREAM_LOOP = false;
