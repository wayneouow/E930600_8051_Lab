#ifndef LCD1602_H
#define LCD1602_H

#include <regx51.h>

typedef unsigned char uint8;
typedef unsigned char bool;
typedef unsigned int uint16;

#define true 1
#define false 0
//#define LCD1602_RS P2_0
//#define LCD1602_E P2_1
//#define LCD1602_RW P2_2
//#define Data_PORT P0


//the pin connected to RS
sbit LCD1602_RS=P2^0;
//the pin connected to RW
sbit LCD1602_RW=P2^2;
//the pin connected to E
sbit LCD1602_E=P2^1;

//the 8-bit port connected to D0~D7
#define LCD1602_PORT P0

void lcd1602_delay(uint16 p_time);

void lcd1602_write_cmd(uint8 p_cmd);
void lcd1602_write_data(uint8 p_data);

//init
void lcd1602_init();

//tun on/off the display of character, the display of cursor and the flash of cursor
void lcd1602_display_switch(bool p_show_char,bool p_show_cursor,bool p_flash_cursor);

//move the cursor to left or right (one character)
void lcd1602_cursor_shift(bool p_right);

//clear the screen
void lcd1602_clear();

//reset the cursor the the left-top of screen
void lcd1602_cursor_return();

//set a character at the given position(p_x=0~15,p_y=0~1)
void lcd1602_char_set(uint8 p_x,uint8 p_y,char p_char);

//write a string from the given position(p_x=0~15,p_y=0~1,p_string)
void lcd1602_string_set(uint8 p_x,uint8 p_y,const char* p_string);

void CreateCustomCharacter (unsigned char *Pattern, const char Location);

void print_msg(char *msg);



#endif