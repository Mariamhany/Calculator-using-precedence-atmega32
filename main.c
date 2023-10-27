/*
 * main.c
 *
 *  Created on: Oct 25, 2023
 *      Author: HP
 */

#include "calc.h"
#include"keypad.h"
#include"lcd.h"
#include"DIO.h"

int main() {
	DIO_init();
	LCD_init();

	while(1)
	{
		calculator_app();
	}
return 0;
}
