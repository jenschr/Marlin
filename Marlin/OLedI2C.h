/*

Library for 20x4/2004 OLED screens based on the SSD131x controller
This allows you to build a full reprap controller with a sexy oled
instead of the typical thick LED's with poor contrast & visibility.

I'm using one of the screens from wide.hk, but it should work with
others based on the chip as well.

This library is based in part on ideas from the OLED 1602 library
published by Phil Grant:
http://gadjetsblog.blogspot.no/2013/09/oled-1602-display-and-library-for.html

To use this library with a 16x2/1602 screen, it should be sufficient
to replace sendCommand(0x09) with sendCommand(0x08) in the init()
method. Unfortunately I don't have access to a screen to test with.

*/

#ifndef OLedI2C_h
#define OLedI2C_h

#if (ARDUINO < 100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <inttypes.h>
#include <Print.h>

class OLedI2C : public Print {
public:
	OLedI2C();
	void begin(uint8_t);
	virtual size_t write(uint8_t);
  	using Print::write;
	void clear();
	void setCursor(uint8_t, uint8_t); // column, row
	void createChar(uint8_t, uint8_t[]);
	void printChar(char);

	// Not required, but useful
	void home();
	void scrollString(char* message, byte row, unsigned int time); //written by Nathan Chantrell http://nathan.chantrell.net/
	void lcdOff();
	void lcdOn();
	void setContrast(unsigned char contrast); // contrast should be the hex value between 0x00 and 0xFF
private:
	void init();
	void sendCommand(unsigned char command);
	void sendData(unsigned char data);
	uint8_t _OLED_Address; // I2C address
	uint8_t _OLED_Command_Mode; // bit to set for entering Command mode
	uint8_t _OLED_Data_Mode; // bit to set for sending data
};

#endif
