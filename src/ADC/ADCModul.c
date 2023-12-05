/*
 * ADC.c
 *
 *  Created on: 02.12.2023
 *      Author: sfage
 */
#include <src/ADC/ADCModul.h>
#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
#include "src/globalVariables.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/adc.c"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "ADCModul.h"


int loadValue = 120000000;

void readADCvalue_routine(void){ // Service Routine to get the ADC Values
    ADCIntClear(ADC0_BASE, 0); // clear the interrupt
    // Get Results
    int resultCH1, resultCH2;
    resultCH1 = (unsigned long) ADC0_SSFIFO0_R; // Take result out of FIFO for Channel 1
    resultCH2 = (unsigned long) ADC0_SSFIFO0_R; // Take result out of FIFO for Channel 2
    // Triggering at Channel 1: Check for
    if( resultCH1 > -10 || resultCH1 < 10){      // Value near Zero reached

    }
    resultsCH1[arrayPosition] =  convertADCtoVolt(resultCH1);
    resultsCH2[arrayPosition] =  convertADCtoVolt(resultCH2);
    // Array full: Start Again
    if (arrayPosition == arrayLen){
        arrayPosition = 0;          // Reset Array Position
        triggerZeroReached = False;        // Reset Trigger Status
    }
    // Print result
    printf("CH1: %d, CH2 %d \n",resultsCH1[arrayPosition],resultsCH2[arrayPosition]);
    arrayPosition++;
}

int convertADCtoVolt(int adcVal){ // Conversion Values determined by Measurement with Hameg HM 412-5 Oszilloskope
   int voltage = adcVal*1000000 / (2*1323125);  // Convert Byte Value into Voltage X,XXX [V]
   return voltage;
}

void setupADC(void){    // Setup the timer triggered ADC
    int wt = 0; // Variable for very short wait times
    // Set Clock with PLL to run from external crystal with 120MHz
    SysCtlClockFreqSet((SYSCTL_OSC_MAIN  |
                        SYSCTL_USE_PLL   |
                        SYSCTL_XTAL_25MHZ |
                        SYSCTL_CFG_VCO_480),120000000);
    // Port and ADC Clock Gating Control
    // Clock switch on AIN of ADC0 ... Pin is PE0
    SYSCTL_RCGCGPIO_R |= 0x00000018; // Clock Port E + D enable
    SYSCTL_RCGCADC_R |= 0x1;
    wt++; // Clock ADC0 enable set

    // Configure the Timer 0 to Trigger the ADC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);  // Enable the Timer0 peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {} // Wait for the Timer0 module to be ready
    TimerConfigure(TIMER0_BASE, (TIMER_CFG_A_PERIODIC )); // Timer 0 in periodic mode
    TimerLoadSet(TIMER0_BASE,TIMER_A,loadValue);  // 1 Second Intervall
    TimerControlTrigger(TIMER0_BASE,TIMER_A,true); // Activate Timer ADC control Trigger

    // Start the ADC Clocking
    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR; // power on the PLL
    while (!(SYSCTL_PLLSTAT_R & SYSCTL_PLLSTAT_LOCK)); // wait till PLL has locked
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 24);  // Use the external OSC at 20MHz
    wt++;

    // Configure ADC for Ports PE2+PE3
    GPIO_PORTE_AHB_AFSEL_R |= 0x14; //PE2+PE3 alternative function select
    GPIO_PORTE_AHB_AMSEL_R |= 0x14; //PE2+PE3 analog function selecttitle
    GPIO_PORTE_AHB_DEN_R &= ~0x14; // PE2+PE3 digital pin function DISABLE
    GPIO_PORTE_AHB_DIR_R &= ~0x14; // Allow input PE2+PE3 (AIN0+AIN1)

    // ADC init
    ADC0_ACTSS_R &= 0xF0; // all sequencers off
    ADC0_SSMUX0_R |= 0x00000001; // Sequencer 0 channel AIN1 (PE3) and AIN0 (PE2)
    ADC0_SSCTL0_R |= 0x00000020; // Sequencer END1 set sequence Length= 2
    ADC0_CTL_R = 0x10; // 3,3 V external V_ref
    ADC0_SAC_R = 0x3; // Averaging over 8 samples in HW
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_TIMER, 0); // will use ADC0, SS3, processor-trigger, priority 0

    // Register and enable ADC Interrupt
    ADCIntRegister(ADC0_BASE,0,readADCvalue_routine);
    ADCIntEnable(ADC0_BASE,0);
    ADCIntClear(ADC0_BASE, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH1 | ADC_CTL_IE |
                             ADC_CTL_END);

    // Enable ADC interrupts
    ADCIntEnableEx(ADC0_BASE, ADC_INT_SS0);

}
void startADC(){    // Starts the timer triggered ADC
    // Start Sample Sequencer 0
    ADC0_ACTSS_R &= 0xF0; // all sequencers off
    printf("Measurement block starts now\n");
    ADCSequenceEnable(ADC0_BASE, 0);
    // Start Timer 0
    TimerEnable(TIMER0_BASE,TIMER_A);

}
void changeTimeBase(int newTimeBase){   // Changes the Timebase (input: newTimeBase [us])
    loadValue = newTimeBase*120000;     // Convert us to Sysclock Steps (for 120MHz)
}


