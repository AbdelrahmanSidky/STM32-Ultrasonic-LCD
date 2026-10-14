/*
 * Systick_privt.h
 *
 *  Created on: August 26th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef Systick_PRIVT_H_
#define Systick_PRIVT_H_

#define STK_CTRL  (*(volatile uint32_t *)0xE000E010UL)
#define STK_LOAD  (*(volatile uint32_t *)0xE000E014UL)
#define STK_VAL   (*(volatile uint32_t *)0xE000E018UL)

#endif
