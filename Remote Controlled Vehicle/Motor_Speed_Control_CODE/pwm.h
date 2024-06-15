 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: pwm.h
 *
 * Description: Header file for the AVR PWM module
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*
 * Description :
 * Function responsible for initialize the Fast PWM mode in timer 0 driver.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
