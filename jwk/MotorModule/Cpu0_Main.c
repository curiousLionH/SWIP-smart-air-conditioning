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

unsigned int range;
unsigned char range_valid_flag = 0;
unsigned int duty = 0;
int speed_mode = 0;

__interrupt(0x0A) __vector_table(0)
void ERU0_ISR(void)
{
    if( (P00_IN.U & (0x1 << P4_BIT_LSB_IDX)) != 0 )     // rising edge of echo
    {
        //                    _________
        //        echo ______|
        //                   ^
        CCU61_TCTR4.U = 0x1 << T12RS_BIT_LSB_IDX;       // start CCU61 T12 counter
    }
    else                                            // falling edge of echo
    {
        //             ______
        //        echo       |______
        //                   ^

        CCU61_TCTR4.B.T12RR = 0x1;       // stop CCU61 T12 counter

        // (1 / t_freq) * counter * 1000000 / 58  =  centimeter
        range = ((CCU61_T12.B.T12CV * 1000000) / 48828) / 58;
        range_valid_flag = 1;

        CCU61_TCTR4.B.T12RES = 0x1;       // reset CCU61 T12 counter
    }
}

__interrupt(0x0B) __vector_table(0)
void CCU60_T12_ISR(void)
{
    // end of 10us Trig
    // GPIO P02.6 --> LOW
    P02_OUT.U &= ~(0x1 << P6_BIT_LSB_IDX);
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

    initSensors();

    ////////////////////added
    GTM_TOM0_TGC1_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX;

    while(1)
    {
        usonicTrigger();
        while( range_valid_flag == 0);

        if(range >= 50)
        {
            duty = 0;
        }
        else if ((P00_IN.B.P1 != 0)) {
            duty = 20000;
            speed_mode = 3;
        }
        else if ((P00_IN.B.P3 != 0) && (P00_IN.B.P2 == 0))
        {
            duty = (25000 * 2000) / 4096;
            speed_mode = 2;
        }
        else if ((P00_IN.B.P3 == 0) && (P00_IN.B.P2 != 0))
        {
            duty = (25000 * 1000) / 4096;
            speed_mode = 1;
        }
        else if ((P00_IN.B.P3 == 0) && (P00_IN.B.P2 == 0))
        {
            duty = 0;
            speed_mode = 0;
        }


        GTM_TOM0_CH9_SR1.B.SR1 = duty;

    }
    /////////////////////added_end
    return (1);
}