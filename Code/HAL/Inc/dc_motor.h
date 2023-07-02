 /******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for DC motor's driver
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include "pwm_timer0.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_PORT     PORTA_ID
#define DC_PIN_A    PIN0_ID
#define DC_PIN_B    PIN1_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	STOP , CLOCKWISE , ANTI_CLOCKWISE
} DcMotor_State ;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description :
 * Responsible to setup the direction for the two motor pins through GPIO driver
 * Stop DC motor at the beginning
 */

void DcMotor_Init (void);

/* Description :
 * 1. Responsible to rotate the motor clock-wise or anti clock-wise or stop the motor
 * based on the state input state value
 * 2. Send the required duty cycle to the PWM driver based on the required speed value
 */

void DcMotor_Rotate(DcMotor_State state , uint8 speed);

#endif /* DC_MOTOR_H_ */
