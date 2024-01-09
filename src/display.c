
#include "headers/globalVariables.h"
#include <stdbool.h> // type bool for giop.h
#include <stdio.h>   // Debug only
#include <stdint.h>
#include <inc/hw_memmap.h>      // GPIO_PORTX_BASE
#include <src/headers/ADC.h>
#include "inc/hw_types.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/gpio.h"     // GPIO_PIN_X
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "headers/cursor.h"
#include "headers/display.h"
#include "headers/font.h"


/********************************************************************************
     Elementary output functions  => speed optimized as inline
*********************************************************************************/
inline void write_command(unsigned char command)
{   GPIO_PORTM_DATA_R = command;        // Write command byte
    GPIO_PORTL_DATA_R = 0x11;           // Chip select = 0, Command mode select = 0, Write state = 0
    GPIO_PORTL_DATA_R = 0x1F;           // Initial state
}
/********************************************************************************/
inline void write_data(unsigned char data)
{   GPIO_PORTM_DATA_R = data;           // Write data byte
    GPIO_PORTL_DATA_R = 0x15;           // Chip select = 0, Write state = 0
    GPIO_PORTL_DATA_R = 0x1F;           // Initial state
}
/********************************************************************************/
inline void window_set(int min_x,int min_y,int max_x,int max_y)
{
    write_command(0x2A);           // Set row address x-axis
    write_data(min_x >> 8);        // Set start  address           (high byte)
    write_data(min_x);             // as above                     (low byte)
    write_data(max_x >> 8);        // Set stop address             (high byte)
    write_data(max_x);             // as above                     (low byte)
    write_command(0x2B);           // Set column address (y-axis)
    write_data(min_y >> 8);        // Set start column address     (high byte)
    write_data(min_y);             // as above                     (low byte)
    write_data(max_y >> 8);        // Set stop column address      (high byte)
    write_data(max_y);             // as above                     (low byte)
}
/********************************************************************************/



/*********************************************************************************
                        Display configuration
*********************************************************************************/
void init_ports_display(void)
{
    // Set Port M Pins 0-7: used as Output of LCD Data
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);            // enable clock-gate Port M
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM));     // wait until clock ready
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, 0xFF);
    // Set Port L Pins 0-4: used as Output of LCD Control signals:
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);  // Clock Port Q
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL));
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3| GPIO_PIN_4);
}
/********************************************************************************/
void configure_display_controller_large (void) // 800 x 480 pixel ???
{
//////////////////////////////////////////////////////////////////////////////////
    GPIO_PORTL_DATA_R = INITIAL_STATE;      // Initial state
    GPIO_PORTL_DATA_R &= ~RST;              // Hardware reset
    SysCtlDelay(10000);                     // wait >1 ms
    GPIO_PORTL_DATA_R |= RST;               //
    SysCtlDelay(12000);                     // wait >1 ms

    write_command(SOFTWARE_RESET);          // Software reset
    SysCtlDelay(120000);                    // wait >10 ms

    write_command(SET_PLL_MN);               // Set PLL Freq to 120 MHz
    write_data(0x24);                        //
    write_data(0x02);                        //
    write_data(0x04);                        //

    write_command(START_PLL);                // Start PLL
    write_data(0x01);                        //
    SysCtlDelay(10000);                      // wait 1 ms

    write_command(START_PLL);                // Lock PLL
    write_data(0x03);                        //
    SysCtlDelay(10000);                      // wait 1 ms

    write_command(SOFTWARE_RESET);           // Software reset
    SysCtlDelay(100000);                     // wait 10 ms

    write_command(0xe6);                    // Set pixel clock frequency
    write_data(0x01);                       // KRR Set LCD Pixel Clock 9MHz
    write_data(0x70);                       // KRR
    write_data(0xA3);                       // KRR

    write_command(SET_LCD_MODE);          // SET LCD MODE SIZE, manual p. 44
    write_data(0x20);                     // ..TFT panel 24bit
    write_data(0x00);                     // ..TFT mode
    write_data(0x03);                     // SET horizontal size = 800-1 (high byte)
    write_data(0x1F);                     // SET horizontal size = 800-1 (low byte)
    write_data(0x01);                     // Set vertical size = 480-1 (high byte)
    write_data(0xDF);                     // Set vertical size = 480-1 (low byte)
    write_data(0x00);                     // Even line RGB sequence / Odd line RGB sequence RGB

    write_command(SET_HORI_PERIOD);       // Set Horizontal Period
    write_data(0x03);                     // Horizontal total period (display + non-displayed)  (high byte)
    write_data(0x5E);                     // Horizontal total period (display + non-display) (low byte)
    write_data(0x00);                     // Non-displayed period between the start of the horizontal sync (LLINE) signal and the first displayed data.
    write_data(0x46);                     // Low byte of the non-display period between the start of the horizontal sync (LLINE) signal and the first display data
    write_data(0x09);                     // Set the vertical sync width
    write_data(0x00);                     // Set horiz.Sync pulse start    (high byte)
    write_data(0x08);                     // Set horiz.Sync pulse start    (low byte)
    write_data(0x00);                     //

    write_command(SET_VERT_PERIOD);         // Set vertical periods, manual  p. 49
    write_data(0x01);                       // Vertical total period (display + non-displayed) in lines (high byte)
    write_data(0xFE);                       // as above (low byte) = total 510  lines
    write_data(0x00);                       //
    write_data(0x0C);                       // The non-displayed period in lines between the start of the frame and the first
                                            // display data = 12 line.s
    write_data(0x0A);                       // Set the vertiacla sync width = 10 pixels
    write_data(0x00);                       // Set vertical sync pulse start position (high byte)
    write_data(0x04);                       // as above (low byte) = total sync pulse start position is 4 lines

    write_command(SET_ADRESS_MODE);         // Pixel address counting = flip display , manual p. 36
    write_data(0x03);                       // necessary to match with touch screen addressing

//  write_command(0x0A);                    // Power control mode not tested in detail
//  write_data(0x1C);

    write_command(SET_PIXEL_DATA_FORMAT);    // set pixel data format 8bit manual p. 78
    write_data(0x00);

    write_command(SET_DISPLAY_ON);           // Set display on  manual p. 78
}
/********************************************************************************/
void initDisplay(void){

   enum colors color;   // see global definition
   init_ports_display(); // Init Port L for Display Control and Port M for Display Data
   configure_display_controller_large();  // initalize and  configuration
   printf("Start Background Pixel by Pixel set\n"); // for debug only
   // set pixel by pixel to change the background colors
   color=BLACK;
   window_set(0,0,MAX_X-1,MAX_Y-1); // set single position see B.4  // to do faster ?
   write_command(0x2C); //write pixel command
   int x,y;
   for (x=0;x<=(MAX_X)-1;x++)
        for (y=0;y<=(MAX_Y)-1;y++)
        {
            write_data((color>>16)&0xff); // red
            write_data((color>>8)&0xff); // green
            write_data((color)&0xff); // blue
        }
    printf("Background ready \n"); // for debug only

}
/********************************************************************************/



/********************************************************************************
                        Drawing functions
*********************************************************************************/
void drawRectangle(int x0,int y0,int x1,int y1,int color){
    window_set(x0,y0,x1,y1); // set rectangle position see B.4
    write_command(0x2C); //write pixel command
    int x,y;
    for (x=x0;x<=x1;x++)
        for (y=y0;y<=y1;y++)
        {
            write_data((color>>16)&0xff); // red
            write_data((color>>8)&0xff); // green
            write_data((color)&0xff); // blue
        }
}

void drawLine(int x0,int y0,int x1,int y1,int color)
{
    // Calculate differences between start and end point of the line
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    // Calculate increments in the direction of the line
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    // Calculate as long as end of line is not reached
    while(1){
        // Abort, if another write process is running
        if(displayWriteCommandSemaphore){
            return;
        }
        // Set Semaphore to block other write processes
        displayWriteCommandSemaphore = 1;
        // Draw Line
        window_set(x0,y0,x0,y0);        // Set window size to draw pixel in
        write_command(0x2C);            //write pixel command
        write_data((color>>16)&0xff);   // red
        write_data((color>>8)&0xff);    // green
        write_data((color)&0xff);       // blue
        // Reset Semaphore to free other write processes
        displayWriteCommandSemaphore = 0;
        if(x0 == x1 && y0 == y1) break;     // End calculation if end of line is reached
        e2 = 2 * err;                       // Calculate double of current error
        if(e2 > dy){        // If double of current error bigger than vertical difference
            err += dy;      // Raise error by vertical difference
            x0 += sx;       // Move X-Position towards X-Endpoint (1)
        }
        if(e2 < dx){        // If double of current error smaller than horizontal difference
            err += dx;      // Raise error by horizontal difference
            y0 += sy;       //Move Y-Position towards Y-Endpoint (1)
        }
    }
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
    drawLine(XaxisXend - 1, XaxisYmiddle - 1, XaxisXend - arrowLength - 1, XaxisYmiddle - arrowWidth - 1, WHITE);       // Upper upper arrow line
    drawLine(XaxisXend - 2, XaxisYmiddle - 1, XaxisXend - arrowLength - 2, XaxisYmiddle - arrowWidth - 1, WHITE);       // Lower upper arrow line
    drawLine(XaxisXend - 1, XaxisYmiddle + 2, XaxisXend - arrowLength - 1, XaxisYmiddle + arrowWidth + 2, WHITE);       // Upper lower arrow line
    drawLine(XaxisXend - 2, XaxisYmiddle + 2, XaxisXend - arrowLength - 2, XaxisYmiddle + arrowWidth + 2, WHITE);       // Lower lower arrow line
}


