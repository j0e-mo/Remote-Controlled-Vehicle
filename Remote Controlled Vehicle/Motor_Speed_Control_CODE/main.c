/******************************************************************************
 *
 * Module: APPLICATION
 *
 * File Name: main.c
 *
 * Description: Main Source file for the APPLICATION
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#include "header.h"

int main(void) {
	SENSOR_sensorInit();
	DcMotor_Init();
	INPUT_inputInit();

	for (;;) {
		checkDirectionSelection();
		checkSpeedSelection();
		DcMotor_Move(INPUT_direction, INPUT_speedSelection);
	}
}

