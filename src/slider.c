/*
 * slider.c
 *
 *  Created on: 18.12.2023
 *      Author: sfage
 */
#include <stdint.h>
#include <stdbool.h> // type bool for giop.h
#include <src/headers/globalVariables.h>
#include "inc/hw_types.h"
#include "inc/tm4c1294ncpdt.h"
#include "headers/slider.h"
#include "headers/display.h"
#include "driverlib/timer.h"
#include "headers/ADC.h"
#include <inc/hw_memmap.h>      // GPIO_PORTX_BASE


extern int trigSliderPos = 220;         // Startup y-position, x-position is fixed
extern int timeSliderPos = 460;         // Startup x-position, y-position is fixed


void moveTrigSliderPosition(int y){
    // Moves the Trigger Slider

    // Y-Range: 90->359 (resolution of 270 positions)
    // Check y for upper bounds
    if(y<(YaxisYbegin+10)){
        y=(YaxisYbegin+10);
    }
    // Check y for lower bounds
    else if(y>(YaxisYend-10)){
        y=(YaxisYend-10);
    }

    //Remove sliderbutton at old position
    drawRectangle(29, trigSliderPos-(sliderHeight/2), 57, trigSliderPos+(sliderHeight/2), BLACK);
    drawRectangle(61, trigSliderPos-(sliderHeight/2), 89, trigSliderPos+(sliderHeight/2), BLACK);

    trigSliderPos = y;
    triggerValue = (430 - trigSliderPos) * 9.8;      // TrigSliderPixelRange: 80-359
    //Draw new sliderbutton
    drawRectangle(59-(sliderWidth/2), trigSliderPos-(sliderHeight/2), 59+(sliderWidth/2), trigSliderPos+(sliderHeight/2), GREY);

}

void moveTimeSliderPosition(int x){
    // Moves the Timebase Slider

    // Check x for left bounds
    if(x<(160+10)){
        x=(160+10);
    }
    // Check x for right bounds
    else if(x>(759-10)){
        x=(759-10);
    }


    //Remove sliderbutton at old position
    drawRectangle(timeSliderPos-(sliderHeight/2),370,timeSliderPos+(sliderWidth/2),398,BLACK);
    drawRectangle(timeSliderPos-(sliderHeight/2),402,timeSliderPos+(sliderWidth/2),430,BLACK);

    timeSliderPos = x;
    timeLenXAxis = timeSliderPos * 22;
    loadValue = (timeLenXAxis*120/arrayLen);
    TimerLoadSet(TIMER0_BASE,TIMER_A,loadValue);        // refresh timer

    // adjust resolution of ADC
    changeADCclock(timeSliderPos);


    //Draw new sliderbutton
    drawRectangle(timeSliderPos-(sliderHeight/2), 400-(sliderWidth/2), timeSliderPos+(sliderHeight/2), 400+(sliderWidth/2), GREY);
    // Update cursors
    updateCursorValues();

}


