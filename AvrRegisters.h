/*
 * IO_reg.h
 *
 *  Created on: Oct 17, 2023
 *      Author: HP
 */

#ifndef AVRREGISTERS_H_
#define AVRREGISTERS_H_

#define PORTA *((volatile u8*)0x3B)
#define DDRA *((volatile u8*)0x3A)
#define PINA *((volatile u8*)0x39)

#define PORTB *((volatile u8*)0x38)
#define DDRB *((volatile u8*)0x37)
#define PINB *((volatile u8*)0x36)

#define PORTC *((volatile u8*)0x35)
#define DDRC *((volatile u8*)0x34)
#define PINC *((volatile u8*)0x33)

#define PORTD *((volatile u8*)0x32)
#define DDRD *((volatile u8*)0x31)
#define PIND *((volatile u8*)0x30)

#define SREG *((volatile u8*)0x5F)
#define MCUCR *((volatile u8*)0x55)
#define MCUCSR *((volatile u8*)0x54)
#define GICR *((volatile u8*)0x5B)
#define GIFR *((volatile u8*)0x5A)

#define SFIOR *((volatile u8*)0x50)
#define ADMUX *((volatile u8*)0x27)
#define ADCSRA *((volatile u8*)0x26)
#define ADCH *((volatile u8*)0x25)
#define ADCL *((volatile u8*)0x24)
#define ADC *((volatile u16*)0x24) //u16 to store both adcl + adch start at adcl!

#endif /* AVRREGISTERS_H_ */
