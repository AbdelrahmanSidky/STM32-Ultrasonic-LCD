/*
 * Systick_prog.c
 *
 *  Created on: August 26th, 2026
 *      Author: Abd El Rahman Sidky
 */

#include <stdint.h>
#include <stddef.h>
#include "Systick_privt.h"
#include "Systick_config.h"
#include "Systick_int.h"

uint8_t Systick_setTimer(uint16_t ms){
	if(ms < 16777 && ms != 0){
		if(ms < 2097){ // use 8Mhz directly
			STK_CTRL = (1U << 2);
			STK_LOAD = (8000L * ms) - 1;
		}
		else{ /// bigger then 2097   Use 8Mhz/8
			STK_LOAD = (1000L * ms) - 1;
			STK_CTRL = 0;
		}
	}
	else
		return 1;
	STK_VAL = 0;
	STK_CTRL |= (1U << 0);
	return 0;
}

void Systick_watchFlag(void){
	while(!(STK_CTRL & (1U << 16)));
}

void Systick_stopTimer(void){
	STK_CTRL = 0;
}

void Systick_enableInterrupt(void){
	STK_CTRL |= (1U << 1);
}

void Systick_disableInterrupt(void){
	STK_CTRL &= ~(1U << 1);
}

/*
void SysTick_Handler(void){

	// Interrupt function
}
*/
