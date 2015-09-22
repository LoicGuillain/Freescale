/*
 * main.cpp
 *
 *  Created on: 4 sept. 2015
 *      Author: lguillain
 */

#include "Cpu.h"
#include "Events.h"
#include "WAIT1.h"
#include "OLED_DC.h"
#include "OLED_RESET.h"
#include "OLED_SUPPLY.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "SM3.h"
#include "SMasterLdd3.h"
#include "SS.h"
#include "TmDt1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

#include "lib_next_extract.h"
#include "empreinte.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "SSD1351.h"
#include "spi_next.h"

#include "define.h"
#define USE_NEXT_SENSOR

#ifndef NO_SCREEN
#include "font5x8.cpp"
#include "image.cpp"
#endif



byte buffer[250];
int bufferLength = 0;
uint8_t finger_template[256*180] = {0};
uint8_t match_values[2] = {0};
int nb_retry = 0;

uint32_t awake_value = 0;
bool SetVLP = FALSE;

int get_next_msg(byte * pBuffer,int* pLength);
int parse_msg(byte * pBuffer,int* pLength,int* p_event);
int parse_C0(byte * pBuffer,int* pLength,int* p_event);
int parse_C8(byte * pBuffer,int* pLength,int* p_event);
int send_msg(byte * pBuffer,int length);
void init_screen(void);

int start_acquisition(byte * pBuffer,int* pLength,int* p_event);
void back_to_first_screen(void);

int event = EVENT_NOTHING_TO_DO;
bool transaction_done = false;
bool in_transaction = false;
bool need_display = false;

char msg_fin_ok[100]={0};
char msg_fin_ko[100]={0};

void Waitms(int ms)
{
	for(int loop = 0; loop < 120 ; loop++)
		WAIT1_Waitms(ms);
}

void set_event(int* p_event,int event_to_set)
{
	*p_event |=event_to_set;
}

void clear_event(int* p_event,int event_to_clear)
{
	*p_event &= ~event_to_clear;
}

void set_event_interrupt(void)
{
	awake_value = 0;

	if(SetVLP == TRUE){
		PE_low_level_init();
		Cpu_SetClockConfiguration(1);
		need_display = true;

		SetVLP = FALSE;
	}
	EInt1_Disable();
	set_event(&event,EVENT_MSG_TO_FETCH);
}

void set_timer_interrupt()
{
	if(in_transaction == false)
	{
		awake_value++;
		if(awake_value >= SLEEP_TIME && SetVLP == FALSE){
			//On eteint tout
			OLED_RESET_PutVal(NULL,0);
			OLED_SUPPLY_PutVal(NULL,0);
			spi_next_free();
			//puis on passe en VLP
			SetVLP = TRUE;
			Cpu_SetClockConfiguration(0);
			Cpu_VLPModeEnable();
		}
		if(awake_value >= SLEEP_TIME && SetVLP == TRUE){
			//awake_value = 0;
		}
	}
}


int parse_event(int * p_event)
{
	int ret = MAIN_SUCCESS;

	if(need_display == true)
	{
		//back_to_first_screen();
		init_screen();
		writeCommand(SSD1351_CMD_DISPLAYON);
		need_display = false;
	}

	if(*p_event&EVENT_MSG_TO_FETCH)
	{
		*p_event = *p_event ^ EVENT_MSG_TO_FETCH;
		Waitms(10);
		bufferLength = sizeof(buffer);
		memset(buffer,0,sizeof(buffer));
		SS_SetDir(NULL,true);
		ret = get_next_msg(buffer,&bufferLength);
		if(ret==MAIN_SUCCESS)
			set_event(p_event,EVENT_CMD_TO_PARSE);
	}
	else if(*p_event&EVENT_CMD_TO_PARSE)
	{
		*p_event = *p_event ^ EVENT_CMD_TO_PARSE;
		ret = parse_msg(buffer,&bufferLength,p_event);
	}
	else if(*p_event&EVENT_MSG_TO_SEND)
	{
		*p_event = *p_event ^ EVENT_MSG_TO_SEND;
		ret = send_msg(buffer,bufferLength);
		memset(buffer,0,sizeof(buffer));

		if(transaction_done)
		{
			transaction_done= false;
			Waitms(6000);
			back_to_first_screen();
			in_transaction = false;
		}

	}
	else if(*p_event&EVENT_START_FINGER_ACQUISITION)
	{
		*p_event = *p_event ^ EVENT_START_FINGER_ACQUISITION;
		ret = start_acquisition(buffer,&bufferLength,p_event);

	}
	else
	{
		ret = MAIN_ERROR_UNKNOWN_EVENT;
	}

/*		switch(*p_event)
		{
			case EVENT_MSG_TO_FETCH:
				*p_event = *p_event ^ EVENT_MSG_TO_FETCH;
				WAIT1_Waitms(10);
				bufferLength = sizeof(buffer);
				memset(buffer,0,sizeof(buffer));
				ret = get_next_msg(buffer,&bufferLength);
				if(ret==MAIN_SUCCESS)
					set_event(p_event,EVENT_CMD_TO_PARSE);
				//ret = 0;
				break;
			case EVENT_CMD_TO_PARSE:
				*p_event = *p_event ^ EVENT_CMD_TO_PARSE;
				ret = parse_msg(buffer,&bufferLength,p_event);
				break;
			case EVENT_MSG_TO_SEND:
				*p_event = *p_event ^ EVENT_MSG_TO_SEND;
				ret = send_msg(buffer,bufferLength);
				memset(buffer,0,sizeof(buffer));

				if(transaction_done)
				{
					transaction_done= false;
					WAIT1_Waitms(6000);
					back_to_first_screen();
				}

				break;

			case EVENT_START_FINGER_ACQUISITION:
				*p_event = *p_event ^ EVENT_START_FINGER_ACQUISITION;
				ret = start_acquisition(buffer,&bufferLength,p_event);
				break;



			default:
			ret = MAIN_ERROR_UNKNOWN_EVENT;
			break;
		}*/
	return ret;
}

int get_next_msg(byte * pBuffer,int* pLength)
{
	int ret = MAIN_ERROR_SPI;
	int err;

	SM3_ClearRxBuf();
	byte length=0;

	SS_PutVal(NULL,0);//Chip select low
	SM3_SendChar(0x55);
	SM3_RecvChar(&length);

	if(length!=0){
		Waitms(1);
		WAIT1_Waitus(8);
		for (int i = 0;i < length;i++) {
			SM3_SendChar(0x55);
			err = SM3_RecvChar(pBuffer + i);
		}
		*pLength = length;
		ret = MAIN_SUCCESS;
	}
	SS_PutVal(NULL,1);
	SM3_ClearRxBuf();

	return ret;
}

int parse_msg(byte * pBuffer,int* pLength,int* p_event)
{
	int ret = MAIN_SUCCESS;
	switch(pBuffer[0])
	{
	case TAG_C0_MSG_FROM_WAD :
		ret = parse_C0(pBuffer,pLength,p_event);
		break;

	case TAG_C8_RAPDU_FROM_WPD :
		ret = parse_C8(pBuffer,pLength,p_event);
		break;

	default:
		ret = MAIN_ERROR_UNKNOWN_MSG;
		break;
	}

	return ret;
}

int parse_C0(byte * pBuffer,int* pLength,int* p_event)
{
	int ret = MAIN_SUCCESS;
	char msg_start[100]={0};

	in_transaction = true;
	nb_retry = 0;

	memset(msg_start,0,sizeof(msg_start));
	memset(msg_fin_ok,0,sizeof(msg_fin_ok));
	memset(msg_fin_ko,0,sizeof(msg_fin_ko));


	// display msg ds tag 86
	//pBuffer[*pLength]=0;
	clear(0x0000);

	memcpy(msg_start,&pBuffer[4],pBuffer[3]);
	memcpy(msg_fin_ok,&pBuffer[4+pBuffer[3]+2],pBuffer[4+pBuffer[3]+1]);
	memcpy(msg_fin_ko,&pBuffer[4+pBuffer[3]+2+pBuffer[4+pBuffer[3]+1]+2],pBuffer[4+pBuffer[3]+2+pBuffer[4+pBuffer[3]+1]+1]);

	fillRect(0,14,128,9,0x0000);
	drawString(msg_start, 2, 15, 0xFFFF, 0x0000);

	memset(pBuffer,0,*pLength);
	*pLength = 0;

	//start finger acquisition
	set_event(p_event,EVENT_START_FINGER_ACQUISITION);

	return ret;
}

int parse_C8(byte * pBuffer,int* pLength,int* p_event)
{
	int ret = MAIN_SUCCESS;

	uint16 SW1SW2= pBuffer[*pLength-2];
	SW1SW2 = SW1SW2<<8 | pBuffer[*pLength-1];

	int index = 0;
	pBuffer[0]=0xC0;

	if(SW1SW2==0x9000)
	{
		uint8 data_from_wpd[100]={0};
		memcpy(data_from_wpd,pBuffer+2,*pLength-4);

		pBuffer[1]=(*pLength-2);
		pBuffer[2]=0x86;
		pBuffer[3]=*pLength-4;
		memcpy(&pBuffer[4],data_from_wpd,*pLength-4);
		//*pLength -=1;
		//fingerprint in green because it matches
		printFinger(finger_template, 19, GREEN);
		drawString(msg_fin_ok,2,60,0xFFFF,0x0000);

		set_event(p_event,EVENT_MSG_TO_SEND);
		transaction_done = true;


	}
	else
	{
		nb_retry++;
		if(nb_retry < 3)
		{
			clear(0x0000);
			set_event(p_event,EVENT_START_FINGER_ACQUISITION);

		}
		else
		{
			nb_retry = 0;
			pBuffer[1]=0x04;
			pBuffer[2]=0xE1;
			pBuffer[3]=0x02;
			pBuffer[4]=(SW1SW2&0xFF00)>>8;
			pBuffer[5]=(SW1SW2&0x00FF);
			*pLength = 6;
			//fingerprint in red because it does not match
			printFinger(finger_template, 19, RED);
			drawString(msg_fin_ko,2,60,0xFFFF,0x0000);

			// Post APDU
			set_event(p_event,EVENT_MSG_TO_SEND);

			transaction_done = true;
		}


	}

	return ret;
}


int start_acquisition(byte * pBuffer,int* pLength,int* p_event)
{
#ifndef USE_NEXT_SENSOR
	uint8_t s_template[256*180] = EMPREINTE_ANT;
#else
	uint8_t s_template[256*180] = {0};
#endif

	int ret = MAIN_SUCCESS;

	int counter = 0;
	int counter_max = 60;
	byte result = 0;

	// Afficher texte

#ifdef USE_NEXT_SENSOR
	// Init capteur
	spi_next_init();

	if(Next_isConnected()) {
		Next_calibrate();
	}
#endif
	fillRect(0,41,128,9,0x0000);
	drawString("Put your finger", 19, 60, 0xFFFF, 0x0000);

	//Finger detection
#ifdef USE_NEXT_SENSOR
	while(counter++ < counter_max){
		//waiting for a finger
		ret = Next_isFinger(&result);
		if(result>HIGH_THRESHOLD)
			break;

		Waitms(200);
	}

	if(counter>=counter_max)
	{
		spi_next_free();

		// New code
		pBuffer[0]=0xC0;
		pBuffer[1]=0x04;
		pBuffer[2]=0xE1;
		pBuffer[3]=0x02;
		pBuffer[4]=0x69;
		pBuffer[5]=0x85;
		*pLength = 6;
		//fingerprint in red because it does not match
		clear(0x0000);
		drawString("Error during capture",2,60,0xFFFF,0x0000);

		// Post APDU
		set_event(p_event,EVENT_MSG_TO_SEND);

		transaction_done = true;



		return MAIN_SUCCESS;
		//old
		//return MAIN_ERROR_NO_FINGERPRINT;
	}
	Waitms(2);
	fillRect(0,79,128,9,0x0000);
	drawString("Please hold", 31, 80, 0xFFFF, 0x0000);
#endif

	do{
#ifdef USE_NEXT_SENSOR
		if(Next_getFinger(s_template) == 0)
#else
			if(1)
#endif
			{
				spi_next_free();
				uint8_t buffer[MEMALLOC_MAX_SIZE] = {0};
				int bufferLength = MEMALLOC_MAX_SIZE;
				int templateLength = 0;
				int index = 0;
				memcpy(&finger_template, s_template, 256*180);
				//fingerprint in blue because not still verified
				clear(0x0000);
				printFinger(finger_template, 19, BLUE);

				//Extraction
				ret = lib_next_extract(buffer,bufferLength,s_template,(unsigned int*)&templateLength,55);
				if(ret!=0)
				{
					ret = MAIN_ERROR_FINGERPRINT_EXTRACT_KO;
					break;
				}

				pBuffer[index++]=0xC7;
				pBuffer[index++]=0x81;
				pBuffer[index++]=templateLength + 9;

				pBuffer[index++]=0x00;//CLA
				pBuffer[index++]=0x31;//INS
				pBuffer[index++]=0x00;//P1
				pBuffer[index++]=0x00;//P2

				/**/
				pBuffer[index++]=(templateLength+3);//LC
				pBuffer[index++]=0x81;//Data 1
				pBuffer[index++]=0x81;//Data 2
				pBuffer[index++]=templateLength;//Data 3
				memcpy(&pBuffer[index],s_template,templateLength);
				pBuffer[index+templateLength]=0x00;

				*pLength = templateLength + index+1;

				// Post APDU
				set_event(p_event,EVENT_MSG_TO_SEND);
			}
			else
			{
				spi_next_free();
				ret = MAIN_ERROR_NO_FINGERPRINT;
				break;
			}

	}while(0);

	return ret;
}


void reset_interrupt(void)
{
	SS_SetDir(NULL,false);
	EInt1_Enable();
}

int send_msg(byte * pBuffer,int length)
{
	int k = 0;

	SS_PutVal(NULL,0);
	WAIT1_Waitus(8);

	for(k=0;k<length;k++){
		SM3_SendChar(pBuffer[k]);
	}

	SS_PutVal(NULL,1);

	memset(pBuffer,0,length);
	reset_interrupt();

	return MAIN_SUCCESS;
}

void init_screen(void)
{
	OLED_SUPPLY_PutVal(NULL,1);
	Waitms(10);
	begin();
	Waitms(10);
	clear(0x0000);
	Waitms(10);
}


int reset_ST()
{
	event=EVENT_NOTHING_TO_DO;
	transaction_done = false;
	in_transaction = false;

	back_to_first_screen();
	reset_interrupt();

	return MAIN_SUCCESS;
}

void back_to_first_screen(void)
{
	init_screen();
	printImage(logo_final_dark,0,0,128,128);
	writeCommand(SSD1351_CMD_DISPLAYON);
}

int main(void)
{
	byte ret = MAIN_SUCCESS;
	event = EVENT_NOTHING_TO_DO;

	PE_low_level_init();
	Cpu_SetClockConfiguration(1);
	back_to_first_screen();

	do{
		if(event!=EVENT_NOTHING_TO_DO)
			ret = parse_event(&event);
		else{
			__asm("WFI\n\t");
			//Waitms(100);
		}

		//Waitms(100);

		if(ret!=MAIN_SUCCESS)
		{
			ret = reset_ST();
		}
	}while(TRUE);

	for(;;){}

	return 0;
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	for(;;){}
	/*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
}
