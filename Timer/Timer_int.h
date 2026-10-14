/*
 * Timer_int.h
 *
 *  Created on: August 26th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef TIMER_INT_H_
#define TIMER_INT_H_

#define Timer1_ID    1
#define Timer2_ID    2
#define Timer3_ID    3
#define Timer4_ID    4

#define Timer_DirUp    1
#define Timer_DirDown  2

#define Timer_channel1  1
#define Timer_channel2  2
#define Timer_channel3  3
#define Timer_channel4  4


uint8_t Timer_init(uint8_t timer_id, uint16_t prescaler, uint16_t auto_reload);

uint8_t Timer_start(uint8_t timer_id);

uint8_t Timer_stop(uint8_t timer_id);

uint8_t Timer_watchFlag(uint8_t timer_id);

uint8_t Timer_readCNT(uint8_t timer_id, uint16_t *counter);

uint8_t Timer_setDirection(uint8_t timer_id, uint8_t direction);

uint8_t Timer_setTimer(uint8_t Timer_ID, uint32_t ms);

uint8_t Timer_enableInterrupt(uint8_t Timer_ID);

uint8_t Timer_disableInterrupt(uint8_t Timer_ID);

uint8_t Timer_PWM_initChannel(uint8_t Timer_ID, uint8_t channel, uint8_t duty_percentage);

uint8_t Timer_PWM_changeDuty(uint8_t Timer_ID, uint8_t channel, uint8_t duty_percentage);

uint8_t Timer_PWM_fullSetup(uint8_t Timer_ID, uint8_t channel, uint32_t frequency, uint8_t duty_percentage);

#endif
