#ifndef serialGLCD_h
#define serialGLCD_h

#include "Arduino.h"

class serialGLCD
{
public:
	serialGLCD();        // Empty constructor, but needed.
	
	void clearLCD();		// Clears the screen
	void setDebug(int l);		// Set debug level, 0=off,1=binary,2=text
	void backLight(int x);		// Set backlight duty cycle integer from 0 to 100 where 0 is off
	void drawCircle(int x, int y, int r, int z);		// Draws a circle with center x,y, radius r and z=1 for write, z=0 for erase
	void toggleCRLF();		// toggles CR/LF. each time this command is sent, wheather or not a CR automatically executes a LF is toggled. this is saved to EEPROM and is persistant over power cycles
	void eraseBlock(int x1, int y1, int x2, int y2);		// Erase a block on the screen with top left corner x1,y1, bottom right corner x2,y2
	void resetLCD();		// Resets the LCD, clears the screen and sets x and y offset to 0,0
	void changeBaud(int x);		// Changes the baudrate. 1=4800,2=9600,3=19200,4=38400,5=57600,6=115200. (Persistant)
	void toggleFont();		// Toggles between the default and aux font. does not affect previosly written text.
	void setFontMode(int x);		// Sets the mode for drawing text, default is 7=Copy, and is the only mode that respects reverse color.
	void drawSprite(int x, int y, int n, int mode);		// Draws a sprite stored in the backpack. Uses same modes as when drawing text
	void drawLine(int x1, int y1, int x2, int y2, int z);		// Draws a line from x1,y1 to x2,y2. z=1 to write, z=0 to erase.
	void uploadSprite(int n, int w, int h, byte *data);		// Uploads sprites for use with the drawSprite function (not persistant), MUST be 32 bytes or the display will go out of sync. Consult with firmware README for more info
	void drawBox(int x1, int y1, int x2, int y2, int z);		// Draws a box with top left corner x1,y1, bottom right corner x2,y2. z=1 to write, z=0 to erase
	void togglePixel(int x, int y, int z);		// Toggles a pixel. x,y-coords and z=1 to write, z=0 to erase
	void drawFilledBox(int x1, int y1, int x2, int y2, byte fill);		// Draws a filled box with top left corner x1,y1, bottom right corner x2,y2. the last byte is the fill byte 0x00 for empty 0xFF for filled, other values can be used.
	void reverseColor();		// Inverts the display, text/graphics written before this command will inverted aswell
	void toggleSplash();		// Toggles the sparkfun logo when powering up (persistent)
	void drawData(int x, int y, int mode, int w, int h, byte *data);		// Function to draw bitmaps from an array of hex values, requires the lenght of the array. Consult with firmware README for more info
	void gotoPosition(int x, int y);		// Set the position before writing text
	void gotoLine(int line);		// Simpler way of selecting which line to write text on (1-8). Uses the gotoPosition function, simply splits the screen up in 8 lines
};

#endif


