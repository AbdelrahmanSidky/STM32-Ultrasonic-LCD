/*
 * UART_privt.h
 *
 *  Created on: August 31th, 2026
 *      Author: Abd El Rahman Sidky
 */
#ifndef UART_PRIVT_H_
#define UART_PRIVT_H_

#define PERIPH_BASE        0x40000000UL
#define APB1PERIPH_BASE    0x40000000UL
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000UL)

#define USART1_BASE        (APB2PERIPH_BASE + 0x3800UL)
#define USART2_BASE        (APB1PERIPH_BASE + 0x4400UL)
#define USART3_BASE        (APB1PERIPH_BASE + 0x4800UL)


#define UART1_TX_PIN       DIO_PIN9
#define UART1_RX_PIN       DIO_PIN10
#define UART1_PORT         DIO_PortA

#define UART2_TX_PIN       DIO_PIN2
#define UART2_RX_PIN       DIO_PIN3
#define UART2_PORT         DIO_PortA

#define UART3_TX_PIN       DIO_PIN10
#define UART3_RX_PIN       DIO_PIN11
#define UART3_PORT         DIO_PortB

typedef struct {
    volatile uint32_t SR;      /* Status register          */
    volatile uint32_t DR;      /* Data register            */
    volatile uint32_t BRR;     /* Baud rate register       */
    volatile uint32_t CR1;     /* Control register 1       */
    volatile uint32_t CR2;     /* Control register 2       */
    volatile uint32_t CR3;     /* Control register 3       */
    volatile uint32_t GTPR;    /* Guard time & prescaler   */
} USART_t;

#define USART1   ((USART_t *) USART1_BASE)
#define USART2   ((USART_t *) USART2_BASE)
#define USART3   ((USART_t *) USART3_BASE)

// RCC clock enable bits
#define RCC_APB2ENR_USART1EN   (1U << 14)
#define RCC_APB1ENR_USART2EN   (1U << 17)
#define RCC_APB1ENR_USART3EN   (1U << 18)

/* SR bits */
#define USART_SR_TXE     (1U << 7)   /* TX buffer empty - write next byte */
#define USART_SR_TC      (1U << 6)   /* Transmission complete */
#define USART_SR_RXNE    (1U << 5)   /* RX buffer not empty - read DR */

/* CR1 bits */
#define USART_CR1_UE     (1U << 13)  /* USART enable */
#define USART_CR1_TE     (1U << 3)   /* Transmitter enable */
#define USART_CR1_RE     (1U << 2)   /* Receiver enable */

/* Blocking timeout */
#define UART_TIMEOUT_COUNT   1000000U

#endif
