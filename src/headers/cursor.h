#include <stdbool.h>
#include <stdint.h>

// Function Prototypes
void setupCursor_routine(void);                 // Setups all the cursor fucntions
void initValueDescriptions(void);               // Initialised the descriptions for the cursor values
void updateCursorValues(void);                  // Updates the displayed cursor values
void moveCursor1Position(int x,bool redraw);    // Moves cursor 1 position on screen and in the value arrays
void moveCursor2Position(int x,bool redraw);    // Moves cursor 1 position on screen and in the value arrays
