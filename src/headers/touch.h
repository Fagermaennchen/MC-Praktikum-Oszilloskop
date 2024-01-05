/*
 * touch.h
 *
 *  Created on: 05.01.2024
 *      Author: sfage
 */
void initTouch(void);
void touch_write(unsigned char value);
unsigned int  touch_read(void);
void processTouch(void);
void setupProcessTouch_routine(void);
int pixelPosY(int ypos);// Converts the Pixel position byte into the selected pixel
int pixelPosX(int xpos);// Converts the Pixel position byte into the selected pixel
