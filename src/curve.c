#include "headers/curve.h"
#include "headers/globalVariables.h"
#include "headers/cursor.h"



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
void initTimebaseAxis(void){
    // Inisialises the timebase axis
    drawRectangle(160,399,759,401,GREY);
    drawRectangle(450,370,470,430,GREY);
}
void drawAxes(void){
    // Draws the axis of the coordinate system
    //enum colors color;
    //color = WHITE;
    //Write X-Axis  (double lined)
    drawLine(XaxisXbegin, XaxisYmiddle, XaxisXend, XaxisYmiddle, WHITE);                       // Uppder line of double line
    drawLine(XaxisXbegin, XaxisYmiddle + 1, XaxisXend, XaxisYmiddle + 1, WHITE);               // Lower line
    //Write X-Axis Arrow (double lined)
    drawLine(XaxisXbegin + 2, YaxisYbegin + 1, XaxisXbegin + arrowWidth + 2, YaxisYbegin + arrowLength + 1, WHITE);      // Right right arrow line
    drawLine(XaxisXbegin + 2, YaxisYbegin + 2, XaxisXbegin + arrowWidth + 2, YaxisYbegin + arrowLength + 2, WHITE);      // Left right arrow line
    drawLine(XaxisXbegin - 1, YaxisYbegin + 1, XaxisXbegin - arrowWidth - 1, YaxisYbegin + arrowLength + 1, WHITE);      // Right left arrow line
    drawLine(XaxisXbegin - 1, YaxisYbegin + 2, XaxisXbegin - arrowWidth - 1, YaxisYbegin + arrowLength + 2, WHITE);      // Left left arrow line

    //Write Y-Axis (double lined)
    drawLine(XaxisXbegin, YaxisYbegin, XaxisXbegin, YaxisYend, WHITE);
    drawLine(XaxisXbegin + 1,YaxisYbegin,XaxisXbegin + 1,YaxisYend, WHITE);
    //Write Y-Axis Arrow (double lined)
    drawLine(XaxisXend - 1, XaxisYmiddle - 1, XaxisXend - arrowLength - 1, XaxisYmiddle - arrowWidth - 1, WHITE);
    drawLine(XaxisXend - 2, XaxisYmiddle - 1, XaxisXend - arrowLength - 2, XaxisYmiddle - arrowWidth - 1, WHITE);
    drawLine(XaxisXend - 1, XaxisYmiddle + 2, XaxisXend - arrowLength - 1, XaxisYmiddle + arrowWidth + 2, WHITE);
    drawLine(XaxisXend - 2, XaxisYmiddle + 2, XaxisXend - arrowLength - 2, XaxisYmiddle + arrowWidth + 2, WHITE);
    printf("Axes ready\n");
}
void initTriggerAxis(void){
    // draws the trigegr axis
    drawRectangle(58,80,60,359,GREY);       //draw Trigger Axis
    drawRectangle(29,210,89,230,GREY);
}


void drawVoltageCurve(void){
    int i,j;
    int voltageY0, voltageY1;
    double voltagePixel;
    int voltagePixelint;
    enum colors color = WHITE;

    //Spannungsreferenz erstmal f�r 0-5V

    for(i = 0; i < arrayLen-1; i++){

        voltageY0 = resultsCH1[i];
        voltagePixel = 360 - ((voltageY0-300)*0.08);
        voltagePixelint = (int) voltagePixel;

        if(!(voltagePixelint==219 | voltagePixelint==220 | i==cursor1ArrPos | i==cursor2ArrPos)){
            //Overwrite Old pixels
            drawLine(121+i,oldVoltage[i],121+i,oldVoltage[i],BLACK);
            //Write current pixels
            drawLine(121+i,voltagePixelint,121+i,voltagePixelint,WHITE);
            //Save written pixel to be deletable in next cycle
            oldVoltage[i]=voltagePixelint;
        }





        //printf("voltage: %d\n", voltageY0);
        //printf("pixelpos: %lf\n", voltagePixel);
        //printf("PixelInt: %d\n" , voltagePixelint);


    }
}



