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
    Function Name   : initGTM
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Set GTM
*/
void initGTM(void)
{
    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);    // wait until unlocked

    // Modify Access to clear ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);    // wait until locked

    GTM_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);    // enable GTM

    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);    // wait until unlocked

    // Modify Access to set ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    while((GTM_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0); // wait until GTM module enabled


    // GTM clock configuration
    GTM_CMU_FXCLK_CTRL.U &= ~(0xF << FXCLK_SEL_BIT_LSB_IDX);        // input clock of CMU_FXCLK --> CMU_GCLK_EN
    GTM_CMU_CLK_EN.U |= 0x2 << EN_FXCLK_BIT_LSB_IDX;                // enable all CMU_FXCLK


    // GTM TOM0 PWM configuration

    // P10.2 => TOUT104, TOMO_2, TOM0, Channel 2
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x2 << UPEN_CTRL2_BIT_LSB_IDX;      // TOM channel 2 update enable

    GTM_TOM0_TGC0_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL2_BIT_LSB_IDX;   // enable channel 2 on update trigger

    GTM_TOM0_TGC0_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL2_BIT_LSB_IDX;   // enable channel 2 output on update trigger

    GTM_TOM0_CH2_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;                   // high signal level for duty cycle
    GTM_TOM0_CH2_CTRL.U |= 0x1 << CLK_SRC_SR_BIT_LSB_IDX;           // clock source --> CMU_FXCLK(1) = 6250 kHz
    GTM_TOM0_CH2_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);               // continuous mode enable
    GTM_TOM0_CH2_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX);           // TRIG[x] = TRIG[x-1]

    GTM_TOM0_CH2_SR0.U = 12500 - 1;                                 // PWM freq. = 6250 kHz / 12500 = 500 Hz

    GTM_TOM0_CH2_SR1.U = 1250 - 1;                                  // duty cycle = 1250 / 12500 = 10 % (temporary)

    GTM_TOUTSEL6.U &= ~(0x3 << SEL8_BIT_LSB_IDX);                   // TOUT104 => TOUTSEL6 => SEL8 bits
                                                                    // 104 = 16 * 6 + 8

    // set GTM TOM0 channel 11 - Buzzer
    GTM_TOM0_TGC1_GLB_CTRL.B.UPEN_CTRL3     |= 0x2;                   // TOM0 channel 11 enable
    GTM_TOM0_TGC1_ENDIS_CTRL.B.ENDIS_CTRL3  |= 0x2;                   // enable channel 11 on update trigger
    GTM_TOM0_TGC1_OUTEN_CTRL.B.OUTEN_CTRL3  |= 0x2;                   // enable channel 11 output on update trigger

    // TOM 0_11
    GTM_TOM0_CH11_CTRL.B.SL = 0x1;                                  // high signal level for duty cycle
    GTM_TOM0_CH11_CTRL.B.CLK_SRC_SR = 0x1;                          // clock source --> CMU_FXCLK(1) = 6250 kHz
    GTM_TOM0_CH11_SR0.B.SR0 = 12500 - 1;                            // PWM freq. = 6250 kHz / 12500 = 500 Hz
    GTM_TOM0_CH11_SR1.B.SR1 = 6250 - 1;                             // duty cycle = 6250 / 12500 = 50 %

    GTM_TOM0_CH11_SR0.B.SR0 = 0;
    GTM_TOM0_CH11_SR1.B.SR1 = 0;

    // TOUT pin selection
    GTM_TOUTSEL0.B.SEL3 = 0x0;                                      // TOUT3  --> TOM0 channel 11
}