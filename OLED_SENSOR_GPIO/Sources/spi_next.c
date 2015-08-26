/*
 * spi_next.c
 *
 *  Created on: 15 juin 2015
 *      Author: dusautois
 *
 *  Description: function to manage spi next sensor interface without spi device because mosi / miso signal exchange
 */

#include <stdint.h>

#include "SPI_NEXT_MOSI.h"
#include "SPI_NEXT_MISO.h"
#include "SPI_NEXT_SCLK.h"
#include "SPI_NEXT_SS.h"
#include "SPI_NEXT_AWAKE.h"
#include "SPI_NEXT_RESET.h"

#include "spi_next.h"

enum NextMsgCode {
	GET_LINE 			= 0x10,
	GET_PARTIAL_LINE 	= 0x11,
	FINGER_IS_PRESENT 	= 0x12,
	SET_STOP 			= 0x83,
	SET_IMAGE_MODE 		= 0x27,
	GET_SERIAL 			= 0x20,
	GET_VERSION 		= 0xF5,
	DIAGNOSTIC 			= 0x26,
	STOP                = 0x83,
};

enum NextGetLineParam {
	FIRST 				= 0x80,
	ANY					= 0x00,
	LAST				= 0x01,
};

enum NextFingerParam {
	RESET 				= 0x00,
	GET					= 0x01,

	THRESHOLD 			= 0x32,
	HIGH_THRESHOLD 		= 0x5A,
};

enum NextErrCode {
	READY	 			= 0x01, //normal processing, ready
	BUSY 				= 0xB0, //normal processing, busy
	PARAM_ERR 			= 0x10, //error in the parameter fields
	DATA_LEN_ERR 		= 0x11, //data length error
	DATA_ERR 			= 0x12, //error in the data field
	UNKNOW_CMD_ERR		= 0x30, //unknown command (INS)
	USAGE_ERR 			= 0x31, //conditions of use not satisfied (operation mode)
	COM_ERR 			= 0x32, //communication error
	HARD_FAIL_ERR 		= 0x33, //sensor hardware failure
	DCA_INTERN_ERR 		= 0x34, //DCA internal error
	MCU_INTERN_ERR 		= 0x35, //MCU internal error

	TIME_OUT_REACHED 	= 0xFF,
};
static byte Next_clear();

static int variable = 0;
static void waitUs(int32_t us)	{

	for(uint32_t i = 0; i < (1*us); i++){
		variable++;
	}
}

void spi_next_init()
{
	SPI_NEXT_SCLK_ClrVal(NULL);
	SPI_NEXT_SS_SetVal(NULL);
	SPI_NEXT_RESET_ClrVal(NULL);
	waitUs(1000);
	SPI_NEXT_RESET_SetVal(NULL);
}

void spi_next_free()
{
	Next_stop(1);
	SPI_NEXT_SS_SetVal(NULL);
	SPI_NEXT_SCLK_ClrVal(NULL);
	SPI_NEXT_RESET_ClrVal(NULL);
}

void spi_next_resart()
{
	spi_next_init();
}

//uint32_t spi_next_getversion()
//{
//	uint8_t cmd[] = {0xF5, 0x00, 0x00, 0x00};
//	uint8_t buf[5] = {0};
//	uint32_t version = 0;
//
//	spi_next_frame(cmd, sizeof(cmd), buf, sizeof(buf));
//
//	return version;
//}


uint8_t spi_next_transmit(uint8_t byte)
{
	uint8_t retval = 0;
	for(int i = 0;i<8; i++) {
		if((byte & (0x80 >> i)) == 0)
			SPI_NEXT_MOSI_ClrVal(NULL);
		else
			SPI_NEXT_MOSI_SetVal(NULL);
		SPI_NEXT_SCLK_SetVal(NULL);
		waitUs(10);
		retval <<= 1;
		retval |= SPI_NEXT_MISO_GetVal(NULL);
		SPI_NEXT_SCLK_ClrVal(NULL);
	}

	waitUs(70);

	return retval;
}

//uint16_t spi_next_frame(uint8_t *send, uint16_t length_send, uint8_t *recv, uint16_t length_recv)
//{
//	uint8_t byte = 0;
//	uint16_t length = 0;
//
//	length = length_send < length_recv ? length_recv : length_send;
//
//	SPI_NEXT_SS_ClrVal(NULL);
//	waitUs(1000);
//
//	for(int i = 0;i<length; i++) {
//		if(i < length_send)
//			byte = spi_next_transmit(send[i]);
//		else
//			byte = spi_next_transmit(0x00);
//		if(i>0 && ((i-1) < length_recv))
//			recv[i-1] = byte;
//	}
//	SPI_NEXT_SS_SetVal(NULL);
//
//	return length;
//
//}

//static int write(uint8_t *buf, int count)
//{
//	for(int i = 0; i<count; i++)
//		spi_next_transmit(buf[i]);
//
//	return 0;
//}
//
//
//static int read(uint8_t *buf, int count)
//{
//	for(int i = 0; i<count; i++)
//		buf[i] = spi_next_transmit(0x00);
//	return 0;
//}



static int send(byte query[4], byte* data, int len) {
   int ret = 0;

   //Send header
   //ret = write(query, 4);

   do
   {
	   if(spi_next_transmit(query[0]) != 0xCC) {
		   ret = 1;
		   break;
	   }
	   if(spi_next_transmit(query[1]) != 0xCC) {
		   ret = 1;
		   break;
	   }
	   if(spi_next_transmit(query[2]) != 0xCC) {
		   ret = 1;
		   break;
	   }
	   if(spi_next_transmit(query[3]) != 0xCC) {
		   ret = 1;
		   break;
	   }


	   //Wait 1ms
	   waitUs(1000);

	   //Send body
	   for(int i = 0; i< len; i++) {
		   if(spi_next_transmit(data[i]) != 0xAA) {
			   ret = 2;
		   	   break;
		   }
	   }

	   //ret = write(data, len);
   }
   while(0);

   return ret;
}


static int receive(byte* out, int len, int utime, int countOut) {
   int ret = 0;
   byte buf = 0;
   int count = 0;

   do {
      waitUs(utime);
      buf = spi_next_transmit(0x00);
      if(buf == READY)
    	  break;
      waitUs(utime);
      ++count;

   } while ((countOut == 0) || (count < countOut));

   if (buf == READY) {
	   for(int i = 0; i< len; i++)
		   out[i] = spi_next_transmit(0x00);
      //ret = read(out, len);
      ret = 0;
   } else if (buf == BUSY){
      ret = TIME_OUT_REACHED;
   } else {
      ret = 1;
   }

   return ret;
}

static byte sync_send(byte query[4], byte* in, byte* out, int len, int utime, int countOut) {
   int ret = 0;
   byte needRestart = 0;

   SPI_NEXT_SS_ClrVal(NULL);
   //Next_clear();

   ret = send(query, in, query[3]);
   if(ret == 0)
	   ret = receive(out, len, utime, countOut);

   if(ret != 0)
	   needRestart = Next_clear();

   SPI_NEXT_SS_SetVal(NULL);

   if(needRestart != 0) {
	   spi_next_resart();
   }
   return ret;
}


static byte Next_clear() {
   int ret = 0;
   byte cleared = 0;
   byte buf = 0x00;

   int headerSeq = 0;
   int criticalErr = 0;

   int totalCount = 0;

   while (!cleared) {
      buf = spi_next_transmit(0x00);
      totalCount++;

      switch (buf) {
         case UNKNOW_CMD_ERR:
            if (headerSeq == 4) {
               cleared = 1;
            } else {
               headerSeq = 0;
               criticalErr = 0;
            }
            break;
         case 0xCC:
            headerSeq++;
            criticalErr = 0;
            break;
         case COM_ERR:
         case HARD_FAIL_ERR:
         case DCA_INTERN_ERR:
         case MCU_INTERN_ERR:
            criticalErr++;
            headerSeq = 0;
            break;
         default:
            headerSeq = 0;
            criticalErr = 0;
            break;
      }

      if (totalCount >= 20)  {
    	 ret = 1;
         break;
      }
   }

   return ret;
}


byte Next_calibrate() {
   byte err = 0;
   byte query[4] = { FINGER_IS_PRESENT, RESET, 0x00, 0x00 };
   byte result;

   sync_send(query, NULL, &result, 1, 10, 128);

   return result;
}

byte Next_isFinger() {
   byte query[4] = { FINGER_IS_PRESENT, GET, 0x00, 0x00 };
   byte result = 0;

   sync_send(query, NULL, &result, 1, 100, 128);

   return result > HIGH_THRESHOLD;
}

static byte get(byte* data, int rows, int cols) {
   byte err = 0;
   byte query[4] = { GET_LINE, 0, 0, 0 };

   do
   {
	   query[1] = FIRST;
	   //10 ms delay instead of 55 specified to avoid a second long wait.
	   err = sync_send(query, NULL, data, cols, 1000, 1100);
	   if(err != 0)
		   break;

	   query[1] = ANY;
	   for (int row = 1; row < rows - 1; row++) {
		  query[2] = row;
		  err = sync_send(query, NULL, data + row*cols, cols, 10, 128);
		   if(err != 0)
			   break;
	   }
	   if(err != 0)
		   break;

	   query[1] = LAST;
	   query[2] = rows - 1;
	   err = sync_send(query, NULL, data + (rows - 1)*cols, cols, 10, 128);
	   if(err != 0)
		   break;
   }
   while(0);

   return err;
}

byte Next_getFinger(byte* data) {
   return get(data, 180, 256);
}

byte Next_getHalfFinger(byte* data) {
   return get(data, 90, 128);
}

uint32_t Next_version() {
   uint32_t ver = 0;;
   byte query[4] = { GET_VERSION, 0, 0, 0 };
   uint8_t data[3] = {0};

   sync_send(query, NULL, data, 3, 10, 128);

   ver = data[0] << 16 | data[1] << 8 | data[2];

   return ver;
}

byte Next_serial(byte* data) {
   byte err;
   byte query[4] = { GET_SERIAL, 0, 0, 0 };

   err = sync_send(query, NULL, data, 12, 10, 128);

   return err;
}

byte Next_isConnected() {
   byte ret = 0;
   byte check[9] = {0};

   Next_diagnostic(check);

   if (check[8] == 0x00) {
      int i = 0;
      for (;i < 8;++i) {
         if (check[i] != 0x55) {
            break;
         }
      }
      ret = (i == 8);
   } else {
      ret = 0;
   }
   return ret;
}

byte Next_diagnostic(byte out[9]) {
   byte err;
   byte query[4] = { DIAGNOSTIC, 0x01, 0, 0x08 };
   byte data[8] = { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 };

   err = sync_send(query, data, out, 9, 10, 128);
   return err;
}

byte Next_stop(byte scanCount)
{
   byte err;
   byte query[4] = { STOP, scanCount, 0, 0x00 };

   err = sync_send(query, NULL, NULL, 0, 10, 128);
   return err;
}

