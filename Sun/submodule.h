/*
    File Name   : Cpu_Main.h
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#ifndef CPU_MAIN_H_
#define CPU_MAIN_H_
// Port registers
// Port registers
#define PC1_BIT_LSB_IDX         11
#define PC2_BIT_LSB_IDX         19
#define PC3_BIT_LSB_IDX         27
#define PC5_BIT_LSB_IDX         11
#define PC7_BIT_LSB_IDX         27
#define P1_BIT_LSB_IDX          1
#define P2_BIT_LSB_IDX          2
#define P3_BIT_LSB_IDX          3
#define P5_BIT_LSB_IDX          5
#define P7_BIT_LSB_IDX          7

// SCU registers
#define LCK_BIT_LSB_IDX         1
#define ENDINIT_BIT_LSB_IDX     0
#define EXIS0_BIT_LSB_IDX       4
#define FEN0_BIT_LSB_IDX        8
#define EIEN0_BIT_LSB_IDX       11
#define INP0_BIT_LSB_IDX        12
#define IGP0_BIT_LSB_IDX        14

// SRC registers
#define SRPN_BIT_LSB_IDX        0
#define TOS_BIT_LSB_IDX         11
#define SRE_BIT_LSB_IDX         10

// CCU60 registers
#define DISS_BIT_LSB_IDX        1
#define DISR_BIT_LSB_IDX        0
#define CTM_BIT_LSB_IDX         7
#define T12PRE_BIT_LSB_IDX      3
#define T12CLK_BIT_LSB_IDX      0
#define T12STR_BIT_LSB_IDX      6
#define T12RS_BIT_LSB_IDX       1
#define INPT12_BIT_LSB_IDX      10
#define ENT12PM_BIT_LSB_IDX     7

// VADC registers
#define DISS_BIT_LSB_IDX        1
#define DISR_BIT_LSB_IDX        0
#define ANONC_BIT_LSB_IDX       0
#define ASEN0_BIT_LSB_IDX       24
#define CSM0_BIT_LSB_IDX        3
#define PRIO0_BIT_LSB_IDX       0
#define CMS_BIT_LSB_IDX         8
#define FLUSH_BIT_LSB_IDX       10
#define TREV_BIT_LSB_IDX        9
#define ENGT_BIT_LSB_IDX        0
#define RESPOS_BIT_LSB_IDX      21
#define RESREG_BIT_LSB_IDX      16
#define ICLSEL_BIT_LSB_IDX      0
#define VF_BIT_LSB_IDX          31
#define RESULT_BIT_LSB_IDX      0
#define ASSCH7_BIT_LSB_IDX      7

// GTM registers
#define DISS_BIT_LSB_IDX            1
#define DISR_BIT_LSB_IDX            0
#define SEL7_BIT_LSB_IDX            14
#define SEL8_BIT_LSB_IDX            16
#define EN_FXCLK_BIT_LSB_IDX        22
#define FXCLK_SEL_BIT_LSB_IDX       0

// GTM - TOM0 registers
#define HOST_TRIG_BIT_LSB_IDX       0

#define UPEN_CTRL1_BIT_LSB_IDX      18
#define UPEN_CTRL2_BIT_LSB_IDX      20

#define ENDIS_CTRL1_BIT_LSB_IDX     2
#define ENDIS_CTRL2_BIT_LSB_IDX     4

#define OUTEN_CTRL1_BIT_LSB_IDX     2
#define OUTEN_CTRL2_BIT_LSB_IDX     4

#define CLK_SRC_SR_BIT_LSB_IDX      12
#define OSM_BIT_LSB_IDX             26
#define TRIGOUT_BIT_LSB_IDX         24
#define SL_BIT_LSB_IDX              11

void initLED(void);
void initPWMLED(void);
void initButton(void);
void initERU(void);
void initCCU60(void);
void initRGBLED(void);
void initVADC(void);
void VADC_startConversion(void);
void VADC_readResult(unsigned int*);
void initGTM(void);

#endif 
