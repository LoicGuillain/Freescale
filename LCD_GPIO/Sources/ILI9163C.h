/*
 * ILI9163C.h
 *
 *  Created on: 12 juin 2015
 *      Author: lguillain
 */

#ifndef ILI9163_H_
#define ILI9163_H_

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "LCD_SDA.h"
#include "LCD_SCL.h"
#include "LCD_CS.h"
#include "LCD_RS.h"
#include "LCD_RST.h"
#include "LCD_LED.h"

// ILI9163 LCD Controller Commands
#define NOP                     0	//0x00
#define SOFT_RESET              1	//0x01
#define GET_RED_CHANNEL         6	//0x06
#define GET_GREEN_CHANNEL       7	//0x07
#define GET_BLUE_CHANNEL        8	//0x08
#define GET_PIXEL_FORMAT        12	//0x0C
#define GET_POWER_MODE          10	//0x0A
#define GET_ADDRESS_MODE        11	//0x0B
#define GET_DISPLAY_MODE        13	//0x0D
#define GET_SIGNAL_MODE         14	//0x0E
#define GET_DIAGNOSTIC_RESULT   15	//0x0F
#define ENTER_SLEEP_MODE        16	//0x10
#define EXIT_SLEEP_MODE         0x11
#define ENTER_PARTIAL_MODE      18	//0x12
#define ENTER_NORMAL_MODE       19	//0x13
#define EXIT_INVERT_MODE        32	//0x20
#define ENTER_INVERT_MODE       33	//0x21
#define SET_GAMMA_CURVE         38	//0x26
#define SET_DISPLAY_OFF         40	//0x28
#define SET_DISPLAY_ON          41	//0x29
#define SET_COLUMN_ADDRESS      42	//0x2A
#define SET_PAGE_ADDRESS        43	//0x2B
#define WRITE_MEMORY_START      44	//0x2C
#define WRITE_LUT               45	//0x2D
#define READ_MEMORY_START       46	//0x2E
#define SET_PARTIAL_AREA        48	//0x30
#define SET_SCROLL_AREA         51	//0x33
#define SET_TEAR_OFF            52	//0x34
#define SET_TEAR_ON             53	//0x35
#define SET_ADDRESS_MODE        54	//0x36
#define SET_SCROLL_START        55	//0X37
#define EXIT_IDLE_MODE          56	//0x38
#define ENTER_IDLE_MODE         57	//0x39
#define SET_PIXEL_FORMAT        58	//0x3A
#define WRITE_MEMORY_CONTINUE   60	//0x3C
#define READ_MEMORY_CONTINUE    62	//0x3E
#define SET_TEAR_SCANLINE       68	//0x44
#define GET_SCANLINE            69	//0x45
#define READ_ID1                0xDA
#define READ_ID2                0xDB
#define READ_ID3                0xDC
#define FRAME_RATE_CONTROL1     0xB1
#define FRAME_RATE_CONTROL2     0xB2
#define FRAME_RATE_CONTROL3     0xB3
#define DISPLAY_INVERSION       0xB4
#define SOURCE_DRIVER_DIRECTION 0xB7
#define GATE_DRIVER_DIRECTION   0xB8
#define POWER_CONTROL1          192	//0xC0
#define POWER_CONTROL2          193	//0xC1
#define POWER_CONTROL3          194	//0xC2
#define POWER_CONTROL4          195	//0xC3
#define POWER_CONTROL5          196	//0xC4
#define VCOM_CONTROL1           197	//0xC5
#define VCOM_CONTROL2           198	//0xC6
#define VCOM_OFFSET_CONTROL     199	//0xC7
#define WRITE_ID4_VALUE         211	//0xD3
#define NV_MEMORY_FUNCTION1     215	//0xD7
#define NV_MEMORY_FUNCTION2     222	//0xDE
#define POSITIVE_GAMMA_CORRECT  224	//0xE0
#define NEGATIVE_GAMMA_CORRECT  225	//0xE1
#define GAM_R_SEL               242	//0xF2


// RGB24 to RGB16: Translates a 3 byte RGB value into a 2 byte value for the LCD (values should be 0-31)
// Radu Motisan: we need to scale the 8bit values to 5bit (for blue or red) / 6bit (for green)
inline uint16_t rgb24to16(uint8_t r, uint8_t g, uint8_t b) {
	//return ((b/8) << 11) | ((g/4) << 5) | (r/8);
	return ((b>>3) << 11) | ((g>>2) << 5) | (r>>3);
	/*
	 	 return 	((b << 8) & 0xF800) | // 5 bits for blue : most significant
			((g << 3) & 0x7E0) | // 6 bits for green : most significant
			(r >> 3);	// 5 bits for red : most significant
			*/
}

// This routine takes a row number from 0 to 20 and returns the x coordinate on the screen (0-127)
inline uint8_t textX(uint8_t x) { return x*6; }

// This routine takes a column number from 0 to 20 and returns the y coordinate on the screen (0-127)
inline uint8_t textY(uint8_t y) { return y*8; }


enum ORIENTATION {
		TOP = 0, LEFT = 96, RIGHT = 160, BOTTOM = 192 //192
	};

void lcd_Reset(void);
void writeCommand(uint8_t address);
void writeParameter(uint8_t parameter);
void writeData(uint16_t word);
void init(uint8_t orientation);

void clear(uint16_t colour);
void printImage(const uint16_t image1[], int width, int height);
void drawPixel(uint8_t x, uint8_t y, uint16_t colour);
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour);
void drawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour);
void drawRectFilled(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour);
void drawCircle(int16_t xCentre, int16_t yCentre, int16_t radius, uint16_t colour);

void drawChar(unsigned char character, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour);
void drawString(const char *string, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour);

void waitMs(int ms);
void waitUs(int ms);

#endif /* ILI9163_H_ */

