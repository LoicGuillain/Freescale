/* ###################################################################
**     Filename    : main.c
**     Project     : SD_CARD
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-31, 14:16, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "TmDt1.h"
#include "UTIL1.h"
#include "SM1.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include "Functions.h"


/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	static FAT1_FATFS fileSystemObject;
	static FIL fp;
	TIMEREC time;
	uint8_t write_buf[48];
	UINT bw;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  if (FAT1_Init()!=ERR_OK) { /* initialize FAT driver */
      Err();
    }
  if (FAT1_mount(&fileSystemObject, "0", 1) != FR_OK) { /* mount file system */
      Err();
    }
  /* For example: for(;;) { } */
  for(;;){
	  /* open file */
	    if (FAT1_open(&fp, "./heure.txt", FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) {
	      Err();
	    }
	    /* move to the end of the file */
	    if (FAT1_lseek(&fp, fp.fsize) != FR_OK || fp.fptr != fp.fsize) {
	      Err();
	    }
	    /* get time */
	    if (TmDt1_GetTime(&time)!=ERR_OK) {
	      Err();
	    }
	    /* write data */
	     write_buf[0] = '\0';
	     UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Hour);
	     UTIL1_chcat(write_buf, sizeof(write_buf), ':');
	     UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Min);
	     UTIL1_chcat(write_buf, sizeof(write_buf), ':');
	     UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Sec);
	     UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
	     if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
	         (void)FAT1_close(&fp);
	         Err();
	       }
	       /* closing file */
	       (void)FAT1_close(&fp);
	       WAIT1_Waitms(1000);
  }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
