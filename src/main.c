// Example and Testprogram  Touch Function
// See Installation Manual
// K.R. Riemschneider v.04  2023
// Git test 2 ADC Modul
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/adc.h"
#include "headers/ADC.h"
#include "headers/curve.h"
#include "headers/display.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include <stdbool.h>
#include "headers/cursor.h"
#include "headers/globalVariables.h"
#include "headers/font.h"


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
    drawLogo();
    initTriggerAxis();
    initTimebaseAxis();
    SYSCTL_RCGCGPIO_R = 0x0008; //Enable clock Port D
    init_ports_display(); // Init Port L for Display Control and Port M for Display Data
    while ((SYSCTL_PRGPIO_R & 0x08) == 0);  //GPIO Clock ready?
    GPIO_PORTD_AHB_DEN_R = 0x1F;            //PortD digital enable
    GPIO_PORTD_AHB_DIR_R = 0x0D;            //PortD Input/Output
    GPIO_PORTD_AHB_DATA_R &= 0xF7;          //Clk=0
    //------------
    // Setups all underlying Modules
    setupADC();
    setupCursor();
    // Enable Interrupts
    IntMasterEnable();
}
int main(void){

    // Setup all underlying Modules
    setupAll();
    // Start all underlying Modules
    startADC();
    // Start endless loop
    int j,k;
    for(j = 0; j<arrayLen;j++){
        oldVoltageCH1[j]=0;
        oldVoltageCH2[j]=0;
    }
    k=0;
     while(1)
     {

        updateCursorValues();
        readTouchValues();
        drawVoltageCurve();
     }
}

