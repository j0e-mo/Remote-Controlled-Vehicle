 /******************************************************************************
 *
 * Module: MOTO
 *
 * File Name: motor.h
 *
 * Description: Header file for the AVR MOTOR driver
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#ifndef MOTOR_H_
#define MOTOR_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#include "std_types.h"
#include "input.h"
#define DcMotor1_PORT PORTC_ID
#define DcMotor1_PIN PIN0_ID

#define DcMotor2_PORT PORTC_ID
#define DcMotor2_PIN PIN2_ID

#define DcMotor1_ID 1
#define DcMotor2_ID 2
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	STOP,CW,A_CW
}DcMotor_State;
/*type definition for rotation directions of the Dc Motor*/
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initializes the motor module with connected h-bridge
 */
void DcMotor_Init(void);

/*
 * Description :
 * Changes the direction a single motor is moving towards
 */
static void DcMotor_Rotate(DcMotor_State state, uint8 ID);

/*
 * Description :
 * Changes the direction the vehicle is moving towards and sets the speed
 */
void DcMotor_Move(INPUT_DirectionType direction,INPUT_SpeedType speed);

#endif /* MOTOR_H_ */
