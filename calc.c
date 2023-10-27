/*
 * calc.c
 *
 *  Created on: Oct 23, 2023
 *      Author: HP
 */

#include "calc.h"
#include"stdtypes.h"
/******* local data ********/
static u8 button = 0;
static f32 val1=0,val2=0,val3=0;
static f32 result=0;
static calc_operation operation1=init;
static calc_operation operation2=init;
static calc_operation lastoperation=init;
static calc_state state=init_state;
u8 error_flag=0;
u8 float_result_flag=0;
/** local function prototypes ***/
/******************************************************************************
 start the calculator initial state where you insert first number or minus sign
*******************************************************************************/
static void calc_init_state(void);
/******************************************************************************
 start calculator 1st_num_neg state where you insert negative number at first
*******************************************************************************/
static void calc_1st_num_neg (void);
/******************************************************************************
start the calculator 1st_number_After_init_state,
where you can insert operator or another digit for your first number
*******************************************************************************/
static void calc_After_init_state (void);
/******************************************************************************
 start the calculator 2nd_num_init_state where you can
 insert your 2nd number 1st digit or minus sign
*******************************************************************************/
static void calc_2nd_num_init_state(void);
/******************************************************************************
start the calculator 2nd_num_neg_state where you insert the first digit of your 2nd negative number
*******************************************************************************/
static void calc_2nd_num_neg_State (void);
/******************************************************************************
 start the calculator 2nd_num_after_init_state where you insert another
 digit for your second number , or operator , or equal sign to show result
*******************************************************************************/
static void calc_2nd_num_After_init_state (void);
/******************************************************************************
 insert your 3rd_num 1st digit or minus sign
*******************************************************************************/
static void calc_3rd_num_init_state (void);
/******************************************************************************
 insert the first digit of your 2nd negative number
*******************************************************************************/
static void calc_3rd_num_neg_state(void);
/******************************************************************************
 start the calculator 3rd_num_after_init_state where you can insert
 another digit for your 3rd number , or operator , or equal sign to show result
*******************************************************************************/
static void calc_3rd_num_After_init_state(void);

 /******************************************************************************
 clear LCD screen and return to calc_init_state
 *******************************************************************************/
static void clear_calc(void);
/******************************************************************************
 Shows the result when you insert only 2 numbers
*******************************************************************************/
static void calc_2nums_Show_Result(void);
/******************************************************************************
 Shows the result depending on the operators precedence rules
*******************************************************************************/
static void calc_operator_precedence_Show_Result(void);
/******************************************************************************
 apply the operator precedence rules for the 3 numbers before inserting another number
*******************************************************************************/
static void calc_operator_precedence_in_the_middle(void);
/******************************************************************************
 return 1 if value is integer value or 0 if it's float value
*******************************************************************************/
//static u8 is_integer(f64 value);
/******************************************************************************
 writes float numbers on LCD
*******************************************************************************/
//static void Calc_LCD_Write_Float(f64 value);
/******************************************************************************
 it's the state where the error appears on Lcd when you divide by zero
you must press clear to pass this state
*******************************************************************************/
static void calc_After_error_state(void);
/******************************************************************************
 Shows the error message on LCD when you try to divide by zero
*******************************************************************************/
static void calc_Show_error(void);
/******************************************************************************
* this function is used in lcd_write_float function it's responsible for showing decimal numbers
*******************************************************************************/
//static void LCD_Write_Decimal_num(s32 num);
static void LCD_Write_Negative_num(s32 num);

/****************************************************************
 *                  Function declarations                       *
 * **************************************************************/

static void calc_init_state(void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		val1=button-48;
		state=after_init_state;
	}
	else if (button==MINUSSIGN)
		{
		LCD_writeChar(button);
		state=_1st_num_neg_state;
		}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}

static void calc_1st_num_neg (void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		val1=(button-48)*(-1);
		state=after_init_state;
	}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}
static void calc_After_init_state (void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		if (val1<0)
		{
			val1 = val1*10-(button-48);
		}
		else {
			val1 = val1*10+(button-48);
		}
		state=after_init_state;
	}
	else if ((button=ADD)||(button=SUB)||(button=MUL)||(button=DIV)){
		LCD_writeChar(button);
		operation1=button;
		state=_2nd_num_init_state;
	}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}
static void calc_2nd_num_init_state(void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		val2=button-48;
		state=_2nd_num_after_init_state;
	}
	else if (button==MINUSSIGN)
		{
		LCD_writeChar(button);
		state=_2nd_num_neg_state;
		}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}
static void calc_2nd_num_neg_State (void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		val2=(button-48)*(-1);
		state=_2nd_num_after_init_state;
	}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}

static void calc_2nd_num_After_init_state (void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		if (val2<0)
		{
			val2 = val2*10-(button-48);
		}
		else {
			val2 = val2*10+(button-48);
		}
		state=_2nd_num_after_init_state;
	}
	else if ((button==ADD)||(button==SUB)||(button==MUL)||(button==DIV)){
		LCD_writeChar(button);
		operation2=button;
		state=_3rd_num_init_state;
	}
	else if(button==EQUALSIGN){
		calc_2nums_Show_Result();
	}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}
static void calc_3rd_num_init_state(void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		val3=button-48;
		state=_3rd_num_after_init_state;
	}
	else if (button==MINUSSIGN)
		{
		LCD_writeChar(button);
		state=_3rd_num_neg_state;
		}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}

static void calc_3rd_num_neg_state(void){
	if ((button >= '0') &&(button<='9')){
		LCD_writeChar(button);
		val3=(button-48)*(-1);
		state=_3rd_num_after_init_state;
	}
	else if (button==CLEAR)
	{
		clear_calc();
	}
}
static void calc_3rd_num_After_init_state(void){
if ((button >= '0') &&(button<='9')){
	LCD_writeChar(button);
	if (val3<0)
	{
		val3 = val3*10-(button-48);
	}
	else {
		val3 = val3*10+(button-48);
	}
	state=_3rd_num_after_init_state;
}
else if ((button==ADD)||(button==SUB)||(button==MUL)||(button==DIV)){

	calc_operator_precedence_in_the_middle();
}
else if(button==EQUALSIGN){
	calc_operator_precedence_Show_Result();
}
else if (button==CLEAR)
{
	clear_calc();
}

}

static void calc_2nums_Show_Result(void){
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
	switch(operation1){
	case ADD: result=val1+val2;
		break;
	case SUB: result=val1-val2;
		break;
	case MUL: result=val1*val2;
		break;
	case DIV:
		{if (val2==0){
		error_flag=1;}
	   else result=val1/val2;
		}
		break;
	case init:break;
	}
	if (!error_flag){
		LCD_integertoString(result);
		val1=result;
		state=after_init_state;
	}
	else {
		state= after_error_state;
		calc_Show_error();
	}
}

static void calc_operator_precedence_in_the_middle(void){
	LCD_writeChar(button);
	if( ((operation1==ADD)||(operation1==SUB)) && ((operation2==MUL)||(operation2==DIV))){
		switch (operation2){
		case MUL: val1=val1*val2;
		break;
		case DIV: if (val2==0)
			error_flag=1;
		else val1=val1/val2;
	    break;
		}
	  operation2=button;
	  state=_3rd_num_after_init_state;
	}
	else if( ((operation2==ADD)||(operation2==SUB)) && ((operation1==MUL)||(operation1==DIV)))
	{
		switch (operation1){
		case MUL: val1=val1*val2;
		break;
		case DIV:
		if (val2==0)
		{error_flag=1;
			}
		else
		{val1=val1/val2;
		}
	    break;
		}
      val2=val3;
	  operation1=operation2;
	  state=_3rd_num_after_init_state;

	  operation2=button;
	}
	else {
		switch (operation1){
		case ADD:val1=val1+val2;
		break;
		case SUB:val1=val1-val2;
	   break;
		case MUL:val1=val1*val2;
		break;
		case DIV:
			if (val2==0)
			{error_flag=1;
				}
			else
			{val1=val1/val2;
			}
		    break;
		}
		   val2=val3;
		  operation1=operation2;
		  state=_3rd_num_after_init_state;

		  operation2=button;
	}

}
static void calc_operator_precedence_Show_Result(void){
	if (!error_flag){
		LCD_sendCommand(LCD_CLEAR_DISPLAY);
	if( ((operation1==ADD)||(operation1==SUB)) && ((operation2==MUL)||(operation2==DIV))){
		switch (operation2){
		case MUL: val2=val2*val3;
		break;
		case DIV: if (val3==0)
			error_flag=1;
		else val2=val2/val3;
	    break;
		case init:break;
	}
	    lastoperation=operation1;

	}
	else if( ((operation2==ADD)||(operation2==SUB)) && ((operation1==MUL)||(operation1==DIV)))
	{
		switch (operation1){
		case MUL: val1=val1*val2;
		break;
		case DIV:
		if (val2==0)
		{error_flag=1;
			}
		else
		{val1=val1/val2;
		}
	    break;
		case init: break;
		}
	    lastoperation = operation2;
        val2=val3;

	}
	else {
		switch (operation1){
		case ADD:val1=val1+val2;
		break;
		case SUB:val1=val1-val2;
	   break;
		case MUL:val1=val1*val2;
		break;
		case DIV:
			if (val2==0)
			{error_flag=1;
				}
			else
			{val1=val1/val2;
			}
		    break;
		case init: break;

		}
		   val2=val3;
		  lastoperation=operation2;

	}

	switch (lastoperation){
	case ADD:result=val1+val2;
	break;
	case SUB:result=val1-val2;
   break;
	case MUL:result=val1*val2;
	break;
	case DIV:
		if (val2==0)
		{error_flag=1;
			}
		else
		{result=val1/val2;
		}
	    break;
	case init: break;

	}
		if (!error_flag){
			if (result<0){
				LCD_Write_Negative_num(result);
			}
			else { LCD_integertoString(result);}
			val1=result;
			state=after_init_state;
		}
		else {
			state= after_error_state;
			calc_Show_error();
		}
	}//
	else {
		state= after_error_state;
		calc_Show_error();
	}
}
static void LCD_Write_Negative_num(s32 num){
	LCD_writeChar('-');
	num = num*(-1);
	LCD_integertoString(num);
}
static void calc_After_error_state(void){
	if (button==CLEAR){
		clear_calc();
	}
}
static void calc_Show_error(void)
{
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
	LCD_GotoRowColumn(0,0);
	LCD_writeString("ERROR! ");
	LCD_GotoRowColumn(1,0);
	LCD_writeString("DIVISION BY ZERO");
}

void clear_calc(){
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
	state=init_state;
	float_result_flag=0;
	error_flag=0;
}


void calculator_app(void){
	button = KYP_GetPressedKey;
	if (button != KEY_NOT_PRESSED)
	{
	if (state==init_state)
		calc_init_state();
	else if (state==_1st_num_neg_state)
		calc_1st_num_neg();
	else if(state==after_init_state)
		calc_After_init_state();
	else if(state==_2nd_num_init_state)
		calc_2nd_num_init_state();
	else if (state==_2nd_num_neg_state)
		calc_2nd_num_neg_State();
	else if(state==_2nd_num_after_init_state)
		calc_2nd_num_After_init_state();
	else if (state==_3rd_num_init_state)
		 calc_3rd_num_init_state();
	else if(state==_3rd_num_neg_state)
		calc_3rd_num_neg_state();
	else if(state==_3rd_num_after_init_state)
	calc_3rd_num_After_init_state();
	else if (state==after_error_state)
		calc_After_error_state();
	}

}
