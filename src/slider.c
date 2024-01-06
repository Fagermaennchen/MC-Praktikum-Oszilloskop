/*
 * slider.c
 *
 *  Created on: 18.12.2023
 *      Author: sfage
 */

#include "headers/globalVariables.h"
#include <stdbool.h> // type bool for giop.h
#include <stdint.h>
#include <inc/hw_memmap.h>      // GPIO_PORTX_BASE
#include "inc/hw_types.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/timer.h"
#include "headers/ADC.h"
#include "headers/cursor.h"
#include "headers/display.h"
#include "headers/font.h"
#include "headers/slider.h"

/********************************************************************************
                             Slider Initialization
*********************************************************************************/
void initTriggerAxis(void){
    // draws the trigger axis
    drawRectangle(58,80,60,359,GREY);       // Draw Trigger Axis
    drawRectangle(59-(sliderWidth/2),220-(sliderHeight/2),59+(sliderWidth/2),220+(sliderHeight/2),GREY);
    drawFont(font_t,30,370,WHITE,BLACK);
    drawFont(font_r,30+fontWidth,370,WHITE,BLACK);
    drawFont(font_i,30+2*fontWidth,370,WHITE,BLACK);
    drawFont(font_g,30+3*fontWidth,375,WHITE,BLACK);
}
/********************************************************************************/
void initTimebaseAxis(void){
    // Inizialises the timebase axis
    drawRectangle(160,399,759,401,GREY);    // Draw Timebase Axis
    drawRectangle(460-(sliderHeight/2),400-(sliderWidth/2),460+(sliderHeight/2),400+(sliderWidth/2),GREY);
    drawFont(font_t, 450, 439,WHITE,BLACK);
}
/********************************************************************************/



/********************************************************************************
                           Slider Operating Functions
*********************************************************************************/
void moveTrigSliderPosition(int y){
    // Moves the Trigger Slider

    // Y-Range: 90->359 (resolution of 270 positions)
    // Check y for upper bounds
    if(y<(YaxisYbegin+(sliderHeight/2))){
        y=(YaxisYbegin+(sliderHeight/2));
    }
    // Check y for lower bounds
    else if(y>(YaxisYend-(sliderHeight/2))){
        y=(YaxisYend-(sliderHeight/2));
    }

    //Remove sliderbutton at old position
    drawRectangle(29, trigSliderPos-(sliderHeight/2), 57, trigSliderPos+(sliderHeight/2), BLACK);
    drawRectangle(61, trigSliderPos-(sliderHeight/2), 89, trigSliderPos+(sliderHeight/2), BLACK);

    trigSliderPos = y;
    triggerValue = (430 - trigSliderPos) * 9.8;      // TrigSliderPixelRange: 80-359
    //Draw new sliderbutton
    drawRectangle(59-(sliderWidth/2), trigSliderPos-(sliderHeight/2), 59+(sliderWidth/2), trigSliderPos+(sliderHeight/2), GREY);

}
/********************************************************************************/
void moveTimeSliderPosition(int x){
    // Moves the Timebase Slider

    // Check x for left bounds
    if(x<(160+(sliderHeight/2))){
        x=(160+(sliderHeight/2));
    }
    // Check x for right bounds
    else if(x>(759-(sliderHeight/2))){
        x=(759-(sliderHeight/2));
    }


    //Remove sliderbutton at old position
    drawRectangle(timeSliderPos-(sliderHeight/2),370,timeSliderPos+(sliderWidth/2),398,BLACK);
    drawRectangle(timeSliderPos-(sliderHeight/2),402,timeSliderPos+(sliderWidth/2),430,BLACK);

    timeSliderPos = x;
    timeLenXAxis = timeSliderPos * 22;
    ADCloadValue = (timeLenXAxis*120/arrayLen)+150;         // +150 Offset to rise minimum ADC clock, preventing ripple
    TimerLoadSet(TIMER0_BASE,TIMER_A,ADCloadValue);         // refresh timer of ADC

    // adjust resolution of ADC
    changeADCclock(timeSliderPos);


    //Draw new sliderbutton
    drawRectangle(timeSliderPos-(sliderHeight/2), 400-(sliderWidth/2), timeSliderPos+(sliderHeight/2), 400+(sliderWidth/2), GREY);
    // Update cursors
    updateCursorValues();

}
/********************************************************************************/

