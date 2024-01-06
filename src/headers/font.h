#include <stdint.h>
#include <stdbool.h>


// Functions to display font on the display
void drawFont(const uint8_t character[],int x, int y,int color,int backdrop); // Draws a comma
void drawComma(int x, int y,int color,int backdrop); // Draws a comma
int* numbtofont(int number);    // Maps a font array to a one digit number
void drawMilliVolt(int voltage_mv,int x, int y,int foregroundColor,int backgroundColor,bool includeNegatives);    // Draws a 4 digit voltage in mV (XXX,1 mV) at postitions x and y
void drawDeltaVolt(int voltage_mv,int x, int y,int foregroundColor,int backgroundColor);    // Draws an absolute 4 digit voltage in mV or V (XXX,X mV or X,XXX V) at postitions x and y
void drawMilliSeconds(int time_us,int x, int y,int foregroundColor,int backgroundColor);    // Draws a 4 digit time in or ms or us (XX,XX ms or X,XXX ms or X,XXX us)  at postitions x and y
//void drawText(void); // Draws the Channal 1 Line
void drawLogo(void); // Draws the Haw Logo

