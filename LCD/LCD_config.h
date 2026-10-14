/*
 * LCD_config.h
 *
 *  Created on: October 12th, 2026
 *      Author: Abd El Rahman Sidky
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_


/*		Mode:		EIGHT_BIT  ---  FOUR_BIT		*/
#define LCD_u8MODE			FOUR_BIT

/*		Control Pin	in Ket	*/
#define RS_GRP				DIO_PortB
#define RS_PIN				DIO_PIN1

#define RW_GRP				DIO_PortB
#define RW_PIN				DIO_PIN0

#define EN_GRP				DIO_PortA
#define EN_PIN				DIO_PIN7

/*		Control Pin	in my Bord		*/
//#define RS_GRP				DIO_PortA
//#define RS_PIN				DIO_PIN0
//
//#define RW_GRP				DIO_PortA
//#define RW_PIN				DIO_PIN1
//
//#define EN_GRP				DIO_PortA
//#define EN_PIN				DIO_PIN2


/*			Data Pins			*/
#define D7_GRP				DIO_PortA
#define D7_PIN				DIO_PIN3

#define D6_GRP				DIO_PortA
#define D6_PIN				DIO_PIN4

#define D5_GRP				DIO_PortA
#define D5_PIN				DIO_PIN5

#define D4_GRP				DIO_PortA
#define D4_PIN				DIO_PIN6

#define D3_GRP				DIO_PortB
#define D3_PIN				DIO_PIN0

#define D2_GRP				DIO_PortC
#define D2_PIN				DIO_PIN1

#define D1_GRP				DIO_PortC
#define D1_PIN				DIO_PIN6

#define D0_GRP				DIO_PortA
#define D0_PIN				DIO_PIN1

#endif /* HAL_LCD_LCD_CONFIG_H_ */
