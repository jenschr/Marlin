#if (ARDUINO < 100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <Wire.h>
#include "OLedI2C.h"

OLedI2C::OLedI2C(){
  _OLED_Address = 0x3c;
  _OLED_Command_Mode = 0x80;
  _OLED_Data_Mode = 0x40;
}

void OLedI2C::begin( uint8_t addr ) {
  Wire.begin();
  if( addr ){
    _OLED_Address = addr;
  }
  init();
}
 
void OLedI2C::setCursor(uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x20, 0x40, 0x60 };
  sendCommand(0x80 | (col + row_offsets[row]));
}

void OLedI2C::clear()
{
  sendCommand(0x01);
  home();
}

// By inheriting from Print.h and overwriting this single method
// we can use all the 9 different print-methods from that class.
size_t OLedI2C::write(uint8_t value)
{
  sendData( value );
}

// Write custom graphic chars to one of the eight possible CGRAM positions
// Thanks to Rafael Camacho (rafaelcamacho @ github) for solving this one!
// Very similar to the LiquidCrystal example, but needs delays to work.
void OLedI2C::createChar(uint8_t location, uint8_t charmap[]) 
{
  location &= 0x7;            // we only have 8 locations 0-7
   
  sendCommand(0x40 | (location << 3));
  delayMicroseconds(30);
   
  for (int i=0; i<8; i++) 
  {
      sendData(charmap[i]);      // call the virtual write method
      delayMicroseconds(40);
  }
}

void OLedI2C::printChar(char singleChar)
{
  sendData(singleChar);
}

// Not required, but nice to have
void OLedI2C::home()
{
  setCursor(0,0);
}

void OLedI2C::lcdOff()
{
  sendCommand(0x08);    // **** Turn on Off
}

void OLedI2C::lcdOn()
{
  sendCommand(0x0C);    // **** Turn on On
}

void OLedI2C::setContrast(unsigned char contrast) // contrast as 0x00 to 0xFF
{
  //Set OLED Command set
  sendCommand(0x2A); 
  sendCommand(0x79);
  sendCommand(0x81);    // Set Contrast
  sendCommand(contrast);  // send contrast value
  sendCommand(0x78);    // Exiting Set OLED Command set
  sendCommand(0x28);
}


// private
void OLedI2C::init() {
  // *** All custom stuff for this specific LCD *** //

  delay(100);
  sendCommand(0x80);
  sendCommand(0x2A); // **** Set "RE"=1  00101010B
  sendCommand(0x71);
  sendCommand(0xC0);
  sendCommand(0x00);
  sendCommand(0x28);

  sendCommand(0x08); // **** Set Sleep Mode On
  sendCommand(0x2A); // **** Set "RE"=1  00101010B
  sendCommand(0x79); // **** Set "SD"=1  01111001B
  /*
  sendCommand(0xD5); // Set Display Clock Divide Ratio/Oscillator Frequency
  sendCommand(0x70);
  */
  sendCommand(0x2A);   // **** Set "RE"=1 
  sendCommand(0x78); // **** Set "SD"=0  01111000B
  
  sendCommand(0x09); // **** Set 5-dot, 3 or 4 line(0x09), 1 or 2 line(0x08)

  sendCommand(0x05); // Common bi-direction function. **** Set Com31-->Com0  Seg0-->Seg99
  
  sendCommand(0x72); // CGROM/CGRAM Management
  sendCommand(0x00);

  // **** Set OLED Characterization *** //
  sendCommand(0x2A);   // **** Set "RE"=1 
  sendCommand(0x79);   // **** Set "SD"=1

  sendCommand(0xDA);   // **** Set Seg Pins HW Config
  sendCommand(0x10);   

  sendCommand(0x81);   // **** Set Contrast
  sendCommand(0xD9);  // 

  sendCommand(0xDB);   // **** Set VCOM deselect level
  sendCommand(0x30);   // **** VCC x 0.83

  sendCommand(0xDC);   // **** Set gpio - turn EN for 15V generator on.
  sendCommand(0x03);

  sendCommand(0x78);   // **** Exiting Set OLED Characterization
  sendCommand(0x28); 
  //sendCommand(0x2A); 
  //sendCommand(0x05);   // **** Set Entry Mode
  sendCommand(0x06);   // **** Set Entry Mode
  //sendCommand(0x08);  
  sendCommand(0x28);   // **** Set "IS"=0 , "RE" =0 //28
  //sendCommand(0x01); 
  sendCommand(0x80);   // **** Set DDRAM Address to 0x80 (line 1 start)

  delay(100);
  sendCommand(0x0C);   // **** Turn on Display
}

void OLedI2C::sendCommand(unsigned char command)
{
  Wire.beginTransmission(_OLED_Address);   // **** Start I2C 
  Wire.write(_OLED_Command_Mode);          // **** Set OLED Command mode
  Wire.write(command);
  Wire.endTransmission();                    // **** End I2C 
  delay(10);
}

void OLedI2C::sendData(unsigned char data)
{
  Wire.beginTransmission(_OLED_Address);    // **** Start I2C 
  Wire.write(_OLED_Data_Mode);        // **** Set OLED Data mode
  Wire.write(data);
  Wire.endTransmission();                     // **** End I2C
}