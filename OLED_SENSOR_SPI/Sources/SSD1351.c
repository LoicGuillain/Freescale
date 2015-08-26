/*
 * SSD1351.c
 *
 *  Created on: 30 juil. 2015
 *      Author: lguillain
 */

#include "SSD1351.h"
#include "WAIT1.h"

extern const unsigned char font5x8[][6];

void writeCommand(uint8_t command) {
    OLED_DC_PutVal(NULL,0);
    //SM1_SendBlock(NULL,&command,1);
    SM1_SendChar(command);
}

void writeData(uint8_t data) {
    OLED_DC_PutVal(NULL,1);
    //SM1_SendBlock(NULL,&data,1);
    SM1_SendChar(data);
}

void writeColor(uint16_t color) {
    OLED_DC_PutVal(NULL,1);
    //SM1_SendBlock(NULL,&color,2);
    SM1_SendChar(color>>8);
    SM1_SendChar(color);
}

void reset(void){
	OLED_RESET_PutVal(NULL,0);
	OLED_RESET_PutVal(NULL,1);
}

void begin(void){
	OLED_RESET_PutVal(NULL,1);
	reset();

	// Initialization Sequence
	writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
	writeData(0x12);
	writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
	writeData(0xB1);

	writeCommand(SSD1351_CMD_DISPLAYOFF);  		// 0xAE

	writeCommand(SSD1351_CMD_CLOCKDIV);  		// 0xB3
	writeCommand(0xF1);  						// 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)

	writeCommand(SSD1351_CMD_MUXRATIO);
	writeData(127);

	writeCommand(SSD1351_CMD_SETREMAP);
	writeData(0x74);

	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(0x00);
	writeData(0x7F);
	writeCommand(SSD1351_CMD_SETROW);
	writeData(0x00);
	writeData(0x7F);

	writeCommand(SSD1351_CMD_STARTLINE); 		// 0xA1
	if (SSD1351HEIGHT == 96) {
	  writeData(96);
	} else {
	  writeData(0);
	}


	writeCommand(SSD1351_CMD_DISPLAYOFFSET); 	// 0xA2
	writeData(0x0);

	writeCommand(SSD1351_CMD_SETGPIO);
	writeData(0x00);

	writeCommand(SSD1351_CMD_FUNCTIONSELECT);
	writeData(0x01); // internal (diode drop)
	//writeData(0x01); // external bias

//    writeCommand(SSSD1351_CMD_SETPHASELENGTH);
//    writeData(0x32);

	writeCommand(SSD1351_CMD_PRECHARGE);  		// 0xB1
	writeCommand(0x32);

	writeCommand(SSD1351_CMD_VCOMH);  			// 0xBE
	writeCommand(0x05);

	writeCommand(SSD1351_CMD_NORMALDISPLAY);  	// 0xA6

	writeCommand(SSD1351_CMD_CONTRASTABC);
	writeData(0xC8);
	writeData(0x80);
	writeData(0xC8);

	writeCommand(SSD1351_CMD_CONTRASTMASTER);
	writeData(0x0F);

	writeCommand(SSD1351_CMD_SETVSL );
	writeData(0xA0);
	writeData(0xB5);
	writeData(0x55);

	writeCommand(SSD1351_CMD_PRECHARGE2);
	writeData(0x01);

	writeCommand(SSD1351_CMD_DISPLAYON);		//--turn on oled panel

}

uint16_t Color565(uint8_t red, uint8_t green, uint8_t blue){
	uint16_t c;
	c = red >> 3;
	c <<= 6;
	c |= green >> 2;
	c <<= 5;
	c |= blue >> 3;

	return c;
}

void goTo(uint8_t x, uint8_t y){
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) return;

	// set x and y coordinate
	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(x);
	writeData(SSD1351WIDTH-1);

	writeCommand(SSD1351_CMD_SETROW);
	writeData(y);
	writeData(SSD1351HEIGHT-1);

	writeCommand(SSD1351_CMD_WRITERAM);
}


void fillRect(uint8_t x, uint8_t y , uint8_t w, uint8_t h , uint16_t color){
	 if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
	    return;

	  // Y bounds check
	  if (y+h > SSD1351HEIGHT)
	  {
	    h = SSD1351HEIGHT - y - 1;
	  }

	  // X bounds check
	  if (x+w > SSD1351WIDTH)
	  {
	    w = SSD1351WIDTH - x - 1;
	  }

	  // set location
	  writeCommand(SSD1351_CMD_SETCOLUMN);
	  writeData(x);
	  writeData(x+w-1);
	  writeCommand(SSD1351_CMD_SETROW);
	  writeData(y);
	  writeData(y+h-1);
	  // fill!
	  writeCommand(SSD1351_CMD_WRITERAM);

	  for (uint16_t i=0; i < w*h; i++) {
	    //writeColor(color);
		  writeData(color>>8);
		  writeData(color);
	  }
}
void clear(uint16_t fillcolor){
	fillRect(0, 0, SSD1351WIDTH, SSD1351HEIGHT, fillcolor);
}

void drawPixel (uint8_t x, uint8_t y, uint16_t color){
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) return;
	goTo(x, y);
	writeData(color>>8);
	writeData(color);
}

void drawVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color){
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
	return;

	// Y bounds check
	if (y+h > SSD1351HEIGHT)
	{
		h = SSD1351HEIGHT - y - 1;
	}

	// set location
	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(x);
	writeData(x);
	writeCommand(SSD1351_CMD_SETROW);
	writeData(y);
	writeData(y+h-1);
	// fill!
	writeCommand(SSD1351_CMD_WRITERAM);

	for (uint8_t i=0; i < h; i++) {
		writeData(color>>8);
		writeData(color);
	}
}

void drawHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color){
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
		return;

	  // X bounds check
	  if (x+w > SSD1351WIDTH)
	  {
		w = SSD1351WIDTH - x - 1;
	  }

	  // set location
	  writeCommand(SSD1351_CMD_SETCOLUMN);
	  writeData(x);
	  writeData(x+w-1);
	  writeCommand(SSD1351_CMD_SETROW);
	  writeData(y);
	  writeData(y);
	  // fill!
	  writeCommand(SSD1351_CMD_WRITERAM);

	  for (uint8_t i=0; i < w; i++){
		  writeData(color>>8);
		  writeData(color);
	  }
}

void drawChar(unsigned char character, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour) {
    uint8_t row, column;

    // To speed up plotting we define a x window of 6 pixels and then
    // write out one row at a time.  This means the LCD will correctly
    // update the memory pointer saving us a good few bytes

    writeCommand(SSD1351_CMD_SETCOLUMN); // Horizontal Address Start Position
    writeData(x);
    writeData(x+5);

    writeCommand(SSD1351_CMD_SETROW); // Vertical Address end Position
    writeData(y);
    writeData(0x7F);

    writeCommand(SSD1351_CMD_WRITERAM);

    // Plot the font data
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 6; column++) {
            if ((font5x8[character][column]) & (1 << row)){ // using PROGMEM instead
        	    //writeData(fgColour>>8);
            	//writeData(fgColour);
            	writeColor(fgColour);
            }
            else{
            	//writeData(bgColour>>8);
            	//writeData(bgColour);
            	writeColor(bgColour);
            }
        }
    }
}

void drawString(const char *string, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour) {
    uint8_t origin = x;

    for (uint8_t characterNumber = 0; characterNumber < strlen(string); characterNumber++) {
        // Check if we are out of bounds and move to
        // the next line if we are
        if (x > 119) {
            x = origin;
            y += 8;
        }

        // If we move past the bottom of the screen just exit
        if (y > 119) break;

        // Plot the current character
        drawChar(string[characterNumber], x, y, fgColour, bgColour);
        x += 6;
    }
}
