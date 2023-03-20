/*
    File Name   : submodule_RX.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.16
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxGtm_reg.h"

#include "submodule.h"

/*
    Function Name   : initRX
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.16
    input           : void
    output          : void
    Description     : init RX (void)
*/

void initRX(void)
{
    P00_IOCR0.U &= ~(0x1F << PC3_BIT_LSB_IDX);
    P00_IOCR0.U |= (0x01 << PC3_BIT_LSB_IDX);

    P00_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P00_IOCR0.U |= (0x01 << PC1_BIT_LSB_IDX);

    P00_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX);
    P00_IOCR0.U |= (0x01 << PC2_BIT_LSB_IDX);
}