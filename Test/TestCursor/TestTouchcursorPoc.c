// E// Testprogram two LCD Displays 480x272 and 800x480 RGB
// Display controller Type SSD 1963 => Solomon Systech
// Initialisation + Single Pixel and Rectangle Output
// ARM-Contoller Clock not changed ... to be tested
// Based partially of tests and sources from Ole Roenna 2020
// V0.1-V0.4 K.R. Riemschneider .. 1-4 Oct 2020

// Size of Display define
#define LARGE_DISPLAY
// #define SMALL_DISPLAY

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

int pixelPosY(int ypos){
    // Converts the Pixel position byte into the selected pixel
    return ypos*480/4095;
}

int pixelPosX(int xpos){
    // Converts the Pixel position byte into the selected pixel
    return 800-xpos*800/4095;
}

void fillRect(int x, int y, int height, int width){
    window_set(x,y,x+width,x+height); // Set Window
    write_command(0x2C); //write pixel command
    int i;
    int k;
    // Draw each Pixel
    for(i=0;i<height*width;i++)  {   // Each Entry in Byte Array

        //     Draw Color
            write_data((0x00FFFFFF>>16)&0xff); // red
            write_data((0x00FFFFFF>>8)&0xff); // green
            write_data((0x00FFFFFF)&0xff); // blue
        }
}
int main(void)
{
    int x, xpos, ypos;
    // Set Clock with PLL to run from external crystal with 120MHz
    SysCtlClockFreqSet((SYSCTL_OSC_MAIN  |
                        SYSCTL_USE_PLL   |
                        SYSCTL_XTAL_25MHZ |
                        SYSCTL_CFG_VCO_480),120000000);
    SYSCTL_RCGCGPIO_R = 0x0008; //Enable clock Port D
    init_ports_display(); // Init Port L for Display Control and Port M for Display Data
    while ((SYSCTL_PRGPIO_R & 0x08) == 0);  //GPIO Clock ready?
    GPIO_PORTD_AHB_DEN_R = 0x1F;            //PortD digital enable
    GPIO_PORTD_AHB_DIR_R = 0x0D;            //PortD Input/Output
    GPIO_PORTD_AHB_DATA_R &= 0xF7;          //Clk=0
    configure_display_controller_large();
    // set pixel by pixel to change the background colors
    int color=BLACK;
    window_set(0,0,800-1,480-1); // set single position see B.4  // to do faster ?
    write_command(0x2C); //write pixel command
    int i;
    int y;
     for (i=0;i<=(800)-1;i++)

         for (y=0;y<=(800)-1;y++)
         {
             write_data((color>>16)&0xff); // red
             write_data((color>>8)&0xff); // green
             write_data((color)&0xff); // blue
         }
     printf("Background ready \n"); // for debug only
    while (1) {
        touch_write(0xD0);                  //Touch Command XPos read
        for (x = 0; x < 10; x++);           //Busy wait
        xpos = pixelPosX(touch_read());                //xpos value read ( 0......4095 )
    //    printf("xpox= %5d ", xpos);
        touch_write(0x90);                  //Touch Command YPos read
        for (x = 0; x < 10; x++);           //Busy wait
        ypos = pixelPosY(touch_read());                //ypos value read ( 0.....4095 )
   //     printf("ypox= %5d\n", ypos);
        if(xpos != 800 and ){
            fillRect(xpos,ypos,10,10);
        }
    }
}
