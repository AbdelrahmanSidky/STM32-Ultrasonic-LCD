/*
 * LCD_prog.c
 *
 *  Created on: October 12th, 2026
 *      Author: Abd El Rahman Sidky
 */

#include <stdint.h>
#include <stddef.h>
#include "DIO_int.h"
#include "Systick_int.h"
#include "LCD_config.h"
#include "LCD_priv.h"


void LCD_init(void){

	Systick_setTimer(32);
	Systick_watchFlag();

	DIO_setMode(RS_GRP , RS_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(RW_GRP , RW_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(EN_GRP , EN_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);

	DIO_setMode(D7_GRP , D7_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(D6_GRP , D6_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(D5_GRP , D5_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(D4_GRP , D4_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);

#if LCD_u8MODE == EIGHT_BIT
	DIO_setMode(D3_GRP , D3_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(D2_GRP , D2_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(D1_GRP , D1_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);
	DIO_setMode(D0_GRP , D0_PIN , DIO_OUTPUT_2M, DIO_GENERAL_OUTPUT);

	DIO_setValue(RS_GRP , RS_PIN , DIO_LOW );
	LCD_writeNLatch(0x38);

#elif LCD_u8MODE == FOUR_BIT

	DIO_setValue(RS_GRP , RS_PIN , DIO_LOW );

	DIO_setValue(D7_GRP , D7_PIN , DIO_LOW );
	DIO_setValue(D6_GRP , D6_PIN , DIO_LOW );
	DIO_setValue(D5_GRP , D5_PIN , DIO_HIGH);
	DIO_setValue(D4_GRP , D4_PIN , DIO_LOW );

	DIO_setValue(EN_GRP , EN_PIN , DIO_HIGH);
	Systick_setTimer(5);
	Systick_watchFlag();
	DIO_setValue(EN_GRP , EN_PIN , DIO_LOW);
	//difference speed bt. atmega & lcd
	Systick_setTimer(32);
	Systick_watchFlag();
	LCD_writeNLatch(0x28);

#else
#error "LCD Mode has a wrong configuration"
#endif

	//Display control
	DIO_setValue(RS_GRP , RS_PIN , DIO_LOW );
	LCD_writeNLatch(0x0f);

	//Display Clear
	DIO_setValue(RS_GRP , RS_PIN , DIO_LOW );
	LCD_writeNLatch(0x01);

	//Entry Set
	DIO_setValue(RS_GRP , RS_PIN , DIO_LOW );
	LCD_writeNLatch(0x06);
}

void LCD_writeData(uint8_t data){
	DIO_setValue(RS_GRP , RS_PIN , DIO_HIGH );
	LCD_writeNLatch(data);
}

uint8_t LCD_sendString(const char * Copy_pcString){
	if (Copy_pcString != NULL){
		while (*Copy_pcString)
		{
			DIO_setValue(RS_GRP , RS_PIN , DIO_HIGH );
			LCD_writeNLatch(*Copy_pcString++);
		}
	}
	else
		return 1;
	return 0;
}

void LCD_writeCommand(uint8_t cmd){
	DIO_setValue(RS_GRP, RS_PIN, DIO_LOW);
	LCD_writeNLatch(cmd);
}
/* set cursor: row 0 -> 0x80 + col, row 1 -> 0xC0 + col */

void LCD_writeNLatch(uint8_t data){
#if LCD_u8MODE == EIGHT_BIT

	DIO_setValue(EN_GRP , EN_PIN , DIO_LOW);
	DIO_setValue(RW_GRP , RW_PIN , DIO_LOW);

	//data
	DIO_setValue(D7_GRP , D7_PIN , ((data>>7)&1) );
	DIO_setValue(D6_GRP , D6_PIN , ((data>>6)&1) );
	DIO_setValue(D5_GRP , D5_PIN , ((data>>5)&1) );
	DIO_setValue(D4_GRP , D4_PIN , ((data>>4)&1) );
	DIO_setValue(D3_GRP , D3_PIN , ((data>>3)&1) );
	DIO_setValue(D2_GRP , D2_PIN , ((data>>2)&1) );
	DIO_setValue(D1_GRP , D1_PIN , ((data>>1)&1) );
	DIO_setValue(D0_GRP , D0_PIN , ((data>>0)&1) );


	DIO_setValue(EN_GRP , EN_PIN , DIO_HIGH);
	Systick_setTimer(5);
	Systick_watchFlag();
	DIO_setValue(EN_GRP , EN_PIN , DIO_LOW);

	//difference speed bt. atmega & lcd
	Systick_setTimer(32);
	Systick_watchFlag();

#elif LCD_u8MODE == FOUR_BIT

	DIO_setValue(EN_GRP , EN_PIN , DIO_LOW);
	DIO_setValue(RW_GRP , RW_PIN , DIO_LOW);

	//data
	DIO_setValue(D7_GRP , D7_PIN , ((data>>7)&1) );
	DIO_setValue(D6_GRP , D6_PIN , ((data>>6)&1) );
	DIO_setValue(D5_GRP , D5_PIN , ((data>>5)&1) );
	DIO_setValue(D4_GRP , D4_PIN , ((data>>4)&1) );

	DIO_setValue(EN_GRP , EN_PIN , DIO_HIGH);
	Systick_setTimer(5);
	Systick_watchFlag();
	DIO_setValue(EN_GRP , EN_PIN , DIO_LOW);
	//difference speed bt. atmega & lcd
	Systick_setTimer(20);
	Systick_watchFlag();

	DIO_setValue(D7_GRP , D7_PIN , ((data>>3)&1) );
	DIO_setValue(D6_GRP , D6_PIN , ((data>>2)&1) );
	DIO_setValue(D5_GRP , D5_PIN , ((data>>1)&1) );
	DIO_setValue(D4_GRP , D4_PIN , ((data>>0)&1) );


	DIO_setValue(EN_GRP , EN_PIN , DIO_HIGH);
	Systick_setTimer(5);
	Systick_watchFlag();
	DIO_setValue(EN_GRP , EN_PIN , DIO_LOW);

	//difference speed bt. atmega & lcd
	Systick_setTimer(32);
	Systick_watchFlag();
#else
#error "LCD Mode has a wrong configuration"
#endif
}

/*void LCD_writeIntegerNum(int32_t Num){
	int32_t Local_s32Reverse=0;
	uint8_t Local_u8Remainder=0 , Local_u8NumDigit=0;
	if(Num <0){
		DIO_setValue(RS_GRP , RS_PIN , DIO_HIGH);
		LCD_writeNLatch('-');
		Num *= -1 ;
	}
	while (Num){
		Local_u8Remainder = Num % 10;
		Local_s32Reverse = Local_s32Reverse * 10 + Local_u8Remainder;
		Num /=10;
		Local_u8NumDigit ++;
	}

	while (Local_u8NumDigit){
		Local_u8Remainder = Local_s32Reverse % 10;
		DIO_setValue(RS_GRP , RS_PIN , DIO_HIGH);
		LCD_writeNLatch(Local_u8Remainder + '0');
		Local_s32Reverse /= 10;
		Local_u8NumDigit --;
	}
}
*/

void LCD_writeIntegerNum(int32_t Num){
	char buf[11];
	uint8_t i = 0;
	uint32_t n;

	DIO_setValue(RS_GRP, RS_PIN, DIO_HIGH);
	if(Num < 0){
		LCD_writeNLatch('-');
		n = (uint32_t)(-(int64_t)Num);
	}
	else
		n = (uint32_t)Num;

	do{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	} while(n);

	while(i)
		LCD_writeNLatch(buf[--i]);
}
