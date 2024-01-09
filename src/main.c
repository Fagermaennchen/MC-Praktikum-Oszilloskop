// Example and Testprogram  Touch Function
// See Installation Manual
// K.R. Riemschneider v.04  2023
// Git test 2 ADC Modul

#include "headers/globalVariables.h"
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>      // GPIO_PORTX_BASE
#include <src/headers/ADC.h>
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "headers/cursor.h"
#include "headers/curve.h"
#include "headers/display.h"
#include "headers/font.h"
#include "headers/slider.h"
#include "headers/touch.h"

/********************************************************************************
         Setup System and Interrupt-Modules and draw initial Layout
*********************************************************************************/
void setupAll(void){
    // Setup clock: PLL to run from external crystal with 120MHz
    SysCtlClockFreqSet((SYSCTL_OSC_MAIN  |
                        SYSCTL_USE_PLL   |
                        SYSCTL_XTAL_25MHZ |
                        SYSCTL_CFG_VCO_480),120000000);

    initDisplay();          // Initialize Display Ports, configure for 800x480 pixel, set Background
    drawAxes();             // Draw X- and Y-Axis
    drawLogo();             // Draw HAW logo with font
    initTriggerSlider();      // Draw Trigger-Axis for touch
    initTimebaseSlider();     // Draw Timebase-Axis for touch
    initTouch();            // Initialize Pins on Port D for Touch

    // Setups all underlying Modules
    setupADC_routine();                 // Setup ADC module
    setupCursor_routine();              // Setup Cursor module
    setupDrawVoltageCurve_routine();    // Setup drawVoltageCurve module
    setupProcessTouch_routine();        // Setup processTouch module

}

void startAll(void){
    startADC();                             // Start ADC
    TimerEnable(TIMER0_BASE,TIMER_A);       // Start Timer for ADC-Interrupt (Prio 0)
    TimerEnable(TIMER1_BASE,TIMER_A);       // Start Timer for Cursor-Interrupt (Prio 1)
    TimerEnable(TIMER2_BASE, TIMER_A);      // Start Timer for drawVoltageCurve-Interrupt (Prio 1)
    TimerEnable(TIMER3_BASE, TIMER_A);      // Start Timer for Touch-Interrupt (Prio 1)
    IntMasterEnable();                      // Enable all Interrupts
}

int main(void){

    setupAll();         // Setup all underlying Modules
    startAll();         // Start all underlying Modules

     while(1)
     {

     }
}

