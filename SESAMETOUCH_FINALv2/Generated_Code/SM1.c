/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SM1.c
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
** @file SM1.c
** @version 01.01
** @brief
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup SM1_module SM1 module documentation
**  @{
*/         

/* MODULE SM1. */

#include "Events.h"
#include "SM1.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define OVERRUN_ERR      0x01U         /* Overrun error flag bit   */
#define TX_BUF_EMPTY     0x02U         /* Tx buffer state flag bit   */
#define CHAR_IN_RX       0x08U         /* Char is in RX buffer     */
#define FULL_TX          0x10U         /* Full transmit buffer     */
#define RUNINT_FROM_TX   0x20U         /* Interrupt is in progress */
#define FULL_RX          0x40U         /* Full receive buffer      */

LDD_TDeviceData *SMasterLdd1_DeviceDataPtr; /* Device data pointer */
static bool EnMode;                    /* Enable/Disable SPI in speed mode */
static byte SerFlag;                   /* Flags for serial communication */
                                       /* Bits: 0 - OverRun error */
                                       /*       1 - Tx buffer state after init */
                                       /*       2 - Unused */
                                       /*       3 - Char in RX buffer */
                                       /*       4 - Full TX buffer */
                                       /*       5 - Running int from TX */
                                       /*       6 - Full RX buffer */
                                       /*       7 - Unused */
static byte ErrFlag;                   /* Error flags for GetError method */
static volatile word SM1_InpLen;       /* Length of input buffer's content */
static byte InpIndexR;                 /* Index for reading from input buffer */
static byte InpIndexW;                 /* Index for writing to input buffer */
static SM1_TComData InpBuffer[SM1_INP_BUF_SIZE]; /* Input buffer SPI communication */
static SM1_TComData BufferRead;        /* Input char SPI communication */
static volatile word SM1_OutLen;       /* Length of output bufer's content */
static byte OutIndexR;                 /* Index for reading from output buffer */
static byte OutIndexW;                 /* Index for writing to output buffer */
static SM1_TComData OutBuffer[SM1_OUT_BUF_SIZE]; /* Output buffer for SPI communication */
static bool OnFreeTxBufSemaphore;      /* Disable the false calling of the OnFreeTxBuf event */
/* Internal method prototypes */
static void HWEnDi(void);

/*
** ===================================================================
**     Method      :  HWEnDi (component SynchroMaster)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (EnMode) {                        /* Enable device? */
    (void)SMasterLdd1_Enable(SMasterLdd1_DeviceDataPtr); /* Enable SPI device */
    (void)SMasterLdd1_ReceiveBlock(SMasterLdd1_DeviceDataPtr, &BufferRead, 1U); /* Receive one data byte */
    if ((SM1_OutLen) != 0U) {          /* Is number of bytes in the transmit buffer greater then 0? */
      SerFlag |= RUNINT_FROM_TX;       /* Set flag "running int from TX"? */
      (void)SMasterLdd1_SendBlock(SMasterLdd1_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
    }
  } else {
    SerFlag &= (byte)~(RUNINT_FROM_TX); /* Clear RUNINT_FROM_TX flag */
    (void)SMasterLdd1_Disable(SMasterLdd1_DeviceDataPtr); /* Disable device */
  }
}

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
byte SM1_RecvChar(SM1_TComData *Chr)
{
  register byte FlagTmp;

  if (!EnMode) {                       /* Is the device disabled in the actual speed CPU mode? */
    return ERR_SPEED;                  /* If yes then error */
  }
  if (SM1_InpLen > 0U) {               /* Is number of received chars greater than 0? */
    EnterCritical();                   /* Disable global interrupts */
    SM1_InpLen--;                      /* Decrease number of received chars */
    *Chr = InpBuffer[InpIndexR++];     /* Read the char */
    if (InpIndexR >= SM1_INP_BUF_SIZE) { /* Is the index out of the receive buffer? */
      InpIndexR = 0x00U;               /* Set index to the first item into the receive buffer */
    }
    FlagTmp = SerFlag;                 /* Safe the flags */
    SerFlag &= (byte)~(OVERRUN_ERR | FULL_RX); /* Clear flag "char in RX buffer" */
    ExitCritical();                    /* Enable global interrupts */
  } else {
    return ERR_RXEMPTY;                /* Receiver is empty */
  }
  if ((FlagTmp & (OVERRUN_ERR | FULL_RX)) != 0U) { /* Is the overrun occurred? */
    return ERR_OVERRUN;                /* If yes then return error */
  } else {
    return ERR_OK;
  }
}

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
byte SM1_SendChar(SM1_TComData Chr)
{
  if (!EnMode) {                       /* Is the device disabled in the actual speed CPU mode? */
    return ERR_SPEED;                  /* If yes then error */
  }
  if (SM1_OutLen == SM1_OUT_BUF_SIZE) { /* Is number of chars in buffer the same as the size of transmit buffer? */
    return ERR_TXFULL;                 /* If yes then error */
  }
  EnterCritical();                     /* Disable global interrupts */
  SM1_OutLen++;                        /* Increase number of bytes in the transmit buffer */
  OutBuffer[OutIndexW++] = Chr;        /* Store char to buffer */
  if (OutIndexW >= SM1_OUT_BUF_SIZE) { /* Is the index out of the transmit buffer? */
    OutIndexW = 0x00U;                 /* Set index to the first item in the transmit buffer */
  }
  if ((SerFlag & RUNINT_FROM_TX) == 0U) {
    SerFlag |= RUNINT_FROM_TX;         /* Set flag "running int from TX"? */
    (void)SMasterLdd1_SendBlock(SMasterLdd1_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
  }
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;
}

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
byte SM1_RecvBlock(SM1_TComData *Ptr,word Size,word *Rcv)
{
  register word count;                 /* Number of received chars */
  register byte Result = ERR_OK;       /* Most serious error */
  register byte ResultTmp;             /* Last error */


  if (!EnMode) {                       /* Is the device disabled in the actual speed CPU mode? */
    return ERR_SPEED;                  /* If yes then error */
  }
  count = 0U;
  while (count < Size) {
    ResultTmp = SM1_RecvChar(Ptr++);   /* Receive one character */
    if (ResultTmp > Result) {          /* Is last error most serious than through error state? */
      Result = ResultTmp;              /* If yes then prepare error value to return */
    }
    if ((ResultTmp != ERR_OK)&&(ResultTmp != ERR_OVERRUN)) { /* Receiving given number of chars */
      break;                           /* Break data block receiving */
    }
    count++;
  }
  *Rcv = count;                        /* Return number of received chars */
  return Result;                       /* Return most serious error */
}

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
byte SM1_SendBlock(SM1_TComData *Ptr, word Size, word *Snd)
{
  word count = 0x00U;                  /* Number of sent chars */
  SM1_TComData *TmpPtr = Ptr;          /* Temporary output buffer pointer */
  bool tmpOnFreeTxBufSemaphore = OnFreeTxBufSemaphore; /* Local copy of OnFreeTxBufSemaphore state */

  if (!EnMode) {                       /* Is the device disabled in the actual speed CPU mode? */
    return ERR_SPEED;                  /* If yes then error */
  }
  while((count < Size) && (SM1_OutLen < SM1_OUT_BUF_SIZE)) { /* While there is some char desired to send left and output buffer is not full do */
    EnterCritical();                   /* Enter the critical section */
    OnFreeTxBufSemaphore = TRUE;       /* Set the OnFreeTxBufSemaphore to block OnFreeTxBuf calling */
    SM1_OutLen++;                      /* Increase number of bytes in the transmit buffer */
    OutBuffer[OutIndexW++] = *TmpPtr++; /* Store char to buffer */
    if (OutIndexW >= SM1_OUT_BUF_SIZE) { /* Is the index out of the transmit buffer? */
      OutIndexW = 0x00U;               /* Set index to the first item in the transmit buffer */
    }
    count++;                           /* Increase the count of sent data */
    if ((count == Size) || (SM1_OutLen == SM1_OUT_BUF_SIZE)) { /* Is the last desired char put into buffer or the buffer is full? */
      if (!tmpOnFreeTxBufSemaphore) {  /* Was the OnFreeTxBufSemaphore clear before enter the method? */
        OnFreeTxBufSemaphore = FALSE;  /* If yes then clear the OnFreeTxBufSemaphore */
      }
    }
    if ((SerFlag & RUNINT_FROM_TX) == 0U) {
      SerFlag |= RUNINT_FROM_TX;       /* Set flag "running int from TX"? */
      (void)SMasterLdd1_SendBlock(SMasterLdd1_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
    }
    ExitCritical();                    /* Exit the critical section */
  }
  *Snd = count;                        /* Return number of sent chars */
  if (count != Size) {                 /* Is the number of sent chars less then desired number of chars */
    return ERR_TXFULL;                 /* If yes then error */
  }
  return ERR_OK;                       /* OK */
}

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
byte SM1_ClearRxBuf(void)
{
  if (!EnMode) {                       /* Is the device disabled in the actual speed CPU mode? */
    return ERR_SPEED;                  /* If yes then error */
  }
  EnterCritical();                     /* Disable global interrupts */
  SM1_InpLen = 0U;                     /* Set number of chars in the transmit buffer to 0 */
  InpIndexW = 0x00U;                   /* Set index on the first item in the transmit buffer */
  InpIndexR = 0x00U;
  SerFlag &= (byte)~(OVERRUN_ERR | FULL_RX); /* Clear flags */
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;                       /* OK */
}

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
byte SM1_ClearTxBuf(void)
{
  if (!EnMode) {                       /* Is the device disabled in the actual speed CPU mode? */
    return ERR_SPEED;                  /* If yes then error */
  }
  EnterCritical();                     /* Disable global interrupts */
  SM1_OutLen = 0U;                     /* Set number of chars in the receive buffer to 0 */
  OutIndexW = 0x00U;                   /* Set index on the first item in the receive buffer */
  OutIndexR = 0x00U;
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;                       /* OK */
}

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
word SM1_GetCharsInRxBuf(void)
{
  return SM1_InpLen;                   /* Return number of chars in receive buffer */
}

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
word SM1_GetCharsInTxBuf(void)
{
  return SM1_OutLen;                   /* Return number of chars in the transmit buffer */
}

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
byte SM1_GetError(SM1_TError *Err)
{
  if (!EnMode) {                       /* Is the device disabled in the actual speed CPU mode? */
    return ERR_SPEED;                  /* If yes then error */
  }
  EnterCritical();                     /* Disable global interrupts */
  Err->err = 0U;
  Err->errName.OverRun = (((ErrFlag & OVERRUN_ERR) != 0U)? 1U : 0U); /* Overrun error */
  Err->errName.RxBufOvf = (((ErrFlag & FULL_RX) != 0U)? 1U : 0U); /* Buffer overflow */
  ErrFlag = 0x00U;                     /* Reset error flags */
  ExitCritical();                      /* Enable global interrupts */
  return ERR_OK;                       /* OK */
}

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
void SM1_Init(void)
{
  SerFlag = 0U;                        /* Reset all flags */
  ErrFlag = 0U;                        /* Reset all flags in mirror */
  OnFreeTxBufSemaphore = FALSE;        /* Clear the OnFreeTxBufSemaphore */
  SM1_InpLen = 0U;                     /* No char in the receive buffer */
  InpIndexR = 0x00U;                   /* Set index on the first item in the receive buffer */
  InpIndexW = 0x00U;
  SM1_OutLen = 0U;                     /* No char in the transmit buffer */
  OutIndexR = 0x00U;                   /* Set index on the first item in the transmit buffer */
  OutIndexW = 0x00U;
  SMasterLdd1_DeviceDataPtr = SMasterLdd1_Init(NULL); /* Calling init method of the inherited component */
  EnMode = FALSE;                      /* Set the flag "device disabled" in high speed CPU mode */
  HWEnDi();                            /* Enable/disable device according to the status flags */
}

/*
** ===================================================================
**     Method      :  SM1_SetClockConfiguration (component SynchroMaster)
**
**     Description :
**         This method changes the clock configuration.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void SM1_SetClockConfiguration(LDD_TClockConfiguration ClockConfiguration)
{
  switch (ClockConfiguration) {
    case CPU_CLOCK_CONFIG_1:
      EnMode = TRUE;                   /* Set the flag "device enabled" in the actual speed CPU mode */
      break;
    default:
      EnMode = FALSE;                  /* Set the flag "device disabled" in the actual speed CPU mode */
      break;
  }
  if (EnMode) {                        /* Enable device? */
    HWEnDi();                          /* Enable/disable device according to status flags */
  }
}

#define ON_ERROR        0x01U
#define ON_FULL_RX      0x02U
#define ON_RX_CHAR      0x04U
#define ON_RX_CHAR_EXT  0x08U
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
void SMasterLdd1_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
  register byte Flags = 0U;            /* Temporary variable for flags */

  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  if (SM1_InpLen < SM1_INP_BUF_SIZE) { /* Is number of bytes in the receive buffer lower than size of buffer? */
    SM1_InpLen++;                      /* Increase number of chars in the receive buffer */
    InpBuffer[InpIndexW++] = (SM1_TComData)BufferRead; /* Save received char to the receive buffer */
    if (InpIndexW >= SM1_INP_BUF_SIZE) { /* Is the index out of the receive buffer? */
      InpIndexW = 0x00U;               /* Set index on the first item into the receive buffer */
    }
    Flags |= ON_RX_CHAR;               /* If yes then set the OnRxChar flag */
    if (SM1_InpLen == SM1_INP_BUF_SIZE) { /* Is number of bytes in the receive buffer equal to the size of buffer? */
      Flags |= ON_FULL_RX;             /* Set flag "OnFullRxBuf" */
    }
  } else {
    SerFlag |= FULL_RX;                /* Set flag "full RX buffer" */
    ErrFlag |= FULL_RX;                /* Set flag "full RX buffer" for GetError method */
    Flags |= ON_ERROR;                 /* Set the OnError flag */
  }
  if ((Flags & ON_ERROR) != 0U) {      /* Is any error flag set? */
    SM1_OnError();                     /* Invoke user event */
  } else {
    if ((Flags & ON_RX_CHAR) != 0U) {  /* Is OnRxChar flag set? */
      SM1_OnRxChar();                  /* Invoke user event */
    }
    if ((Flags & ON_FULL_RX) != 0U) {  /* Is OnTxChar flag set? */
      SM1_OnFullRxBuf();               /* Invoke user event */
    }
  }
  (void)SMasterLdd1_ReceiveBlock(SMasterLdd1_DeviceDataPtr, &BufferRead, 1U); /* Receive one data byte */
}

#define ON_FREE_TX  0x01U
#define ON_TX_CHAR  0x02U
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
void SMasterLdd1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  register byte Flags = 0U;            /* Temporary variable for flags */

  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  if ((SerFlag & RUNINT_FROM_TX) != 0U) { /* Is flag "running int from TX" set? */
    Flags |= ON_TX_CHAR ;              /* Set the OnTXChar flag */
  }
  OutIndexR++;
  if (OutIndexR >= SM1_OUT_BUF_SIZE) { /* Is the index out of the transmit buffer? */
    OutIndexR = 0x00U;                 /* Set index on the first item into the transmit buffer */
  }
  SM1_OutLen--;                        /* Decrease number of chars in the transmit buffer */
  if (SM1_OutLen != 0U) {              /* Is number of bytes in the transmit buffer greater then 0? */
    SerFlag |= RUNINT_FROM_TX;         /* Set flag "running int from TX"? */
    (void)SMasterLdd1_SendBlock(SMasterLdd1_DeviceDataPtr, (LDD_TData *)&OutBuffer[OutIndexR], 1U); /* Send one data byte */
  } else {
    SerFlag &= (byte)~(RUNINT_FROM_TX | FULL_TX); /* Clear "running int from TX" and "full TX buff" flags */
    if (!(OnFreeTxBufSemaphore)) {     /* Is the OnFreeTXBuf flag blocked ?*/
      Flags |= ON_FREE_TX;             /* If not, set the OnFreeTxBuf flag */
    }
  }
  if ((Flags & ON_TX_CHAR) != 0U) {    /* Is flag "OnTxChar" set? */
    SM1_OnTxChar();                    /* Invoke user event */
  }
  if ((Flags & ON_FREE_TX) != 0U) {    /* Is flag "OnFreeTxBuf" set? */
    SM1_OnFreeTxBuf();                 /* Invoke user event */
  }
}

/* END SM1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
