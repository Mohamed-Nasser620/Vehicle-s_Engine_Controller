 /******************************************************************************
 *
 * Module: stepper motor
 *
 * File Name: stepper_motor.h
 *
 * Description: Header file for stepper motor's driver
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "std_types.h"
#include "gpio.h"

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define HALF_WAVE_STEPS 8
#define FULL_WAVE_STEPS 4
#define STEPPER_MOTOR_PORT_ID           PORTB_ID
#define MOTOR_FIRST_DATA_PIN_ID         PIN4_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
		{
	      half_wave_step , full_wave_step
		} Stepper_motor_sequence;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/* Description :
* Responsible to setup the direction (right or left) for the stepper motor through GPIO driver
* and make it start from last position at the beginning
*/

void turn_motor_right(uint8 angle , Stepper_motor_sequence mode);

void turn_motor_left(uint8 angle , Stepper_motor_sequence mode);

#endif /* STEPPER_MOTOR_H_ */
