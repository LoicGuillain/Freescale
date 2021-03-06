/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : SM2.h
**     Project     : OLED_SENSOR_SPI
**     Processor   : MK64FN1M0VLL12
**     Component   : SynchroMaster
**     Version     : Component 02.347, Driver 01.01, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-08-26, 16:41, # CodeGen: 1
**     Abstract    :
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**         Synchro type                : MASTER
**
**         Serial channel              : SPI1
**
**         Protocol
**             Clock edge              : falling
**             Width                   : 8 bits
**             Empty character         : 0
**             Empty char. on input    : RECEIVED
**
**         Registers
**             Control register        : SPI1_MCR  [0x4002D000]
**             Mode register           : SPI1_CTAR0 [0x4002D00C]
**             Baud setting reg.       : SPI1_CTAR0 [0x4002D00C]
**
**
**
**         Used pins                   :
**         ----------------------------------------------------------
**              Function    | On package |    Name
**         ----------------------------------------------------------
**               Input      |     63     |  PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b
**               Output     |     62     |  PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN
**               Clock      |     59     |  ADC1_SE15/PTB11/SPI1_SCK/UART3_TX/FB_AD18/FTM0_FLT2
**           Select slave   |     58     |  ADC1_SE14/PTB10/SPI1_PCS0/UART3_RX/FB_AD19/FTM0_FLT1
**         ----------------------------------------------------------
**
**     Contents    :
**         RecvChar        - byte SM2_RecvChar(SM2_TComData *Chr);
**         SendChar        - byte SM2_SendChar(SM2_TComData Chr);
**         GetCharsInRxBuf - word SM2_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word SM2_GetCharsInTxBuf(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file SM2.h
** @version 01.01
** @brief
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup SM2_module SM2 module documentation
**  @{
*/         

#ifndef __SM2
#define __SM2

/* MODULE SM2. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "SMasterLdd2.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 

#ifndef __BWUserType_SM2_TComData
#define __BWUserType_SM2_TComData
  typedef byte SM2_TComData;           /* User type for communication. */
#endif

#ifndef __BWUserType_SM2_TError
#define __BWUserType_SM2_TError
  typedef union {
  byte err;
  struct {
    bool OverRun  : 1;   /* OverRun error flag - the data overflow on the input has been detected. Both hardware detection (if supported) and software detection (when the value of Input buffer size property is 0) is used. */
    bool RxBufOvf : 1;   /* Rx buffer full error flag - the input circular buffer defined by the Input buffer size property has overrun. */
    bool FaultErr : 1;   /* Fault mode error flag - only if supported by hardware */
  }errName;
} SM2_TError;                          /* Error flags. For languages which don't support bit access is byte access only to error flags possible.  */
#endif

#define SM2_EOF 0                      /* Value of the empty character defined in the <a href="SynchroMasterProperties.html#EOF">Empty character</a> property. */

byte SM2_RecvChar(SM2_TComData *Chr);
/*
** ===================================================================
**     Method      :  SM2_RecvChar (component SynchroMaster)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). 
**         For information about SW overrun behavior please see
**         <General info page>.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - A pointer to the received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK - The valid data is received.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode.
**                           ERR_RXEMPTY - No data in receiver.
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last char or block received. In
**                           polling mode, this error code is returned
**                           only when the hardware supports detection
**                           of the overrun error. If interrupt service
**                           is enabled, and input buffer allocated by
**                           the component is full, the component
**                           behaviour depends on <Input buffer size>
**                           property : if property is 0, last received
**                           data-word is preserved (and previous is
**                           overwritten), if property is greater than 0,
**                           new received data-word are ignored.
**                           ERR_FAULT - Fault error was detected from
**                           the last char or block received. In the
**                           polling mode the ERR_FAULT is return until
**                           the user clear the fault flag bit, but in
**                           the interrupt mode ERR_FAULT is returned
**                           only once after the fault error occured.
**                           This error is supported only on the CPUs
**                           supports the faul mode function - where
**                           <Fault mode> property is available.
** ===================================================================
*/

byte SM2_SendChar(SM2_TComData Chr);
/*
** ===================================================================
**     Method      :  SM2_SendChar (component SynchroMaster)
**     Description :
**         Sends one character to the channel.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled (only if
**                           output DMA is supported and enabled)
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/

word SM2_GetCharsInRxBuf(void);
/*
** ===================================================================
**     Method      :  SM2_GetCharsInRxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the input buffer.
**         Note: If the Interrupt service is disabled, and the Ignore
**         empty character is set to yes, and a character has been
**         received, then this method returns 1 although it was an
**         empty character.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer.
** ===================================================================
*/

word SM2_GetCharsInTxBuf(void);
/*
** ===================================================================
**     Method      :  SM2_GetCharsInTxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the output buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/

void SM2_Init(void);
/*
** ===================================================================
**     Method      :  SM2_Init (component SynchroMaster)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void SMasterLdd2_OnBlockReceived(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Method      :  SM2_SMasterLdd2_OnBlockReceived (component SynchroMaster)
**
**     Description :
**         This event is called when the requested number of data is 
**         moved to the input buffer. This method is available only if 
**         the ReceiveBlock method is enabled. The event services the 
**         event of the inherited component and eventually invokes other 
**         events.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void SMasterLdd2_OnBlockSent(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Method      :  SM2_SMasterLdd2_OnBlockSent (component SynchroMaster)
**
**     Description :
**         This event is called after the last character from the output 
**         buffer is moved to the transmitter. This event is available 
**         only if the SendBlock method is enabled. The event services 
**         the event of the inherited component and eventually invokes 
**         other events.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END SM2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __SM2 */
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
