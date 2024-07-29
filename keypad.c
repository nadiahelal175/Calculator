/*
 * CFile1.c
 *
 * Created: 7/29/2024 5:05:02 PM
 *  Author: Nadia
 */ 
#include "keypad.h"

void keypad_vInit() {
	for (int i = 0; i < 4; i++) {
		DIO_vsetPINDir('D', i, 1);    // Set rows as output
		DIO_vsetPINDir('D', i + 4, 0); // Set columns as input
		DIO_vconnectpullup('D', i + 4, 1);
	}
}

char keypad_u8check_press() {
char arr[4][4] = {{'7', '8', '9', '/'}, {'4', '5', '6', '*'}, {'1', '2', '3', '-'}, {'A', '0', '=', '+'}};
char row, column;
for (row = 0; row < 4; row++) {
	DIO_write_port('D', 0xFF); // Reset all rows to high
	DIO_write('D', row, 0);    // Set current row to low
	for (column = 0; column < 4; column++) {
		if (!DIO_u8read('D', column + 4)) {
			return arr[row][column];
		}
	}
}
return NOTPRESSED;
}
