/*
    File Name   : submodule_buzzer.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "submodule.h"

/*
    Function Name   : initBuzzer
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Set Buzzer
*/
void initBuzzer(void)
{
    P02_IOCR0.B.PC3 = 0x11; // GTM Output
    //P02_IOCR0.B.PC3 = 0x10; // General-purpose Output
}
