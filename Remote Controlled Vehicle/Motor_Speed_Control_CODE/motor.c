/******************************************************************************
 *
 * Module: MOTOR
 *
 * File Name: motor.c
 *
 * Description: Source file for the AVR MOTOR driver
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#include "motor.h"
#include "gpio.h"
#include "pwm.h"
/*
 * Description :
 * Initializes the motor module with connected h-bridge
 */
void DcMotor_Init(void) {
	//Configuring output pins.
	GPIO_setupPinDirection(DcMotor1_PORT, DcMotor1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor1_PORT, (DcMotor1_PIN + 1), PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor2_PORT, DcMotor2_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor2_PORT, (DcMotor2_PIN + 1), PIN_OUTPUT);
	//Initializing motor pins to LOGIC_LOW (Stop motors from spinning).
	GPIO_writePin(DcMotor1_PORT, DcMotor1_PIN, LOGIC_LOW);
	GPIO_writePin(DcMotor1_PORT, (DcMotor1_PIN + 1), LOGIC_LOW);
	GPIO_writePin(DcMotor2_PORT, DcMotor2_PIN, LOGIC_LOW);
	GPIO_writePin(DcMotor2_PORT, (DcMotor2_PIN + 1), LOGIC_LOW);
}

/*
 * Description :
 * Changes the direction a single motor is moving towards
 */
static void DcMotor_Rotate(DcMotor_State state, uint8 ID) {
	if (ID == DcMotor1_ID) {
		switch (state) {
		case STOP:

			GPIO_writePin(DcMotor1_PORT, DcMotor1_PIN, LOGIC_LOW);
			GPIO_writePin(DcMotor1_PORT, (DcMotor1_PIN + 1), LOGIC_LOW);
			break;
		case CW:
			GPIO_writePin(DcMotor1_PORT, DcMotor1_PIN, LOGIC_LOW);
			GPIO_writePin(DcMotor1_PORT, (DcMotor1_PIN + 1), LOGIC_HIGH);
			break;
		case A_CW:
			GPIO_writePin(DcMotor1_PORT, DcMotor1_PIN, LOGIC_HIGH);
			GPIO_writePin(DcMotor1_PORT, (DcMotor1_PIN + 1), LOGIC_LOW);
			break;
		}
	} else if (ID == DcMotor2_ID) {
		switch (state) {
		case STOP:

			GPIO_writePin(DcMotor2_PORT, DcMotor2_PIN, LOGIC_LOW);
			GPIO_writePin(DcMotor2_PORT, (DcMotor2_PIN + 1), LOGIC_LOW);
			break;
		case CW:
			GPIO_writePin(DcMotor2_PORT, DcMotor2_PIN, LOGIC_LOW);
			GPIO_writePin(DcMotor2_PORT, (DcMotor2_PIN + 1), LOGIC_HIGH);
			break;
		case A_CW:
			GPIO_writePin(DcMotor2_PORT, DcMotor2_PIN, LOGIC_HIGH);
			GPIO_writePin(DcMotor2_PORT, (DcMotor2_PIN + 1), LOGIC_LOW);
			break;
		}
	}
}

/*
 * Description :
 * Changes the direction the vehicle is moving towards and sets the speed
 */
void DcMotor_Move(INPUT_DirectionType direction,INPUT_SpeedType speed) {
	/*call the timer start function to provide the correct speed for the motor*/
	PWM_Timer0_Start(255 * ((float) speed / 100.0));
	switch (direction) {
	case HALT:
		DcMotor_Rotate(STOP, DcMotor1_ID);
		DcMotor_Rotate(STOP, DcMotor2_ID);
		break;
	case FORWARD:
		DcMotor_Rotate(CW, DcMotor1_ID);
		DcMotor_Rotate(CW, DcMotor2_ID);
		break;
	case BACKWARD:
		DcMotor_Rotate(A_CW, DcMotor1_ID);
		DcMotor_Rotate(A_CW, DcMotor2_ID);
		break;
	case RIGHT:
		DcMotor_Rotate(STOP, DcMotor1_ID);
		DcMotor_Rotate(CW, DcMotor2_ID);
		break;
	case LEFT:
		DcMotor_Rotate(CW, DcMotor1_ID);
		DcMotor_Rotate(STOP, DcMotor2_ID);
		break;
	}

}
