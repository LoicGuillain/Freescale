/*
 * SSD1351.h
 *
 *  Created on: 30 juil. 2015
 *      Author: lguillain
 */

#ifndef SSD1351_H_
#define SSD1351_H_

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SM1.h"
#include "OLED_DC.h"
#include "OLED_RESET.h"

#define SSD1351WIDTH 128
#define SSD1351HEIGHT 128

// SSD1351 Commands
#define SSD1351_CMD_SETCOLUMN 		0x15
#define SSD1351_CMD_SETROW    		0x75
#define SSD1351_CMD_WRITERAM   		0x5C
#define SSD1351_CMD_READRAM   		0x5D
#define SSD1351_CMD_SETREMAP 		0xA0
#define SSD1351_CMD_STARTLINE 		0xA1
#define SSD1351_CMD_DISPLAYOFFSET 	0xA2
#define SSD1351_CMD_DISPLAYALLOFF 	0xA4
#define SSD1351_CMD_DISPLAYALLON  	0xA5
#define SSD1351_CMD_NORMALDISPLAY 	0xA6
#define SSD1351_CMD_INVERTDISPLAY 	0xA7
#define SSD1351_CMD_FUNCTIONSELECT 	0xAB
#define SSD1351_CMD_DISPLAYOFF 		0xAE
#define SSD1351_CMD_DISPLAYON     	0xAF
#define SSD1351_CMD_PRECHARGE 		0xB1
#define SSD1351_CMD_DISPLAYENHANCE	0xB2
#define SSD1351_CMD_CLOCKDIV 		0xB3
#define SSD1351_CMD_SETVSL 			0xB4
#define SSD1351_CMD_SETGPIO 		0xB5
#define SSD1351_CMD_PRECHARGE2 		0xB6
#define SSD1351_CMD_SETGRAY 		0xB8
#define SSD1351_CMD_USELUT 			0xB9
#define SSD1351_CMD_PRECHARGELEVEL 	0xBB
#define SSD1351_CMD_VCOMH 			0xBE
#define SSD1351_CMD_CONTRASTABC		0xC1
#define SSD1351_CMD_CONTRASTMASTER	0xC7
#define SSD1351_CMD_MUXRATIO        0xCA
#define SSD1351_CMD_COMMANDLOCK     0xFD
#define SSD1351_CMD_HORIZSCROLL     0x96
#define SSD1351_CMD_STOPSCROLL      0x9E
#define SSD1351_CMD_STARTSCROLL     0x9F


void begin(void);
void reset(void);

inline uint16_t rgb24to16(uint8_t r, uint8_t g, uint8_t b) {
	//return ((b/8) << 11) | ((g/4) << 5) | (r/8);
	return ((b>>3) << 11) | ((g>>2) << 5) | (r>>3);
	/*
	 	 return 	((b << 8) & 0xF800) | // 5 bits for blue : most significant
			((g << 3) & 0x7E0) | // 6 bits for green : most significant
			(r >> 3);	// 5 bits for red : most significant
			*/
}

uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
void writeData(uint8_t d);
void writeCommand(uint8_t c);
void writeColor(uint16_t color);
void goTo(uint8_t x, uint8_t y);
void clear(uint16_t color);
void drawPixel (uint8_t x, uint8_t y, uint16_t color);
void drawVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color);
void drawHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color);
void drawChar(unsigned char character, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour);
void drawString(const char *string, uint8_t x, uint8_t y, uint16_t fgColour, uint16_t bgColour);

#endif /* SSD1351_H_ */
