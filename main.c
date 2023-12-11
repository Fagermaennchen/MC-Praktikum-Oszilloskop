// Testprogram two LCD Displays 480x272 and 800x480 RGB
// Display controller Type SSD 1963 => Solomon Systech
// Initialisation + Single Pixel and Rectangle Output
// ARM-Contoller Clock not changed ... to be tested
// Based partially of tests and sources from Ole Roenna 2020
// V0.1-V0.4 K.R. Riemschneider .. 1-4 Oct 2020

#include "header.h"


void drawFont(const uint8_t character[], int x, int y, int color,int backdrop);


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
   for (x=0;x<=(MAX_X)-1;x++)
        for (y=0;y<=(MAX_Y)-1;y++)
        {
            write_data((color>>16)&0xff); // red
            write_data((color>>8)&0xff); // green
            write_data((color)&0xff); // blue
        }
    printf("Background ready \n"); // for debug only

}
/*********************************************************************************
                        Touch configuration
*********************************************************************************/
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
/********************************************************************************/
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
/********************************************************************************
                        Drawing functions
*********************************************************************************/
void drawRectangle(x0,y0,x1,y1,color){
    window_set(x0,y0,x1,y1); // set rectangle position see B.4
    write_command(0x2C); //write pixel command
    for (x=x0;x<=x1;x++)
        for (y=y0;y<=y1;y++)
        {
            write_data((color>>16)&0xff); // red
            write_data((color>>8)&0xff); // green
            write_data((color)&0xff); // blue
        }
}
/********************************************************************************/
void drawLine(x0,y0,x1,y1,color)
{
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
    for (x = 0; x < 10; x++);           //Busy wait
    xpos = touch_read();                //xpos value read ( 0......4095 )
    printf("xpos= %5d ", xpos);
    touch_write(0x90);                  //Touch Command YPos read
    for (x = 0; x < 10; x++);           //Busy wait
    ypos = touch_read();                //ypos value read ( 0.....4095 )
    printf("ypos= %5d\n", ypos);
}
/********************************************************************************/
void refreshTimebaseButton(void){
    if(((xpos>=205)&&(xpos<=3379)) && ((ypos>=3072)&&(ypos<=3755))){
        //Upper side Button
        printf("Printing new Button\n");
        drawLine(100,100,400,400,WHITE);
        //drawRectangle(100,100,200,400,BLACK);
        //Lower side Button
    }
}
/********************************************************************************/
void initTimebaseAxis(void){
    drawRectangle(160,398,759,402,GREY);
    drawRectangle(450,370,470,430,GREY);
}
/********************************************************************************/
void drawFont(const uint8_t character[], int x, int y, int color,int backdrop){
    window_set(x,y,x+fontWidth,x+fontHeight); // Set Window
    write_command(0x2C); //write pixel command
    int i;
    int k;
    // Draw each Pixel
    for(i=0;i<fontArrayLen;i++)     // Each Entry in Byte Array
        for(k=0;k<8;k++){
        //     Draw Color if 1
            if(character[i] & 0x80 >> k){
                write_data((color>>16)&0xff); // red
                write_data((color>>8)&0xff); // green
                write_data((color)&0xff); // blue
            }
            // Else Draw Backdrop
            else{
                write_data((backdrop>>16)&0xff); // red
                write_data((backdrop>>8)&0xff); // green
                write_data((backdrop)&0xff); // blue
            }
        }
}
/********************************************************************************/
void drawText(void){
    //draw first Font line
    drawFont(font_C, xStartCHX, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_1, xStartCHX+2*fontWidth+2*fontSpace, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+3*fontSpace, yStartCHfirstLine, WHITE, BLACK);
    //draw second Font line
    drawFont(font_C, xStartCHX, yStartCHsecondLine, WHITE, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHsecondLine, WHITE, BLACK);
    drawFont(font_2, xStartCHX+2*fontWidth+2*fontSpace, yStartCHsecondLine, WHITE, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+3*fontSpace, yStartCHsecondLine, WHITE, BLACK);

    drawFont(font_C, 450, 439,WHITE,BLACK);
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
   drawText();
   initTriggerAxis();
   initTimebaseAxis();

   //Initialize Touch
   SYSCTL_RCGCGPIO_R = 0x0008; //Enable clock Port D
   while ((SYSCTL_PRGPIO_R & 0x08) == 0);  //GPIO Clock ready?
   GPIO_PORTD_AHB_DEN_R = 0x1F;            //PortD digital enable
   GPIO_PORTD_AHB_DIR_R = 0x0D;            //PortD Input/Output
   GPIO_PORTD_AHB_DATA_R &= 0xF7;          //Clk=0

   // Start endless loop
    while(1)
    {
        readTouchValues();
        refreshTimebaseButton();


    }
}

