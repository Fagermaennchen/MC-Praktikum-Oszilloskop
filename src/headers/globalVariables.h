// This Module is the Header of the Global Variables
#include <stdbool.h>
#include <stdint.h>



uint32_t sysClock; // Variable for system clock



/*********************************************************************************
                                    Interrupts
*********************************************************************************/
#define cursorLoadValue 120000000    // Load Value of the cursor service routine trigger timer (1s)
#define loadValueTouch 1     // Load Value of the touch service routine trigger timer (10us)
#define loadValueDrawVoltage 12000000       // Load Value of the cursor service routine trigger timer (100ms)
extern int displayWriteCommandSemaphore;            // Semaphore to prevent two display write commands interfering
#define ADCprio 0x00
#define CURSORprio 0x20
#define CURVEprio 0x20
#define TOUCHprio 0x20



/*********************************************************************************
                                   ADC Module
*********************************************************************************/
extern int arrayPosition;   // Current Position in the Arrays
#define arrayLen 656        // Fixed lenght of Arrays, old one: 678
int resultsCH1[arrayLen];   // Array for Channel 1
int resultsCH2[arrayLen];   // Array for Channel 2
#define triggerZeroValue 2000     // Value, at which the Sine function is Zero and the derivative is positive
#define dcSignalToler 2           // Tolerance at which values are seen as the same
extern int triggerZeroReached;    // Remember, if zero has been reached
extern int triggerValue;          // Value, at which to start saving the data
extern int prevValueCH1;          // Last Values, to check if Trigger has been reached
extern int prev2ValueCH1;
extern int prev3ValueCH1;
extern int prev4ValueCH1;
extern int prev5ValueCH1;
extern int prev6ValueCH1;
extern int prev7ValueCH1;
extern int prev8ValueCH1;
extern int prev9ValueCH1;
extern int triggered;             // Remember if triggered
extern int noTrigCounter;         // Count iterations not triggered
// Conversion of units
extern int timeLenXAxis;            // Total Length of X Axis in us
//#define mintimeLenXAxis 3100;       // Min length of X Axis in us
//#define maxtimeLenXAxis 16000;      // Max length of X Axis in us
extern int ADCloadValue;               // Conversion of X Axis time into timer load value
#define tSample (timeLenXAxis*10/arrayLen) // Sample time in 0,1*us



/*********************************************************************************
                                  Cursor Module
*********************************************************************************/
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
extern int cursor1ArrPosOld;    // Previous Position of cursor 1 in the value arrays
extern int cursor2ArrPosOld;    // Previous Position of cursor 2 in the value arrays
// Cursor Line variables
#define cursorTouchWidth 15     // Wrapper around the cursor, to detect touch hits [Pixels]
extern int cursor1DispPos;      // Position of cursor 1 on the screen
extern int cursor2DispPos;      // Position of cursor 1 on the screen
extern int cursorSelected;      // Remeber if cursor is currently seclted: 0 = no Cursor, 1 = Cursor , 2 = Cursor 2



/*********************************************************************************
                                   Curve Module
*********************************************************************************/
int oldVoltageCH1[arrayLen];
int oldVoltageCH2[arrayLen];
int nextOldVoltageCH1[arrayLen];
int nextOldVoltageCH2[arrayLen];



/*********************************************************************************
                                  Display Module
*********************************************************************************/
#define LARGE_DISPLAY
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
#define MAX_X 800
#define MAX_Y 480
#define XaxisXbegin  120            // Space of 120 pixels on the left for trigger slider
#define XaxisXend  (MAX_X - 1)      // End X-axis on the total right side
#define XaxisYmiddle  219
#define YaxisYbegin  80             // 2 lines of font (40 pixels per line) above for measurement values
#define YaxisXmiddle 120            // ((YaxisEnd-YaxisBegin)/2)-YaxisBegin
#define YaxisYend  (MAX_Y - 121)    // Space of 120 pixels on bottom (3 lines) for timebase slider
#define arrowLength 20              // Length of Axis-arrows
#define arrowWidth 10               // Width of Axis-arrows
extern int colorarray[];            // same values as array for indexed colors
enum colors{BLACK=0x00000000,WHITE=0x00FFFFFF,GREY=0x00AAAAAA,RED=0x00FF0000,
            GREEN=0x0000FF00,BLUE=0x000000FF,YELLOW=0x00FFFF00};



/*********************************************************************************
                                   Font Module
*********************************************************************************/
// Font NotoMono
#define fontHeight 19   // Font Height in pixels
#define commaHeight 23    // Comma width in pixels
#define fontWidth 15    // Font width in pixels
#define fontSpace 2     // font space inbetween in pixels
#define fontArrayLen 38 // Length of font arrays
// Arrays with indivual characters
extern uint8_t font_C[fontArrayLen];
extern uint8_t font_H[fontArrayLen];
extern uint8_t font_m[fontArrayLen];
extern uint8_t font_t[fontArrayLen];
extern uint8_t font_s[fontArrayLen];
extern uint8_t font_r[fontArrayLen];
extern uint8_t font_i[fontArrayLen];
extern uint8_t font_g[fontArrayLen];
extern uint8_t font_a[fontArrayLen];
extern uint8_t font_b[fontArrayLen];
extern uint8_t font_e[fontArrayLen];
extern uint8_t font_r[fontArrayLen];
extern uint8_t font_V[fontArrayLen];
extern uint8_t font_U[fontArrayLen];
extern uint8_t font_A[fontArrayLen];
extern uint8_t font_T[fontArrayLen];
extern uint8_t font_W[fontArrayLen];
extern uint8_t font_0[fontArrayLen];
extern uint8_t font_1[fontArrayLen];
extern uint8_t font_2[fontArrayLen];
extern uint8_t font_3[fontArrayLen];
extern uint8_t font_4[fontArrayLen];
extern uint8_t font_5[fontArrayLen];
extern uint8_t font_6[fontArrayLen];
extern uint8_t font_7[fontArrayLen];
extern uint8_t font_8[fontArrayLen];
extern uint8_t font_9[fontArrayLen];
extern uint8_t font_colon[fontArrayLen];
extern uint8_t font_comma[fontArrayLen];
extern uint8_t font_delta[fontArrayLen];
extern uint8_t font_minus[fontArrayLen];
extern uint8_t font_space[fontArrayLen];



/*********************************************************************************
                                  Slider Module
*********************************************************************************/
#define sliderWidth 60              // Width of Slider-buttons
#define sliderHeight 10             // Height of Slider-buttons
extern int trigSliderPos;         // Startup y-position, x-position is fixed
extern int timeSliderPos;         // Startup x-position, y-position is fixed
extern int adcResolution;            // to make ADC resolution adjustable for timebase slider



/*********************************************************************************
                                  Touch Module
*********************************************************************************/
extern int xpos,ypos;      //Touch position variables
extern int trigSliderSelected;
extern int timeSliderSelected;





