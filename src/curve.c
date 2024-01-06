#include "headers/globalVariables.h"
#include <stdbool.h>
#include <stdint.h>
//#include <stdio.h>   // Debug only
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>      // GPIO_PORTX_BASE
#include "headers/curve.h"
#include "headers/cursor.h"
#include "headers/display.h"
#include "headers/font.h"



/*********************************************************************************
                               Cursor Initialization
*********************************************************************************/
void setupDrawVoltageCurve_routine(void){

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);               // Enable Timer 2 periphal
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2)) {}     // Wait for Timer 2 module to be ready
    TimerConfigure(TIMER2_BASE, TIMER_CFG_A_PERIODIC);          // Configure Timer 2 in periodic mode
    TimerLoadSet(TIMER2_BASE, TIMER_A, loadValueDrawVoltage);   // Set the load value for Timer 2
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);            // Enable Timer 2A timeout interrupt
    TimerIntRegister(TIMER2_BASE, TIMER_A, drawVoltageCurve);
    IntPrioritySet(INT_TIMER2A, CURVEprio); // Adjust priority as needed
    // Set old voltage to 0 axis for start
    int i;
    for(i = 0; i<arrayLen;i++){
        oldVoltageCH1[i] = 360 - ((triggerZeroValue-535)*0.095);
        oldVoltageCH2[i] = 360 - ((triggerZeroValue-535)*0.095);
    }
}
/********************************************************************************/



/*********************************************************************************
                            Cursor Operating Functions
*********************************************************************************/
void drawVoltageCurve(void){
    int i;                                          // Array iterator
    int VoltageY, nextVoltageY;                 // variable for receiving voltage from ADC array
    double VoltagePixel;                            // calculated pixel (decimal) from voltage
    int VoltagePixelIntCH1,VoltagePixelIntCH2;      // precise INT pixel from decimal pixel
    int nextVoltagePixelIntCH1, nextVoltagePixelIntCH2;

    // Voltage reference: 0-3,5V

    // calculate pixel from received voltage CH1
    VoltageY = resultsCH1[0];                           // Get voltage from ADC CH1
    VoltagePixel = 360 - ((VoltageY-535)*0.095);        // Calculate pixel position for CH1
    VoltagePixelIntCH1 = (int) VoltagePixel;            // cast double value to int for pixel position

    // calculate pixel from received voltage CH2
    VoltageY = resultsCH2[0];                           // Get voltage from ADC CH2
    VoltagePixel = 360 - ((VoltageY-535)*0.095);        // Calculate pixel position for CH2
    VoltagePixelIntCH2 = (int) VoltagePixel;            // cast double value to int for pixel position



    for(i = 0; i < arrayLen-1; i++){                    // Array iteration to show all pixel in the current timebase, arrayLen-2 to not run out of bounds du to drawLine(i+1)

        // calculate next pixel from received voltage CH1 for drawLine purpose
        nextVoltageY = resultsCH1[i+1];                     // Calculate next value
        VoltagePixel = 360 - ((nextVoltageY-535)*0.095);    // Calculate next pixel position for CH1
        nextVoltagePixelIntCH1 = (int) VoltagePixel;        // cast double value to int for next pixel position

        // calculate next pixel from received voltage CH1 for drawLine purpose
        nextVoltageY = resultsCH2[i+1];                     // Calculate next value
        VoltagePixel = 360 - ((nextVoltageY-535)*0.095);    // Calculate next pixel position for CH1
        nextVoltagePixelIntCH2 = (int) VoltagePixel;        // cast double value to int for next pixel position

        // Draw line if triggered and in bounds and not current value of adc being changed
        if((VoltagePixelIntCH1>=YaxisYbegin) && (VoltagePixelIntCH1<=YaxisYend) && (VoltagePixelIntCH2>=YaxisYbegin) && (VoltagePixelIntCH2<=YaxisYend)){
            // draw line if not on cursor or x-axis or Cursor
            if(!(i==(cursor1ArrPos-2) | i==(cursor2ArrPos-2) |i==(cursor1ArrPos-1) | i==(cursor2ArrPos-1))){

                //Overwrite Old pixels
                drawLine(122+i,oldVoltageCH1[i],122+i+1,oldVoltageCH1[i+1],BLACK);                  // Channel 1
                drawLine(122+i,oldVoltageCH2[i],122+i+1,oldVoltageCH2[i+1],BLACK);                  // Channel 2

                //Write current pixels
                drawLine(122+i,VoltagePixelIntCH1,122+i+1,nextVoltagePixelIntCH1,YELLOW);         // Channel 1
                drawLine(122+i,VoltagePixelIntCH2,122+i+1,nextVoltagePixelIntCH2,BLUE);               // Channel 2

                // Fix middle line
                drawLine(122+i,XaxisYmiddle,122+i+1,XaxisYmiddle+1,WHITE);

                // Fix Y-axis arrow
                if(i>(arrayLen-arrowLength-2)){
                    if(((VoltagePixelIntCH1>(XaxisYmiddle - arrowWidth - 1))&&(VoltagePixelIntCH1<(XaxisYmiddle + arrowWidth + 2)))||(VoltagePixelIntCH2>(XaxisYmiddle - arrowWidth - 1))&&(VoltagePixelIntCH2<(XaxisYmiddle + arrowWidth + 2))){
                        drawLine(XaxisXend - 1, XaxisYmiddle - 1, XaxisXend - arrowLength - 1, XaxisYmiddle - arrowWidth - 1, WHITE);       // Upper upper arrow line
                        drawLine(XaxisXend - 2, XaxisYmiddle - 1, XaxisXend - arrowLength - 2, XaxisYmiddle - arrowWidth - 1, WHITE);       // Lower upper arrow line
                        drawLine(XaxisXend - 1, XaxisYmiddle + 2, XaxisXend - arrowLength - 1, XaxisYmiddle + arrowWidth + 2, WHITE);       // Upper lower arrow line
                        drawLine(XaxisXend - 2, XaxisYmiddle + 2, XaxisXend - arrowLength - 2, XaxisYmiddle + arrowWidth + 2, WHITE);       // Lower lower arrow line
                    }
                }
            }

            //Save written pixel to be deletable in next cycle
            oldVoltageCH1[i]=VoltagePixelIntCH1;
            oldVoltageCH2[i]=VoltagePixelIntCH2;

            // Set Next Voltage to be next interrupts starting voltage
            VoltagePixelIntCH1 = nextVoltagePixelIntCH1;
            VoltagePixelIntCH2 = nextVoltagePixelIntCH2;
        }
    }
    //Overwrite Old pixels at last value
    drawLine(122+i,oldVoltageCH1[arrayLen-1],122+i+1,oldVoltageCH1[arrayLen-1],BLACK);                  // Channel 1
    drawLine(122+i,oldVoltageCH2[arrayLen-1],122+i+1,oldVoltageCH2[arrayLen-1],BLACK);                  // Channel 2
    // Remeber old pixels at last value
    oldVoltageCH1[arrayLen-1] = VoltagePixelIntCH1;
    oldVoltageCH2[arrayLen-1] = VoltagePixelIntCH2;
    // Fix middle line for bug at end of X-Axis
    drawLine(122+arrayLen-1,XaxisYmiddle,122+arrayLen+2,XaxisYmiddle+1,WHITE);

}
/********************************************************************************/
void refreshTimebaseButton(void){
    // Button to refresh the timebase
    if(((xpos>=205)&&(xpos<=3379)) && ((ypos>=3072)&&(ypos<=3755))){
        //Upper side Button
        //printf("Printing new Button\n");
        //drawLine(100,100,400,400,WHITE);
        drawRectangle((xpos*0.195),(ypos*0.117),(xpos*0.195+10),(ypos*0.117+10),GREEN);
        //Lower side Button
    }
}
/********************************************************************************/

