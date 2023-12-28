

/********************************************************************************
     Elementary output functions  => speed optimized as inline
*********************************************************************************/
inline void write_command(unsigned char command);
/********************************************************************************/
inline void write_data(unsigned char data);
/********************************************************************************/
inline void window_set(min_x, min_y, max_x, max_y);
/*********************************************************************************
                        Display configuration
*********************************************************************************/
void init_ports_display(void);
/********************************************************************************/
void configure_display_controller_large (void);
/********************************************************************************/
void initDisplay(void);
/*********************************************************************************
                        Touch configuration
*********************************************************************************/
void touch_write(unsigned char value);
/********************************************************************************/
int pixelPosY(int ypos);// Converts the Pixel position byte into the selected pixel
int pixelPosX(int xpos);// Converts the Pixel position byte into the selected pixel
unsigned int touch_read();
/********************************************************************************
                        Drawing functions
*********************************************************************************/
void drawRectangle(x0,y0,x1,y1,color);
void drawLine(x0,y0,x1,y1,color);
void moveTrigSliderPosition(int y);
void readTouchValues(void);

