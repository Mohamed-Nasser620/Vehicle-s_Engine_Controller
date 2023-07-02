/******************************************************************************
 *
 * Module: 	TIMER1 Compare Mode
 *
 * File Name: timer1_compare.c
 *
 * Description: Source file for the TIMER1 CMP MODE AVR driver
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/


#include "timer1_compare.h"

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

static volatile void (*Timer1_interrupt)(void) = NULL_PTR;

/*******************************************************************************
 *                             ISR                                             *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(Timer1_interrupt != NULL_PTR)
		(*Timer1_interrupt)();
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* Description:
 * 1. Set I-bit to enable interrupts
 * 2. Set timer1 initial count to zero
 * 3. Set FOC1A for non-PWM mode
 * 4. Set WGM12 for CTC mode
 * 5. Inserting prescaler in CS10 & CS11 & CS12
 * 6. Set compare value in OCR1A
 * 7. Match interrupt enable
 */

void Timer1_compareInit(Timer1_ConfigType* config_ptr)
{
	SREG |= (1 << 7);
	TCNT1 = 0;
	TCCR1A |= (1 << FOC1A);
	TCCR1B = (1 << WGM12) ;
	TCCR1B = (TCCR1B & 0xF8) | (config_ptr->prescaler);
	OCR1A = config_ptr->compare_value;
	TIMSK |= (1 << OCIE1A);
}

/*Description :
 * we store in this function the address of the function we want to execute
 * each time there is an interrupt of compare match detection
 */

void Timer1_setCallBack(void (*function_ptr)(void))
{
	Timer1_interrupt = function_ptr;
}

/*Description :
 * function to disable timer1
 */

void Timer1_deinit (void)
{
	TIMSK &= ~(1<<OCIE1A);
	TCCR1B &= 0xF8;
}
