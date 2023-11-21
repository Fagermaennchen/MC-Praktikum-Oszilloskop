/*
 * testADCPOC.c
 *
 *  Created on: 21.11.2023
 *      Author: sfage
 */
// TESTCODE aus Vorlesung
// Two Channel ADC selftriggered, continuously running, FIFO empty, full and overfull
// Try different behavior by uncommenting a single ADC0_SAC_R value, line 41ff.
// For experimental test set PE0 to GND and PE1 to Vdd
#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/adc.h"
#include "driverlib/adc.c"
#include "driverlib/interrupt.h"
#define MAXARRAY 20 // Block length of sampling

int cnter = 0;
int result;

void readADCvalue_routine(void); //Routine to read adc value from FIFO

void readADCvalue_routine(void){
    result = (unsigned long) ADC0_SSFIFO0_R; // Take result out of FIFO
    printf("Result: %d ",result);
    printf("Counter: %d \n",cnter);
    cnter++;
}

void main(void)
{
    int i, j, k, wt = 0; // Loop counter variables, aux. variable for waiting
    int result1[MAXARRAY], result2[MAXARRAY]; // ADC results 2 channels


    // Port and ADC Clock Gating Control
    // Clock switch on AIN of ADC0 ... Pin is PE0
    SYSCTL_RCGCGPIO_R |= 0x00000018; // Clock Port E + D enable
    SYSCTL_RCGCADC_R |= 0x1;
    wt++; // Clock ADC0 enable set

    // Start the ADC Clocking
    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR; // power on the PLL
    while (!(SYSCTL_PLLSTAT_R & SYSCTL_PLLSTAT_LOCK)); // wait till PLL has locked
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 24);  // Use the external OSC at 20MHz
    wt++;


    GPIO_PORTE_AHB_AFSEL_R |= 0x14; //PE2+PE3 alternative function select
    GPIO_PORTE_AHB_AMSEL_R |= 0x14; //PE2+PE3 analog function selecttitle
    GPIO_PORTE_AHB_DEN_R &= ~0x14; // PE2+PE3 digital pin function DISABLE
    GPIO_PORTE_AHB_DIR_R &= ~0x14; // Allow input PE2+PE3 (AIN0+AIN1)

    // for timing debug only
    GPIO_PORTD_AHB_DEN_R = 0x14; // PD3 und PD2 digital enable
    GPIO_PORTD_AHB_DIR_R = 0x03; // PD3 und PD2 output direction enable

    // ADC init
    ADC0_ACTSS_R &= 0xF0; // all sequencers off
    ADC0_SSMUX0_R |= 0x00000001; // Sequencer 3 channel AIN1 (PE3) and AIN0 (PE2)
    ADC0_SSCTL0_R |= 0x00000020; // Sequencer END1 set sequence Length= 2
    ADC0_CTL_R = 0x10; // 3,3 V external V_ref
    //ADC0_SAC_R=0x0; // No averaging of samples in HW
    //ADC0_SAC_R=0x1; // Averaging of 2 samples in HW
    //ADC0_SAC_R=0x2; // Averaging over 4 samples in HW
    ADC0_SAC_R = 0x3; // Averaging over 8 samples in HW
    //ADC0_SAC_R=0x4; // Averaging over 16 samples in HW
    //ADC0_SAC_R=0x5; // Averaging over 32 samples in HW
    //ADC0_SAC_R=0x6; // Averaging over 64 samples in HW
    ADC0_EMUX_R |= 0x000F; // continuoulsy sample enable (selftrigger seq. 0)

    // Register and enable ADC Interrupt
    ADCIntRegister(ADC0_BASE,0,readADCvalue_routine);
    ADCIntEnable(ADC0_BASE,0);
    ADCIntClear(ADC0_BASE, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH1 | ADC_CTL_IE |
                             ADC_CTL_END);
    IntMasterEnable();

    // Start Sample Sequencer 0
    ADC0_ACTSS_R &= 0xF0; // all sequencers off
    printf("Measurement block starts now\n");
    //ADC0_ACTSS_R |= 0x01; // sequencer 0 on
    ADCSequenceEnable(ADC0_BASE, 0);
    while (1)
    {

    }
}



