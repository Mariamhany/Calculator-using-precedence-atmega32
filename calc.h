/*
 * calc.h
 *
 *  Created on: Oct 23, 2023
 *      Author: HP
 */

#ifndef CALC_H_
#define CALC_H_

#include "lcd.h"
#include "keypad.h"
#include"DIO.h"

/**COMMON MACROS**/
#define EQUALSIGN '='
#define MINUSSIGN '-'
#define CLEAR 'c'
#define KEY_NOT_PRESSED '#'

/**Global data types **/

typedef enum state{
	init_state =0,
	_1st_num_neg_state,
	after_init_state,
	_2nd_num_init_state,
	_2nd_num_neg_state,
	_2nd_num_after_init_state,
	_3rd_num_init_state,
	_3rd_num_neg_state,
	_3rd_num_after_init_state,
	after_error_state,
} calc_state;

typedef enum operation{
init,
ADD='+',
SUB='-',
MUL='*',
DIV='/'
} calc_operation;

void calculator_app(void);

#endif /* CALC_H_ */
