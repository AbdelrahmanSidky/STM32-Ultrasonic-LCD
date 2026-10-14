/*
 * UART_int.h
 *
 *  Created on: August 31th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef UART_INT_H_
#define UART_INT_H_

#define UART_transmitter	0
#define UART_receiver  		1

#define UART1_ID  1
#define UART2_ID  2
#define UART3_ID  3

uint8_t UART_init(uint8_t id, uint32_t baud, uint8_t uart_type);

uint8_t UART_putc(uint8_t id, const char data);

uint8_t UART_puts(uint8_t id, const char *data);

uint8_t UART_getc(uint8_t id, uint8_t *byte);

uint8_t UART_enable(uint8_t id);

uint8_t UART_disable(uint8_t id);


#endif
