#include "headers/cursor.h"
#include "headers/display.h"
#include "headers/globalVariables.h"
#include "headers/font.h"

void initValueDescriptions(void){
    // Channel 1
    //draw Value Description
    drawFont(font_C, xStartCHX, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_1, xStartCHX+2*fontWidth+2*fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+3*fontSpace, yStartCHfirstLine, YELLOW, BLACK);
    // Draw Delta Voltage
    drawFont(font_delta, xStartDelta, yStartCHfirstLine, YELLOW, BLACK);
    drawMilliVolt(5555,xStartDeltaVolVal,yStartCHfirstLine,YELLOW,BLACK);
    // Draw Cursor 1 Values
    drawMilliVolt(-1234,xStartVol1,yStartCHfirstLine,GREEN,BLACK);
    // Draw Cursor 2 Values
    drawMilliVolt(-1234,xStartVol2,yStartCHfirstLine,RED,BLACK);
    // Draw Time Description
    drawFont(font_delta, xStartDeltaT, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_t, xStartDeltaT+fontWidth+fontSpace, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_colon, xStartDeltaT+2*(fontWidth+fontSpace), yStartCHfirstLine, WHITE, BLACK);
    // Draw Time
    drawMilliSeconds(1234,xStartValTime,yStartCHfirstLine, WHITE, BLACK);


    //draw second Font line
    drawFont(font_C, xStartCHX, yStartCHsecondLine, BLUE, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHsecondLine, BLUE, BLACK);
    drawFont(font_2, xStartCHX+2*fontWidth+2*fontSpace, yStartCHsecondLine, BLUE, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+2*fontSpace, yStartCHsecondLine, BLUE, BLACK);
    drawFont(font_C, 450, 439,BLUE,BLACK);
    // Draw Delta Voltage
    drawFont(font_delta, xStartDelta, yStartCHsecondLine, BLUE, BLACK);
    drawMilliVolt(5555,xStartDeltaVolVal,yStartCHsecondLine,BLUE,BLACK);
    // Draw Cursor 1 Values
    drawMilliVolt(-1234,xStartVol1,yStartCHsecondLine,GREEN,BLACK);
    // Draw Cursor 2 Values
    drawMilliVolt(-1234,xStartVol2,yStartCHsecondLine,RED,BLACK);


}

void setupCursor(void){
    initValueDescriptions();
}



