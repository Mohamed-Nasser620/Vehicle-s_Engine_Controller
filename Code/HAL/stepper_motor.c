/******************************************************************************
 *
 * Module: stepper motor
 *
 * File Name: stepper_motor.c
 *
 * Description: Source file for stepper motor's driver
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/

#include "stepper_motor.h"

uint8 count_right = 0;
uint8 count_left = 0;
uint8 last_position = 0;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void turn_motor_right(uint8 angle , Stepper_motor_sequence mode)
{

	uint8 motor_steps[FULL_WAVE_STEPS] = {3,9,12,6};

	// Configure first 4 pins in stepper motor's PORT as output pins
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID+1,PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID+2,PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID+3,PIN_OUTPUT);

	if(mode == full_wave_step)
	{
		for (unsigned char i = 0; i < angle; i++)
		{
			// move the motor to the next step
			switch (STEPPER_MOTOR_PORT_ID)
			{
			case PORTA_ID : PORTA = ((motor_steps[count_right] & 0x0F)<<PIN4_ID) | (PORTA & 0x0F);
			break;
			case PORTB_ID : PORTB = ((motor_steps[count_right] & 0x0F)<<PIN4_ID) | (PORTB & 0x0F);
			break;
			case PORTC_ID : PORTC = ((motor_steps[count_right] & 0x0F)<<PIN4_ID) | (PORTC & 0x0F);
			break;
			case PORTD_ID : PORTD = ((motor_steps[count_right] & 0x0F)<<PIN4_ID) | (PORTD & 0x0F);
			break;
			}
			count_right++;
			if(count_right == FULL_WAVE_STEPS)
			{
				//start from the beginning after finish the full motor rotation.
				count_right = 0;
			}
			if(count_left == 0)
			{
				//start from the beginning after finish the full motor rotation.
				count_left = FULL_WAVE_STEPS;
			}
			count_left--;
			_delay_ms(35);
		}
		last_position = motor_steps[count_right];
	}
}

void turn_motor_left(uint8 angle , Stepper_motor_sequence mode)
{
	uint8 motor_steps[FULL_WAVE_STEPS] = {12,9,3,6};

	// Configure first 4 pins in stepper motor's PORT as output pins
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID+1,PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID+2,PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_MOTOR_PORT_ID,MOTOR_FIRST_DATA_PIN_ID+3,PIN_OUTPUT);

	if(mode == full_wave_step)
	{
		for (unsigned char i = 0; i < angle; i++)
		{
			// move the motor to the next step
			switch (STEPPER_MOTOR_PORT_ID)
			{
			case PORTA_ID : PORTA = ((motor_steps[count_left] & 0x0F)<<PIN4_ID) | (PORTA & 0x0F);
			break;
			case PORTB_ID : PORTB = ((motor_steps[count_left] & 0x0F)<<PIN4_ID) | (PORTB & 0x0F);
			break;
			case PORTC_ID : PORTC = ((motor_steps[count_left] & 0x0F)<<PIN4_ID) | (PORTC & 0x0F);
			break;
			case PORTD_ID : PORTD = ((motor_steps[count_left] & 0x0F)<<PIN4_ID) | (PORTD & 0x0F);
			break;
			}
			count_left++;
			if(count_left == FULL_WAVE_STEPS)
			{
				//start from the beginning after finish the full motor rotation.
				count_left = 0;
			}
			if(count_right == 0)
			{
				//start from the beginning after finish the full motor rotation.
				count_right = FULL_WAVE_STEPS;
			}
			count_right--;
			_delay_ms(35);
		}
		last_position = motor_steps[count_left];
	}
}
