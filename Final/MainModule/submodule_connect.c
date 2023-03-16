/*
    File Name   : submodule_connect.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxGtm_reg.h"

#include "submodule.h"

/*
    Function Name   : initConnect
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : set Connect (P00.2, P00.3)
*/

void initConnect(void)
{
    P00_IOCR0.U &= ~(0x1F << PC3_BIT_LSB_IDX);
    P00_IOCR0.U |= (0x10 << PC3_BIT_LSB_IDX);

    P00_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX);
    P00_IOCR0.U |= (0x10 << PC2_BIT_LSB_IDX);

    P00_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P00_IOCR0.U |= (0x10 << PC1_BIT_LSB_IDX);

    P00_IOCR0.U &= ~(0x1F << PC0_BIT_LSB_IDX);
    P00_IOCR0.U |= (0x10 << PC0_BIT_LSB_IDX);

    P00_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX);
    P00_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX);
    P00_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX);
    P00_OUT.U &= ~(0x1 << P0_BIT_LSB_IDX);
}

/*
    Function Name   : decideTX
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : decide TX(+, -)
*/

void decideSpeedMode(unsigned int* adcResult, int* tgtMode) 
{
    if(*adcResult > 3072) 
    {
        *tgtMode = 3;
    }
    else if(*adcResult > 2048)
    {
        *tgtMode = 2;
    }
    else if(*adcResult > 1024)
    {
        *tgtMode = 1;
    }
    else
    {
        *tgtMode = 0;
    }

    sendTX(tgtMode, MANUAL_MODE, 0);

}

/*
    Function Name   : setTX
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : send TX (void)
*/

void sendTX(int* tgtMode, int MODE, int* smartAcc)
{
    // Manual Mode => RGB LED (WHITE)
    if(!MODE)
    {
        P00_OUT.U &=  ~(0x1 << P0_BIT_LSB_IDX); // P00.0 OFF

        switch (*tgtMode)
        {
        case 0:
            // send mode 0
            P00_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX); // P00.1 OFF
            P00_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX); // P00.2 OFF
            P00_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // P00.3 OFF
            break;
        case 1:
            // send mode 1
            P00_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX); // P00.1 OFF
            P00_OUT.U |=  (0x1 << P2_BIT_LSB_IDX); // P00.2 ON
            P00_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // P00.3 OFF
            break;
        case 2:
            // send mode 2
            P00_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX); // P00.1 OFF
            P00_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX); // P00.2 OFF
            P00_OUT.U |=  (0x1 << P3_BIT_LSB_IDX); // P00.3 ON
            break;
        case 3:
            // send mode 3
            P00_OUT.U |=  (0x1 << P1_BIT_LSB_IDX); // P00.1 ON
            P00_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX); // P00.2 OFF
            P00_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // P00.3 OFF
            break;
        default:
            break;
        }
    }
    // Smart Mode => RGB LED (GREEN)
    else
    {
        P00_OUT.U |=  (0x1 << P0_BIT_LSB_IDX); // P00.0 ON

        switch (*smartAcc)
        {
        case 0:
            // None
            P00_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX); // P00.1 OFF
            P00_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX); // P00.2 OFF
            P00_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // P00.3 OFF
            break;
        case 1:
            // Accelerate
            P00_OUT.U |=  (0x1 << P1_BIT_LSB_IDX); // P00.1 ON
            P00_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX); // P00.2 OFF
            P00_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // P00.3 OFF
            break;
        case 2:
            // Decelerate
            P00_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX); // P00.1 OFF
            P00_OUT.U |=  (0x1 << P2_BIT_LSB_IDX); // P00.2 ON
            P00_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // P00.3 OFF
            break;
        default:
            break;
        }
    }

    
}

