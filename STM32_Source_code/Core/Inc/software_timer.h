/*
 * software_timer.h
 *
 *  Created on: Nov 10, 2024
 *      Author: LEGION
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_


#include <stdint.h>
#include "main.h"
#include "stm32f1xx_hal.h"
#include "button.h"
#include "scheduler.h"


#define max_timer		10
#define TIMER_CYCLE  	10 // 10ms


extern TIM_HandleTypeDef htim2;
extern uint8_t flag_timer[max_timer];


void timer_init();
void setTimer(uint8_t index, uint16_t duration);
void timer_run();
uint8_t is_flag_set(uint8_t index);

uint8_t index_isnot_used();

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


#endif /* INC_SOFTWARE_TIMER_H_ */
