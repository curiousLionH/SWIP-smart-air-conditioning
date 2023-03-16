/*
    File Name   : submodule_led.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.16
*/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "submodule.h"

extern unsigned int range;

/*
    Function Name   : initMotor
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


/*
    Function Name   : calDuty
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.16
    input           : void
    output          : void
    Description     : Calculate Duty
*/

unsigned int calDuty(void)
{
    unsigned int duty = 0;

    if(P00_IN.B.P0 == 0) // manual mode
    {
        if ((P00_IN.B.P1 != 0)) {
            duty = 25000;
        }
        else if ((P00_IN.B.P3 != 0) && (P00_IN.B.P2 == 0))
        {
            duty = (25000 * 2000) / 4096;
        }
        else if ((P00_IN.B.P3 == 0) && (P00_IN.B.P2 != 0))
        {
            duty = (25000 * 1000) / 4096;
        }
        else if ((P00_IN.B.P3 == 0) && (P00_IN.B.P2 == 0))
        {
            duty = 0;
        }
    }
    else // smart mode
    {

        if(range >= 50)
        {
            duty = 0;
        }
        else if((P00_IN.B.P1 != 0))
        {
            duty += 10;
        }
        else if((P00_IN.B.P2 != 0))
        {
            duty -= 10;
        }
        else
        {
            // Bypass
        }
    }

    return duty;
}