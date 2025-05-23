/*
 * software_timer.c
 *
 *  Created on: Nov 10, 2024
 *      Author: LEGION
 */
/*
 * software_timer.c
 *
 *  Created on: Aug 1, 2024
 *      Author: Admin
 */


#include "software_timer.h"


uint8_t flag_timer[max_timer];
int timer_counter[max_timer];


void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
	setTimer(2, 40);
}

uint8_t is_flag_set(uint8_t index) {
	return flag_timer[index];
}

void setTimer(uint8_t index, uint16_t duration){
	timer_counter[index] = duration / TIMER_CYCLE;
	flag_timer[index] = 0;
}

void timer_run(){
	for(uint8_t i = 0; i < max_timer; i++) {
		timer_counter[i]--;
		if(timer_counter[i] <= 0)
			flag_timer[i] = 1;
	}
}

///////////////////////////////////////////////////////////
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timer_run();
		getKeyInput();
		sche_update();
	}
}

