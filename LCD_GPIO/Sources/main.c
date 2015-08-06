/* ###################################################################
**     Filename    : main.c
**     Project     : LCD_GPIO
**     Processor   : MK64FX512VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-12, 15:48, # CodeGen: 0
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
#include "LCD_SDA.h"
#include "LCD_SCL.h"
#include "LCD_CS.h"
#include "LCD_RS.h"
#include "LCD_RST.h"
#include "LCD_LED.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include "ILI9163C.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	extern const uint16_t image1[];
	extern const uint16_t image2[];
	extern const uint16_t image3[];
	extern const uint16_t image4[];

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  init(BOTTOM);

  for(;;) {

	  //---- print characters ----
	/*  drawString("Hello World! This is a success!", 0, 80, rgb24to16(0,0,0), rgb24to16(0xFF,0xFF,0xFF));
	  waitMs(1000);
	  waitMs(1000);
	  //drawChar('0', 64, 80, rgb24to16(0xFF,0,0), rgb24to16(0,0,0));


	  //---- print image ----
	  printImage(image2,128,160); //128*160
	  waitMs(1000);
	  waitMs(1000);
	  printImage(image1,128,128); //128*128
	  waitMs(1000);
	  waitMs(1000);
	  printImage(image3,128,128); //128*128
	  waitMs(1000);
	  waitMs(1000);
	  printImage(image4,128,128); //128*128

	  waitMs(1000);
	  waitMs(1000);
	  LCD_LED_PutVal(NULL,0);
	  clear(rgb24to16(0xFF,0xFF,0xFF));
	  LCD_LED_PutVal(NULL,1);
	  waitMs(1000);
	  waitMs(1000);*/
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
