/*
    File Name   : submodule_buzzer.h
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxVadc_reg.h"

#include "submodule.h"

/*
    Function Name   : initButton
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Set Button
*/
void initButton(void)
{
    P02_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);       // reset P02_IOCR0 PC1

    P02_IOCR0.U |= 0x02 << PC1_BIT_LSB_IDX;          // set P02.1 general input (pull-up connected)
}