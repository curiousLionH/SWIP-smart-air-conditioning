/*
    File Name   : submodule_ultrasonic.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.16
*/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxCcu6_reg.h"

#include "submodule.h"

/*
    Function Name   : initUSonic
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.16
    input           : void
    output          : void
    Description     : Set ultrasonic
*/

extern unsigned int range;
extern unsigned char range_valid_flag;

void initUSonic(void)
{
    P02_IOCR4.U &= ~(0x1F << PC6_BIT_LSB_IDX);       // reset P02_IOCR4 PC6
    P00_IOCR4.U &= ~(0x1F << PC4_BIT_LSB_IDX);       // reset P00_IOCR4 PC4

    P00_IOCR4.U |= 0x01 << PC4_BIT_LSB_IDX;        // set P00.4 general input (pull-down connected) [Echo]
    P02_IOCR4.U |= 0x10 << PC6_BIT_LSB_IDX;        // set P02.6 push-pull general output            [Trig]

    P02_OUT.U &= ~(0x1 << P6_BIT_LSB_IDX);
}

/*
    Function Name   : usonicTrigger
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.16
    input           : void
    output          : void
    Description     : set uSonic trigger
*/

void usonicTrigger(void)
{
    // start of 10us Trigger Pulse
    // GPIO P02.6 --> HIGH
    P02_OUT.U |= 0x1 << P6_BIT_LSB_IDX;
    range_valid_flag = 0;
    CCU60_TCTR4.U = 0x1 << T12RS_BIT_LSB_IDX;           // T12 start counting
}