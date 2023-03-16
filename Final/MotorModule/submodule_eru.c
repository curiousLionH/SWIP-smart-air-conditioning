/*
    File Name   : submodule_eru.c
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
    Description     : Set ERU
*/

void initERU(void)
{
    // ERU setting
    SCU_EICR1.U &= ~(0x7 << EXIS0_BIT_LSB_IDX);

    SCU_EICR1.U |= (0x2  << EXIS0_BIT_LSB_IDX);     // ERS2 - Input 2


    SCU_EICR1.U |= 0x1   << FEN0_BIT_LSB_IDX;       // falling edge

    SCU_EICR1.U |= 0x1   << REN0_BIT_LSB_IDX;       // rising edge


    SCU_EICR1.U |= 0x1   << EIEN0_BIT_LSB_IDX;

    SCU_EICR1.U &= ~(0x7 << INP0_BIT_LSB_IDX);

    SCU_IGCR0.U &= ~(0x3 << IGP0_BIT_LSB_IDX);
    SCU_IGCR0.U |= 0x1   << IGP0_BIT_LSB_IDX;

    // SRC Interrupt setting
    SRC_SCU_SCU_ERU0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU0.U |= 0x0A   << SRPN_BIT_LSB_IDX;

    SRC_SCU_SCU_ERU0.U &= ~(0x3  << TOS_BIT_LSB_IDX);

    SRC_SCU_SCU_ERU0.U |= 1      << SRE_BIT_LSB_IDX;
}