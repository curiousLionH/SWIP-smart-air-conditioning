/*
    File Name   : submodule_motor.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxCcu6_reg.h"
#include "IfxVadc_reg.h"
#include "IfxGtm_reg.h"

#include "submodule.h"

/*
    Function Name   : initMotor
    Author          : SWIP 1th   - Team 1
    Date            : 2023.03.15
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
    Function Name   : driveMotor
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Drive Motor
*/
void driveMotor(unsigned short* duty)
{
    P10_OUT.U |= 0x1 << P1_BIT_LSB_IDX;
    P02_OUT.U |= 0x1 << P1_BIT_LSB_IDX;
    P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);
    GTM_TOM0_CH2_SR1.U = *duty;
    GTM_TOM0_CH9_SR1.U = *duty;
}
