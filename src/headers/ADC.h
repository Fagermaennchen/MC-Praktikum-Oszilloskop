/*
 * ADC.h
 *
 *  Created on: 02.12.2023
 *      Author: sfage
 */

// Headers
void readADCvalue_routine(void); //Routine to read adc value from FIFO
void setupADC(void);    // Setup the timer triggered ADC
void startADC(void);    // Starts the timer triggered ADC
int convertADCtoVolt(int adcVal); // Converts ADC Value into Voltage [mV]   #TODO: In Cursormodul einbauen

