/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SM1.h
**     Project     : SESAMETOUCH_FINALv2
**     Processor   : MK64FN1M0VLL12
**     Component   : SynchroMaster
**     Version     : Component 02.347, Driver 01.01, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-14, 09:36, # CodeGen: 0
**     Abstract    :
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**          Component name                                 : SM1
**          Channel                                        : SPI0
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : 
**            Interrupt from input                         : INT_SPI0
**            Interrupt input priority                     : medium priority
**            Interrupt from output                        : INT_SPI0
**            Interrupt output priority                    : medium priority
**            Input buffer size                            : 2
**            Output buffer size                           : 2
**          Settings                                       : 
**            Width                                        : 8 bits
**            Input pin                                    : Enabled
**              Pin                                        : ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK
**            Output pin                                   : Enabled
**              Pin                                        : PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1
**            Clock pin                                    : 
**              Pin                                        : PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0
**            Slave select pin                             : Enabled
**              Pin                                        : PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1
**              Direction                                  : Output
**              Active level                               : Low
**            Clock edge                                   : falling edge
**            Shift clock rate                             : 0.1 �s
**            Delay between chars                          : 0.1 �s
**            CS to CLK delay                              : 0.1 �s
**            CLK to CS delay                              : 0.1 �s
**            Empty character                              : 0
**            Ignore empty char.                           : no
**            Send MSB first                               : yes
**            Shift clock idle polarity                    : Low
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component disabled
**            Low speed mode                               : This component enabled
**            Slow speed mode                              : This component disabled
**          Referenced components                          : 
**            SPIMaster_LDD                                : SPIMaster_LDD
**     Contents    :
**         RecvChar        - byte SM1_RecvChar(SM1_TComData *Chr);
**         SendChar        - byte SM1_SendChar(SM1_TComData Chr);
**         RecvBlock       - byte SM1_RecvBlock(SM1_TComData *Ptr, word Size, word *Rcv);
**         SendBlock       - byte SM1_SendBlock(SM1_TComData *Ptr, word Size, word *Snd);
**         ClearRxBuf      - byte SM1_ClearRxBuf(void);
**         ClearTxBuf      - byte SM1_ClearTxBuf(void);
**         GetCharsInRxBuf - word SM1_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word SM1_GetCharsInTxBuf(void);
**         GetError        - byte SM1_GetError(SM1_TError *Err);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
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
** @file SM1.h
** @version 01.01
** @brief
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup SM1_module SM1 module documentation
**  @{
*/         

#ifndef __SM1
#define __SM1

/* MODULE SM1. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "SMasterLdd1.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 

#ifndef __BWUserType_SM1_TComData
#define __BWUserType_SM1_TComData
  typedef byte SM1_TComData;           /* User type for communication. */
#endif

#ifndef __BWUserType_SM1_TError
#define __BWUserType_SM1_TError
  typedef union {
  byte err;
  struct {
    bool OverRun  : 1;   /* OverRun error flag - the data overflow on the input has been detected. Both hardware detection (if supported) and software detection (when the value of Input buffer size property is 0) is used. */
    bool RxBufOvf : 1;   /* Rx buffer full error flag - the input circular buffer defined by the Input buffer size property has overrun. */
    bool FaultErr : 1;   /* Fault mode error flag - only if supported by hardware */
  }errName;
} SM1_TError;                          /* Error flags. For languages which don't support bit access is byte access only to error flags possible.  */
#endif

#define SM1_EOF 0                      /* Value of the empty character defined in the <a href="SynchroMasterProperties.html#EOF">Empty character</a> property. */
#define SM1_INP_BUF_SIZE 2U            /* Input buffer size */
#define SM1_OUT_BUF_SIZE 2U            /* Output buffer size */

byte SM1_RecvChar(SM1_TComData *Chr);
/*
** ===================================================================
**     Method      :  SM1_RecvChar (component SynchroMaster)
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

byte SM1_SendChar(SM1_TComData Chr);
/*
** ===================================================================
**     Method      :  SM1_SendChar (component SynchroMaster)
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

byte SM1_RecvBlock(SM1_TComData *Ptr,word Size,word *Rcv);
/*
** ===================================================================
**     Method      :  SM1_RecvBlock (component SynchroMaster)
**     Description :
**         If any data received, this method returns the block of the
**         data and its length (and incidental error), otherwise it
**         returns error code (it does not wait for data).
**         If less than requested number of characters is received only
**         the available data is copied from the receive buffer to the
**         user specified destination and the ERR_EXEMPTY value is
**         returned.
**         This method is available only if non-zero length of input
**         buffer is defined.
**         For information about SW overrun behavior please see
**         <General info page>.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block of received data
**         Size            - The size of the block
**       * Rcv             - Pointer to a variable where an actual
**                           number of copied characters is stored
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK - The valid data is received.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode.
**                           ERR_RXEMPTY - It was not possible to read
**                           requested number of bytes from the buffer.
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last char or block received. If
**                           interrupt service is enabled, and input
**                           buffer allocated by the component is full,
**                           the component behaviour depends on <Input
**                           buffer size> property : if property is 0,
**                           last received data-word is preserved (and
**                           previous is overwritten), if property is
**                           greater than 0, new received data-word are
**                           ignored.
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

byte SM1_SendBlock(SM1_TComData *Ptr,word Size,word *Snd);
/*
** ===================================================================
**     Method      :  SM1_SendBlock (component SynchroMaster)
**     Description :
**         Send a block of characters to the channel. This method is
**         only available if a non-zero length of output buffer is
**         defined.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send
**         Size            - Size of the block
**       * Snd             - Pointer to number of data that are sent
**                           (moved to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled (only if
**                           output DMA is supported and enabled)
**                           ERR_TXFULL - It was not possible to send
**                           requested number of bytes
** ===================================================================
*/

byte SM1_ClearRxBuf(void);
/*
** ===================================================================
**     Method      :  SM1_ClearRxBuf (component SynchroMaster)
**     Description :
**         Clears the receive buffer. This method is available only if
**         a non-zero length of input buffer is defined.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte SM1_ClearTxBuf(void);
/*
** ===================================================================
**     Method      :  SM1_ClearTxBuf (component SynchroMaster)
**     Description :
**         Clears the transmit buffer. This method is only available if
**         a non-zero length of output buffer is defined.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

word SM1_GetCharsInRxBuf(void);
/*
** ===================================================================
**     Method      :  SM1_GetCharsInRxBuf (component SynchroMaster)
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

word SM1_GetCharsInTxBuf(void);
/*
** ===================================================================
**     Method      :  SM1_GetCharsInTxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the output buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/

byte SM1_GetError(SM1_TError *Err);
/*
** ===================================================================
**     Method      :  SM1_GetError (component SynchroMaster)
**     Description :
**         Returns a set of errors on the channel (errors that cannot
**         be returned in given methods). The component accumulates
**         errors in a set; after calling [GetError] this set is
**         returned and cleared. This method is available only if the
**         "Interrupt service/event" property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Err             - A pointer to the returned set of errors
**     Returns     :
**         ---             - Error code (if GetError did not succeed),
**                           possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

void SM1_Init(void);
/*
** ===================================================================
**     Method      :  SM1_Init (component SynchroMaster)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void SM1_SetClockConfiguration(LDD_TClockConfiguration ClockConfiguration);
/*
** ===================================================================
**     Method      :  SM1_SetClockConfiguration (component SynchroMaster)
**
**     Description :
**         This method changes the clock configuration.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void SMasterLdd1_OnBlockReceived(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Method      :  SM1_SMasterLdd1_OnBlockReceived (component SynchroMaster)
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

void SMasterLdd1_OnBlockSent(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Method      :  SM1_SMasterLdd1_OnBlockSent (component SynchroMaster)
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

/* END SM1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __SM1 */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
