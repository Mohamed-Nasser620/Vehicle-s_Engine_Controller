/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm_timer0.c
 *
 * Description: Source file for timer0 PWM mode driver
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/


#include "pwm_timer0.h"

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* Description :
 *1. The function responsible for trigger the Timer0 with the PWM Mode.
 *2. Setup the PWM mode with Non-Inverting.
 *3. Setup the prescaler with F_CPU/256.
 *4. Setup the compare value based on the required input duty cycle
 *5. Setup the direction for OC0 as output pin through the GPIO driver.
 *6. The generated PWM signal frequency will control the DC Motor speed.
 */

void PWM_Timer0_Start( uint8 duty_cycle )
{
	TCNT0 = 0; // Set Timer Initial Value to 0

	OCR0  = ceil((float)(duty_cycle/100.0)*255) ; // Set Compare Value

	DDRB  = DDRB | (1<<PB3); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/256 CS00=0 CS01=0 CS02=1
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS02);
}
