# include <stdbool.h>

//Cursor Value
#define xStartCHX  170          // x Position of CHX Label [Pixels]
#define xStartDelta  237        // x Position of Delta Label [Pixels]
#define xStartDeltaVolVal  240  // x Position of Delta Voltage Values [Pixels]
#define xStartVol1  370         // x Position of Cursor 1 Voltages [Pixels]
#define xStartVol2  500         // x Position of Cursor 2 Voltages [Pixels]
#define xStartDeltaT  635       // x Position of Delta t Label[Pixels]
#define xStartValTime  665      // x Position of Delta t Values [Pixels]
#define yStartCHfirstLine 10    // y Position of Channel 1 Data (first line) [Pixels]
#define yStartCHsecondLine 40   // y Position of Channel 2 Data (second line) [Pixels]
extern int cursor1ArrPos;       // Position of cursor 1 in the value arrays
extern int cursor2ArrPos;       // Position of cursor 2 in the value arrays

// Cursor Line variables
#define cursorTouchWidth 15     // Wrapper around the cursor, to detect touch hits [Pixels]
extern int cursor1DispPos;       // Position of cursor 1 on the screen
extern int cursor2DispPos;       // Position of cursor 1 on the screen
extern int cursorSelected;     // Remeber if cursor is currently seclted: 0 = no Cursor, 1 = Cursor , 2 = Cursor 2
// Function Prototypes
void setupCursor(void);             // Setups all the cursor fucntions
void startCursorValueUpdates(void);             // Starts the cursor Values dispaly Function
void initValueDescriptions(void);   // Initialised the descriptions for the cursor values
void updateCursorValues(void);            // Updates the displayed cursor values
void moveCursor1Position(int x,bool redraw);      // Moves cursor 1 position on screen and in the value arrays
void moveCursor2Position(int x,bool redraw);      // Moves cursor 1 position on screen and in the value arrays
