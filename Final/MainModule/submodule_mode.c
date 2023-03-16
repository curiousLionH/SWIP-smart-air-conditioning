/*
    File Name   : submodule_mode.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxGtm_reg.h"

#include "submodule.h"

/*
    Function Name   : setMode
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Set Mode (Manual, Smart)
*/
void setMode(void)
{   
    // Manual (White) => Smart (Green)
    if ( (P10_OUT.U & (0x1 << P3_BIT_LSB_IDX)) )
    {
        P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX);
        P10_OUT.U |=  (0x1 << P5_BIT_LSB_IDX);
        P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);
    }

    // Smart (Green) => Manual (White)
    else
    {
        P10_OUT.U |= (0x1 << P3_BIT_LSB_IDX);
        P10_OUT.U |= (0x1 << P5_BIT_LSB_IDX);
        P02_OUT.U |= (0x1 << P7_BIT_LSB_IDX); 
    }
    
    // Buzzer On / Off
    GTM_TOM0_CH11_SR0.B.SR0 = 6250000 / 130;
    GTM_TOM0_CH11_SR1.B.SR1 = 3125000 / 130;
    for(unsigned int i = 0; i < 20000000; i++);
    GTM_TOM0_CH11_SR0.B.SR0 = 0;
    GTM_TOM0_CH11_SR1.B.SR1 = 0;
}

/*
    Function Name   : decideACC
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : unsigned short*, unsigned short* , int*
    output          : void
    Description     : decide SMART MODE ACC value
*/

void decideAcc(unsigned short* cur_duty, unsigned short* tgt_duty, int* smartAcc)
{
    if(*cur_duty == *tgt_duty)
            {
                // ... 
                *smartAcc = 0;
            }
            else if(*cur_duty < *tgt_duty)
            {
                // Acc
                *smartAcc = 1;
                *cur_duty = *cur_duty + 10;
            }
            else 
            {
                // Dec
                *smartAcc = 2;
                *cur_duty = *cur_duty - 10;
            }
}
