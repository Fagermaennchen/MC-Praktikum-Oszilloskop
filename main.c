// Example and Testprogram  Touch Function
// See Installation Manual
// K.R. Riemschneider v.04  2023
// Git test 2 Display Modul

#include <stdio.h>
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"

void touch_write(unsigned char value)
{
    unsigned char i = 0x08; // 8 bit command
    unsigned char x, DI;
    GPIO_PORTD_AHB_DATA_R &= 0xFB; //CS=0
    while (i > 0) {
        DI = (value >> 7);
        if (DI == 0) {GPIO_PORTD_AHB_DATA_R &= 0xfe;} //out bit=0
        else {GPIO_PORTD_AHB_DATA_R |= 0x01;} //out bit=1
        value <<= 1; //next value
        GPIO_PORTD_AHB_DATA_R |= 0x08; //Clk=1
        for (x = 0; x < 10; x++);
        GPIO_PORTD_AHB_DATA_R &= 0xf7; //Clk=0
        for (x = 0; x < 10; x++);
        i--;
    }
}

unsigned int touch_read()
{
    unsigned char i = 12; // 12 Bit ADC
    unsigned int x, value = 0x00;
    while (i > 0)
    {
        value <<= 1;
        GPIO_PORTD_AHB_DATA_R |= 0x08; //Clk=1
        for (x = 0; x < 10; x++);
        GPIO_PORTD_AHB_DATA_R &= 0xf7; //Clk=0
        for (x = 0; x < 10; x++);
        value |= ((GPIO_PORTD_AHB_DATA_R >> 1) & 0x01); // read value
        i--;
    }
    GPIO_PORTD_AHB_DATA_R |= 0x04; //CS=1
    return value;
}

int main(void)
{
<<<<<<< Updated upstream
    int x, xpos, ypos;
    SYSCTL_RCGCGPIO_R = 0x0008; //Enable clock Port D
    while ((SYSCTL_PRGPIO_R & 0x08) == 0);  //GPIO Clock ready?
    GPIO_PORTD_AHB_DEN_R = 0x1F;            //PortD digital enable
    GPIO_PORTD_AHB_DIR_R = 0x0D;            //PortD Input/Output
    GPIO_PORTD_AHB_DATA_R &= 0xF7;          //Clk=0
    while (1) {
        touch_write(0xD0);                  //Touch Command XPos read
        for (x = 0; x < 10; x++);           //Busy wait
        xpos = touch_read();                //xpos value read ( 0......4095 )
        printf("xpos= %5d ", xpos);
        touch_write(0x90);                  //Touch Command YPos read
        for (x = 0; x < 10; x++);           //Busy wait
        ypos = touch_read();                //ypos value read ( 0.....4095 )
        printf("ypos= %5d\n", ypos);
=======
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while(1){
        window_set(x0,y0,x0,y0);
        write_command(0x2C); //write pixel command
        write_data((color>>16)&0xff); // red
        write_data((color>>8)&0xff); // green
        write_data((color)&0xff); // blue
        if(x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if(e2 > dy){
            err += dy;
            x0 += sx;
        }
        if(e2 < dx){
            err += dx;
            y0 += sy;
        }
    }

}
/********************************************************************************/
void drawAxes(void){
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
/********************************************************************************/
void initTriggerAxis(void){
    drawRectangle(57,80,61,359,GREY);       //draw Trigger Axis
    drawRectangle(29,210,89,230,GREY);
}
/********************************************************************************/
void readTouchValues(void){

    //read Touch values
    touch_write(0xD0);                  //Touch Command XPos read
    for (x = 0; x < 100; x++);           //Busy wait
    xpos = touch_read();                //xpos value read ( 0......4095 )
    //printf("xpos= %5d ", xpos);
    touch_write(0x90);                  //Touch Command YPos read
    for (x = 0; x < 100; x++);           //Busy wait
    ypos = touch_read();                //ypos value read ( 0.....4095 )
    //printf("ypos= %5d\n", ypos);
}
/********************************************************************************/
void refreshTimebaseButton(void){
    if(((xpos>=205)&&(xpos<=3379)) && ((ypos>=3072)&&(ypos<=3755))){
        //Upper side Button
        //printf("Printing new Button\n");
        //drawLine(100,100,400,400,WHITE);
        drawRectangle((xpos*0.195),(ypos*0.117),(xpos*0.195+10),(ypos*0.117+10),GREEN);
        //Lower side Button
>>>>>>> Stashed changes
    }
}
