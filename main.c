/*
 * main.c
 *
 *  Created on: August 24th, 2026
 *      Author: Abd El Rahman Sidky
 */

#include <stdint.h>
#include <stddef.h>
#include "registers.h"
#include "DIO_int.h"
#include "Systick_int.h"
#include "Timer_int.h"
#include "UART_int.h"
#include "LCD_int.h"
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define Ultra_port       DIO_PortB
#define Ultra_echoPin    DIO_PIN10
#define Ultra_trigPin    DIO_PIN11

uint8_t Ultrasonic_getDistance(uint16_t *cm);

int main(void)
{
	DIO_int();

	UART_init(UART1_ID, 9600,UART_transmitter);
	UART_enable(UART1_ID);

	DIO_setMode(Ultra_port,Ultra_echoPin,DIO_INPUT,DIO_FLOATING_INPUT);
	DIO_setMode(Ultra_port,Ultra_trigPin,DIO_OUTPUT_2M,DIO_GENERAL_OUTPUT);

	LCD_init();
	LCD_writeCommand(0x0C);              /* display on, cursor off */
	LCD_writeCommand(0x80);
	LCD_sendString(" Ultrasonic Read");
	LCD_writeCommand(0xC0);              /* row 1, col 0 */
	LCD_sendString("Distance:");

	uint16_t cm =0;
	while(1){
			LCD_writeCommand(0xC0 + 9);          /* row 1, col 0 */

			if(Ultrasonic_getDistance(&cm) == 0){
				LCD_writeIntegerNum(cm);
				LCD_sendString(" cm    ");    /* trailing spaces wipe old digits */
			}
			else{
				LCD_sendString("Error");
			}

			Systick_setTimer(400);
			Systick_watchFlag();
		}
}

/*
 	while (1){
		if(Ultrasonic_getDistance(&cm) == 0){
			UART_puts(UART1_ID, "Distance: ");
			UART_putc(UART1_ID, '0' + cm / 100);
			UART_putc(UART1_ID, '0' + (cm / 10) % 10);
			UART_putc(UART1_ID, '0' + cm % 10);
			UART_puts(UART1_ID, " cm\r\n");
		}
		Systick_setTimer(500);
		Systick_watchFlag();
	}
 */

void SysTick_Handler(void){
	DIO_togglePin(DIO_PortC,DIO_PIN13);
	// Interrupt function
}

uint8_t Ultrasonic_getDistance(uint16_t *cm){
	if(cm != NULL){
		Timer_init(Timer1_ID,0,80);  // 8 Microsecond
		Timer_setDirection(Timer1_ID, Timer_DirUp);
		DIO_setValue(Ultra_port,Ultra_trigPin,DIO_HIGH);
		Timer_start(Timer1_ID);
		Timer_watchFlag(Timer1_ID);
		DIO_setValue(Ultra_port,Ultra_trigPin,DIO_LOW);
		uint8_t value = 0;
		while(!value){
			if(!DIO_getValue(Ultra_port,Ultra_echoPin,&value)){
				continue;
			}
			else
				return 1;
		}
		Timer_init(Timer1_ID,0,65535);
+		Timer_start(Timer1_ID);
		value = 1;
		while(value){
			if(!DIO_getValue(Ultra_port,Ultra_echoPin,&value)){
				continue;
			}
			else
				return 1;
		}
		Timer_stop(Timer1_ID);
		uint16_t CNT_reg = 0;
		Timer_readCNT(Timer1_ID, &CNT_reg);
		uint32_t numMicroSecond = CNT_reg/8;
		*cm = numMicroSecond/58U;
	}
	else
		return 1;
	return 0;
}

