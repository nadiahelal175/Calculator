/*
 * IncFile1.h
 *
 * Created: 7/29/2024 5:05:29 PM
 *  Author: Nadia
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define NOTPRESSED 0xff
#include "DIO.h"

void keypad_vInit();
char keypad_u8check_press();

#endif 
