
#include "headers/font.h"
#include "headers/globalVariables.h"




extern uint8_t font_C[] = {
    0x00, 0x00,  //.............
    0x07, 0xf0,  //.....%%%%%%%.
    0x0f, 0xf8,  //....%%%%%%%%%
    0x3c, 0x10,  //..%%%%.....%.
    0x30, 0x00,  //..%%.........
    0x70, 0x00,  //.%%%.........
    0x60, 0x00,  //.%%..........
    0x60, 0x00,  //.%%..........
    0x60, 0x00,  //.%%..........
    0x60, 0x00,  //.%%..........
    0x60, 0x00,  //.%%..........
    0x60, 0x00,  //.%%..........
    0x60, 0x00,  //.%%..........
    0x70, 0x00,  //.%%%.........
    0x30, 0x00,  //..%%.........
    0x38, 0x00,  //..%%%........
    0x1f, 0xf0,  //...%%%%%%%%%.
    0x07, 0xf0,  //.....%%%%%%%.
    0x00, 0x00,  //.............

};
extern uint8_t font_H[] = {
     0x00, 0x00,  //............
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x7f, 0xf0,  //.%%%%%%%%%%%
     0x7f, 0xf0,  //.%%%%%%%%%%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x60, 0x30,  //.%%.......%%
     0x00, 0x00,  //............
};
extern uint8_t font_m[] = {
     0x00, 0x00,  //.............
     0x00, 0x00,  //.............
     0x00, 0x00,  //.............
     0x00, 0x00,  //.............
     0x00, 0x00,  //.............
     0xdc, 0xe0,  //%%.%%%..%%%..
     0xff, 0xf0,  //%%%%%%%%%%%%.
     0xe7, 0x30,  //%%%..%%%..%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0xc6, 0x30,  //%%...%%...%%.
     0x00, 0x00,  //.............
};

extern uint8_t font_V[] = {
     0x00, 0x00,  //..............
     0x60, 0x0c,  //.%%.........%%
     0x60, 0x1c,  //.%%........%%%
     0x60, 0x18,  //.%%........%%.
     0x30, 0x18,  //..%%.......%%.
     0x30, 0x30,  //..%%......%%..
     0x30, 0x30,  //..%%......%%..
     0x18, 0x30,  //...%%.....%%..
     0x18, 0x60,  //...%%....%%...
     0x18, 0x60,  //...%%....%%...
     0x0c, 0x60,  //....%%...%%...
     0x0c, 0xc0,  //....%%..%%....
     0x0c, 0xc0,  //....%%..%%....
     0x06, 0xc0,  //.....%%.%%....
     0x07, 0x80,  //.....%%%%.....
     0x07, 0x80,  //.....%%%%.....
     0x03, 0x80,  //......%%%.....
     0x03, 0x00,  //......%%......
     0x00, 0x00,  //..............
};

extern uint8_t font_0[] = {
     0x00, 0x00,  //.............
     0x0f, 0x80,  //....%%%%%....
     0x3f, 0xc0,  //..%%%%%%%%...
     0x70, 0xe0,  //.%%%....%%%..
     0x60, 0x70,  //.%%......%%%.
     0xe0, 0x30,  //%%%.......%%.
     0xe0, 0x30,  //%%%.......%%.
     0xc0, 0x30,  //%%........%%.
     0xc0, 0x30,  //%%........%%.
     0xc0, 0x30,  //%%........%%.
     0xc0, 0x30,  //%%........%%.
     0xc0, 0x30,  //%%........%%.
     0xe0, 0x30,  //%%%.......%%.
     0xe0, 0x30,  //%%%.......%%.
     0x60, 0x60,  //.%%......%%..
     0x70, 0xe0,  //.%%%....%%%..
     0x3f, 0xc0,  //..%%%%%%%%...
     0x0f, 0x80,  //....%%%%%....
     0x00, 0x00,  //.............

};


extern uint8_t font_1[] = {
    0x00, 0x00,  //.......
    0x0e, 0x00,  //....%%%
    0x1e, 0x00,  //...%%%%
    0x3e, 0x00,  //..%%%%%
    0x66, 0x00,  //.%%..%%
    0x46, 0x00,  //.%...%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06,  0x00, //.....%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06, 0x00,  //.....%%
    0x06,  0x00, //.....%%
    0x00, 0x00,  //.......
};

extern uint8_t font_2[] = {
    0x00, 0x00,  //............
    0x1f, 0x00,  //...%%%%%....
    0x3f, 0xc0,  //..%%%%%%%%..
    0x60, 0xc0,  //.%%.....%%..
    0x00, 0xe0,  //........%%%.
    0x00, 0x60,  //.........%%.
    0x00, 0x60,  //.........%%.
    0x00, 0xc0,  //........%%..
    0x00, 0xc0,  //........%%..
    0x01, 0x80,  //.......%%...
    0x03, 0x80,  //......%%%...
    0x07, 0x00,  //.....%%%....
    0x0e, 0x00,  //....%%%.....
    0x0c, 0x00,  //....%%......
    0x18, 0x00,  //...%%.......
    0x30, 0x00,  //..%%........
    0x7f, 0xe0,  //.%%%%%%%%%%.
    0x7f, 0xf0,  //.%%%%%%%%%%%
    0x00, 0x00,  //............

};

extern uint8_t font_3[] = {
     0x00, 0x00,  //............
     0x1f, 0x00,  //...%%%%%....
     0x7f, 0xc0,  //.%%%%%%%%%..
     0x60, 0xe0,  //.%%.....%%%.
     0x00, 0x60,  //.........%%.
     0x00, 0x60,  //.........%%.
     0x00, 0xc0,  //........%%..
     0x01, 0xc0,  //.......%%%..
     0x1f, 0x00,  //...%%%%%....
     0x1f, 0x80,  //...%%%%%%...
     0x00, 0xe0,  //........%%%.
     0x00, 0x60,  //.........%%.
     0x00, 0x60,  //.........%%.
     0x00, 0x60,  //.........%%.
     0x00, 0x60,  //.........%%.
     0x00, 0xe0,  //........%%%.
     0x7f, 0xc0,  //.%%%%%%%%%..
     0x3f, 0x00,  //..%%%%%%....
     0x00, 0x00,  //............

};

extern uint8_t font_4[] = {
     0x00, 0x00,  //..............
     0x00, 0xe0,  //........%%%...
     0x01, 0xe0,  //.......%%%%...
     0x01, 0xe0,  //.......%%%%...
     0x03, 0x60,  //......%%.%%...
     0x06, 0x60,  //.....%%..%%...
     0x06, 0x60,  //.....%%..%%...
     0x0c, 0x60,  //....%%...%%...
     0x18, 0x60,  //...%%....%%...
     0x18, 0x60,  //...%%....%%...
     0x30, 0x60,  //..%%.....%%...
     0x60, 0x60,  //.%%......%%...
     0x7f, 0xf8,  //.%%%%%%%%%%%%.
     0x7f, 0xf8,  //.%%%%%%%%%%%%.
     0x00, 0x60,  //.........%%...
     0x00, 0x60,  //.........%%...
     0x00, 0x60,  //.........%%...
     0x00, 0x60,  //.........%%...
     0x00, 0x00,  //..............

};

extern uint8_t font_5[] = {
     0x00, 0x00,  //...........
     0x7f, 0x80,  //.%%%%%%%%..
     0x7f, 0x80,  //.%%%%%%%%..
     0x60, 0x00,  //.%%........
     0x60, 0x00,  //.%%........
     0x60, 0x00,  //.%%........
     0x60, 0x00,  //.%%........
     0xfe, 0x00,  //%%%%%%%....
     0xff, 0x80,  //%%%%%%%%%..
     0x03, 0xc0,  //......%%%%.
     0x00, 0xc0,  //........%%.
     0x00, 0xc0,  //........%%.
     0x00, 0xc0,  //........%%.
     0x00, 0xc0,  //........%%.
     0x00, 0xc0,  //........%%.
     0x81, 0xc0,  //%......%%%.
     0xff, 0x80,  //%%%%%%%%%..
     0x7e, 0x00,  //.%%%%%%....
     0x00, 0x00,  //...........

};

extern uint8_t font_6[] = {
    0x00, 0x00,  //............
    0x07, 0xc0,  //.....%%%%%..
    0x0f, 0xc0,  //....%%%%%%..
    0x18, 0x00,  //...%%.......
    0x30, 0x00,  //..%%........
    0x30, 0x00,  //..%%........
    0x60, 0x00,  //.%%.........
    0x67, 0x80,  //.%%..%%%%...
    0x6f, 0xc0,  //.%%.%%%%%%..
    0x70, 0xe0,  //.%%%....%%%.
    0x60, 0x60,  //.%%......%%.
    0x60, 0x70,  //.%%......%%%
    0x60, 0x70,  //.%%......%%%
    0x60, 0x60,  //.%%......%%.
    0x70, 0x60,  //.%%%.....%%.
    0x38, 0xe0,  //..%%%...%%%.
    0x1f, 0xc0,  //...%%%%%%%..
    0x0f, 0x80,  //....%%%%%...
    0x00, 0x00,  //............

};

extern uint8_t font_7[] = {
     0x00, 0x00,  //............
     0x7f, 0xf0,  //.%%%%%%%%%%%
     0x7f, 0xf0,  //.%%%%%%%%%%%
     0x00, 0x60,  //.........%%.
     0x00, 0x60,  //.........%%.
     0x00, 0xc0,  //........%%..
     0x00, 0xc0,  //........%%..
     0x01, 0xc0,  //.......%%%..
     0x01, 0x80,  //.......%%...
     0x01, 0x80,  //.......%%...
     0x03, 0x00,  //......%%....
     0x03, 0x00,  //......%%....
     0x06, 0x00,  //.....%%.....
     0x06, 0x00,  //.....%%.....
     0x0e, 0x00,  //....%%%.....
     0x0c, 0x00,  //....%%......
     0x0c, 0x00,  //....%%......
     0x18, 0x00,  //...%%.......
     0x00, 0x00,  //............

};
extern uint8_t font_8[] = {
     0x00, 0x00,  //............
     0x0f, 0x80,  //....%%%%%...
     0x3f, 0xc0,  //..%%%%%%%%..
     0x30, 0xe0,  //..%%....%%%.
     0x70, 0x60,  //.%%%.....%%.
     0x70, 0x60,  //.%%%.....%%.
     0x30, 0x60,  //..%%.....%%.
     0x38, 0xc0,  //..%%%...%%..
     0x1f, 0x80,  //...%%%%%%...
     0x0f, 0x80,  //....%%%%%...
     0x39, 0xc0,  //..%%%..%%%..
     0x70, 0xe0,  //.%%%....%%%.
     0x60, 0x60,  //.%%......%%.
     0x60, 0x70,  //.%%......%%%
     0x60, 0x60,  //.%%......%%.
     0x70, 0x60,  //.%%%.....%%.
     0x3f, 0xc0,  //..%%%%%%%%..
     0x1f, 0x80,  //...%%%%%%...
     0x00, 0x00,  //............

};

extern uint8_t font_9[] = {
     0x00, 0x00,  //............
     0x0f, 0x00,  //....%%%%....
     0x3f, 0xc0,  //..%%%%%%%%..
     0x30, 0xc0,  //..%%....%%..
     0x60, 0x60,  //.%%......%%.
     0x60, 0x60,  //.%%......%%.
     0x60, 0x60,  //.%%......%%.
     0x60, 0x70,  //.%%......%%%
     0x60, 0x70,  //.%%......%%%
     0x70, 0xf0,  //.%%%....%%%%
     0x3f, 0xe0,  //..%%%%%%%%%.
     0x0e, 0x60,  //....%%%..%%.
     0x00, 0x60,  //.........%%.
     0x00, 0x60,  //.........%%.
     0x00, 0xc0,  //........%%..
     0x01, 0xc0,  //.......%%%..
     0x3f, 0x80,  //..%%%%%%%...
     0x3e, 0x00,  //..%%%%%.....
     0x00, 0x00,  //............

};

extern uint8_t font_colon[] = {
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x60,0x00,  //.%%.
     0x70,0x00,  //.%%%
     0x60,0x00,  //.%%.
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x60,0x00,  //.%%.
     0x70,0x00,  //.%%%
     0x60,0x00,  //.%%.
     0x00,0x00,  //....
     0x00,0x00,  //....
     0x00,0x00,  //....
};

extern uint8_t font_comma[] = {
     0x00,  //.....
     0x00,  //.....
     0x00, //.....
     0x00,     //.....
     0x00,       //.....
     0x00,   //.....
     0x00, //.....
     0x00,     //.....
     0x00,  //.....
     0x00,    //.....
     0x70,  //.%%%.
     0x70,     //.%%%.
     0x60,      //.%%..
     0x60,     //.%%..
     0x60,      //.%%..
     0xc0, //%%...
     0x00,      //.....
     0x00,     //.....
     0x00,     //.....
};

void drawFont(const uint8_t character[],int x, int y,int color,int backdrop){
    window_set(x,y,x+fontWidth,x+fontHeight); // Set Window
    write_command(0x2C); //write pixel command
    int i;
    int k;
    // Draw each Pixel
    for(i=0;i<fontArrayLen;i++)     // Each Entry in Byte Array
        for(k=0;k<8;k++){
        //     Draw Color if 1
            if(character[i] & 0x80 >> k){
                write_data((color>>16)&0xff); // red
                write_data((color>>8)&0xff); // green
                write_data((color)&0xff); // blue
            }
            // Else Draw Backdrop
            else{
                write_data((backdrop>>16)&0xff); // red
                write_data((backdrop>>8)&0xff); // green
                write_data((backdrop)&0xff); // blue
            }
        }
}
void drawComma(int x, int y,int color,int backdrop){
    window_set(x,y,x+7,x+fontHeight); // Set Window
    write_command(0x2C); //write pixel command
    int i;
    int k;
    // Draw each Pixel
    for(i=0;i<fontHeight ;i++)     // Each Entry in Byte Array
        for(k=0;k<8;k++){
        //     Draw Color if 1
            if(font_comma[i] & 0x80 >> k){
                write_data((color>>16)&0xff); // red
                write_data((color>>8)&0xff); // green
                write_data((color)&0xff); // blue
            }
            // Else Draw Backdrop
            else{
                write_data((backdrop>>16)&0xff); // red
                write_data((backdrop>>8)&0xff); // green
                write_data((backdrop)&0xff); // blue
            }
        }
}

int* numbtofont(int number){
    // Maps a font array to a one digit number
    switch(number) {
        case 0: return font_0; break;
        case 1: return font_1; break;
        case 2: return font_2; break;
        case 3: return font_3; break;
        case 4: return font_4; break;
        case 5: return font_5; break;
        case 6: return font_6; break;
        case 7: return font_7; break;
        case 8: return font_8; break;
        case 9: return font_9; break;
        default: printf("a ist irgendwas\n"); break;
    }


}

void drawMilliVolt(int voltage_mv,int x, int y,int foregroundColor,int backgroundColor){
    // Draws a 4 digit voltage in mV (XXX,1 mV) at postitions x and y
    int digit[4];
    digit[0] = (int)(voltage_mv/1000);  // Calculate digit 0
    digit[1] = (int)((voltage_mv-digit[0]*1000)/100);   // Calculate digit 2
    digit[2] = (int)((voltage_mv-digit[0]*1000-digit[1]*100)/10);   // Calculate digit 2
    digit[3] = (int)(voltage_mv-digit[0]*1000-digit[1]*100-digit[2]*10)%10;   // Calculate digit 3
    // Draw first 3 digits digit
    int i;
    for(i=0;i<3;i++){
        drawFont(numbtofont(digit[i]),x+i*(fontWidth),y,foregroundColor,backgroundColor);
    }
    // Draw Comma
    drawComma(x+fontWidth+2*(fontWidth)+0.3*(fontWidth),y,foregroundColor,backgroundColor);
    // Draw last  digits
    drawFont(numbtofont(digit[i]),x+4*fontWidth,y,foregroundColor,backgroundColor);
    // Draw mV
    drawFont(font_m,x+5*(fontWidth)+0.3*(fontWidth),y,foregroundColor,backgroundColor);
    drawFont(font_V,x+6*fontWidth+fontSpace+0.3*(fontWidth),y,foregroundColor,backgroundColor);
}
/********************************************************************************/
void drawText(void){
    //draw first Font line
    drawFont(font_C, xStartCHX, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_1, xStartCHX+2*fontWidth+2*fontSpace, yStartCHfirstLine, WHITE, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+3*fontSpace, yStartCHfirstLine, WHITE, BLACK);
    //draw second Font line
    drawFont(font_C, xStartCHX, yStartCHsecondLine, WHITE, BLACK);
    drawFont(font_H, xStartCHX+fontWidth+fontSpace, yStartCHsecondLine, WHITE, BLACK);
    drawFont(font_2, xStartCHX+2*fontWidth+2*fontSpace, yStartCHsecondLine, WHITE, BLACK);
    drawFont(font_colon, xStartCHX+3*fontWidth+3*fontSpace, yStartCHsecondLine, WHITE, BLACK);

    drawFont(font_C, 450, 439,WHITE,BLACK);
}





