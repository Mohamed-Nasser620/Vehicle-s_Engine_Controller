/******************************************************************************
 *
 * Module: 	TIMER1 Compare Mode
 *
 * File Name: timer1_compare.h
 *
 * Description: Header file for the TIMER1 CMP MODE AVR driver
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/


#ifndef TIMER1_COMPARE_H_
#define TIMER1_COMPARE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	OFF, NO_PRESCALING, FCPU_8 , FCPU_64 , FCPU_256 , FCPU_1024
} Prescaler ;

typedef struct
{
	uint16 compare_value;
	Prescaler prescaler;
}Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
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

void Timer1_compareInit(Timer1_ConfigType* config_ptr);

/*Description :
 * we store in this function the address of the function we want to execute
 * each time there is an interrupt of compare match detection
 */

void Timer1_setCallBack(void (*function_ptr)(void));

/*Description :
 * function to disable timer1
 */

void Timer1_deinit (void);

#endif /* TIMER1_COMPARE_H_ */
