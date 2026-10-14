/*
 * LCD_int.h
 *
 *  Created on: October 12th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

void LCD_init(void);

void LCD_writeData(uint8_t data);

void LCD_writeCommand(uint8_t cmd);

uint8_t LCD_sendString(const char * Copy_pcString);

void LCD_writeIntegerNum(int32_t Num);

#endif /* HAL_LCD_LCD_INT_H_ */
