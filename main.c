// Testprogram two LCD Displays 480x272 and 800x480 RGB
// Display controller Type SSD 1963 => Solomon Systech
// Initialisation + Single Pixel and Rectangle Output
// ARM-Contoller Clock not changed ... to be tested
// Based partially of tests and sources from Ole Roenna 2020
// V0.1-V0.4 K.R. Riemschneider .. 1-4 Oct 2020

// Size of Display define
#define LARGE_DISPLAY
#define MAX_X 800
#define MAX_Y 480

// Global Variables
int Buchstabenhöhe = 40;
int XaxisBegin = 200;           //Beginn bei 201. Pixel
int XaxisEnd = MAX_X - 1;
int YaxisBegin = 80;            //2 Zeilen oben für Schieberegler und Bezeichnungen (Beginn bei 81. Pixel)
int YaxisEnd = MAX_Y - 121;     //3 Zeilen unten zum Anzeigen der Werte (Ende 1 Pixel vorher)
int YaxisMiddle = 219;          //((YaxisEnd-YaxisBegin)/2)-YaxisBegin

#include <stdint.h>
#include <stdbool.h> // type bool for giop.h
#include "inc/hw_types.h"
#include "inc/tm4c1294ncpdt.h"
#include <stdio.h>   // Debug only
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>     // GPIO_PIN_X
#include <inc/hw_memmap.h>      // GPIO_PORTX_BASE

// constants for display initialization
#define RST 0x10
#define INITIAL_STATE (0x1F)
#define SOFTWARE_RESET (0x01)
#define SET_PLL_MN (0xE2)
#define START_PLL (0xE0)
#define LOCK_PLL (0xE0)  // same as START_PLL
#define SET_LSHIFT (0xE6)
#define SET_LCD_MODE (0xB0)
#define SET_HORI_PERIOD (0xB4)
#define SET_VERT_PERIOD (0xB6)
#define SET_ADRESS_MODE (0x36)
#define SET_PIXEL_DATA_FORMAT (0xF0)
#define SET_DISPLAY_ON (0x29)
#define SET_DISPLAY_OFF (0x29) // not tested ??
uint32_t sysClock; // Variable for system clock
/* some predefined basic colors to use with names */
enum colors{BLACK=0x00000000,WHITE=0x00FFFFFF,GREY=0x00AAAAAA,RED=0x00FF0000,GREEN=0x0000FF00,BLUE=0x000000FF,YELLOW=0x00FFFF00};
/* same values as array for indexed colors */
int colorarray[]={0x00000000,0x00FFFFFF,0x00AAAAAA,0x00FF0000,0x0000FF00,0x000000FF,0x00FFFF00};

int i,j,x,y;


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
inline void window_set(min_x, min_y, max_x, max_y)
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
void configure_display_controller_small (void) // 480 x 272 pixel
{
    GPIO_PORTL_DATA_R = INITIAL_STATE;      // Initial state of display control signals
    GPIO_PORTL_DATA_R &= ~RST;              // Display hardware reset prepare, manual p. 79
    SysCtlDelay(10000);                     // wait >1 ms
    GPIO_PORTL_DATA_R |= RST;               // Display hardware reset trigger
    SysCtlDelay(10000);                     // wait >1 ms

    write_command(SOFTWARE_RESET);          // Display Software reset, manual p. 24
    SysCtlDelay(100000);                    // wait >5 ms

    write_command(SET_PLL_MN);              // Set PLL Freq of display controller to 100MHz
    write_data(0x1D);                       // see manual p. 74
    write_data(0x02);                       //
    write_data(0x04);                       //

    write_command(START_PLL);               // Start PLL, see manual p. 73
    write_data(0x01);                       //
    SysCtlDelay(10000);                     // wait >1 ms

    write_command(LOCK_PLL);               // Lock PLL, see manual p. 73/74
    write_data(0x03);                       //
    SysCtlDelay(10000);                     // wait >1 ms

    write_command(SOFTWARE_RESET);          // Software reset, manual p. 24
    SysCtlDelay(100000);                    // wait > 10 ms

    write_command(SET_LSHIFT);              // Pixel clock frequency
    write_data(0x01);                       // set pixel Clock 9MHz, see manual p. 76
    write_data(0x70);                       //
    write_data(0xA3);                       //

    write_command(SET_LCD_MODE);            // Set LCD Panel mode, see manual p. 76
    write_data(0x20);                       // TFT panel 24bit
    write_data(0x00);                       // TFT mode
    write_data(0x01);                       // Set horizontal size = 480-1 (high byte)
    write_data(0xDF);                       // Set horizontal size = 480-1 (low byte)
    write_data(0x01);                       // Set vertical size = 272-1  (high byte)
    write_data(0x0F);                       // Set vertical size = 272-1 (low byte)
    write_data(0x00);                       // Even line RGB sequence / Odd line RGB sequence RGB

    write_command(SET_HORI_PERIOD);         // Set horizontal periods, manual  p. 47
    write_data(0x02);                       // Horizontal total period (display + non-displayed) in pixels (high byte)
    write_data(0x13);                       // as above (low byte) = total 531 pixels
    write_data(0x00);                       // Non-displayed period between the start of the horizontal sync (LLINE) signal
                                            // and the first display data  (high byte)
    write_data(0x2B);                       // as above (low byte) = total sync pulse start position  is 43 pixels
    write_data(0x0A);                       // Set the horizontal sync width = 10 pixels
    write_data(0x00);                       // Set horizontal sync pulse start (high byte)
    write_data(0x08);                       // as above (low byte) = total sync pulse start position is 8 pixels
    write_data(0x00);                       //

    write_command(SET_VERT_PERIOD);         // Set vertical periods, manual  p. 49
    write_data(0x01);                       // Vertical total period (display + non-displayed) in lines (high byte)
    write_data(0x20);                       // as above (low byte) = total 288 lines
    write_data(0x00);                       //
    write_data(0x0C);                       // The non-displayed period in lines between the start of the frame and the first
                                            // display data in line = 12 pixels.
    write_data(0x0A);                       // Set the horizontal sync width = 10 pixels
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

/********************************************************************************/
void drawSquares(void){


    enum colors color;   // see global definition
    printf("Write rectangles\n"); // for debug only
    for (x=0;x<=(MAX_X)-1-20;x=x+40)
        for (y=0;y<=(MAX_Y)-1-20;y=y+40)
         {
            color=colorarray[(j)%7]; j++; // change color
            window_set(x,y,x+20,y+20); // set rectangle position see B.4
            write_command(0x2C); //write pixel command
            for(i=0;i<(40*40);i++) // set pixels
            {
                write_data((color>>16)&0xff); // red
                write_data((color>>8)&0xff); // green
                write_data((color)&0xff); // blue
            }
         }
}
/********************************************************************************/
void drawAxes(void){
    int x,y,z,x_end,y_end,a,b, ya;
    enum colors color;
    color = WHITE;
    //Write X-Axis
    window_set(XaxisBegin,YaxisMiddle,XaxisEnd,YaxisMiddle+1);  //Mitte des Display in X-Richtung (X-Anfang, Y-Anfang, X-Ende, Y-Ende)
    write_command(0x2C); //write pixel command
    for (x=0;x<=(MAX_X)-1;x++)  //von 0 bis MAX_X weil Achse über gesamte Breite lang
        for (y=0;y<=1;y++)      //Von 0 bis 1 weil Achse nur 2+ Pixel breit
        {
            write_data((color>>16)&0xff); // red
            write_data((color>>8)&0xff); // green
            write_data((color)&0xff); // blue
        }
    //Write x-Axis Arrow

    //Write Y-Axis
    window_set(XaxisBegin,YaxisBegin,XaxisBegin+1,YaxisEnd);  //(X-Anfang, Y-Anfang, X-Ende, Y-Ende)
    write_command(0x2C); //write pixel command
    for (x=0;x<=1;x++)              //Sweep Breite der Y-Achse
        for (y=0;y<=(MAX_Y)-1;y++)  //Sweep Länge der Y-Achse
        {
            write_data((color>>16)&0xff); // red
            write_data((color>>8)&0xff); // green
            write_data((color)&0xff); // blue
        }
    //Write X-Axis Arrow
    for(y=0; y<=1; y++){    //Dicke des Pfeils = 2
        for(x=0,x_end=12;x<=x_end;){         //Sweep X
            for(ya=13+y; ya>=1; ya--){       //Sweep Y
                window_set(187+x, 80+ya, 187+x, 80+ya);
                write_command(0x2C); //write pixel command
                write_data((color>>16)&0xff); // red
                write_data((color>>8)&0xff); // green
                write_data((color)&0xff); // blue
                x++;
            }
        }
    }
    for(y=0; y<=1; y++){    //Dicke des Pfeils = 2
        for(x=0,x_end=12;x<=x_end;){         //Sweep X
            for(ya=1+y; ya<=14; ya++){       //Sweep Y
                window_set(202+x, 80+ya, 202+x, 80+ya);
                write_command(0x2C); //write pixel command
                write_data((color>>16)&0xff); // red
                write_data((color>>8)&0xff); // green
                write_data((color)&0xff); // blue
                x++;
            }
        }
    }



    printf("Axes ready\n");
}
/********************************************************************************/




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// Main-Function /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
   sysClock = SysCtlClockFreqSet(   SYSCTL_OSC_INT | SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480,120000000); // Set system frequency to 120 MHz
   init_ports_display(); // Init Port L for Display Control and Port M for Display Data
   initDisplay();
   drawAxes();
    // Start endless loop
   j = 0;

    while(1)
    {

    }
}
