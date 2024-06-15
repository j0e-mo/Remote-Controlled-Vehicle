/******************************************************************************
 *
 * Module: INPUT
 *
 * File Name: input.c
 *
 * Description: Source file for the INPUT module
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#include "input.h"
#include "gpio.h"

INPUT_DirectionType INPUT_direction = 0;
INPUT_SpeedType INPUT_speedSelection = 0;

void INPUT_inputInit(void) {
	GPIO_setupPinDirection(INPUT_PORT, INPUT_PIN, PIN_INPUT);
	GPIO_setupPinDirection(INPUT_PORT, INPUT_PIN + 1, PIN_INPUT);
	GPIO_setupPinDirection(INPUT_PORT, INPUT_PIN + 2, PIN_INPUT);
	GPIO_setupPinDirection(INPUT_PORT, INPUT_PIN + 5, PIN_INPUT);
	GPIO_setupPinDirection(INPUT_PORT, INPUT_PIN + 6, PIN_INPUT);
	GPIO_setupPinDirection(INPUT_PORT, INPUT_PIN + 7, PIN_INPUT);
}

INPUT_DirectionType checkDirectionSelection(void) {
	if (GPIO_readPin(INPUT_PORT, INPUT_PIN) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 1) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 2) == LOGIC_LOW) {
		INPUT_direction = HALT;
		return INPUT_direction;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 1) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 2) == LOGIC_LOW) {
		INPUT_direction = FORWARD;
		return INPUT_direction;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 1) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 2) == LOGIC_LOW) {
		INPUT_direction = BACKWARD;
		return INPUT_direction;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 1) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 2) == LOGIC_LOW) {
		INPUT_direction = RIGHT;
		return INPUT_direction;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 1) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 2) == LOGIC_HIGH) {
		INPUT_direction = LEFT;
		return INPUT_direction;
	}
	return INPUT_direction;
}

INPUT_SpeedType checkSpeedSelection(void) {
	if (GPIO_readPin(INPUT_PORT, INPUT_PIN + 5) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 6) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 7) == LOGIC_LOW) {
		INPUT_speedSelection = NON;
		return INPUT_speedSelection;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN + 5) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 6) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 7) == LOGIC_LOW) {
		INPUT_speedSelection = SLOWEST;
		return INPUT_speedSelection;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN + 5) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 6) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 7) == LOGIC_LOW) {
		INPUT_speedSelection = SLOW;
		return INPUT_speedSelection;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN + 5) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 6) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 7) == LOGIC_LOW) {
		INPUT_speedSelection = MID;
		return INPUT_speedSelection;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN + 5) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 6) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 7) == LOGIC_HIGH) {
		INPUT_speedSelection = FAST;
		return INPUT_speedSelection;
	} else if (GPIO_readPin(INPUT_PORT, INPUT_PIN + 5) == LOGIC_HIGH
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 6) == LOGIC_LOW
			&& GPIO_readPin(INPUT_PORT, INPUT_PIN + 7) == LOGIC_HIGH) {
		INPUT_speedSelection = FASTEST;
		return INPUT_speedSelection;
	}
	return INPUT_speedSelection;
}
