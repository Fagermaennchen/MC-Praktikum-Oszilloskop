// Example and Testprogram  Touch Function
// See Installation Manual
// K.R. Riemschneider v.04  2023
// Git test 2 ADC Modul
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/adc.h"
#include <src/ADC/ADCModul.h>
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include <stdbool.h>


void setupAll(void){
    // Setup clock
    // Set Clock with PLL to run from external crystal with 120MHz
    SysCtlClockFreqSet((SYSCTL_OSC_MAIN  |
                        SYSCTL_USE_PLL   |
                        SYSCTL_XTAL_25MHZ |
                        SYSCTL_CFG_VCO_480),120000000);
    // Setups all underlying Modules
    setupADC();
    // Enable Interrupts
    IntMasterEnable();
}
int main456(void)
{
    // Setup all underlying Modules
    setupAll();
    // Start all underlying Modules
    startADC();
    // Non Busy waiting for Interrupt Based program
    while(1){

    }
}
