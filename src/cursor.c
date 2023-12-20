#include "headers/cursor.h"
#include "headers/display.h"
#include "headers/globalVariables.h"
#include "headers/font.h"
#include "headers/ADC.h"
#include <stdio.h>
#include <stdbool.h>


// Global Variables
cursor1ArrPos = 30;      // Cursor one start position
cursor2ArrPos = 300;      // Cursor one start position

void initValueDescriptions(void){
    // Channel 1
    //draw Value Description
    drawFont(font_C, xStartCHX, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_1, xStartCHX+2*fontWidth+2*fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+3*fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    // Draw Delta Voltage
    drawFont(font_delta, xStartDelta, yStartCHfirstLine, YELLOW, BLACK);
    drawMilliVolt(0,xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK,false);
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
    drawFont(font_C, 450, 439,BLUE,BLACK);
    // Draw Delta Voltage
    drawFont(font_delta, xStartDelta, yStartCHsecondLine, BLUE, BLACK);
    drawMilliVolt(0,xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK,false);
    // Draw Cursor 1 Values
    drawMilliVolt(0,xStartVol1,yStartCHsecondLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(0,xStartVol2,yStartCHsecondLine,RED,BLACK,true);


}

void updateCursorValues(void){            // Moves the cursors position on screen and in the value arrays
    printf("CH1: %d, CH2 : %d \n",resultsCH1[cursor1ArrPos],resultsCH2[cursor1ArrPos]);
    // Channel 1
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor1ArrPos])-convertADCtoVolt(resultsCH1[cursor2ArrPos]),xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK,false);
    // Draw Cursor 1 Values
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor1ArrPos]),xStartVol1,yStartCHfirstLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor2ArrPos]),xStartVol2,yStartCHfirstLine,RED,BLACK,true);
    // Draw Time Description
    // Draw Time
    drawMilliSeconds((cursor1ArrPos-cursor2ArrPos),xStartValTime,yStartCHfirstLine, WHITE, BLACK);

    //Channel 2
    // Draw Delta Voltage
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor1ArrPos])-convertADCtoVolt(resultsCH2[cursor2ArrPos]),xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK,false);
    // Draw Cursor 1 Values
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor1ArrPos]),xStartVol1,yStartCHsecondLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor2ArrPos]),xStartVol2,yStartCHsecondLine,RED,BLACK,true);

}

void setupCursor(void){
    initValueDescriptions();
}



