/*
 * Timer_privt.h
 *
 *  Created on: August 26th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef TIMER_PRIVT_H_
#define TIMER_PRIVT_H_

#define PERIPH_BASE        0x40000000UL
#define APB1PERIPH_BASE    0x40000000UL
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE     (PERIPH_BASE + 0x00020000UL)

#define TIM1_BASE          (APB2PERIPH_BASE + 0x2C00UL)
#define TIM2_BASE          (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE          (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE          (APB1PERIPH_BASE + 0x0800UL)

#define TIM1_CH1_PIN     DIO_PIN8
#define TIM1_CH2_PIN     DIO_PIN9
#define TIM1_CH3_PIN     DIO_PIN10
#define TIM1_CH4_PIN     DIO_PIN11
#define TIM2_CH1_PIN     DIO_PIN0
#define TIM2_CH2_PIN     DIO_PIN1
#define TIM2_CH3_PIN     DIO_PIN2
#define TIM2_CH4_PIN     DIO_PIN3
#define TIM3_CH1_PIN     DIO_PIN6
#define TIM3_CH2_PIN     DIO_PIN7
#define TIM3_CH3_PIN     DIO_PIN0
#define TIM3_CH4_PIN     DIO_PIN1
#define TIM4_CH1_PIN     DIO_PIN6
#define TIM4_CH2_PIN     DIO_PIN7
#define TIM4_CH3_PIN     DIO_PIN8
#define TIM4_CH4_PIN     DIO_PIN9

#define TIM1_CH_PORT       	DIO_PortA
#define TIM2_CH_PORT       	DIO_PortA
#define TIM3_CH12_PORT     	DIO_PortA
#define TIM3_CH34_PORT     	DIO_PortB
#define TIM4_CH_PORT     	DIO_PortB

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RCR;     /* TIM1 only */
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t BDTR;    /* TIM1 only */
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
} TIM_t;

#define TIM1   ((TIM_t *) TIM1_BASE)
#define TIM2   ((TIM_t *) TIM2_BASE)
#define TIM3   ((TIM_t *) TIM3_BASE)
#define TIM4   ((TIM_t *) TIM4_BASE)

#define NVIC_BASE   0xE000E100UL

typedef struct{
	volatile uint32_t ISER[8];       /* Interrupt Set-Enable Registers */
	uint32_t RESERVED0[24];
	volatile uint32_t ICER[8];       /* Interrupt Clear-Enable Registers */
} NVIC_t;

#define NVIC    ((NVIC_t *)NVIC_BASE)


#endif
