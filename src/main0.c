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



void setupAll(void){
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
