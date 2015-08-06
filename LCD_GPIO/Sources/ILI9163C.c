/*
 * ILI9163C.c
 *
 *  Created on: 12 juin 2015
 *      Author: lguillain
 */

#include "ILI9163C.h"


LDD_TDeviceData *Led_Lcd, *Cs_Lcd, *Rs_Lcd, *Reset_Lcd, *Scl_Lcd, *Sda_Lcd;
extern const unsigned char font5x8[][6];
static int variable = 0;
void waitUs(int us)	{

	for(int i = 0; i < (1*us); i++){
		variable++;
	}
}

void waitMs(int ms)	{

	for(int i = 0; i < (1000*ms); i++){
		waitUs(1);
	}
}

void lcd_Reset(void) {
    // Reset pin is active low (0 = reset, 1 = ready)

	LCD_RST_PutVal(Reset_Lcd,0);

	waitMs(5);
	LCD_RST_PutVal(Reset_Lcd,1);

    waitMs(5);

}

void writeCommand(uint8_t address) {
    uint8_t i;
    LCD_CS_PutVal(Cs_Lcd,0);
    LCD_RS_PutVal(Rs_Lcd,0);
    for(i=0;i<8;i++) {
        if(address & (0x80>>i)){
        	LCD_SDA_PutVal(Sda_Lcd,1);
        }
        else {
        	LCD_SDA_PutVal(Sda_Lcd,0);
        }
        LCD_SCL_PutVal(Scl_Lcd,1);
        LCD_SCL_PutVal(Scl_Lcd,0);
    }

    LCD_CS_PutVal(Cs_Lcd,1);
}



void writeParameter(uint8_t parameter) {
    uint8_t i;
    LCD_CS_PutVal(Cs_Lcd,0);
    LCD_RS_PutVal(Rs_Lcd,1);
    for(i=0;i<8;i++) {
        if(parameter & (0x80>>i)){
        	LCD_SDA_PutVal(Sda_Lcd,1);
        }
        else{
        	LCD_SDA_PutVal(Sda_Lcd,0);
        }
        LCD_SCL_PutVal(Scl_Lcd,1);
        LCD_SCL_PutVal(Scl_Lcd,0);
    }

    LCD_CS_PutVal(Cs_Lcd,1);
}

void writeData(uint16_t word) {
    uint8_t i;
    LCD_CS_PutVal(Cs_Lcd,0);
    LCD_RS_PutVal(Rs_Lcd,1);
    for(i=0;i<16;i++) {
        if(word & (0x8000>>i)){
        	LCD_SDA_PutVal(Sda_Lcd,1);
        }
        else{
        	LCD_SDA_PutVal(Sda_Lcd,0);
        }

        LCD_SCL_PutVal(Scl_Lcd,1);
        LCD_SCL_PutVal(Scl_Lcd,0);
    }

    LCD_CS_PutVal(Cs_Lcd,1);
}

void clear(uint16_t colour) {
    uint16_t pixel;

    // Set the column address to 0-127
    writeCommand(SET_COLUMN_ADDRESS);
    writeParameter(0x00);
    writeParameter(0x00);
    writeParameter(0x00);
    writeParameter(0x7f);

    // Set the page address to 0-159
    writeCommand(SET_PAGE_ADDRESS);
    writeParameter(0x00);
    writeParameter(0x00);
    writeParameter(0x00);
    writeParameter(0x9f);

    // Plot the pixels
    writeCommand(WRITE_MEMORY_START);
    for( pixel = 0; pixel < 20480; pixel++) writeData(colour);
}

void init(uint8_t orientation) {
	LCD_CS_PutVal(NULL,1);
	LCD_SCL_PutVal(Scl_Lcd,0);
	LCD_RST_PutVal(Reset_Lcd,1);

    // Hardware reset the LCD
    lcd_Reset();

    writeCommand(EXIT_SLEEP_MODE);
    waitMs(10); // Wait for the screen to wake up

    writeCommand(SET_PIXEL_FORMAT);
        writeParameter(0x05); // 16 bits per pixel

        writeCommand(SET_GAMMA_CURVE);
        writeParameter(0x04); // Select gamma curve 3

        writeCommand(GAM_R_SEL);
        writeParameter(0x01); // Gamma adjustment enabled

        writeCommand(POSITIVE_GAMMA_CORRECT);
        writeParameter(0x3f); // 1st Parameter
        writeParameter(0x25); // 2nd Parameter
        writeParameter(0x1c); // 3rd Parameter
        writeParameter(0x1e); // 4th Parameter
        writeParameter(0x20); // 5th Parameter
        writeParameter(0x12); // 6th Parameter
        writeParameter(0x2a); // 7th Parameter
        writeParameter(0x90); // 8th Parameter
        writeParameter(0x24); // 9th Parameter
        writeParameter(0x11); // 10th Parameter
        writeParameter(0x00); // 11th Parameter
        writeParameter(0x00); // 12th Parameter
        writeParameter(0x00); // 13th Parameter
        writeParameter(0x00); // 14th Parameter
        writeParameter(0x00); // 15th Parameter

        writeCommand(NEGATIVE_GAMMA_CORRECT);
        writeParameter(0x20); // 1st Parameter
        writeParameter(0x20); // 2nd Parameter
        writeParameter(0x20); // 3rd Parameter
        writeParameter(0x20); // 4th Parameter
        writeParameter(0x05); // 5th Parameter
        writeParameter(0x00); // 6th Parameter
        writeParameter(0x15); // 7th Parameter
        writeParameter(0xa7); // 8th Parameter
        writeParameter(0x3d); // 9th Parameter
        writeParameter(0x18); // 10th Parameter
        writeParameter(0x25); // 11th Parameter
        writeParameter(0x2a); // 12th Parameter
        writeParameter(0x2b); // 13th Parameter
        writeParameter(0x2b); // 14th Parameter
        writeParameter(0x3a); // 15th Parameter

        writeCommand(FRAME_RATE_CONTROL1);
        writeParameter(0x08); // DIVA = 8
        writeParameter(0x08); // VPA = 8

        writeCommand(DISPLAY_INVERSION);
        writeParameter(0x07); // NLA = 1, NLB = 1, NLC = 1 (all on Frame Inversion)

        writeCommand(POWER_CONTROL1);
        writeParameter(0x0a); // VRH = 10:  GVDD = 4.30
        writeParameter(0x02); // VC = 2: VCI1 = 2.65

        writeCommand(POWER_CONTROL2);
        writeParameter(0x02); // BT = 2: AVDD = 2xVCI1, VCL = -1xVCI1, VGH = 5xVCI1, VGL = -2xVCI1

        writeCommand(VCOM_CONTROL1);
        writeParameter(0x50); // VMH = 80: VCOMH voltage = 4.5
        writeParameter(0x5b); // VML = 91: VCOML voltage = -0.225

        writeCommand(VCOM_OFFSET_CONTROL);
        writeParameter(0x40); // nVM = 0, VMF = 64: VCOMH output = VMH, VCOML output = VML

        writeCommand(SET_COLUMN_ADDRESS);
        writeParameter(0x00); // XSH
        writeParameter(0x00); // XSL
        writeParameter(0x00); // XEH
        writeParameter(0x7f); // XEL (128 pixels x)

        writeCommand(SET_PAGE_ADDRESS);
        writeParameter(0x00);
        writeParameter(0x00);
        writeParameter(0x00);
        writeParameter(0x9f); // 160 pixels y

        // Select display orientation
        writeCommand(SET_ADDRESS_MODE);
        writeParameter(orientation);

        // Set the display to on
        writeCommand(SET_DISPLAY_ON);
        writeCommand(WRITE_MEMORY_START);

        clear(rgb24to16(0xFF,0xFF,0xFF));
        LCD_LED_PutVal(NULL,1);
}


void printImage(const uint16_t image[], int width, int height){ //image = 128*160 pixels
	 uint16_t pixel;

	    // Set the column address to 0-width
	    writeCommand(SET_COLUMN_ADDRESS);
	    writeParameter(0x00);
	    writeParameter(0x00);
	    writeParameter(0x00);
	    writeParameter(width-1);


	    // Set the page address to 0-height
	    writeCommand(SET_PAGE_ADDRESS);
	    writeParameter(0x00);
	    writeParameter(0x00);
	    writeParameter(0x00);
	    writeParameter(height-1);

	    // Plot the pixels
	    writeCommand(WRITE_MEMORY_START);
	    if(width == 128 && height == 160)
	    {
	    	for( pixel = 0; pixel < 20480; pixel++){ //20480 = 128*160
				writeData(image[pixel*2] <<8 | image[pixel*2+1]); //pixels are defined by two bytes separeted for our variable image2
			}
	    }
	    if(width == 128 && height == 128)
	    {
	    	for( pixel = 0; pixel < 16384; pixel++){ //16384 = 128*128
	    		/*if (image[pixel] != 0xFFFF)
	    				writeData(0xF000);
	    		else*/
				writeData(image[pixel]); //pixels are defined by two bytes non-separeted for our variable image1
			}
	    }
}

void drawPixel(uint8_t x, uint8_t y, uint16_t colour) {
    // Horizontal Address Start Position
    writeCommand(SET_COLUMN_ADDRESS);
    writeParameter(0x00);
    writeParameter(x);
    writeParameter(0x00);
    writeParameter(0x7F);

    // Vertical Address end Position
    writeCommand(SET_PAGE_ADDRESS);
    writeParameter(0x00);
    writeParameter(y);
    writeParameter(0x00);
    writeParameter(0x9F);

    // Plot the point
    writeCommand(WRITE_MEMORY_START);
    writeData(colour);
}

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour) {
    int16_t dy = y1 - y0;
    int16_t dx = x1 - x0;
    int16_t stepx, stepy;

    if (dy < 0) {
        dy = -dy; stepy = -1;
    }
    else stepy = 1;

    if (dx < 0) {
        dx = -dx; stepx = -1;
    }
    else stepx = 1;

    dy <<= 1;                           // dy is now 2*dy
    dx <<= 1;                           // dx is now 2*dx

    drawPixel(x0, y0, colour);

    if (dx > dy) {
        int fraction = dy - (dx >> 1);  // same as 2*dy - dx
        while (x0 != x1) {
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;         // same as fraction -= 2*dx
            }

            x0 += stepx;
            fraction += dy;                 // same as fraction -= 2*dy
            drawPixel(x0, y0, colour);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }

            y0 += stepy;
            fraction += dx;
            drawPixel(x0, y0, colour);
        }
    }
}

// Draw a rectangle between x0, y0 and x1, y1
void drawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour) {
    drawLine(x0, y0, x0, y1, colour);
    drawLine(x0, y1, x1, y1, colour);
    drawLine(x1, y0, x1, y1, colour);
    drawLine(x0, y0, x1, y0, colour);
}

// Draw a filled rectangle
// Note:    y1 must be greater than y0  and x1 must be greater than x0
//          for this to work
void drawRectFilled(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour) {
    uint16_t pixels;

    // To speed up plotting we define a x window with the width of the
    // rectangle and then just output the required number of bytes to
    // fill down to the end point

    writeCommand(SET_COLUMN_ADDRESS); // Horizontal Address Start Position
    writeParameter(0x00);
    writeParameter(x0);
    writeParameter(0x00);
    writeParameter(x1);

    writeCommand(SET_PAGE_ADDRESS); // Vertical Address end Position
    writeParameter(0x00);
    writeParameter(y0);
    writeParameter(0x00);
    writeParameter(0x9f);

    writeCommand(WRITE_MEMORY_START);

    for (pixels = 0; pixels < (((x1 - x0) + 1) * ((y1 - y0) + 1)); pixels++)
        writeData(colour);
}

void drawCircle(int16_t xCentre, int16_t yCentre, int16_t radius, uint16_t colour) {
    int16_t x = 0, y = radius;
    int16_t d = 3 - (2 * radius);

    while(x <= y) {
        drawPixel(xCentre + x, yCentre + y, colour);
        drawPixel(xCentre + y, yCentre + x, colour);
        drawPixel(xCentre - x, yCentre + y, colour);
        drawPixel(xCentre + y, yCentre - x, colour);
        drawPixel(xCentre - x, yCentre - y, colour);
        drawPixel(xCentre - y, yCentre - x, colour);
        drawPixel(xCentre + x, yCentre - y, colour);
        drawPixel(xCentre - y, yCentre + x, colour);

        if (d < 0)
        	d += (4 * x) + 6;
        else {
            d += (4 * (x - y)) + 10;
            y -= 1;
        }

        x++;
    }
}

// LCD text manipulation functions --------------------------------------------------------------------------

// Plot a character at the specified x, y co-ordinates (top left hand corner of character): with the current font the screen allows up to 21x16 characters
void drawChar(unsigned char character, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour) {
    uint8_t row, column;

    // To speed up plotting we define a x window of 6 pixels and then
    // write out one row at a time.  This means the LCD will correctly
    // update the memory pointer saving us a good few bytes

    writeCommand(SET_COLUMN_ADDRESS); // Horizontal Address Start Position
    writeParameter(0x00);
    writeParameter(x);
    writeParameter(0x00);
    writeParameter(x+5);

    writeCommand(SET_PAGE_ADDRESS); // Vertical Address end Position
    writeParameter(0x00);
    writeParameter(y);
    writeParameter(0x00);
    writeParameter(0x9f);

    writeCommand(WRITE_MEMORY_START);

    // Plot the font data
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 6; column++) {
            if ((font5x8[character][column]) & (1 << row)) // using PROGMEM instead
        	    writeData(fgColour);
            else
            	writeData(bgColour);
        }
    }
}

// Plot a string of characters to the LCD: with the current font the screen allows up to 21x16 characters
void drawString(const char *string, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour) {
    uint8_t origin = x;

    for (uint8_t characterNumber = 0; characterNumber < strlen(string); characterNumber++) {
        // Check if we are out of bounds and move to
        // the next line if we are
        if (x > 121) {
            x = origin;
            y += 8;
        }

        // If we move past the bottom of the screen just exit
        if (y > 151) break;

        // Plot the current character
        drawChar(string[characterNumber], x, y, fgColour, bgColour);
        x += 6;
    }
}
