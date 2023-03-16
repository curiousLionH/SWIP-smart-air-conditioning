/*
    File Name   : submodule_led.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "submodule.h"

/*
    Function Name   : initLED
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Set LED sesor to use
*/
void initLED(void)
{
    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);     // reset P10_IOCR0 PC1
    P10_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX);     // reset P10_IOCR0 PC2

    P10_IOCR0.U |= 0x10 << PC1_BIT_LSB_IDX;        // set P10.1 push-pull general output
    P10_IOCR0.U |= 0x11 << PC2_BIT_LSB_IDX;        // set P10.2 GTM Out, (PWM Generation)
}

/*
    Function Name   : initRGBLED
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Set LED sesor to use
*/
void initRGBLED(void)
{
    // reset Port IOCR register
    P02_IOCR4.U &= ~(0x1F << PC7_BIT_LSB_IDX);
    P10_IOCR4.U &= ~(0x1F << PC5_BIT_LSB_IDX);
    P10_IOCR0.U &= ~(0x1F << PC3_BIT_LSB_IDX);

    // set Port as general purpose output (push-pull)
    P02_IOCR4.U |= 0x10 << PC7_BIT_LSB_IDX;
    P10_IOCR4.U |= 0x10 << PC5_BIT_LSB_IDX;
    P10_IOCR0.U |= 0x10 << PC3_BIT_LSB_IDX;

    // set default mode (manual mode, white)
    P10_OUT.U |= (0x1 << P3_BIT_LSB_IDX); // Blue
    P10_OUT.U |= (0x1 << P5_BIT_LSB_IDX); // Green
    P02_OUT.U |= (0x1 << P7_BIT_LSB_IDX); // Red
}
