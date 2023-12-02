/*
 * ADC.c
 *
 *  Created on: 02.12.2023
 *      Author: sfage
 */#include <src/ADC/ADCModul.h>
#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/adc.c"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "ADCModul.h"
#include "src/globalVariables.c"

void readADCvalue_routine(void){
     // Service Routine to get the ADC Values
    ADCIntClear(ADC0_BASE, 0); // clear the interrupt
    int resultCH1, resultCH2;
    resultCH1 = (unsigned long) ADC0_SSFIFO0_R; // Take result out of FIFO for Channel 1
    resultCH2 = (unsigned long) ADC0_SSFIFO0_R; // Take result out of FIFO for Channel 2
    resultsCH1[arrayPosition] = convertADCtoVolt(resultCH1);
    resultsCH2[arrayPosition] = convertADCtoVolt(resultCH2);
    arrayPosition++;
    // Resest Array Position if at end
    if (arrayPosition == arrayLen){
        arrayPosition = 0;
    }
}

int convertADCtoVolt(int adcVal){
    // Conversion Values determined by Measurement with Hameg HM 412-5 Oszilloskope
   int voltage = adcVal*1000000 / (2*1323125);  // Convert Byte Value into Voltage X,XXX [V]
   return voltage;
}


