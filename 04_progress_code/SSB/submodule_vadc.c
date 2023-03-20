/*
    File Name   : submodule_vadc.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxVadc_reg.h"

#include "submodule.h"

/*
    Function Name   : initVADC
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Set VADC
*/
void initVADC(void)
{
    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);    // wait until unlocked

    // Modify Access to clear ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);    // wait until locked

    VADC_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);    // enable VADC

    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);    // wait until unlocked

    // Modify Access to set ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);


    // VADC configurations
    while((VADC_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0); // wait until VADC module enabled

    VADC_G4_ARBPR.U |= 0x3 << PRIO0_BIT_LSB_IDX;         // highest priority for Request Source 0
    VADC_G4_ARBPR.U &= ~(0x1 << CSM0_BIT_LSB_IDX);       // Wait-for-Start Mode
    VADC_G4_ARBPR.U |= 0x1 << ASEN0_BIT_LSB_IDX;         // Arbitration Source Input 0 Enable

    VADC_G4_QMR0.U &= ~(0x3 << ENGT_BIT_LSB_IDX);
    VADC_G4_QMR0.U |= 0x1 << ENGT_BIT_LSB_IDX;          // enable conversion request
    VADC_G4_QMR0.U |= 0x1 << FLUSH_BIT_LSB_IDX;         // clear ADC queue

    VADC_G4_ARBCFG.U |= 0x3 << ANONC_BIT_LSB_IDX;       // ADC normal operation

    VADC_G4_ICLASS0.U &= ~(0x7 << CMS_BIT_LSB_IDX);     // Class 0 Standard Conversion (12-bit)

    // VADC Group 4 Channel 6 configurationB
    VADC_G4_CHCTR6.U |= 0x1 << RESPOS_BIT_LSB_IDX;      // result right-aligned
    VADC_G4_CHCTR6.B.RESREG = 0x2;   // store result @ Result Register G4RES0
    VADC_G4_CHCTR6.B.ICLSEL = 0x0;   // Class 0

    VADC_G4_CHASS.B.ASSCH6 = 0x1;

    // VADC Group 4 Channel 7 configuration
    VADC_G4_CHCTR7.U |= 0x1 << RESPOS_BIT_LSB_IDX;      // result right-aligned
    VADC_G4_CHCTR7.B.RESREG = 0x1;   // store result @ Result Register G4RES0
    VADC_G4_CHCTR7.B.ICLSEL = 0x0;   // Class 0

    VADC_G4_CHASS.B.ASSCH7 = 0x1;

    VADC_G4_QINR0.B.RF = 0x1;
}

/*
    Function Name   : VADC_startConversion
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : int
    output          : void
    Description     : Set LED sesor using PWM
*/
void VADC_startConversion(int mode)
{
    while( VADC_G4_QINR0.B.REQCHNR != mode )
        VADC_G4_QINR0.B.REQCHNR = mode;

    if (mode == 6)
        VADC_G4_QINR0.B.REQCHNR = 0x06; 
    else if (mode == 7)
        VADC_G4_QINR0.B.REQCHNR = 0x07;

    VADC_G4_QMR0.U |= 0x1 << TREV_BIT_LSB_IDX;  // Generate Conversion Start Trigger Event
}

/*
    Function Name   : VADC_readResult
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : unsigned int*, int
    output          : void
    Description     : Set LED sesor using PWM
*/
void VADC_readResult(unsigned int* result, int mode)
{
    // unsigned int result;

    if (mode == 6)
    {
        while( (VADC_G4_RES2.U & (0x1 << VF_BIT_LSB_IDX)) == 0 );   // wait until read available
        *result = VADC_G4_RES2.U & (0xFFF << RESULT_BIT_LSB_IDX);    // read ADC value
    }

    else if (mode == 7)
    {
        while( (VADC_G4_RES1.U & (0x1 << VF_BIT_LSB_IDX)) == 0 );   // wait until read available
        *result = VADC_G4_RES1.U & (0xFFF << RESULT_BIT_LSB_IDX);    // read ADC value
    }
    // return result;
}