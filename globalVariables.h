// Size of Display define
#define LARGE_DISPLAY
#define MAX_X 800
#define MAX_Y 480

// Global Variables
int Buchstabenhöhe = 40;

int XaxisXbegin = 120;
int XaxisXend = MAX_X - 1;
int XaxisYmiddle = 219;

int YaxisYbegin = 80; //2 Zeilen oben für Schieberegler und Bezeichnungen (Beginn bei 81. Pixel)
int YaxisXmiddle = 120;          //((YaxisEnd-YaxisBegin)/2)-YaxisBegin
int YaxisYend = MAX_Y - 121; //3 Zeilen unten zum Anzeigen der Werte (Ende 1 Pixel vorher)

int arrowLength = 20;
int arrowWidth = 10;


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
int colorarray[]={0x00000000,0x00FFFFFF,0x00AAAAAA,0x00FF0000,0x0000FF00,0x000000FF,0x00FFFF00};

int i,x,y;            //Counter Variables
int xpos,ypos;      //Touch position variables

