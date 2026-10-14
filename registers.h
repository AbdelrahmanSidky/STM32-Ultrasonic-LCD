/*
 * registers.h
 *
 *  Created on: Aug 24, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <stdint.h>

#define PERIPH_BASE        0x40000000UL
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE     (PERIPH_BASE + 0x00020000UL)

#define RCC_BASE           (AHBPERIPH_BASE + 0x1000UL)
#define GPIOA_BASE         (APB2PERIPH_BASE + 0x0800UL)
#define GPIOB_BASE         (APB2PERIPH_BASE + 0x0C00UL)
#define GPIOC_BASE         (APB2PERIPH_BASE + 0x1000UL)

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
} RCC_TypeDef;

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

#define RCC     ((RCC_TypeDef *) RCC_BASE)
#define GPIOC   ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOA   ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB   ((GPIO_TypeDef *) GPIOB_BASE)

#define RCC_APB2ENR_IOPAEN   (1UL << 2)
#define RCC_APB2ENR_IOPBEN   (1UL << 3)
#define RCC_APB2ENR_IOPCEN   (1UL << 4)

#endif /* REGISTERS_H_ */
