/******************************************************************************
 *
 * Module: Application
 *
 * File Name: task.h
 *
 * Description: Header file for the application code
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/

#ifndef TASK_H_
#define TASK_H_

#include "common_macros.h"
#include "dc_motor.h"
#include "pwm_timer0.h"
#include "gpio.h"
#include "lcd.h"
#include "uart.h"
#include "stepper_motor.h"
#include "std_types.h"
#include "timer1_compare.h"
#include <math.h>
#include <util/delay.h>
#include <string.h>

/*******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/

#define STR_SIZE 9

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*  Description:
 *  This function receives the input from the user using UART driver
 *  and stores it in a string
 */

void Receive_input(void);

/*  Description:
 *  In case there is no wrong inputs we generate this function to generate
 *  DC motor & Stepper motor according to the angle & directions entered and updates
 *  the data printed on LCD
 */

void Do_Instructions(void);

/*  Description:
 *  This function displays the speed & the angle in which stepper motor is directed
 *  in the first line on LCD
 */

void Print_dataOnLCD(void);

/*  Description:
 *  This function displays the time following the hour, minutes, seconds format
 *  in the second line on LCD
 */

void Print_timeOnLCD(void);


#endif /* TASK_H_ */
