/*
 * DIO_int.h
 *
 *  Created on: August 24th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

void DIO_int(void);

uint8_t DIO_setMode(uint8_t port, uint8_t pin, uint8_t mode, uint8_t mode_type);

uint8_t DIO_setValue(uint8_t port, uint8_t pin, uint8_t value);

uint8_t DIO_getValue(uint8_t port, uint8_t pin, uint8_t * value);

uint8_t DIO_togglePin(uint8_t port, uint8_t pin);

uint8_t DIO_setPullType(uint8_t port, uint8_t pin, uint8_t value);

enum
{
	DIO_PortA 		,
	DIO_PortB 		,
	DIO_PortC 		,

	DIO_PIN0=0		    ,
	DIO_PIN1			,
	DIO_PIN2			,
	DIO_PIN3			,
	DIO_PIN4			,
	DIO_PIN5			,
	DIO_PIN6			,
	DIO_PIN7			,
	DIO_PIN8			,
	DIO_PIN9			,
	DIO_PIN10			,
	DIO_PIN11			,
	DIO_PIN12			,
	DIO_PIN13			,
	DIO_PIN14			,
	DIO_PIN15			,

	//  Modes
	DIO_INPUT=0			,
	DIO_OUTPUT_10M		,
	DIO_OUTPUT_2M		,
	DIO_OUTPUT_50M		,
	DIO_ANALOG_INPUT=0	,
	DIO_FLOATING_INPUT	,
	DIO_PULL_INPUT		,
	DIO_GENERAL_OUTPUT=0,
	DIO_OPEN_DRAIN_OUTPUT,
	DIO_FUNCTION_PULL_OUTPUT,
	DIO_FUNCTION_DRAIN_OUTPUT,

	DIO_PULLUP=0        ,
	DIO_PULLDOWN        ,

	DIO_LOW=0			,
	DIO_HIGH
};

#endif
