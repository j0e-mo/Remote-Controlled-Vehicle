 /******************************************************************************
 *
 * Module: SENSOR
 *
 * File Name: sensor.c
 *
 * Description: Source file for the AVR SENSOR module
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#include "sensor.h"
#include <avr/interrupt.h>
#include "motor.h"
#include "gpio.h"
#include <util/delay.h>
#include <avr/io.h>


void INTERRUPTS_int0Enable(void) {

	MCUCR|=0x02; //Configure INT0 to be triggered by falling edge.
	GICR|=0x40;
	//Enable INT0.
	GPIO_setupPinDirection(PORTD_ID, 2, PIN_INPUT);
	/*Configure PD2/INT0 as input.*/
	/*We will take the reading of the sensor on this pin.*/
	SREG|=0x80;//Set Global Interrupt Enable bit.
}
void SENSOR_sensorInit(void){
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);
}

ISR(INT0_vect){
	//Stop the motors completely if the sensors gave a reading
	 DcMotor_Move(STOP,NON);
	_delay_ms(1000);
}
