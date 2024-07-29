/*
 * CFile1.c
 *
 * Created: 7/29/2024 5:06:08 PM
 *  Author: Nadia
 */ 
#include "LCD.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void LCD_vInit(void) {
	_delay_ms(200);
	#if defined eight_bits_mode
	DIO_set_port_direction('A', 0xFF); // Set all PORTA pins as output
	#elif defined four_bits_mode
	for (int i = 4; i < 8; i++)
	DIO_vsetPINDir('A', i, 1); // Set PA4-PA7 as output
	#endif

	DIO_vsetPINDir('B', EN, 1);
	DIO_vsetPINDir('B', RW, 1);
	DIO_vsetPINDir('B', RS, 1);
	DIO_write('B', RW, 0);
	
	#if defined eight_bits_mode
	LCD_vSend_cmd(EIGHT_BITS);
	#elif defined four_bits_mode
	LCD_vSend_cmd(RETURN_HOME);
	LCD_vSend_cmd(FOUR_BITS);
	#endif
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);
	LCD_vSend_cmd(CLR_SCREEN);
	LCD_vSend_cmd(ENTRY_MODE);
}

static void send_falling_edge(void) {
	DIO_write('B', EN, 1);
	_delay_ms(2);
	DIO_write('B', EN, 0);
	_delay_ms(2);
}

void LCD_vSend_cmd(char cmd) {
	#if defined eight_bits_mode
	DIO_write_port('A', cmd);
	#elif defined four_bits_mode
	write_nibble('A', cmd >> 4, 1);
	write_nibble('A', cmd, 1);
	#endif
	DIO_write('B', RS, 0);
	send_falling_edge();
}

void LCD_vSend_char(char data) {
	#if defined eight_bits_mode
	DIO_write_port('A', data);
	#elif defined four_bits_mode
	write_nibble('A', data >> 4, 1);
	write_nibble('A', data, 1);
	#endif
	DIO_write('B', RS, 1);
	send_falling_edge();
}

void LCD_vSend_string(char *data) {
	while ((*data) != '\0') {
		LCD_vSend_char(*data);
		data++;
	}
}

void LCD_clearscreen() {
	LCD_vSend_cmd(CLR_SCREEN);
}

void LCD_movecursor(char row, char col) {
	char data;
	if (row > 2 || row < 1 || col > 16 || col < 1) {
		data = 0x80;
	} else {
		data = (row == 1) ? 0x80 + col - 1 : 0xC0 + col - 1;
	}
	LCD_vSend_cmd(data);
}
