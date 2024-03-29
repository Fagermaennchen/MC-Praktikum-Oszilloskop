
#include <src/headers/ADC.h>
#include "headers/globalVariables.h"
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "headers/cursor.h"
#include "headers/display.h"
#include "headers/font.h"


/*********************************************************************************
                             Cursor Initialization
*********************************************************************************/
void setupCursor_routine(void){
    // Initialise Value Descriptions
    initValueDescriptions();
    // Show Cursors on starting position
    moveCursor1Position(121+cursor1ArrPos,false);
    moveCursor2Position(121+cursor2ArrPos,false);
    // Configure the Timer 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);           // Enable the Timer1 peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)) {}  // Wait for the Timer1 module to be ready
    TimerConfigure(TIMER1_BASE, (TIMER_CFG_A_PERIODIC ));   // Timer 1 in periodic mode
    TimerLoadSet(TIMER1_BASE,TIMER_A,cursorLoadValue);        // 1 Second Intervall
    // Create Timer 1 Interrupt source
    TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);         // Enable Timer 1A as Int Source
    TimerIntRegister(TIMER1_BASE,TIMER_A,updateCursorValues);   // Register Timer 1A Int to updateCursorValues Routine
    IntPrioritySet(INT_TIMER1A_TM4C123,CURSORprio);               // Priority to 1
    printf("prio: %d \n",IntPriorityGet(INT_TIMER1A_TM4C123));
}
/********************************************************************************/
void initValueDescriptions(void){
    // Channel 1
    //draw Value Description
    drawFont(font_C, xStartCHX, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_1, xStartCHX+2*fontWidth+2*fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+3*fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    // Draw Delta Voltage
    drawFont(font_delta, xStartDelta, yStartCHfirstLine, YELLOW, BLACK);
    drawDeltaVolt(0,xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK);
    // Draw Cursor 1 Values
    drawMilliVolt(0,xStartVol1,yStartCHfirstLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(0,xStartVol2,yStartCHfirstLine,RED,BLACK,true);
    // Draw Time Description
    drawFont(font_delta, xStartDeltaT, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_t, xStartDeltaT+fontWidth+fontSpace, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_colon, xStartDeltaT+2*(fontWidth+fontSpace), yStartCHfirstLine, WHITE, BLACK);
    // Draw Time
    drawMilliSeconds(0,xStartValTime,yStartCHfirstLine, WHITE, BLACK);

    //Channel 2
    drawFont(font_C, xStartCHX, yStartCHsecondLine, BLUE, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHsecondLine, BLUE, BLACK);
    drawFont(font_2, xStartCHX+2*fontWidth+2*fontSpace, yStartCHsecondLine, BLUE, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+2*fontSpace, yStartCHsecondLine, BLUE, BLACK);
    // Draw Delta Voltage
    drawFont(font_delta, xStartDelta, yStartCHsecondLine, BLUE, BLACK);
    drawDeltaVolt(0,xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK);
    // Draw Cursor 1 Values
    drawMilliVolt(0,xStartVol1,yStartCHsecondLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(0,xStartVol2,yStartCHsecondLine,RED,BLACK,true);
}
/********************************************************************************/



/*********************************************************************************
                          Cursor Operating Functions
*********************************************************************************/
void updateCursorValues(void){            // Moves the cursors position on screen and in the value arrays
    // Clear Interrupt
    TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
    // Only update of signal is currently triggered no signal is detected
    //printf("CH1: %d, CH2 : %d \n",resultsCH1[cursor1ArrPos],resultsCH2[cursor1ArrPos]);
    // Channel 1
    // Draw Delta Voltage
    drawDeltaVolt((convertADCtoVolt(resultsCH1[cursor1ArrPos])-convertADCtoVolt(resultsCH1[cursor2ArrPos])),
                  xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK);
    // Draw Cursor 1 Values
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor1ArrPos]),xStartVol1,yStartCHfirstLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor2ArrPos]),xStartVol2,yStartCHfirstLine,RED,BLACK,true);
    // Draw Time Description
    drawMilliSeconds((cursor1ArrPos-cursor2ArrPos)*tSample,xStartValTime,yStartCHfirstLine, WHITE, BLACK);
    //Channel 2
    // Draw Delta Voltage
    drawDeltaVolt((convertADCtoVolt(resultsCH2[cursor1ArrPos])-convertADCtoVolt(resultsCH2[cursor2ArrPos])),
                  xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK);
    // Draw Cursor 1 Values
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor1ArrPos]),xStartVol1,yStartCHsecondLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor2ArrPos]),xStartVol2,yStartCHsecondLine,RED,BLACK,true);
}
/********************************************************************************/
void resetValueDescriptions(void){
      // Channel 1
      // Draw Delta Voltage
      drawFont(font_delta, xStartDelta, yStartCHfirstLine, YELLOW, BLACK);
      drawMilliVolt(0,xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK,false);
      // Draw Cursor 1 Values
      drawMilliVolt(0,xStartVol1,yStartCHfirstLine,GREEN,BLACK,true);
      // Draw Cursor 2 Values
      drawMilliVolt(0,xStartVol2,yStartCHfirstLine,RED,BLACK,true);
      // Draw Time
      drawMilliSeconds(0,xStartValTime,yStartCHfirstLine, WHITE, BLACK);
      //Channel 2
      // Draw Delta Voltage
      drawFont(font_delta, xStartDelta, yStartCHsecondLine, BLUE, BLACK);
      drawMilliVolt(0,xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK,false);
      // Draw Cursor 1 Values
      drawMilliVolt(0,xStartVol1,yStartCHsecondLine,GREEN,BLACK,true);
      // Draw Cursor 2 Values
      drawMilliVolt(0,xStartVol2,yStartCHsecondLine,RED,BLACK,true);
}
/********************************************************************************/
void moveCursor1Position(int x, bool redraw){
    // Moves the cursors position on screen and in the value arrays
    // Check x for left bounds
    if (x<(XaxisXbegin+3)){             // +2 to not overwrite Y-axis (axis-width=2)
        x=(XaxisXbegin+3);
    }
    // Check x for right bounds
    else if(x>XaxisXend-1){
        x=XaxisXend-1;
    }
    // Remove Cursor line at old position
    if(cursor1DispPos == cursor2DispPos){
        drawLine(cursor1DispPos,YaxisYbegin,cursor1DispPos,YaxisYend,RED);    // Redraw other cursor if prev on the same spot
    }
    else{
        drawLine(cursor1DispPos,YaxisYbegin,cursor1DispPos,YaxisYend,BLACK);    // Draw Background
    }
    // Remopve adjacent curve pixels at new cursor, if not in other cursors range
    if(x + 1 != cursor2DispPos){
        drawLine(x+1,YaxisYbegin,x+1,YaxisYend,BLACK);                  // Channel 1
        drawLine(x+1,YaxisYbegin,x+1,YaxisYend,BLACK);                  // Channel 2
    }
    if(x - 1 != cursor2DispPos){
        drawLine(x-1,YaxisYbegin,x-1,YaxisYend,BLACK);                  // Channel 1
        drawLine(x-1,YaxisYbegin,x-1,YaxisYend,BLACK);                  // Channel 2
    }
    // Draw new Cursor: Center line
    drawLine(x,YaxisYbegin,x,YaxisYend,GREEN);
    // Fix Middle line
    drawLine(cursor1DispPos,XaxisYmiddle+1,cursor1DispPos,XaxisYmiddle,WHITE);
    drawLine(cursor1DispPos-1,XaxisYmiddle+1,cursor1DispPos-1,XaxisYmiddle,WHITE);
    drawLine(cursor1DispPos+1,XaxisYmiddle+1,cursor1DispPos+1,XaxisYmiddle,WHITE);
    // Fix Y-axis arrow
        // Right right arrow line
    drawLine(XaxisXbegin + 2, YaxisYbegin + 1, XaxisXbegin + arrowWidth + 2, YaxisYbegin + arrowLength + 1, WHITE);
        // Left right arrow line
    drawLine(XaxisXbegin + 2, YaxisYbegin + 2, XaxisXbegin + arrowWidth + 2, YaxisYbegin + arrowLength + 2, WHITE);
    // Move position in array
    cursor1ArrPos = x - XaxisXbegin - 1;
    // Remember position
    cursor1DispPos = x;
}
/********************************************************************************/
void moveCursor2Position(int x, bool redraw){
    // Moves the cursors position on screen and in the value arrays
    // Check x for left bounds
    if (x<(XaxisXbegin+3)){         // +2 to not overwrite Y-axis (axis-width=2)
        x=(XaxisXbegin+3);
    
    }
    // Check x for right bounds
    else if(x>XaxisXend-1){
        x=XaxisXend-1;
    }
    // Remove Cursor line at old position
    if(cursor1DispPos == cursor2DispPos){
        drawLine(cursor2DispPos,YaxisYbegin,cursor2DispPos,YaxisYend,GREEN);    // Redraw other cursor if prev on the same spot
    }
    else{
        drawLine(cursor2DispPos,YaxisYbegin,cursor2DispPos,YaxisYend,BLACK);    // Draw Background
    }
    // Remopve adjacent curve pixels at new cursor, if not in other cursors range
    if(x + 1  != cursor1DispPos){
        drawLine(x+1,YaxisYbegin,x+1,YaxisYend,BLACK);                  // Channel 1
        drawLine(x+1,YaxisYbegin,x+1,YaxisYend,BLACK);                  // Channel 2
    }
    if(x - 1 != cursor1DispPos){
        drawLine(x-1,YaxisYbegin,x-1,YaxisYend,BLACK);                  // Channel 1
        drawLine(x-1,YaxisYbegin,x-1,YaxisYend,BLACK);                  // Channel 2
    }

    // Draw new Cursor
    drawLine(x,YaxisYbegin,x,YaxisYend,RED);
    // Fix Middle line
    drawLine(cursor2DispPos,XaxisYmiddle+1,cursor2DispPos,XaxisYmiddle,WHITE);
    drawLine(cursor2DispPos-1,XaxisYmiddle+1,cursor2DispPos-1,XaxisYmiddle,WHITE);
    drawLine(cursor2DispPos+1,XaxisYmiddle+1,cursor2DispPos+1,XaxisYmiddle,WHITE);
    // Fix Y-axis arrow
    drawLine(XaxisXbegin + 1, YaxisYbegin + 1, XaxisXbegin + arrowWidth + 2, YaxisYbegin + arrowLength + 1, WHITE);      // Right right arrow line
    drawLine(XaxisXbegin + 1, YaxisYbegin + 2, XaxisXbegin + arrowWidth + 2, YaxisYbegin + arrowLength + 2, WHITE);      // Left right arrow line
    // Move position in array
    cursor2ArrPos = x - XaxisXbegin - 1;
    // Remember position
    cursor2DispPos = x;
}
/********************************************************************************/




