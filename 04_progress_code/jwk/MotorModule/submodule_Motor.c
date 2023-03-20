/*
    File Name   : submodule_led.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.16
*/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "submodule.h"

/*
    Function Name   : initLED
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.16
    input           : void
    output          : void
    Description     : Set Motor
*/

void initMotor(void)
{
    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P02_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P02_IOCR4.U &= ~(0x1F << PC7_BIT_LSB_IDX);

    P10_IOCR0.U |= 0x10 << PC1_BIT_LSB_IDX;
    P02_IOCR0.U |= 0x11 << PC1_BIT_LSB_IDX;
    P02_IOCR4.U |= 0x10 << PC7_BIT_LSB_IDX;
}