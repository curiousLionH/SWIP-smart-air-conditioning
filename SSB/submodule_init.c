/*
    File Name   : submodule_init.c
    Author      : SWIP 1th - Team 1
    Date        : 2023.03.15
*/

#include "submodule.h"

/*
    Function Name   : initSensors
    Author          : SWIP 1th - Team 1
    Date            : 2023.03.15
    input           : void
    output          : void
    Description     : Initialize all sensors
*/
void initSensors(void)
{
    initERU();
    //initCCU60();
    initLED();
    initRGBLED();
    initVADC();
    initGTM();
    initButton();
    initBuzzer();
    initMotor();
}
