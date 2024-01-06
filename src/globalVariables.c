// This module sets the values of the global variables
#include "headers/globalVariables.h"


/*********************************************************************************
                                    Interrupts
*********************************************************************************/
displayWriteCommandSemaphore = 0;            // Semaphore to prevent two display write commands interfering



/*********************************************************************************
                                   ADC Module
*********************************************************************************/
arrayPosition = 0;      // Current Position in the Arrays
// Triggering at CH1
triggerZeroReached = 0;    // Remember, if zero has been reached
triggerValue = 2058;       // Value, at which to start saving the data, calculated value for middle of trigSlider at Y=220
prevValueCH1 = 9999;       // Last Values, to check if Trigger has been reached
prev2ValueCH1 = 9999;
prev3ValueCH1 = 9999;
prev4ValueCH1 = 9999;
prev5ValueCH1 = 9999;
prev6ValueCH1 = 9999;
prev7ValueCH1 = 9999;
prev8ValueCH1 = 9999;
prev9ValueCH1 = 9999;
triggered = 0;             // Remeber if triggered
noTrigCounter = 0;         // Count iterations not triggered
timeLenXAxis = 10120;       // initial TotalLength of X Axis in us (460*22)-->middlePixelTimebase*factor
ADCloadValue = (10120*120/arrayLen);



/*********************************************************************************
                                  Cursor Module
*********************************************************************************/
cursor1ArrPos = 200;        // Cursor one start position in Array
cursor2ArrPos = 400;        // Cursor two start position in Array
cursor1DispPos = 221;       // Cursor one start position on Screen
cursor2DispPos = 421;       // Cursor two start position on Screen
cursorSelected = 0;         // Remember if cursor is currently selected



/*********************************************************************************
                                   Curve Module
*********************************************************************************/




/*********************************************************************************
                                  Display Module
*********************************************************************************/
colorarray[]={0x00000000,0x00FFFFFF,0x00AAAAAA,0x00FF0000,0x0000FF00,0x000000FF,0x00FFFF00};



/*********************************************************************************
                                   Font Module
*********************************************************************************/



/*********************************************************************************
                                  Slider Module
*********************************************************************************/
trigSliderPos = 220;        // Startup y-position, x-position is fixed
timeSliderPos = 460;        // Startup x-position, y-position is fixed
adcResolution = 12;         // Initially variable value, now fixed value

/*********************************************************************************
                                  Touch Module
*********************************************************************************/
xpos = 0;
ypos = 0;
trigSliderSelected = 0;      // Startup: not selected
timeSliderSelected = 0;      // Startup: not selected


