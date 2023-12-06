// This Module holds the Global Variables
#include <stdbool.h>
// Value Array
int arrayPosition = 0;      // Current Position in the Arrays
const int arrayLen = 10;   // Fixed lenght of Arrays
int resultsCH1[arrayLen];   // Array for Channel 1
int resultsCH2[arrayLen];   // Array for Channel 2
// Triggering at CH1
int triggerZeroValue = 2000;         // Value, at which the Sine function is Zero and the derivative is positive
bool triggerZeroReached = false;    // Remeber, if zero has been reached
int triggerValue = 2500;             // Value, at which to start saving the data
int prevValueCH1 = 9999;            // Last Value, to check if Trigger has been reached
bool triggered = false;              // Remeber if triggered

