/*
 * UART_prog.c
 *
 *  Created on: August 31th, 2026
 *      Author: Abd El Rahman Sidky
 */

#include <stdint.h>
#include <stddef.h>
#include "registers.h"
#include "DIO_int.h"
#include "Timer_config.h"
#include "UART_privt.h"
#include "UART_config.h"
#include "UART_int.h"

uint8_t UART_init(uint8_t id, uint32_t baud, uint8_t uart_type){
	if((id < 4) && (id != 0) && (baud != 0) && (uart_type <= 1)){
		switch(id){
			case UART1_ID:
				RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
				DIO_setMode(UART1_PORT,UART1_TX_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
				DIO_setMode(UART1_PORT,UART1_RX_PIN, DIO_INPUT,DIO_FLOATING_INPUT);
				USART1->BRR = (System_CLK + (baud / 2)) / baud;
				USART1->CR1 |= ((uart_type)? (USART_CR1_TE | USART_CR1_RE): (USART_CR1_TE));
				break;
			case UART2_ID:
				RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
				DIO_setMode(UART2_PORT,UART2_TX_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
				DIO_setMode(UART2_PORT,UART2_RX_PIN, DIO_INPUT,DIO_FLOATING_INPUT);
				USART2->BRR = (System_CLK + (baud / 2)) / baud;
				USART2->CR1 |= ((uart_type)? (USART_CR1_TE | USART_CR1_RE): (USART_CR1_TE));
				break;
			case UART3_ID:
				RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
				DIO_setMode(UART3_PORT,UART3_TX_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
				DIO_setMode(UART3_PORT,UART3_RX_PIN, DIO_INPUT,DIO_FLOATING_INPUT);
				USART3->BRR = (System_CLK + (baud / 2)) / baud;
				USART3->CR1 |= ((uart_type)? (USART_CR1_TE | USART_CR1_RE): (USART_CR1_TE));
				break;
			default: return 1;
		}
	}
	else
		return 1;
	return 0;
}

uint8_t UART_putc(uint8_t id, const char data){
	uint32_t counter = UART_TIMEOUT_COUNT;
	USART_t *u;
	switch(id){
		case UART1_ID: u = USART1; break;
		case UART2_ID: u = USART2; break;
		case UART3_ID: u = USART3; break;
		default: return 1;
	}
	while(!(u->SR & USART_SR_TXE)){
		counter--;
		if(counter == 0){
			return 1;
		}
	}
	u->DR = data;

	return 0;
}

// only works with a string
uint8_t UART_puts(uint8_t id, const char *data){
	switch(id){
		case UART1_ID: break;
		case UART2_ID: break;
		case UART3_ID: break;
		default: return 1;
	}
	if(data != NULL){
		int i = 0;
		while(data[i] != '\0'){
			if(!(UART_putc(id, data[i])))
				i++;
			else
				return 1;
		}
	}
	else
		return 1;
	return 0;
}

uint8_t UART_getc(uint8_t id, uint8_t *byte){
	uint32_t counter = UART_TIMEOUT_COUNT;
	USART_t *u;
	if(byte != NULL){
		switch(id){
			case UART1_ID: u = USART1; break;
			case UART2_ID: u = USART2; break;
			case UART3_ID: u = USART3; break;
			default: return 1;
		}
		while(!(u->SR & USART_SR_RXNE)){
			counter--;
			if(counter == 0)
				return 1;
		}
		*byte = (uint8_t)u->DR;
	}
	else
		return 1;
	return 0;
}

uint8_t UART_enable(uint8_t id){
	switch(id){
		case UART1_ID:
			USART1->CR1 |= USART_CR1_UE;
			break;
		case UART2_ID:
			USART2->CR1 |= USART_CR1_UE;
			break;
		case UART3_ID:
			USART3->CR1 |= USART_CR1_UE;
			break;
		default: return 1;
	}
	return 0;
}

uint8_t UART_disable(uint8_t id){
	switch(id){
		case UART1_ID:
			USART1->CR1 &= ~(USART_CR1_UE);
			break;
		case UART2_ID:
			USART2->CR1 &= ~(USART_CR1_UE);
			break;
		case UART3_ID:
			USART3->CR1 &= ~(USART_CR1_UE);
			break;
		default: return 1;
	}
	return 0;
}
