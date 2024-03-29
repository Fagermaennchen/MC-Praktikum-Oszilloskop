/*
 * ADC.c
 *
 *  Created on: 02.12.2023
 *      Author: sfage
 */
#include "headers/globalVariables.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/adc.c"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "headers/ADC.h"
#include "headers/cursor.h"


// Value declaration only for ADC Service Routine
int resultCH1, resultCH2,k,prevAvg,currentAvg;


/*********************************************************************************
                                ADC Initialization
*********************************************************************************/
void setupADC_routine(void){    // Setup the timer triggered ADC
    int wt = 0; // Variable for very short wait times
    // Port and ADC Clock Gating Control
    // Clock switch on AIN of ADC0 ... Pin is PE0

    SYSCTL_RCGCGPIO_R |= 0x00000018;    // Clock Port E + D enable
    SYSCTL_RCGCADC_R |= 0x1;            // Clock ADC0 enable
    wt++;                               // short wait after enable

    // Configure the Timer 0 to Trigger the ADC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);           // Enable the Timer0 peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}  // Wait for the Timer0 module to be ready
    TimerConfigure(TIMER0_BASE, (TIMER_CFG_A_PERIODIC ));   // Timer 0 in periodic mode
    //printf("load vlaue %d",loadValue);
    TimerLoadSet(TIMER0_BASE,TIMER_A,ADCloadValue);        // 1 Second Intervall
    TimerControlTrigger(TIMER0_BASE,TIMER_A,true);      // Activate Timer ADC control Trigger

    // Start the ADC Clocking
    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR;            // power on the PLL
    while (!(SYSCTL_PLLSTAT_R & SYSCTL_PLLSTAT_LOCK));      // wait till PLL has locked
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 4);  // Use the external OSC at 120MHz
    wt++;

    // Configure ADC for Ports PE2+PE3  (PE2: Vsin, PE3: Vcos)
    GPIO_PORTE_AHB_AFSEL_R |= 0x14; //PE2+PE3 alternative function select
    GPIO_PORTE_AHB_AMSEL_R |= 0x14; //PE2+PE3 analog function selecttitle
    GPIO_PORTE_AHB_DEN_R &= ~0x14; // PE2+PE3 digital pin function DISABLE
    GPIO_PORTE_AHB_DIR_R &= ~0x14; // Allow input PE2+PE3 (AIN0+AIN1)

    // ADC init
    ADC0_ACTSS_R &= 0xF0; // all sequencers off
    ADC0_CTL_R = 0x10; // 3,3 V external V_ref
    ADC0_SAC_R = 0x3; // Averaging over 8 samples in HW
    ADC0_SSMUX0_R = 0x00000000; // Sequencer 3 channel AIN1 (PE3) and AIN0 (PE2)
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_TIMER, 0); // will use ADC0, SS0, processor-trigger, priority 0
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH0 | ADC_CTL_IE |
                             ADC_CTL_END);
    // Register and enable ADC Interrupt
    ADCIntRegister(ADC0_BASE,0,readADCvalue_routine);
    ADCIntEnable(ADC0_BASE,0);
    ADCIntClear(ADC0_BASE, 0);
    IntPrioritySet(INT_TIMER0A_TM4C123,ADCprio);   // Priority to 0
    printf("ADC prio: %d \n",IntPriorityGet(INT_TIMER0A_TM4C123));

    // Enable ADC interrupts
    ADCIntEnableEx(ADC0_BASE, ADC_INT_SS0);

}
/********************************************************************************/
void startADC(){    	        // Starts the timer triggered ADC
    // Start Sample Sequencer 0
    ADC0_ACTSS_R &= 0xF0; // all sequencers off
    ADCSequenceEnable(ADC0_BASE, 0);
}
/********************************************************************************/



/*********************************************************************************
                              ADC Operating Functions
*********************************************************************************/

void readADCvalue_routine(void)     	// Service Routine to get the ADC Values
{

    ADCIntClear(ADC0_BASE, 0); // clear the interrupt
    // Get Results
    resultCH1 = (unsigned long) ADC0_SSFIFO0_R; // Take result out of FIFO for Channel 1
    resultCH2 = (unsigned long) ADC0_SSFIFO0_R; // Take result out of FIFO for Channel 2
    // Save Data to Array if Triggered
    if(triggered)
    {
        resultsCH1[arrayPosition] =  resultCH1;
        resultsCH2[arrayPosition] =  resultCH2;
        // Array full: Start Again
        if (arrayPosition == arrayLen)
        {
            arrayPosition = -1;          // Reset Array Position
            triggerZeroReached = false;  // Reset Trigger Status
            triggered = false;
            prevValueCH1 = 9999;
            prev2ValueCH1 = 9999;
            prev3ValueCH1 = 9999;
            prev4ValueCH1 = 9999;
            prev5ValueCH1 = 9999;
            prev6ValueCH1 = 9999;
            prev7ValueCH1 = 9999;
            prev8ValueCH1 = 9999;
            prev9ValueCH1 = 9999;
        }
        arrayPosition++;
    }

    else
    {
        // Filter previous values for noise
        prevAvg = (prev5ValueCH1+prev6ValueCH1+prev7ValueCH1+prev8ValueCH1+prev9ValueCH1) / 5;
        currentAvg = (resultCH1 + prevValueCH1+prev2ValueCH1+prev3ValueCH1+prev4ValueCH1) / 5;
        // Triggering at Channel 1: Check for Zero Value
        if(triggerValue > triggerZeroValue )            // Cross Zero on positive slop for trigger > 0
        {
            if( prevAvg < triggerZeroValue  && currentAvg > triggerZeroValue){  // Zero Value has been crossed on positive slope
                triggerZeroReached = true;
            }
        }   // Cross Zero on positive slop for trigger < 0
        else{
            if( prevAvg > triggerZeroValue && currentAvg < triggerZeroValue     // Zero Value has been crossed on positive slope
               && prevValueCH1 < triggerZeroValue && prev2ValueCH1 < triggerZeroValue){
                     triggerZeroReached = true;
            }
        }

        // Triggering at Channel 2: Check if Trigger is crosses
        if( triggerZeroReached && ((prevAvg < triggerValue && currentAvg > triggerValue))) //Trigger crossed on positive slope
        {
            triggered = true;       // Remeber Trigger
            noTrigCounter = 0;   // Reset no Trigger Counter
        }

        // Detect not Triggerable signal (AC Coupling)
        if(noTrigCounter == 10000){
            // Set DC Signal to near 0 Axis, but not overlapping
            for(k=0;k<arrayLen;k++){
                resultsCH1[k] = triggerZeroValue+40;
                resultsCH2[k] = triggerZeroValue+20;
            }
        }

        // Save Current Values for next Trigger Check
        prev9ValueCH1 = prev8ValueCH1;
        prev8ValueCH1 = prev7ValueCH1;
        prev7ValueCH1 = prev6ValueCH1;
        prev6ValueCH1 = prev5ValueCH1;
        prev5ValueCH1 = prev4ValueCH1;
        prev4ValueCH1 = prev3ValueCH1;
        prev3ValueCH1 = prev2ValueCH1;
        prev2ValueCH1 = prevValueCH1;
        prevValueCH1 = resultCH1;

        // Increment no Trigger Counter
        noTrigCounter++;
    }

}
/********************************************************************************/
int convertADCtoVolt(int adcVal) 	    // Conversion Values determined by Measurement with Hameg HM 412-5 Oszilloskope
{
    int voltage = (adcVal-triggerZeroValue)*8;
    return voltage;
}
/********************************************************************************/
