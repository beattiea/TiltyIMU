#include "serialGLCD.h"
#include "Arduino.h"

serialGLCD::serialGLCD()
{	/* Constructor.
	 Example: serialGLCD lcd;
	 */
}

void serialGLCD::clearLCD() 
{   /* Clears the display, eraseBlock is probably faster if you dont need to erase the entire screen.
	 Example: lcd.clearLCD();
	 */  
	Serial.write(0x7C);
	Serial.write(byte(0x00));
}
void serialGLCD::setDebug(int l)
{	/*
	 0 = no messages
	 1 = binary messages, the display will echo a byte = command when the command is started and a byte = 0x00 when the command is finished
	 2 = text messages, useful when using a terminal. will echo "Entered Command n" when command n is started
	 and will echo "Exited Command n, RX_buffer=y" when the command is done, and will report how many bytes are in the recieve buffer
	 Example: lcd.setDebug(1);
	 */
	Serial.write(0x7C);
	Serial.write(0x01);
	Serial.write(l);
}
void serialGLCD::backLight(int x) 
{   /* Sets backlight duty cycle. 0-100, 0=off.
	 Example: lcd.backLight(50);
	 */
	Serial.write(0x7C);
	Serial.write(0x02);
	Serial.write(x);
}
void serialGLCD::drawCircle(int x, int y, int r, int z) 
{   /* Draws a circle at (x,y) with radius r, draw/erase 
	 Example: lcd.drawCircle(30,30,10,1);
	 */
	Serial.write(0x7C);
	Serial.write(0x03);
	Serial.write(x);
	Serial.write(y);
	Serial.write(r);
	Serial.write(z);
}
void serialGLCD::toggleCRLF()
{	/* Toggles CR/LF. each time this command is sent, 
	 wheather or not a CR automatically executes a LF is toggled. 
	 this is saved to EEPROM and is persistant over power cycles.
	 Example: lcd.toggleCRLF();
	 */
	Serial.write(0x7C);
	Serial.write(0x04);
}
void serialGLCD::eraseBlock(int x1, int y1, int x2, int y2) 
{	/* Draws a block on the screen with clear or set pixels (depending on if the screen is inverted or not)
	 Example: lcd.eraseBlock(10,10,20,20);
	 */
	Serial.write(0x7C);
	Serial.write(0x05);
	Serial.write(x1);
	Serial.write(y1);
	Serial.write(x2);
	Serial.write(y2);
}
void serialGLCD::resetLCD() 
{	/* Resets the LCD, clears the screen and resets x,y offsets to 0,0
	 Example: lcd.resetLCD();
	 */
	Serial.write(0x7C);
	Serial.write(0x06);
}
void serialGLCD::changeBaud(int x)
{	/* Changes the baudrate.
	 1=4800
	 2=9600
	 3=19200
	 4=38400
	 5=57600
	 6=115200
	 Persistant over power-cycles. Transmitting to the screen during splash resets the baudrate to 115200
	 Example: lcd.changeBaud(2); // (9600)
	 */
	if(x<1) {
		x=1;
	}
	if(x>6) {
		x=6;
	}
	Serial.write(0x7C);
	Serial.write(0x07);
	Serial.write(x);
}
void serialGLCD::toggleFont()
{	/* Toggles between the standard and AUX font. Only affects text written after the command.
	 Example: lcd.toggleFont();
	 */
	Serial.write(0x7C);
	Serial.write(0x08);
}
void serialGLCD::setFontMode(int x)
{	/* Sets the mode for which text is written to the text.
	 0= AND
	 1= NAND
	 2= OR
	 3= NOR
	 4= XOR
	 5= NXOR
	 6= don't uses this one, will result in corrupted characters
	 7= COPY (this is the default, overwrites whatever is in the background, and is the only one that respects reverse)
	 Example: lcd.setFontMode(2); // (AND)
	 */
	Serial.write(0x7C);
	Serial.write(0x0A);
	Serial.write(x);
}
void serialGLCD::drawSprite(int x, int y, int n, int mode)
{	/* Draws a sprite saved in the backpack. x and y sets the upper left corner, 
	 n is the number of the stored sprite, n sets the mode (same modes ad text).
	 sprite 0 is the sparkfun logo, other uploaded sprites will be deleted if power is removed.
	 Example: lcd.drawSprite(10,10,0,7); // Draws the sparkfun logo
	 */
	Serial.write(0x7C);
	Serial.write(0x0B);
	Serial.write(x);
	Serial.write(y);
	Serial.write(n);
	Serial.write(mode);
}
void serialGLCD::drawLine(int x1, int y1, int x2, int y2, int z) 
{	/* Draws a line from x1,y1 to x2,y2. z=1 to draw, z=0 to erase.
	 Example: lcd.drawLine(10,10,20,20,1); 
	 */
	Serial.write(0x7C);
	Serial.write(0x0C);
	Serial.write(x1);
	Serial.write(y1);
	Serial.write(x2);
	Serial.write(y2);
	Serial.write(z);
}
void serialGLCD::uploadSprite(int n, int w, int h, byte *data)
{	/* Uploads a sprite to the backpack, data must be 32 bytes long. 8 sprites can be stored (0-7).
	 The sparkfun logo is number 0, can be overwritten but reverts when power is removed. 
	 All uploaded sprites will be erased upon removal of power
	 Consult with firmware README for more info
	 Example: byte logo[] = {
	 0x80,0xc0,0x40,0x0c,0x3e,0xfe,0xf2,0xe0,0xf0,0xe0,
	 0xff,0x7f,0x3f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,0x03,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00};
	 lcd.uploadSprite(7,10,16,logo); // Uploads the sparkfun logo as sprite number 7
	 */
	Serial.write(0x7C);
	Serial.write(0x0D);
	Serial.write(n);
	Serial.write(w);
	Serial.write(h);;
	for(int x = 0; x < 32;x++)
	{
		Serial.write(data[x]);
	}
}
void serialGLCD::drawBox(int x1, int y1, int x2, int y2, int z) 
{	/* Draws a rectangle starting from x1,y1 to x2,y2. z=1 for draw, z=0 for erase.
	 Example: lcd.drawBox(10,10,20,20,1);
	 */
	Serial.write(0x7C);
	Serial.write(0x0F);
	Serial.write(x1);
	Serial.write(y1);
	Serial.write(x2);
	Serial.write(y2);
	Serial.write(z);
}
void serialGLCD::togglePixel(int x, int y, int z) 
{     /* Toggles a pixel. x and y for coord, z=1 sets, z=0 erases.
	   Example: lcd.togglePixel(30,30,1);
	   */
	Serial.write(0x7C);
	Serial.write(0x10);
	if(x > 128) {
		Serial.write(128);
	}
	else if(x < 0) {
		Serial.write(byte(0x00));
	}
	else {
		Serial.write(x);
	}
	if(y > 64) {
		Serial.write(64);
	}
	else if(y < 0) {
		Serial.write(byte(0x00));
	}
	else {
		Serial.write(y);
	}
	if(z != 1 && z != 0) {
		Serial.write(1);
	}
	else {
		Serial.write(z);
	}
}
void serialGLCD::drawFilledBox(int x1, int y1, int x2, int y2, byte fill)
{	/* Same as drawBox, but accepts a fill byte. 0xFF for black, 0x00 for white. 
	 Other values can be used to create patterns (like 0x55). 
	 Example: drawFilledBox(10,10,20,20,0xFF);
	 */
	Serial.write(0x7C);
	Serial.write(0x12);
	Serial.write(x1);
	Serial.write(y1);
	Serial.write(x2);
	Serial.write(y2);
	Serial.write(fill);
	
}
void serialGLCD::reverseColor() 
{	/* Reverses the "color" (black on white / white on black)
	 Example: lcd.reverseColor();
	 */
	Serial.write(0x7C);
	Serial.write(0x14);
}
void serialGLCD::toggleSplash()
{	/* Toggles the sparkfun logo during boot.
	 Example: lcd.toggleSplash();
	 */
	Serial.write(0x7C);
	Serial.write(0x15);
}
void serialGLCD::drawData(int x, int y, int mode, int w, int h, byte *data)
{	/* Allows you to draw graphics to the screen like sprites, but the data doesn't have to be uploaded first, and there is no size
	 restrictions.(other than the drawable area of the display). 
	 Consult with firmware README for more info
	 Example:
	 byte data[]={0x00,0x12.....};
	 lcd.drawData(0,0,4,128,64,data); 
	 */
	Serial.write(0x7C);
	Serial.write(0x16);
	Serial.write(x);
	Serial.write(y);
	Serial.write(mode);
	Serial.write(w);
	Serial.write(h);
	int length = w*h/8;
	for(x = 0; x < length; x++) {
		Serial.write(data[x]);
	}
}
void serialGLCD::gotoPosition(int x, int y) 
{  	/* Sets the x and y offsets, text written after this command will start from x,y.
	 Example: lcd.gotoPosition(40,40);
	 */
	Serial.write(0x7C);
	Serial.write(0x18);
	Serial.write(x);
	Serial.write(0x7C);
	Serial.write(0x19);
	Serial.write(y);
}
void serialGLCD::gotoLine(int line)
{	/* Uses the gotoPosition function to select "line" 1-8 on the display. 
	 Text can be written between these lines using gotoPosition. This function makes it simpler.
	 Example: lcd.gotoLine(2);
	 */
	int y;
	if(line > 8) {
		line = 8;
	}
	else if(line < 1) {
		line = 1;
	}
	else {
		y = -8 + line * 8;
		gotoPosition(1,y);
	}
}