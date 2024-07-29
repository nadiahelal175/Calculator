/*
 * IncFile1.h
 *
 * Created: 7/29/2024 5:06:26 PM
 *  Author: Nadia
 */ 

#ifndef LCD_H_
#define LCD_H_

#define eight_bits_mode
//#define four_bits_mode

#include "DIO.h"

#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0E
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06
#define EIGHT_BITS 0x38
#define FOUR_BITS 0x28
#define CURSOR_OFF 0x0C

#define EN 2
#define RW 1
#define RS 0

void LCD_vInit(void);
void LCD_vSend_cmd(char cmd);
void LCD_vSend_char(char data);
void LCD_vSend_string(char *data);
void LCD_clearscreen(void);
void LCD_movecursor(char row, char col);

#endif 
