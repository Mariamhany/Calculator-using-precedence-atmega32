/*
 * keypad.h
 *
 *  Created on: Oct 21, 2023
 *      Author: HP
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stdtypes.h"
#include "DIO.h"

#define KEYPAD_PORT_ROW_ID PORTC_ID
#define KEYPAD_PORT_COL_ID PORTD_ID

//u8 rows_id[4] = {PIN5_ID,PIN4_ID,PIN3_ID,PIN2_ID};
//u8 columns_id[4]={PIN7_ID,PIN6_ID,PIN5_ID,PIN3_ID};

u8 KYP_GetPressedKey(void);
#endif /* KEYPAD_H_ */
