/* ###################################################################
**     Filename    : main.c
**     Project     : OLED_SENSOR_GPIO
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-08-26, 14:13, # CodeGen: 0
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
#include "WAIT1.h"
#include "OLED_DC.h"
#include "OLED_RESET.h"
#include "OLED_SUPPLY.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "SPI_NEXT_MOSI.h"
#include "SPI_NEXT_MISO.h"
#include "SPI_NEXT_SCLK.h"
#include "SPI_NEXT_SS.h"
#include "SPI_NEXT_AWAKE.h"
#include "SPI_NEXT_RESET.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "spi_next.h"
#include "SSD1351.h"

#define ROW_CAPTURE_MAX	180
#define COLUMN_CAPTURE_MAX 256

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	uint8_t s_template[ROW_CAPTURE_MAX * COLUMN_CAPTURE_MAX] = {0};
	uint8_t data[12] = {0};

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
	spi_next_init();
	if(Next_isConnected() != 0) {
		Next_calibrate();
	}
	Next_version();
	Next_serial(data);
	OLED_SUPPLY_PutVal(NULL,1);
	WAIT1_Waitms(20);
	begin();
	WAIT1_Waitms(20);
	clear(0x0000);
	WAIT1_Waitms(50);

	while(Next_isFinger() != 1){} //waiting for a finger
		WAIT1_Waitms(200);

		if(Next_getFinger(s_template) == 0) {
					int cptPoint  = 0;
					for(int i=0; i< ROW_CAPTURE_MAX	; i+=2) { // we'll print 1 on 2 pixel because our screen is 128x128 and captor return 180*256
						for(int j=0; j<COLUMN_CAPTURE_MAX; j+=2) {
							if(s_template[(i*COLUMN_CAPTURE_MAX)+j] < 0x40)
								cptPoint++;
						}
					}
					if(cptPoint > 200) {
						for(int i=0; i< ROW_CAPTURE_MAX	; i+=2) {
							for(int j=0; j<COLUMN_CAPTURE_MAX; j+=2) {
								if(s_template[(i*COLUMN_CAPTURE_MAX)+j]<0x32)
									drawPixel(i/2,j/2,rgb24to16(0xFF, 0xFF, 0xFF));
								else
									drawPixel(i/2,j/2,rgb24to16(0x00, 0x00, 0x00)); //if the grey level returned is under 0x32 we print the pixel in with, else in white
							}
						}
					}
		}

	for(;;){}

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
