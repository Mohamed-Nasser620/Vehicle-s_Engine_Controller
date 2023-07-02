/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm_timer0.h
 *
 * Description: Header file for timer0 PWM mode driver
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/

#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_

#include <avr/io.h>
#include "std_types.h"
#include <math.h>

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description :
 *1. The function responsible for trigger the Timer0 with the PWM Mode.
 *2. Setup the PWM mode with Non-Inverting.
 *3. Setup the prescaler with F_CPU/256.
 *4. Setup the compare value based on the required input duty cycle
 *5. Setup the direction for OC0 as output pin through the GPIO driver.
 *6. The generated PWM signal frequency will control the DC Motor speed.
 */

void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_TIMER0_H_ */
