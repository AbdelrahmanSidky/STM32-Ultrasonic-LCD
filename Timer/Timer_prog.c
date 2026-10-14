/*
 * Timer_prog.c
 *
 *  Created on: August 26th, 2026
 *      Author: Abd El Rahman Sidky
 */

#include <stdint.h>
#include <stddef.h>
#include "DIO_int.h"
#include "Timer_privt.h"
#include "Timer_config.h"
#include "Timer_int.h"
#include "registers.h"

uint8_t Timer_init(uint8_t timer_id, uint16_t prescaler, uint16_t auto_reload){
	if(timer_id == Timer1_ID){
		RCC->APB2ENR |= (1U << 11);
		TIM1->ARR = auto_reload;
		TIM1->PSC = prescaler;
		TIM1->EGR |= (1U << 0);
		TIM1->SR &= ~(1U << 0);
	}
	else if(timer_id == Timer2_ID){
		RCC->APB1ENR |= (1U << 0);
		TIM2->ARR = auto_reload;
		TIM2->PSC = prescaler;
		TIM2->EGR |= (1U << 0);
		TIM2->SR &= ~(1U << 0);
	}
	else if(timer_id == Timer3_ID){
		RCC->APB1ENR |= (1U << 1);
		TIM3->ARR = auto_reload;
		TIM3->PSC = prescaler;
		TIM3->EGR |= (1U << 0);
		TIM3->SR &= ~(1U << 0);
	}
	else if(timer_id == Timer4_ID){
		RCC->APB1ENR |= (1U << 2);
		TIM4->ARR = auto_reload;
		TIM4->PSC = prescaler;
		TIM4->EGR |= (1U << 0);
		TIM4->SR &= ~(1U << 0);
	}
	else
		return 1;
	return 0;
}

uint8_t Timer_start(uint8_t timer_id){
	switch(timer_id){
	case Timer1_ID: TIM1->CNT = 0; TIM1->SR &= ~(1U << 0); TIM1->CR1 |= (1U << 0); break;
	case Timer2_ID: TIM2->CNT = 0; TIM2->SR &= ~(1U << 0); TIM2->CR1 |= (1U << 0); break;
	case Timer3_ID: TIM3->CNT = 0; TIM3->SR &= ~(1U << 0); TIM3->CR1 |= (1U << 0); break;
	case Timer4_ID: TIM4->CNT = 0; TIM4->SR &= ~(1U << 0); TIM4->CR1 |= (1U << 0); break;
	default:
		return 1;
	}
	return 0;
}

uint8_t Timer_stop(uint8_t timer_id){
	switch(timer_id){
		case Timer1_ID:TIM1->CR1 &= ~(1U << 0); break;
		case Timer2_ID:TIM2->CR1 &= ~(1U << 0); break;
		case Timer3_ID:TIM3->CR1 &= ~(1U << 0); break;
		case Timer4_ID:TIM4->CR1 &= ~(1U << 0); break;
		default:
			return 1;
	}
	return 0;
}

uint8_t Timer_readCNT(uint8_t timer_id, uint16_t *counter){
	if(counter != NULL){
		switch(timer_id){
			case Timer1_ID: *counter = TIM1->CNT; break;
			case Timer2_ID: *counter = TIM2->CNT; break;
			case Timer3_ID: *counter = TIM3->CNT; break;
			case Timer4_ID: *counter = TIM4->CNT; break;
			default:
				return 1;
		}
	}
	else
		return 1;
	return 0;
}

uint8_t Timer_watchFlag(uint8_t timer_id){
	switch(timer_id){
		case Timer1_ID:
			while(!((TIM1->SR) & (1U << 0)));
			TIM1->SR &= ~(1U << 0);
			break;
		case Timer2_ID:
			while(!((TIM2->SR) & (1U << 0)));
			TIM2->SR &= ~(1U << 0);
			break;
		case Timer3_ID:
			while(!((TIM3->SR) & (1U << 0)));
			TIM3->SR &= ~(1U << 0);
			break;
		case Timer4_ID:
			while(!((TIM4->SR) & (1U << 0)));
			TIM4->SR &= ~(1U << 0);
			break;
		default:
			return 1;
	}
	return 0;
}

uint8_t Timer_setDirection(uint8_t timer_id, uint8_t direction){
	if((direction == Timer_DirUp) || (direction == Timer_DirDown)){
		switch(timer_id){
			case Timer1_ID:
				if(direction == Timer_DirUp)
					TIM1->CR1 &= ~(1U << 4);
				else
					TIM1->CR1 |= (1U << 4);
				break;
			case Timer2_ID:
				if(direction == Timer_DirUp)
					TIM2->CR1 &= ~(1U << 4);
				else
					TIM2->CR1 |= (1U << 4);
				break;
			case Timer3_ID:
				if(direction == Timer_DirUp)
					TIM3->CR1 &= ~(1U << 4);
				else
					TIM3->CR1 |= (1U << 4);
				break;
			case Timer4_ID:
				if(direction == Timer_DirUp)
					TIM4->CR1 &= ~(1U << 4);
				else
					TIM4->CR1 |= (1U << 4);
				break;
			default:
				return 1;
		}
	}
	else
		return 1;
	return 0;
}

uint8_t Timer_setTimer(uint8_t Timer_ID, uint32_t ms){
	uint16_t prescaler = 1;
	uint64_t load_counter = 0;
	uint64_t ticks = 0;
	if((ms <= 537000) && (Timer_ID <= 4) && (Timer_ID != 0) ){
		ticks = ((uint64_t)System_CLK/1000)*ms;
		while(1){
			load_counter = ticks/prescaler;
			if(load_counter <= 65535)
				break;
			else
				prescaler++;
		}
		Timer_init(Timer_ID,prescaler-1,load_counter-1);
		Timer_setDirection(Timer_ID, Timer_DirUp);
	}
	else
		return 1;
	return 0;
}

uint8_t Timer_enableInterrupt(uint8_t Timer_ID){
	switch(Timer_ID){
		case Timer1_ID:
			TIM1->DIER |= (1U << 0);
			NVIC->ISER[0] |= (1U << 25);
			break;
		case Timer2_ID:
			TIM2->DIER |= (1U << 0);
			NVIC->ISER[0] |= (1U << 28);
			break;
		case Timer3_ID:
			TIM3->DIER |= (1U << 0);
			NVIC->ISER[0] |= (1U << 29);
			break;
		case Timer4_ID:
			TIM4->DIER |= (1U << 0);
			NVIC->ISER[0] |= (1U << 30);
			break;
		default:
			return 1;
	}
	return 0;
}

uint8_t Timer_disableInterrupt(uint8_t Timer_ID){
	switch(Timer_ID){
		case Timer1_ID:
			TIM1->DIER &= ~(1U << 0);
			NVIC->ICER[0] |= (1U << 25);
			break;
		case Timer2_ID:
			TIM2->DIER &= ~(1U << 0);
			NVIC->ICER[0] |= (1U << 28);
			break;
		case Timer3_ID:
			TIM3->DIER &= ~(1U << 0);
			NVIC->ICER[0] |= (1U << 29);
			break;
		case Timer4_ID:
			TIM4->DIER &= ~(1U << 0);
			NVIC->ICER[0] |= (1U << 30);
			break;
		default:
			return 1;
	}
	return 0;
}

uint8_t Timer_PWM_initChannel(uint8_t Timer_ID, uint8_t channel, uint8_t duty_percentage){
	switch(Timer_ID){
		case Timer1_ID:
			switch(channel){
				case Timer_channel1:
					DIO_setMode(TIM1_CH_PORT,TIM1_CH1_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM1->CCMR1 &= ~((3U << 0) | (1U << 3) | (7U << 4));  // clear CC1S, OC1PE, OC1M
					TIM1->CCMR1 |= ((6U << 4) | (1U << 3));
					//             PWM Mode 1 |  preload enable
					TIM1->CCER &= ~(1U << 1); // CC1P = 0 (active high)
					TIM1->CCR1 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
					TIM1->CCER |= (1U << 0);
					break;
				case Timer_channel2:
					DIO_setMode(TIM1_CH_PORT,TIM1_CH2_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM1->CCMR1 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM1->CCMR1 |= ((6U << 12) | (1U << 11));
					TIM1->CCER &= ~(1U << 5);
					TIM1->CCR2 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
					TIM1->CCER |= (1U << 4);
					break;
				case Timer_channel3:
					DIO_setMode(TIM1_CH_PORT,TIM1_CH3_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM1->CCMR2 &= ~((3U << 0) | (1U << 3) | (7U << 4));
					TIM1->CCMR2 |= ((6U << 4) | (1U << 3));
					TIM1->CCER &= ~(1U << 9);
					TIM1->CCR3 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
					TIM1->CCER |= (1U << 8);
					break;
				case Timer_channel4:
					DIO_setMode(TIM1_CH_PORT,TIM1_CH4_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM1->CCMR2 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM1->CCMR2 |= ((6U << 12) | (1U << 11));
					TIM1->CCER &= ~(1U << 13);
					TIM1->CCR4 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
					TIM1->CCER |= (1U << 12);
					break;
				default:
					return 1;
			}
			TIM1->BDTR |= (1U << 15); // Enable Main Output
			break;
		case Timer2_ID:
			switch(channel){
				case Timer_channel1:
					DIO_setMode(TIM2_CH_PORT,TIM2_CH1_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM2->CCMR1 &= ~((3U << 0) | (1U << 3) | (7U << 4));  // clear CC1S, OC1PE, OC1M
					TIM2->CCMR1 |= ((6U << 4) | (1U << 3));	//             PWM Mode 1 |  preload enable
					TIM2->CCER &= ~(1U << 1); // CC1P = 0 (active high)
					TIM2->CCR1 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
					TIM2->CCER |= (1U << 0);
					break;
				case Timer_channel2:
					DIO_setMode(TIM2_CH_PORT,TIM2_CH2_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM2->CCMR1 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM2->CCMR1 |= ((6U << 12) | (1U << 11));
					TIM2->CCER &= ~(1U << 5);
					TIM2->CCR2 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
					TIM2->CCER |= (1U << 4);
					break;
				case Timer_channel3:
					DIO_setMode(TIM2_CH_PORT,TIM2_CH3_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM2->CCMR2 &= ~((3U << 0) | (1U << 3) | (7U << 4));
					TIM2->CCMR2 |= ((6U << 4) | (1U << 3));
					TIM2->CCER &= ~(1U << 9);
					TIM2->CCR3 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
					TIM2->CCER |= (1U << 8);
					break;
				case Timer_channel4:
					DIO_setMode(TIM2_CH_PORT,TIM2_CH4_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM2->CCMR2 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM2->CCMR2 |= ((6U << 12) | (1U << 11));
					TIM2->CCER &= ~(1U << 13);
					TIM2->CCR4 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
					TIM2->CCER |= (1U << 12);
					break;
				default:
					return 1;
			}
			break;
		case Timer3_ID:
			switch(channel){
				case Timer_channel1:
					DIO_setMode(TIM3_CH12_PORT,TIM3_CH1_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM3->CCMR1 &= ~((3U << 0) | (1U << 3) | (7U << 4));  // clear CC1S, OC1PE, OC1M
					TIM3->CCMR1 |= ((6U << 4) | (1U << 3));	//             PWM Mode 1 |  preload enable
					TIM3->CCER &= ~(1U << 1); // CC1P = 0 (active high)
					TIM3->CCR1 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
					TIM3->CCER |= (1U << 0);
					break;
				case Timer_channel2:
					DIO_setMode(TIM3_CH12_PORT,TIM3_CH2_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM3->CCMR1 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM3->CCMR1 |= ((6U << 12) | (1U << 11));
					TIM3->CCER &= ~(1U << 5);
					TIM3->CCR2 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
					TIM3->CCER |= (1U << 4);
					break;
				case Timer_channel3:
					DIO_setMode(TIM3_CH34_PORT,TIM3_CH3_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM3->CCMR2 &= ~((3U << 0) | (1U << 3) | (7U << 4));
					TIM3->CCMR2 |= ((6U << 4) | (1U << 3));
					TIM3->CCER &= ~(1U << 9);
					TIM3->CCR3 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
					TIM3->CCER |= (1U << 8);
					break;
				case Timer_channel4:
					DIO_setMode(TIM3_CH34_PORT,TIM3_CH4_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM3->CCMR2 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM3->CCMR2 |= ((6U << 12) | (1U << 11));
					TIM3->CCER &= ~(1U << 13);
					TIM3->CCR4 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
					TIM3->CCER |= (1U << 12);
					break;
				default:
					return 1;
			}
			break;
		case Timer4_ID:
			switch(channel){
				case Timer_channel1:
					DIO_setMode(TIM4_CH_PORT,TIM4_CH1_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM4->CCMR1 &= ~((3U << 0) | (1U << 3) | (7U << 4));  // clear CC1S, OC1PE, OC1M
					TIM4->CCMR1 |= ((6U << 4) | (1U << 3));	//             PWM Mode 1 |  preload enable
					TIM4->CCER &= ~(1U << 1); // CC1P = 0 (active high)
					TIM4->CCR1 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
					TIM4->CCER |= (1U << 0);
					break;
				case Timer_channel2:
					DIO_setMode(TIM4_CH_PORT,TIM4_CH2_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM4->CCMR1 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM4->CCMR1 |= ((6U << 12) | (1U << 11));
					TIM4->CCER &= ~(1U << 5);
					TIM4->CCR2 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
					TIM4->CCER |= (1U << 4);
					break;
				case Timer_channel3:
					DIO_setMode(TIM4_CH_PORT,TIM4_CH3_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM4->CCMR2 &= ~((3U << 0) | (1U << 3) | (7U << 4));
					TIM4->CCMR2 |= ((6U << 4) | (1U << 3));
					TIM4->CCER &= ~(1U << 9);
					TIM4->CCR3 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
					TIM4->CCER |= (1U << 8);
					break;
				case Timer_channel4:
					DIO_setMode(TIM4_CH_PORT,TIM4_CH4_PIN, DIO_OUTPUT_2M,DIO_FUNCTION_PULL_OUTPUT);
					TIM4->CCMR2 &= ~((3U << 8) | (1U << 11) | (7U << 12));
					TIM4->CCMR2 |= ((6U << 12) | (1U << 11));
					TIM4->CCER &= ~(1U << 13);
					TIM4->CCR4 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
					TIM4->CCER |= (1U << 12);
					break;
				default:
					return 1;
			}
			break;
		default:
			return 1;
	}
	return 0;
}

uint8_t Timer_PWM_changeDuty(uint8_t Timer_ID, uint8_t channel, uint8_t duty_percentage){
	if(duty_percentage <= 100){
		switch(Timer_ID){
			case Timer1_ID:
				switch(channel){
					case Timer_channel1:
						TIM1->CCR1 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
						break;
					case Timer_channel2:
						TIM1->CCR2 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
						break;
					case Timer_channel3:
						TIM1->CCR3 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
						break;
					case Timer_channel4:
						TIM1->CCR4 = ((uint32_t)duty_percentage * (TIM1->ARR + 1)) / 100U;
						break;
					default:
						return 1;
				}
				break;
			case Timer2_ID:
				switch(channel){
					case Timer_channel1:
						TIM2->CCR1 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
						break;
					case Timer_channel2:
						TIM2->CCR2 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
						break;
					case Timer_channel3:
						TIM2->CCR3 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
						break;
					case Timer_channel4:
						TIM2->CCR4 = ((uint32_t)duty_percentage * (TIM2->ARR + 1)) / 100U;
						break;
					default:
						return 1;
				}
				break;
			case Timer3_ID:
				switch(channel){
					case Timer_channel1:
						TIM3->CCR1 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
						break;
					case Timer_channel2:
						TIM3->CCR2 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
						break;
					case Timer_channel3:
						TIM3->CCR3 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
						break;
					case Timer_channel4:
						TIM3->CCR4 = ((uint32_t)duty_percentage * (TIM3->ARR + 1)) / 100U;
						break;
					default:
						return 1;
				}
				break;
			case Timer4_ID:
				switch(channel){
					case Timer_channel1:
						TIM4->CCR1 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
						break;
					case Timer_channel2:
						TIM4->CCR2 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
						break;
					case Timer_channel3:
						TIM4->CCR3 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
						break;
					case Timer_channel4:
						TIM4->CCR4 = ((uint32_t)duty_percentage * (TIM4->ARR + 1)) / 100U;
						break;
					default:
						return 1;
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

uint8_t Timer_PWM_fullSetup(uint8_t Timer_ID, uint8_t channel, uint32_t frequency, uint8_t duty_percentage){
	if((frequency <= System_CLK) && (duty_percentage <= 100)){
		uint64_t var = System_CLK/frequency;
		uint16_t prescaler = 0;
		uint16_t ARR = 0;
		uint32_t error = System_CLK;
		for(uint32_t i = 0; i <= 65535; i++){
			for(uint32_t j = 0; j <= 65535; j++){
				var = System_CLK/((i+1)*(j+1));
				if(((var >= frequency)? ((var-frequency)<error) : ((frequency-var)<error))){
					error = (var >= frequency)? (var-frequency) : (frequency-var);
					prescaler = i;
					ARR = j;
					if(error == 0){
						break;
					}
				}
			}
			if(error == 0){
			break;
			}
		}
		return (Timer_init(Timer_ID,prescaler,ARR) ||  Timer_PWM_initChannel(Timer_ID,channel,duty_percentage));
	}
	else
		return 1;
}
//   IRQHandler

/*
void TIM1_UP_IRQHandler(void){
	if(TIM1->SR & (1U << 0)){
		TIM1->SR &= ~(1U << 0);

	}
}

void TIM2_IRQHandler(void){
	if(TIM2->SR & (1U << 0)){
		TIM2->SR &= ~(1U << 0);

	}
}

void TIM3_IRQHandler(void){
	if(TIM3->SR & (1U << 0)){
		TIM3->SR &= ~(1U << 0);

	}
}

void TIM4_IRQHandler(void){
	if(TIM4->SR & (1U << 0)){
		TIM4->SR &= ~(1U << 0);

	}
}
*/
