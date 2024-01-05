// This Module holds the Global Variables
#include <src/headers/globalVariables.h>


// Value Array
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
// Conversion of units
timeLenXAxis = 10120;       // initial TotalLength of X Axis in us (460*22)-->middlePixelTimebase*factor
// Intterrupts
displayWriteCommandSemaphore = 0;            // Semaphore to prevent two display write commands interfering
/* some predefined basic colors to use with names */
colorarray[]={0x00000000,0x00FFFFFF,0x00AAAAAA,0x00FF0000,0x0000FF00,0x000000FF,0x00FFFF00};
xpos = 0;
ypos = 0;
loadValueADC = (10120*120/arrayLen);
adcResolution = 12;

