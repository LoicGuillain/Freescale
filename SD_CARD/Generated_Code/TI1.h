/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : TI1.h
**     Project     : SD_CARD
**     Processor   : MK64FN1M0VLQ12
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-08-03, 09:53, # CodeGen: 10
**     Abstract    :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings    :
**         Timer name                  : FTM0_CNT (16-bit)
**         Compare name                : FTM0_MOD
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-[driven by slave component]
**             Clock                   : [driven by slave component] Hz
**           Initial period/frequency
**             Xtal ticks              : ---
**             microseconds            : ---
**             milliseconds            : 10
**             seconds                 : ---
**             seconds (real)          : 10
**             Hz                      : ---
**             kHz                     : ---
**             MHz                     : ---
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : FTM0_CNT  [0x40038004]
**              Mode                   : FTM0_SC   [0x40038000]
**              Run                    : FTM0_SC   [0x40038000]
**              Prescaler              : FTM0_SC   [0x40038000]
**
**         Compare registers
**              Compare                : FTM0_MOD  [0x40038008]
**
**         Flip-flop registers
**              Mode                   : FTM0_SC   [0x40038000]
**     Contents    :
**         No public methods
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
** @file TI1.h
** @version 01.02
** @brief
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
*/         
/*!
**  @addtogroup TI1_module TI1 module documentation
**  @{
*/         

#ifndef __TI1_H
#define __TI1_H

/* MODULE TI1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "TimerIntLdd1.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 




/*
** ===================================================================
**     Method      :  TI1_OnInterrupt (component TimerInt)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TimerIntLdd1_OnInterrupt(LDD_TUserData *UserDataPtr);

/* END TI1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __TI1_H */
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
