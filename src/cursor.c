#include <stdio.h>
#include <stdbool.h>
#include "headers/cursor.h"
#include "headers/display.h"
#include "headers/globalVariables.h"
#include "headers/font.h"
#include "headers/ADC.h"
#include "headers/display.h"



// Global Variables
cursor1ArrPos = 200;      // Cursor one start position in Array
cursor2ArrPos = 400;      // Cursor two start position in Array
cursor1DispPos = 221;         // Cursor one start position on Screen
cursor2DispPos = 421;         // Cursor two start position on Screen
cursorSelected = 0;     // Remeber if cursor is currently seclted


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
    drawMikroSeconds(0,xStartValTime,yStartCHfirstLine, WHITE, BLACK);

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
    //printf("CH1: %d, CH2 : %d \n",resultsCH1[cursor1ArrPos],resultsCH2[cursor1ArrPos]);
    // Channel 1
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor1ArrPos])-convertADCtoVolt(resultsCH1[cursor2ArrPos]),xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK,false);
    // Draw Cursor 1 Values
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor1ArrPos]),xStartVol1,yStartCHfirstLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(convertADCtoVolt(resultsCH1[cursor2ArrPos]),xStartVol2,yStartCHfirstLine,RED,BLACK,true);
    // Draw Time Description
    // Draw Time
    drawMikroSeconds((cursor1ArrPos-cursor2ArrPos)*tSample,xStartValTime,yStartCHfirstLine, WHITE, BLACK);

    //Channel 2
    // Draw Delta Voltage
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor1ArrPos])-convertADCtoVolt(resultsCH2[cursor2ArrPos]),xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK,false);
    // Draw Cursor 1 Values
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor1ArrPos]),xStartVol1,yStartCHsecondLine,GREEN,BLACK,true);
    // Draw Cursor 2 Values
    drawMilliVolt(convertADCtoVolt(resultsCH2[cursor2ArrPos]),xStartVol2,yStartCHsecondLine,RED,BLACK,true);

}

void moveCursor1Position(int x){
    // Moves the cursors position on screen and in the value arrays
    // Check x for left bounds
    if (x<(XaxisXbegin+2)){             // +2 to not overwrite Y-axis (axis-width=2)
        x=(XaxisXbegin+2);
    }
    // Check x for right bounds
    else if(x>XaxisXend-1){
        x=XaxisXend-1;
    }
    // Remove Cursor line at old position
    window_set(cursor1DispPos,YaxisYbegin,cursor1DispPos,XaxisXend);
    write_command(0x2C); //write pixel command
    int i;
    for(i=0;i<YaxisYend-YaxisYbegin;i++)  {   // Each Entry in Byte Array
        //  Draw Color
            write_data((BLACK>>16)&0xff); // red
            write_data((BLACK>>8)&0xff); // green
            write_data((BLACK)&0xff); // blue
    }
    // Fix Middle line
    window_set(cursor1DispPos,XaxisYmiddle,cursor1DispPos,XaxisYmiddle-1);
    write_command(0x2C); //write pixel command
    for(i=0;i<2;i++){
        write_data((WHITE>>16)&0xff); // red
        write_data((WHITE>>8)&0xff); // green
        write_data((WHITE)&0xff); // blue
    }
    // Draw new line
    window_set(x,YaxisYbegin,x,XaxisXend);
    write_command(0x2C); //write pixel command
    for(i=0;i<YaxisYend-YaxisYbegin;i++)  {   // Each Entry in Byte Array
        //  Draw Color
            write_data((GREEN>>16)&0xff); // red
            write_data((GREEN>>8)&0xff); // green
            write_data((GREEN)&0xff); // blue
    }
    // Move position in array
    cursor1ArrPos = x - XaxisXbegin - 1;
    // Remember position
    cursor1DispPos = x;

}

void moveCursor2Position(int x){
    // Moves the cursors position on screen and in the value arrays
    // Check x for left bounds
    if (x<(XaxisXbegin+2)){         // +2 to not overwrite Y-axis (axis-width=2)
        x=(XaxisXbegin+2);
    }
    // Check x for right bounds
    else if(x>XaxisXend-1){
        x=XaxisXend-1;
    }
    // Remove Cursor line at old position
    window_set(cursor2DispPos,YaxisYbegin,cursor2DispPos,XaxisXend);
    write_command(0x2C); //write pixel command
    int i;
    for(i=0;i<YaxisYend-YaxisYbegin;i++)  {   // Each Entry in Byte Array
        //  Draw Color
            write_data((BLACK>>16)&0xff); // red
            write_data((BLACK>>8)&0xff); // green
            write_data((BLACK)&0xff); // blue
    }
    // Fix Middle line
    window_set(cursor2DispPos,XaxisYmiddle,cursor2DispPos,XaxisYmiddle-1);
    write_command(0x2C); //write pixel command
    for(i=0;i<2;i++){
        write_data((WHITE>>16)&0xff); // red
        write_data((WHITE>>8)&0xff); // green
        write_data((WHITE)&0xff); // blue
    }
    // Draw new line
    window_set(x,YaxisYbegin,x,XaxisXend);
    write_command(0x2C); //write pixel command
    for(i=0;i<YaxisYend-YaxisYbegin;i++)  {   // Each Entry in Byte Array
        //  Draw Color
        write_data((RED>>16)&0xff); // red
        write_data((RED>>8)&0xff); // green
        write_data((RED)&0xff); // blue
    }
    // Redraw other cursor if on same prev position
    if(cursor2DispPos == cursor1DispPos ){
        moveCursor1Position(cursor1DispPos);
    }
    // Redraw other cursor if on same prev position
    if(cursor1DispPos == cursor2DispPos ){
        moveCursor2Position(cursor2DispPos);
    }
    // Move position in array
    cursor2ArrPos = x - XaxisXbegin - 1;
    // Remember position
    cursor2DispPos = x;
}

void setupCursor(void){
    initValueDescriptions();
    moveCursor1Position(121+cursor1ArrPos);
    moveCursor2Position(121+cursor2ArrPos);
}



