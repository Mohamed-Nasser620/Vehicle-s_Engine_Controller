/******************************************************************************
 *
 * Module: Application
 *
 * File Name: task.c
 *
 * Description: Source file for the application code
 *
 * Author: Mohamed Nasser
 *
 *******************************************************************************/

#include "task.h"

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

uint8 SPEED          = 0;
uint8 DC_DIRECTION   = 0;
uint8 STPR_DIRECTION = 0;
uint8 ANGLE          = 0;
uint8 LAST_ANGLE     = 0;
uint8 str[STR_SIZE]  = {1,1,1,1,1,1,1,1,'\0'} ; // String in which the data will be stored from UART
uint8 flag           = 0;      // A flag that is set when there is a wrong input
uint8 SEC            = 0;      // Seconds
uint8 MIN            = 0;      // Minutes
uint8 HUR            = 0;      // Hours
uint8 DAY            = 'A';    // A variable that changes the time from AM/PM to PM/AM
boolean right_flag   = FALSE;  // A flag that is set when the last entered direction is RIGHT
boolean left_flag    = FALSE;  // A flag that is set when the last entered direction is LEFT


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*  Description:
 *  This function receives the input from the user using UART driver
 *  and stores it in a string
 */

void Receive_input(void)
{
	uint8 i = 0;
	strcpy(str,"11111111");      //reset string before filling it with new inputs
	for(i=0 ; str[i]!='\0' ; i++)
	{
		str[i] = UART_recieveByte(); /* Receive Byte from Terminal1 */
		UART_sendByte(str[i]);       /* Re-send the received byte to Terminal2 */
		if(str[i]== 'E')
		{
			break;
		}
	}
}

/*  Description:
 *  In case there is no wrong inputs we generate this function to generate
 *  DC motor & Stepper motor according to the angle & directions entered and updates
 *  the data printed on LCD
 */

void Do_Instructions(void)
{
  if(DC_DIRECTION == 'F')      //if the direction is forward rotate DC motor ACW
  {
	  DcMotor_Rotate( ANTI_CLOCKWISE , SPEED);
  }
  else if(DC_DIRECTION == 'B') //if the direction is backward rotate DC motor CW
  {
	  DcMotor_Rotate( CLOCKWISE , SPEED);
  }

  if(STPR_DIRECTION == 'R')
  {
	  //In order to rotate stepper motor in the latest position (angle) entered we use the following condtions
	  if(right_flag == TRUE)
	  {
		  if (ANGLE >= LAST_ANGLE)
			  turn_motor_right( ANGLE - LAST_ANGLE , full_wave_step);
		  else
			  turn_motor_left( LAST_ANGLE - ANGLE , full_wave_step);
	  }
	  else
	  {
		  turn_motor_right( ANGLE + LAST_ANGLE , full_wave_step);
	  }

	  right_flag = TRUE;
	  left_flag = FALSE;
  }
  else if(STPR_DIRECTION == 'L')
  {
	  //In order to rotate stepper motor in the latest position (angle) entered we use the following condtions
	  if(left_flag == TRUE)
	  {
		  if (ANGLE >= LAST_ANGLE)
			  turn_motor_left( ANGLE - LAST_ANGLE , full_wave_step);
		  else
			  turn_motor_right( LAST_ANGLE - ANGLE , full_wave_step);
	  }
	  else
	  {
		  turn_motor_left( ANGLE + LAST_ANGLE , full_wave_step);
	  }

	  left_flag = TRUE;
	  right_flag = FALSE;
  }
  Print_dataOnLCD(); //Update data shown on LCD
}

/*  Description:
 *  This function displays the speed & the angle in which stepper motor is directed
 *  in the first line on LCD
 */

void Print_dataOnLCD(void)
{
	LCD_moveCursor(0,0);
	LCD_displayString("SPD:   % DIR:   ");
	LCD_moveCursor(0,4);
	if(SPEED >= 100)
	{
		LCD_intgerToString(SPEED);
	}
	else
	{
		LCD_intgerToString(SPEED);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}
	if(left_flag)
	{
		LCD_moveCursor(0,13);
		LCD_displayCharacter('-');
		LCD_intgerToString(ANGLE);
	}
	else
	{
		LCD_moveCursor(0,13);
		LCD_displayCharacter(' ');
		LCD_intgerToString(ANGLE);
	}
	LCD_moveCursor(0,0);
}

/*  Description:
 *  This function displays the time following the hour, minutes, seconds format
 *  in the second line on LCD
 */

void Print_timeOnLCD(void)
{
	LCD_moveCursor(1,0);
	LCD_displayString("Time:  :  :    M");
    SEC++;
    if(SEC == 60)
    {
    	SEC=0;
    	MIN++;
    }
    if(MIN == 60)
    {
    	MIN=0;
    	HUR++;
    }
    if(HUR == 12)
    {
    	DAY = 'P';
    }
    else if(HUR == 24)
    {
    	DAY = 'A';
    	HUR = 0;
    }
    LCD_moveCursor(1,11);
    if(SEC < 10)
    {
    	LCD_intgerToString(0);
    	LCD_intgerToString(SEC);
    }
    else
    {
    	LCD_intgerToString(SEC);
    }
    LCD_moveCursor(1,8);
    if(MIN < 10)
    {
    	LCD_intgerToString(0);
    	LCD_intgerToString(MIN);
    }
    else
    {
    	LCD_intgerToString(MIN);
    }
    LCD_moveCursor(1,5);
    if(HUR < 10)
    {
    	LCD_intgerToString(0);
    	LCD_intgerToString(HUR);
    }
    else
    {
    	LCD_intgerToString(HUR);
    }
    LCD_moveCursor(1,14);
    LCD_displayCharacter(DAY);
}


int main()
{
	LCD_init();      //Open LCD screen
	DcMotor_Init();  //Enable DC motor
	/* 1. Size of the character = 8 bits
	 * 2. Disable parity check
	 * 3. Use one stop bit
	 * 4. choose 9600 bps baud rate
	 */
	UART_ConfigType UART_Configuration = { EIGHT_BIT , DISABLED , ONE_BIT , 9600 } ;
	UART_init(&UART_Configuration);
	/* Since the frequency of MC FCPU = 8 MHz Using the calculations
	 * in the data sheet the compare value should be 7813 so that we
	 * get an interrupt each second that updates the time shown on LCD
	 */
	Timer1_ConfigType Timer1_Config = { 7813 , FCPU_1024};
	Timer1_compareInit(&Timer1_Config); //Enable timer1 compare mode
	Print_dataOnLCD();
	/* Send the address of the function that updates the time to timer1 driver
	 * so that it will be called by the ISR that's executed with each interrupt
	 * (every second)
	 */
	Timer1_setCallBack(Print_timeOnLCD);
	Receive_input();
	while(1)
	{
		//testing the case of entering a wrong speed
		if(!(str[0]=='0' || str[0]=='1'))
		{
			flag =1;
		}
		else
		{

			SPEED = 100*(str[0]- '0') + 10*(str[1]-'0') + (str[2]-'0');
			if(!(SPEED>=0 && SPEED<=100))
			{
				flag = 1;
			}
		}
		//testing the case of entering a wrong direction of DC motor
		if(!(str[3]=='F' || str[3]=='B'))
		{
			flag = 1;
		}

		LAST_ANGLE = ANGLE;
		ANGLE = 10*(str[4]-'0') + (str[5]-'0') ;
		//testing the case of entering a wrong angle for stepper motor
		if(!(ANGLE>=0 && ANGLE<=45))
		{
			flag = 1;
		}
		//testing the case of entering a wrong direction of stepper motor
		if(!(str[6]=='R' || str[6]=='L'))
		{
			flag = 1;
		}
		//testing the case of entering the indicator of the end of the frame
		if(!(str[7]=='E'))
		{
			flag = 1;
		}
        //checking if there is any wrong input
		if(flag)
		{
			ANGLE = LAST_ANGLE;
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("wrong input");
			flag = 0; //reset flag for the next iteration
			Receive_input();
		}
		else
		{
			DC_DIRECTION = str[3];
			STPR_DIRECTION = str[6];
			Do_Instructions();
			Receive_input();
		}

	}

}
