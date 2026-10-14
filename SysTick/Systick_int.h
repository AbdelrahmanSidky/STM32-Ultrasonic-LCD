/*
 * Systick_int.h
 *
 *  Created on: August 26th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef Systick_INT_H_
#define Systick_INT_H_

uint8_t Systick_setTimer(uint16_t ms);

void Systick_watchFlag(void);

void Systick_stopTimer(void);

void Systick_enableInterrupt(void);

void Systick_disableInterrupt(void);


#endif
