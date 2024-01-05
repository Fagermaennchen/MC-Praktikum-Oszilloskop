/*
 * ADC.h
 *
 *  Created on: 02.12.2023
 *      Author: sfage
 */

// ADC-Header

void setupADC_routine(void);                // Setup the timer triggered ADC
void startADC(void);                        // Starts the timer triggered ADC
void changeADCclock(int timeSliderPos);     // Change ADC clock with timebase slider
void readADCvalue_routine(void);            // Routine to read adc value from FIFO
int convertADCtoVolt(int adcVal);           // Converts ADC Value into Voltage [mV]

