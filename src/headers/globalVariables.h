// This Module is the Header of the Global Variables
#include <stdbool.h>
#include <stdint.h>
// Size of Display define
#define LARGE_DISPLAY
#define MAX_X 800
#define MAX_Y 480
// Global Variables
#define Buchstabenh�he 4
#define XaxisXbegin  120
#define XaxisXend  (MAX_X - 1)
#define XaxisYmiddle  219
#define YaxisYbegin  80 //2 Zeilen oben f�r Schieberegler und Bezeichnungen (Beginn bei 81. Pixel)
#define YaxisXmiddle =120          //((YaxisEnd-YaxisBegin)/2)-YaxisBegin
#define YaxisYend  (MAX_Y - 121) //3 Zeilen unten zum Anzeigen der Werte (Ende 1 Pixel vorher)
#define arrowLength 20
#define arrowWidth 10


// Value Array
extern int arrayPosition;      // Current Position in the Arrays
#define arrayLen 10   // Fixed lenght of Arrays
int resultsCH1[arrayLen];   // Array for Channel 1
int resultsCH2[arrayLen];   // Array for Channel 2
// Triggering at CH1
#define triggerZeroValue 2000  // Value, at which the Sine function is Zero and the derivative is positive
extern int triggerZeroReached;    // Remeber, if zero has been reached
extern int triggerValue;             // Value, at which to start saving the data
extern int prevValueCH1;            // Last Value, to check if Trigger has been reached
extern int triggered;              // Remeber if triggered


// constants for display initialization
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

uint32_t sysClock; // Variable for system clock

/* some predefined basic colors to use with names */
enum colors{BLACK=0x00000000,WHITE=0x00FFFFFF,GREY=0x00AAAAAA,RED=0x00FF0000,GREEN=0x0000FF00,BLUE=0x000000FF,YELLOW=0x00FFFF00};


/* same values as array for indexed colors */
extern int colorarray[];
extern int xpos,ypos;      //Touch position variables
