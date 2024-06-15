/******************************************************************************
 *
 * Module: INPUT
 *
 * File Name: input.h
 *
 * Description: Header file for the INPUT module
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#ifndef INPUT_H_
#define INPUT_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define INPUT_PORT PORTB_ID
#define INPUT_PIN PIN0_ID

typedef enum {
	HALT, FORWARD, BACKWARD, RIGHT, LEFT
} INPUT_DirectionType;

typedef enum {
	NON, SLOWEST = 10, SLOW = 25, MID = 50, FAST = 75, FASTEST = 100
} INPUT_SpeedType;
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
extern INPUT_DirectionType INPUT_direction;
extern INPUT_SpeedType INPUT_speedSelection;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * initializes the INPUT module
 */
void INPUT_inputInit(void);

/*
 * Description :
 * Checks for the input provided by user.
 * returns a value of type INPUT_DirectionType
 */
INPUT_DirectionType checkDirectionSelection(void);
INPUT_SpeedType checkSpeedSelection(void);

#endif /* INPUT_H_ */
