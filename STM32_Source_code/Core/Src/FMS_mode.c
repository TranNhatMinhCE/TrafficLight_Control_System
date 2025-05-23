/*
 * FMS_normal_mode.c
 *
 *  Created on: Nov 12, 2024
 *      Author: LEGION
 */

#include "FMS_mode.h"

uint16_t current_value = 0;

void Blinky_led() {

	switch(status_mode) {
		case SET_RED:
			HAL_GPIO_TogglePin(Traffic_Light1[0].Port, Traffic_Light1[0].Pin);
			HAL_GPIO_TogglePin(Traffic_Light1[1].Port, Traffic_Light1[1].Pin);

			HAL_GPIO_TogglePin(Traffic_Light2[0].Port, Traffic_Light2[0].Pin);
			HAL_GPIO_TogglePin(Traffic_Light2[1].Port, Traffic_Light2[1].Pin);
			break;
		case SET_YELLOW: //chu y
			HAL_GPIO_TogglePin(Traffic_Light1[1].Port, Traffic_Light1[1].Pin);
			HAL_GPIO_TogglePin(Traffic_Light2[1].Port, Traffic_Light2[1].Pin);
			break;
		case SET_GREEN:
			HAL_GPIO_TogglePin(Traffic_Light1[0].Port, Traffic_Light1[0].Pin);
			HAL_GPIO_TogglePin(Traffic_Light2[0].Port, Traffic_Light2[0].Pin);
			break;
		default:
			break;
	}
}

void FMS_mode_run() {

	switch(status_mode) {
		case INIT:

			sche_add_task(Blinky_led, 0, 50);
			sche_add_task(TrafficLight_run, 0, 100);
			status_mode = NORMAL;

			break;

		case NORMAL:

			isButtonPressed(1);
			isButtonLongPressed(1);
			isButtonPressed(2);
			isButtonLongPressed(2);

			if(isButtonPressed(0)) {

//				turn_off_traffic_light();

				status_mode = MANUAL;
			}

			break;

		case MANUAL:

			isButtonPressed(2);
			isButtonLongPressed(2);

			if(isButtonPressed(1)) {

				if(status_traffic_light == red_yellow)
					status_traffic_light == green_red;
				else
					status_traffic_light++;
			}
			if(isButtonLongPressed(1)) {

				if(status_traffic_light == green_red)
					status_traffic_light == red_yellow;
				else
					status_traffic_light--;
			}

			Manual_TrafficLight();

			if(isButtonPressed(0)) {
				turn_off_traffic_light();
				current_value = time_of_color[red];
				status_mode = SET_RED;
			}
			break;

		case SET_RED:

			if(isButtonPressed(1))
				current_value++;
			if(isButtonLongPressed(1))
				current_value--;

			if(isButtonPressed(2))
				set_time_value(red, current_value);

			count_road1 = current_value;
			count_road2 = current_value;

			if(isButtonPressed(0)) {
				HAL_GPIO_WritePin(Traffic_Light1[0].Port, Traffic_Light1[0].Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Traffic_Light1[1].Port, Traffic_Light1[1].Pin, GPIO_PIN_RESET);

				HAL_GPIO_WritePin(Traffic_Light2[0].Port, Traffic_Light2[0].Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Traffic_Light2[1].Port, Traffic_Light2[1].Pin, GPIO_PIN_RESET);

				current_value = time_of_color[yellow];
				status_mode = SET_YELLOW;
			}
			break;

		case SET_YELLOW:

			if(isButtonPressed(1))
				current_value++;
			if(isButtonLongPressed(1))
				current_value--;

			if(isButtonPressed(2))
				set_time_value(yellow, current_value);

			count_road1 = current_value;
			count_road2 = current_value;


			if(isButtonPressed(0)) {
				HAL_GPIO_WritePin(Traffic_Light1[1].Port, Traffic_Light1[1].Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Traffic_Light2[1].Port, Traffic_Light2[1].Pin, GPIO_PIN_RESET);

				current_value = time_of_color[green];
				status_mode = SET_GREEN;
			}
			break;

		case SET_GREEN:

			if(isButtonPressed(1))
				current_value++;
			if(isButtonLongPressed(1))
				current_value--;

			if(isButtonPressed(2))
				set_time_value(green, current_value);

			count_road1 = current_value;
			count_road2 = current_value;

			if(isButtonPressed(0)) {
				HAL_GPIO_WritePin(Traffic_Light1[0].Port, Traffic_Light1[0].Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Traffic_Light2[0].Port, Traffic_Light2[0].Pin, GPIO_PIN_RESET);

				status_mode = NORMAL;
				status_traffic_light = INIT;
			}
			break;

		default:
			break;
	}

}
