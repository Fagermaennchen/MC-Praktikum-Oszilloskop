
/********************************************************************************
     Elementary output functions  => speed optimized as inline
*********************************************************************************/
inline void write_command(unsigned char command);
/********************************************************************************/
inline void write_data(unsigned char data);
/********************************************************************************/
inline void window_set(int min_x,int min_y,int max_x,int max_y);
/*********************************************************************************
                        Display configuration
*********************************************************************************/
void init_ports_display(void);
/********************************************************************************/
void configure_display_controller_large (void);
/********************************************************************************/
void initDisplay(void);
/*********************************************************************************


********************************************************************************/
int pixelPosY(int ypos);// Converts the Pixel position byte into the selected pixel
int pixelPosX(int xpos);// Converts the Pixel position byte into the selected pixel
/********************************************************************************
                        Drawing functions
*********************************************************************************/
void drawRectangle(int x0,int y0,int x1,int y1,enum colors color);
void drawLine(int x0,int y0,int x1,int y1,enum colors color);


