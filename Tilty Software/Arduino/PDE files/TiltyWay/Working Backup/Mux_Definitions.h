/*  Multiplexer Teensy Pin Defines */
#define B0 22
#define B1 21
#define B2 17
#define B3 20
#define SIG 23

/*  Multiplexer Pin Definitions  */
#define SW1 6
#define SW2 5
#define SW3 4
#define SW4 3
#define SW5 2
#define SW6 1
#define SW7 0
#define TRIM_1 12  // Trim pot R3
#define TRIM_2 13  // Trim pot R4
#define TRIM_3 14  // Trim pot R5
#define TRIM_4 15  // Trim pot R6
#define BATT 7  // Battery sensing

/*  Multiplexer Breakout Pin Settings
Change these if you plan on using the mux breakout pins as other types (Eg. ANALOG_OUT or DIGITAL_IN*/
#define MUX_BREAKOUT_8 DIGITAL_IN
#define MUX_BREAKOUT_9 DIGITAL_IN
#define MUX_BREAKOUT_10 DIGITAL_IN
#define MUX_BREAKOUT_11 DIGITAL_IN

/*  Multiplexer Pin Settings Definitions
Set the correct values in the definitions above if you plan on using the MUX breakout pins.
*/
int muxPinSettings[16] = {DIGITAL_IN, DIGITAL_IN, DIGITAL_IN, DIGITAL_IN, DIGITAL_IN, DIGITAL_IN, DIGITAL_IN,\
                             ANALOG_IN, MUX_BREAKOUT_8, MUX_BREAKOUT_9, MUX_BREAKOUT_10, MUX_BREAKOUT_11,\
                             ANALOG_IN,ANALOG_IN,ANALOG_IN,ANALOG_IN};
    
/*  Setup the multiplexer object  */                 
Multiplexer mux(B0, B1, B2, B3, SIG, muxPinSettings);



