#include <stdint.h>
#include <stdbool.h>

// Font NotoMono
#define fontHeight 19   // Font Height in pixels
#define fontWidth 15    // Font width in pixels
#define fontSpace 2     // font space inbetween in pixels
#define fontArrayLen 38 // Length of fotn arrays

// Arrays with indivual characters
extern uint8_t font_C[fontArrayLen];
extern uint8_t font_H[fontArrayLen];
extern uint8_t font_m[fontArrayLen];
extern uint8_t font_t[fontArrayLen];
extern uint8_t font_s[fontArrayLen];
extern uint8_t font_r[fontArrayLen];
extern uint8_t font_i[fontArrayLen];
extern uint8_t font_g[fontArrayLen];
extern uint8_t font_V[fontArrayLen];
extern uint8_t font_U[fontArrayLen];
extern uint8_t font_A[fontArrayLen];
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

// Functions to display font on the display
void drawFont(const uint8_t character[],int x, int y,int color,int backdrop); // Draws a comma
void drawComma(int x, int y,int color,int backdrop); // Draws a comma
int* numbtofont(int number);    // Maps a font array to a one digit number
void drawMilliVolt(int voltage_mv,int x, int y,int foregroundColor,int backgroundColor,bool includeNegatives);    // Draws a 4 digit voltage in mV (XXX,1 mV) at postitions x and y
void drawMikroSeconds(int time_us,int x, int y,int foregroundColor,int backgroundColor);    // Draws a 4 digit time in us (XXX,1 mV) at postitions x and y
void drawText(void); // Draws the Channal 1 Line
void drawLogo(void); // Draws the Haw Logo

