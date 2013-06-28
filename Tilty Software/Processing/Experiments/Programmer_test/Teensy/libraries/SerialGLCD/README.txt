Library for Sparkfun Serial Graphic 128x64 Display with serialGLCD firmware:


This library was written by ¯yvind Schei (http://sourceforge.net/users/sabesto, sabesto@gmail.com) for Sparkfuns Serial Graphic 128x64 LCD.
I concider myself a beginner and i wrote this library in order to help other beginners use this display in a simple but powerfull manner. 

The library works with Jenn Holt's firmware found here: http://sourceforge.net/projects/serialglcd/ (firmware/trunk/main.hex). 
Some of the comments in this library are copied/modified from the firmware readme files.

IMPORTANT! Jenn Holt's firmware only works on the 128x64 display.


I strongly suggest that you install Jenn Holt's firmware if you got this display as it fixes a lot of bugs with the orginal firmware. 
Strange symbols will no longer appear while writing commands to the screen, the backlight will not flicker and 
contrast will work properly (odd that this even was a problem as it has nothing to do with the microcontroller).
In addition, writing to the screen (text/graphics) is a lot faster.

Some of the code was written by Michael Nash (http://www.evernote.com/pub/iklln6/GLCdlibrarywork) for the original firmware, 
but has been changed to work with Jenn Holt's firmware. The new firmware has more functions then the original one, and this 
library contains new functions for most of these.  

In addition to reading this document, i recommend reading the documentation for the firmware.

Feel free to contact me at sabesto@gmail.com or sourceforge for questions or suggestions.


As a sidenote; The datasheet for the backpack states that the input voltage should be 6-7V, 
as it is regulated down to 5v onboard it will not function properly if its supplied with 5v on the Vin pin. 
However, I found that the regulator on the board was really hot when supplying it with 6,5V, so i would recommend one of the following:

1. Supply the Vin pin with about 5,4-5,6V, this is enough to overcome the voltagedrop in the regulator, but not enough for it to heat up.
2. Supply regulated 5V to the unpopulated 5V pin on the opposite side of the board.
3. Short the regulator and supply regulated 5v to the Vin pin.



Functions (look further down for a better explanation): 

serialGLCD()					// Constructor
clearLCD()					// Clear the screen
setDebug(l)					// Set debug level
backLight(x)					// Set backlight
drawCircle(x,y,r,z)				// Draw a circle
toggleCRLF()					// Toggle CRLF
eraseBlock(x1,y1,x2,y2)				// Erase a block
resetLCD()					// Reset the LCD
changeBaud(x)					// Change baud rate
toggleFont()					// Toggle font
setFontMode(x)					// Set font mode
drawSprite(x,y,n,mode)				// Draw a sprite
drawLine(x1,y1,x2,y2,z)				// Draw a line
uploadSprite(n,w,h,data)			// Upload a sprite
drawBox(x1,y1,x2,y2,z)				// Draw a box
togglePixel(x,y,z)				// Toggle pixel on/off
drawFilledBox(x1,y1,x2,y2,fill)			// Draw a filled box
reverseColor()					// Invert / change the color (black on white / white on black)
toggleSplash()					// Toggle splash screen
drawData(x,y,mode,w,h,data)			// Send data directly to LCD
gotoPosition(x,y)				// Go to position
gotoLine(line)					// Go to line


What they do and how to use them:

serialGLCD();
/* Constructor.
Example: serialGLCD lcd;
*/

clearLCD(); 
/* Clears the display. eraseBlock is probably faster if you don't need to erase the entire screen.
Example: lcd.clearLCD();
*/

setDebug(l);
/* 0 = no messages
1 = binary messages, the display will echo a byte = command when the command is started and a byte = 0x00 when the command is finished
2 = text messages, useful when using a terminal. will echo "Entered Command n" when command n is started
and will echo "Exited Command n, RX_buffer=y" when the command is done, and will report how many bytes are in the recieve buffer
Example: lcd.setDebug(1);
*/

backLight(x); 
/* Sets backlight duty cycle. 0-100, 0=off.
Example: lcd.backLight(50);
*/

drawCircle(x,y,r,z); 
/* Draws a circle at (x,y) with radius r, draw/erase 
Example: lcd.drawCircle(30,30,10,1);
*/

toggleCRLF();
/* Toggles CR/LF. each time this command is sent, 
whether or not a CR automatically executes a LF is toggled. 
this is saved to EEPROM and is persistent over power cycles.
Example: lcd.toggleCRLF();
*/

eraseBlock(x1,y1,x2,y2); 
/* Draws a block on the screen with clear or set pixels (depending on if the screen is inverted or not)
Example: lcd.eraseBlock(10,10,20,20);
*/

resetLCD(); 
/* Resets the LCD, clears the screen and resets x,y offsets to 0,0
Example: lcd.resetLCD();
*/

changeBaud(x);
/* Changes the baud rate.
1=4800
2=9600
3=19200
4=38400
5=57600
6=115200
Persistent over power-cycles. Transmitting to the screen during splash resets the baud rate to 115200
Example: lcd.changeBaud(2); // (9600)
*/

toggleFont();
/* Toggles between the standard and AUX font. Only affects text written after the command.
Example: lcd.toggleFont();
*/

setFontMode(x);
/* Sets the mode for which text is written to the text.
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

drawSprite(x,y,n,mode);
/* Draws a sprite saved in the backpack. x and y sets the upper left corner, 
n is the number of the stored sprite, n sets the mode (same modes ad text).
sprite 0 is the Sparkfun logo, other uploaded sprites will be deleted if power is removed.
Example: lcd.drawSprite(10,10,0,7); // Draws the Sparkfun logo
*/

drawLine(x1,y1,x2,y2,z); 
/* Draws a line from x1,y1 to x2,y2. z=1 to draw, z=0 to erase.
Example: lcd.drawLine(10,10,20,20,1); 
*/

uploadSprite(n,w,h,data);
/* Uploads a sprite to the backpack, data must be 32 bytes long. 8 sprites can be stored (0-7).
The Sparkfun logo is number 0, can be overwritten but reverts when power is removed. 
All uploaded sprites will be erased upon removal of power
Consult with firmware README for more info
Example: byte logo[] = {
0x80,0xc0,0x40,0x0c,0x3e,0xfe,0xf2,0xe0,0xf0,0xe0,
0xff,0x7f,0x3f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,0x03,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00};
lcd.uploadSprite(7,10,16,logo); // Uploads the Sparkfun logo as sprite number 7
*/

drawBox(x1,y1,x2,y2,z); 
/* Draws a rectangle starting from x1,y1 to x2,y2. z=1 for draw, z=0 for erase.
Example: lcd.drawBox(10,10,20,20,1);
*/

togglePixel(x,y,z);     
/* Toggles a pixel. x and y for coord, z=1 sets, z=0 erases.
Example: lcd.togglePixel(30,30,1);
*/

drawFilledBox(x1,y1,x2,y2,fill);
/* Same as drawBox, but accepts a fill byte. 0xFF for black, 0x00 for white. 
Other values can be used to create patterns (like 0x55). 
Example: drawFilledBox(10,10,20,20,0xFF);
*/

reverseColor(); 
/* Reverses the "color" (black on white / white on black)
Example: lcd.reverseColor();
*/

toggleSplash();
/* Toggles the Sparkfun logo during boot.
Example: lcd.toggleSplash();
*/

drawData(x,y,mode,w,h,data);
/* Allows you to draw graphics to the screen like sprites, but the data doesn't have to be uploaded first, and there is no size
restrictions.(other than the drawable area of the display). 
Consult with firmware README for more info
Example:
byte data[]={0x00,0x12.....};
lcd.drawData(0,0,4,128,64,data); 
*/

gotoPosition(x,y);    
/* Sets the x and y offsets, text written after this command will start from x,y.
Example: lcd.gotoPosition(40,40);
*/

gotoLine(line);
/* Uses the gotoPosition function to select "line" 1-8 on the display. 
Text can be written between these lines using gotoPosition. This function makes it simpler.
Example: lcd.gotoLine(2);
*/

relayHex(x); 
/* Converts DEC to HEX, then prints it through serial. Used by the library*/



