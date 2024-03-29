/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
#include "submodule.h"

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxCcu6_reg.h"
#include "IfxVadc_reg.h"
#include "IfxGtm_reg.h"

IfxCpu_syncEvent g_cpuSyncEvent = 0;

// Initialize Mode Value
int tgtMode = 0;
unsigned int flag;
unsigned short cur_duty = 0;
unsigned short tgt_duty = 0;

__interrupt(0x0A) __vector_table(0)
void ERU0_ISR(void)
{
    setMode();

    switch (tgtMode)
    {
    case 0:
        cur_duty = 0;
        break;
    case 1:
        cur_duty = 6000;
        break;
    case 2:
        cur_duty = 12000;
        break;
    case 3:
        cur_duty = 25000;
        break;
    default:
        break;
    }
}

__interrupt(0x0B) __vector_table(0)
void CCU60_T12_ISR(void)
{
    if ( tgtMode == 3 )
       flag = 1;
}

int core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    // Initialize all sensors
    initSensors();

    // Initialize duty value
    unsigned int adcResult;

    // trigger update request signal
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX;

    unsigned short duty = 0, tgt_duty;
    int smartAcc = 0;

    while(1)
    {
        // if (flag)
        // {
        //     adcResult = 0;
        //     continue;
        // }

        // Manual Mode => RGB LED (WHITE)
        if ( P10_OUT.U & (0x1 << P3_BIT_LSB_IDX) )
        {
            P00_OUT.U &=  ~(0x1 << P0_BIT_LSB_IDX); // P00.0 OFF
            VADC_startConversion(MANUAL_MODE);
            VADC_readResult(&adcResult, MANUAL_MODE);

            decideSpeedMode(&adcResult, &tgtMode);
            dimLED(&adcResult, &duty);
        }

        // Smart Mode => RGB LED (GREEN)
        else
        {
            P00_OUT.U |=  (0x1 << P0_BIT_LSB_IDX); // P00.0 ON
            VADC_startConversion(SMART_MODE);
            VADC_readResult(&adcResult, SMART_MODE);
            
            tgt_duty = 20000 * adcResult /4096;

            // decideAcc(&adcResult, &tgtMode, &smartAcc);
            // sendTX(&tgtMode, SMART_MODE, &smartAcc);
            decideSpeedMode(&adcResult, &tgtMode);
            dimLED(&adcResult, &cur_duty);
        }
    }
    return (1);
}
