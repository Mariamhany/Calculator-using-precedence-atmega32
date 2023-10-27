/*
 * keypad.c
 *
 *  Created on: Oct 21, 2023
 *      Author: HP
 */

/*rows are output , column input*/
#include "keypad.h"
#include"dio.h"
#include "util/delay.h"

static u8 KYP_value [4][4]= {  {'7','8','9','/'},
		                       {'4','5','6','*'},
                               {'1','2','3','-'} ,
                               {'c','0','=','+'} } ;
u8 rows_id[4] = {PIN5_ID,PIN4_ID,PIN3_ID,PIN2_ID};
u8 columns_id[4]={PIN7_ID,PIN6_ID,PIN5_ID,PIN3_ID};

u8 KYP_GetPressedKey(void)
{
	u8 value ='#'; u8 valueflag=0;
	/*	All rows = 1 */
	DIO_SetPinValue(KEYPAD_PORT_ROW_ID, rows_id[0], LOGIC_HIGH);
	DIO_SetPinValue(KEYPAD_PORT_ROW_ID, rows_id[1], LOGIC_HIGH);
	DIO_SetPinValue(KEYPAD_PORT_ROW_ID, rows_id[2], LOGIC_HIGH);
	DIO_SetPinValue(KEYPAD_PORT_ROW_ID, rows_id[3], LOGIC_HIGH);

	/*	Row 	To send pattern			*/
	for(u8 Row = 0; Row<4 ; Row++)
	{
		/*	Activate Row */
		DIO_SetPinValue(KEYPAD_PORT_ROW_ID, rows_id[Row], LOGIC_LOW);
		/*	Read column */
		for(u8 column =0 ; column <4; column ++)
		{
			if(DIO_GetPinValue(KEYPAD_PORT_COL_ID, columns_id[column]) == 0)
			{
				while(DIO_GetPinValue(KEYPAD_PORT_COL_ID, columns_id[column]) == 0);
				_delay_ms(10);
				value =KYP_value[Row][column];
				valueflag=1;
				break;
			}
		}
		/*	Deactivate Row */
		DIO_SetPinValue(KEYPAD_PORT_ROW_ID, rows_id[Row], LOGIC_HIGH);
		if (valueflag==1)
		{
			break;
		}

	}
return value;
}
