/*
 * DIO_prog.c
 *
 *  Created on: August 24th, 2026
 *      Author: Abd El Rahman Sidky
 */

#include <stdint.h>
#include <stddef.h>
#include "registers.h"
#include "DIO_privt.h"
#include "DIO_config.h"
#include "DIO_int.h"

void DIO_int(void){
	if(DIO_PortA_Enable)
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	if(DIO_PortB_Enable)
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	if(DIO_PortC_Enable)
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	return;
}

uint8_t DIO_setMode(uint8_t port, uint8_t pin, uint8_t mode, uint8_t mode_type){
	uint8_t final_mode = 0;
	if(  ((port < 3) && (pin < 16)) &&
		( ((mode_type < 3) && (mode == 0)) || ((mode != 0) && (mode < 4) && (mode_type <4))) ){
		final_mode = (mode_type << 2) | mode;
	}
	else
		return 1;
	switch(port){
		case(DIO_PortA):
			if(pin < 8){
				GPIOA->CRL &= ~(0xFU << (pin*4));
				GPIOA->CRL |=  (final_mode << (pin*4));
			}
			else{
				GPIOA->CRH &= ~(0xFU << ((pin-8)*4));
				GPIOA->CRH |=  (final_mode << ((pin-8)*4));
			}
			break;
		case(DIO_PortB):
			if(pin < 8){
				GPIOB->CRL &= ~(0xFU << (pin*4));
				GPIOB->CRL |=  (final_mode << (pin*4));
			}
			else{
				GPIOB->CRH &= ~(0xFU << ((pin-8)*4));
				GPIOB->CRH |=  (final_mode << ((pin-8)*4));
			}
			break;
		case(DIO_PortC):
			if(pin < 8){
				GPIOC->CRL &= ~(0xFU << (pin*4));
				GPIOC->CRL |=  (final_mode << (pin*4));
			}
			else{
				GPIOC->CRH &= ~(0xFU << ((pin-8)*4));
				GPIOC->CRH |=  (final_mode << ((pin-8)*4));
			}
			break;
	}
	return 0;
}

uint8_t DIO_setValue(uint8_t port, uint8_t pin, uint8_t value){
	if((pin < 16) && ((value == DIO_HIGH) || (value == DIO_LOW))){
		switch(port){
			case(DIO_PortA):
				if(value){
					GPIOA->BSRR = (1U << pin);
				}
				else{
					GPIOA->BSRR = (1U << (pin + 16U));
				}
				break;
			case(DIO_PortB):
				if(value){
					GPIOB->BSRR = (1U << pin);
				}
				else{
					GPIOB->BSRR = (1U << (pin + 16U));
				}
				break;
			case(DIO_PortC):
				if(value){
					GPIOC->BSRR = (1U << pin);
				}
				else{
					GPIOC->BSRR = (1U << (pin + 16U));
				}
				break;
			default:
					return 1;
		}
	}
	else
		return 1;
	return 0;
}

uint8_t DIO_getValue(uint8_t port, uint8_t pin, uint8_t * value){
	if((pin < 16) && (value != NULL)){
		switch(port){
			case(DIO_PortA):
				*value = (uint8_t)((GPIOA->IDR >> pin) & 1U);
				break;
			case(DIO_PortB):
				*value = (uint8_t)((GPIOB->IDR >> pin) & 1U);
				break;
			case(DIO_PortC):
				*value = (uint8_t)((GPIOC->IDR >> pin) & 1U);
				break;
			default:
					return 1;
		}
	}
	else
		return 1;
	return 0;
}

uint8_t DIO_togglePin(uint8_t port, uint8_t pin){
	if(pin < 16){
		switch(port){
			case(DIO_PortA):
				if(GPIOA->ODR & (1U << pin)){
					GPIOA->BSRR = (1U << (pin + 16U));
				}
				else{
					GPIOA->BSRR = (1U << pin);
				}
				break;
			case(DIO_PortB):
				if(GPIOB->ODR & (1U << pin)){
					GPIOB->BSRR = (1U << (pin + 16U));
				}
				else{
					GPIOB->BSRR = (1U << pin);
				}
				break;
			case(DIO_PortC):
				if(GPIOC->ODR & (1U << pin)){
					GPIOC->BSRR = (1U << (pin + 16U));
				}
				else{
					GPIOC->BSRR = (1U << pin);
				}
				break;
			default:
					return 1;
		}
	}
	else
		return 1;
	return 0;
}

uint8_t DIO_setPullType(uint8_t port, uint8_t pin, uint8_t type){
	if((pin < 16) && ((type == DIO_PULLUP) || (type == DIO_PULLDOWN))){
		switch(port){
		case(DIO_PortA):
			if(type == DIO_PULLUP){
				GPIOA->ODR |= (1U << pin);
			}
			else{
				GPIOA->ODR &= ~(1U << pin);
			}
			break;
		case(DIO_PortB):
			if(type == DIO_PULLUP){
				GPIOB->ODR |= (1U << pin);
			}
			else{
				GPIOB->ODR &= ~(1U << pin);
			}
			break;
		case(DIO_PortC):
			if(type == DIO_PULLUP){
				GPIOC->ODR |= (1U << pin);
			}
			else{
				GPIOC->ODR &= ~(1U << pin);
			}
			break;
		default:
			return 1;
		}
	}
	else
		return 1;
	return 0;
}
