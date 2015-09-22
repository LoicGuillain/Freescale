/*
 * SSD1351.c
 *
 *  Created on: 30 juil. 2015
 *      Author: lguillain
 */

#include "SSD1351.h"
#include "WAIT1.h"

//extern const unsigned char font5x8[][6];
#ifndef NO_SCREEN
#include "font5x8.cpp"
#include "image.cpp"
#endif
#include "spi_next.h"

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

	//writeCommand(SSD1351_CMD_DISPLAYON);		//--turn on oled panel

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

void printImage(const uint16_t image[],int x, int y, int width, int height){ //image = 128*160 pixels
	 uint16_t pixel;
	    if(x+width > SSD1351WIDTH || y+height > SSD1351HEIGHT)
	    	return;

	    writeCommand(SSD1351_CMD_SETCOLUMN);
	    writeData(x);
	    writeData(x+width-1);

	    writeCommand(SSD1351_CMD_SETROW);
	    writeData(y);
	    writeData(y+height-1);

	    writeCommand(SSD1351_CMD_WRITERAM);
		for( pixel = 0; pixel < height*width; pixel++){
			writeData(image[pixel*2]); //pixels are defined by two bytes
			writeData(image[pixel*2+1]);
		}

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
        for (column = 0; column < 6; column++) { //6
            if ((font5x8[character][column]) & (1 << row)){ // or font2 but not very good
            	writeColor(fgColour);
            }
            else{
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
        if(string[characterNumber] == ';')
        {
        	x= origin;
        	y += 8;
        	characterNumber += 1;
        }
        drawChar(string[characterNumber], x, y, fgColour, bgColour);
        x += 6;
    }
}

void printFinger(uint8_t* fingerTemplate, uint8_t x, int color){

	if (x+89 >= SSD1351WIDTH)
		return;
	int i,j;

	writeCommand(SSD1351_CMD_SETCOLUMN); // Horizontal Address Start Position
	writeData(x);
	writeData(x+89);

	writeCommand(SSD1351_CMD_SETROW); // Vertical Address end Position
	writeData(0);
	writeData(0x7F);

	writeCommand(SSD1351_CMD_WRITERAM);

	switch(color){
	case PINK:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
			for( j=0; j < NEXT_MAX_ROW ; j+=2) {
				if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
					writeColor(rgb24to16(0xFF, fingerTemplate[(j*NEXT_MAX_COL)+i], 0xFF));
				else
					writeColor(0x0000);
			}
		}
	break;

	case CYAN:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
					for( j=0; j < NEXT_MAX_ROW ; j+=2) {
						if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
							writeColor(rgb24to16(fingerTemplate[(j*NEXT_MAX_COL)+i], 0xFF, 0xFF));
						else
							writeColor(0x0000);
					}
		}
	break;

	case YELLOW:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
			for( j=0; j < NEXT_MAX_ROW ; j+=2) {
				if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
					writeColor(rgb24to16(0xFF, 0xFF, fingerTemplate[(j*NEXT_MAX_COL)+i]));
				else
					writeColor(0x0000);
			}
		}
	break;

	case BLACK:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
					for( j=0; j < NEXT_MAX_ROW ; j+=2) {
						if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
							writeColor(0x0000);
						else
							writeColor(0xFFFF);
					}
		}
	break;

	case RED:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
					for( j=0; j < NEXT_MAX_ROW ; j+=2) {
						if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
							writeColor(0xF800);
						else
							writeColor(0x0000);
					}
		}
	break;

	case GREEN:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
					for( j=0; j < NEXT_MAX_ROW ; j+=2) {
						if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
							writeColor(0x07E0);
						else
							writeColor(0x0000);
					}
		}
	break;

	case BLUE:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
					for( j=0; j < NEXT_MAX_ROW ; j+=2) {
						if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
							writeColor(0x001F);
						else
							writeColor(0x0000);
					}
		}
	break;

	case WHITE:
		for( i=0; i< NEXT_MAX_COL ; i+=2) {
					for( j=0; j < NEXT_MAX_ROW ; j+=2) {
						if(fingerTemplate[(j*NEXT_MAX_COL)+i] < 0x80)
							writeColor(0xFFFF);
						else
							writeColor(0x0000);
					}
		}
	break;

	default:
		return;
	}
}
