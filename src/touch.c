
#include "headers/touch.h"
#include "headers/cursor.h"
#include "headers/slider.h"
#include "headers/ADC.h"
#include "headers/globalVariables.h"
#include "inc/hw_types.h"
#include "inc/tm4c1294ncpdt.h"
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>      // GPIO_PORTX_BASE
#include "driverlib/timer.h"


int trigSliderSelected = 0;      // Startup: not selected
int timeSliderSelected = 0;      // Startup: not selected
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
unsigned int touch_read(void)
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



void processTouch(void){
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    //read Touch values
    touch_write(0xD0);                  //Touch Command XPos read
    int x;
    for (x = 0; x < 10; x++);          //Busy wait, 10 works well also, before: 100
    xpos = pixelPosX(touch_read());     //xpos value read ( 0......800 )
    touch_write(0x90);                  //Touch Command YPos read
    for (x = 0; x < 10; x++);          //Busy wait, 10 works well also, before: 100
    ypos = pixelPosY(touch_read());     //ypos value read ( 0.....480 )
    // No touch: xpos=800 -> deselect all touch buttons
    if(xpos==800){
        // Redo selection
        cursorSelected = 0;
        trigSliderSelected = 0;
        timeSliderSelected = 0;
    }
    /****** Cursor 1 *******/
    else if(cursorSelected == 1){    // When selected: Move to new position
        moveCursor1Position(xpos,true);
        updateCursorValues();
    }   // Check for selection if not selected
    // Check for selection if not selected
    else if((cursor1DispPos-cursorTouchWidth)<xpos && xpos<(cursor1DispPos+cursorTouchWidth) && ypos>YaxisYbegin && ypos<YaxisYend && cursorSelected == 0){ // When not selected, but hit: Inform about hit

        cursorSelected = 1;
    }

    /****** Cursor 2 *******/
    else if(cursorSelected == 2){    // When selected: Move to new position
        moveCursor2Position(xpos,true);
        updateCursorValues();
    }
    // Check for selection if not selected
    else if((cursor2DispPos-cursorTouchWidth)<xpos && xpos<(cursor2DispPos+cursorTouchWidth) && ypos>YaxisYbegin && ypos<YaxisYend && cursorSelected == 0 ){ // When not selected, but hit: Inform about hit
        cursorSelected = 2;
    }

    /****** Triggerslider *******/
    else if(trigSliderSelected == 1){
        moveTrigSliderPosition(ypos);
    }
    else if((xpos>19)&&(xpos<99)&&(ypos>80)&&(ypos<360)&&(trigSliderSelected==0)){
        trigSliderSelected = 1;
    }

    /****** Timeslider *******/
    else if(timeSliderSelected == 1){
        moveTimeSliderPosition(xpos);
    }
    else if((xpos>160)&&(xpos<759)&&(ypos>360)&&(ypos<440)&&(timeSliderSelected==0)){
        timeSliderSelected = 1;
    }
}

void setupTouchHandler(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)){}
    TimerConfigure(TIMER3_BASE, TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER3_BASE, TIMER_A, loadValueTouch);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER3_BASE, TIMER_A, processTouch);
    IntPrioritySet(INT_TIMER3A, 0x20); // Adjust priority as needed
}
