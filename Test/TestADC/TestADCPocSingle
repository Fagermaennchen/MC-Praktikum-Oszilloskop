/*
 * testADCPOC.c
 *
 *  Created on: 21.11.2023
 *      Author: sfage
 */
// TESTCODE aus Vorlesung
// Simple ADC Test Program: One Channel + Single Conversion in a Software Loop
//--------------------------------------------------------------------------------------/
#include <stdint.h>
#include "stdio.h"
#include "inc/tm4c1294ncpdt.h"

#define ADC_VREF 3300.0 // voltage on V_REF+ pin in mV
#define V_LSB (ADC_VREF / 4096) // V_LSB voltage in mV
#define V_COEFF ((4.70 + 9.137) / 9.137 * V_LSB) // Only valid for Board in HAW-Lab
// Resistive voltage divider before AINx
// ADC input impedance here less relevant if very slow input changes => data sheet 1862ff.

int main0324(void)
{
    unsigned int ADCoutput, wt;

    // Clock switch on AIN1 of ADC0 ... Pin is PE(5)
    SYSCTL_RCGCGPIO_R |= 0x00000010; // Clock Port E enable
    SYSCTL_RCGCADC_R |= 0x1;
    wt++; // Clock ADC0 enable set

    // Magic code for start the ADC Clocking
    // => see tm4c1294ncpdt Datasheet, 15.3.2.7 ADC Module Clocking
    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR; // power on the PLL
    while (!(SYSCTL_PLLSTAT_R & SYSCTL_PLLSTAT_LOCK))
        ; // wait till PLL has locked
    ADC0_CC_R = 0x01;
    wt++; // select PIOSC (internal RCOsc) as ADC analog clock
    SYSCTL_PLLFREQ0_R &= ~SYSCTL_PLLFREQ0_PLLPWR; // power off the PLL (s. above)

    // Prepare Port Pin PE2 as AIN1
    GPIO_PORTE_AHB_AFSEL_R |= 0x04; // PE2 Alternative Pin Function enable
    GPIO_PORTE_AHB_AMSEL_R |= 0x04; // PE2 Analog Pin Function enable
    GPIO_PORTE_AHB_DEN_R &= ~0x04; // PE2 Digital Pin Function DISABLE
    GPIO_PORTE_AHB_DIR_R &= ~0x04; // Allow Input PE2

    ADC0_ACTSS_R &= ~0x0F; // Disable all 4 sequencers of ADC 0
    ADC0_SSMUX0_R |= 0x00000001; // Sequencer SS0 channel AIN1 without multiplexing
    ADC0_SSCTL0_R |= 0x00000002; // Set "END=0" sequence length 1 (one sample sequence)
    ADC0_CTL_R &= ~0x01; // Use Vdda 3.3V as V_REF .. if Bit0 is clear
    ADC0_ACTSS_R |= 0x01; // Enable sequencer SS0 with ADC 0

    while (1) // Start Conversion in an endless Loop
    {
        ADC0_PSSI_R |= 0x01; // Start ADC0
        while (ADC0_SSFSTAT0_R & 0x000000100)
            ; // wait for FIFO (inverted) Flag "EMPTY = False"
        ADCoutput = (unsigned long) ADC0_SSFIFO0_R; // Take avalue from FIFO output
        // Calculate Output in mV with respect to voltage divider 5:3 in the Lab
        printf("0x%3x=%4d (dec) ==> %04d [mV] \n", ADCoutput, ADCoutput,
               (int) (ADCoutput *
               V_COEFF + 0.5));
    }
}
