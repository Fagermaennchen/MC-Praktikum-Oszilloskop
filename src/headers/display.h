#include <stdbool.h>
#include <stdint.h>

inline void write_command(unsigned char command);
inline void write_data(unsigned char data);
inline void window_set(int min_x,int min_y,int max_x,int max_y);
void initPortsDisplay(void);
void configureDisplayController (void);
void initDisplay(void);
int pixelPosY(int ypos);// Converts the Pixel position byte into the selected pixel
int pixelPosX(int xpos);// Converts the Pixel position byte into the selected pixel
void drawRectangle(int x0,int y0,int x1,int y1,int color);
void drawLine(int x0,int y0,int x1,int y1,int color);
void drawAxes(void);                        // Draws the axis of the coordinate system


