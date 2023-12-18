// Example and Testprogram  Touch Function
// See Installation Manual
// K.R. Riemschneider v.04  2023
// Git test 2 ADC Modul
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/adc.h"
#include "src/headers/ADC.h"
#include "src/headers/curve.h"
#include "src/headers/display.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include <stdbool.h>
#include "src/headers/cursor.h"
#include "src/headers/globalVariables.h"
#include "src/headers/font.h"


void setupAll(void){
    // Setup clock
    // Set Clock with PLL to run from external crystal with 120MHz
    SysCtlClockFreqSet((SYSCTL_OSC_MAIN  |
                        SYSCTL_USE_PLL   |
                        SYSCTL_XTAL_25MHZ |
                        SYSCTL_CFG_VCO_480),120000000);


    // Old code
    //-----------------------
    init_ports_display(); // Init Port L for Display Control and Port M for Display Data
    initDisplay();
    drawAxes();
    initTriggerAxis();
    initTimebaseAxis();
    //------------
    // Setups all underlying Modules
    setupCursor();
    // Enable Interrupts
    IntMasterEnable();
}
int main(void)
{
    // Setup all underlying Modules
    setupAll();

    // Start endless loop
     while(1)
     {

         // Randomly set cursors values
         drawMilliVolt(rand(),xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK);
         drawMilliVolt(rand(),xStartVol1,yStartCHfirstLine,GREEN,BLACK);
         drawMilliVolt(rand(),xStartVol2,yStartCHfirstLine,RED,BLACK);
         drawMilliSeconds(rand(),xStartValTime,yStartCHfirstLine, WHITE, BLACK);
         drawMilliVolt(rand(),xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK);
         drawMilliVolt(rand(),xStartVol1,yStartCHsecondLine,GREEN,BLACK);
         drawMilliVolt(rand(),xStartVol2,yStartCHsecondLine,RED,BLACK);


     }
}

