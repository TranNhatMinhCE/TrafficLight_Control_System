/*
 * traffic_light.c
 *
 *  Created on: Nov 10, 2024
 *      Author: LEGION
 */
#include "traffic_light.h"


void set_time_value(COLOR color, uint16_t new_time) {

	if(color < NUM_COLOR)
		time_of_color[color] = new_time;
}

void turn_off_traffic_light() {

	for(uint8_t i = 0; i < 2; i++) {
		HAL_GPIO_WritePin(Traffic_Light1[i].Port, Traffic_Light1[i].Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Traffic_Light2[i].Port, Traffic_Light2[i].Pin, GPIO_PIN_RESET);
	}
}

void Turn_on_color(GPIO_Config Light[2], COLOR color) {

	switch(color) {
		case red:
			HAL_GPIO_WritePin(Light[0].Port, Light[0].Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Light[1].Port, Light[1].Pin, GPIO_PIN_SET);
			break;
		case green:
			HAL_GPIO_WritePin(Light[0].Port, Light[0].Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Light[1].Port, Light[1].Pin, GPIO_PIN_RESET);
			break;
		case yellow:
			HAL_GPIO_WritePin(Light[0].Port, Light[0].Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Light[1].Port, Light[1].Pin, GPIO_PIN_SET);
			break;
		default:
			break;
	}
}

void TrafficLight_run() {

	if(status_mode != NORMAL) return;

	switch (status_traffic_light) {
		case INIT:
			turn_off_traffic_light();

			status_traffic_light =	green_red;

			count_road1 = time_of_color[green];
			count_road2 = time_of_color[red];

		case green_red:

			Turn_on_color(Traffic_Light1, green);
			Turn_on_color(Traffic_Light2, red);

			if(count_road1 > 0) {
				count_road1--;
				count_road2--;
				break;
			}
			else {
				count_road1 = time_of_color[yellow];
//				count_road2--;
				status_traffic_light = yellow_red;
			}

		case yellow_red:

			Turn_on_color(Traffic_Light1, yellow);
			Turn_on_color(Traffic_Light2, red);

			if(count_road1 > 0) {
				count_road1--;
				count_road2--;
				break;
			}
			else {
				count_road1 = time_of_color[red];
				count_road2 = time_of_color[green];
				status_traffic_light = red_green;
			}

		case red_green:

			Turn_on_color(Traffic_Light1, red);
			Turn_on_color(Traffic_Light2, green);

			if(count_road2 > 0) {
				count_road1--;
				count_road2--;
				break;
			}
			else {
//				count_road1--;
				count_road2 = time_of_color[yellow];
				status_traffic_light = red_yellow;
			}

		case red_yellow:

			Turn_on_color(Traffic_Light1, red);
			Turn_on_color(Traffic_Light2, yellow);

			if(count_road2 > 0) {
				count_road1--;
				count_road2--;
				break;
			}
			else {
				count_road1 = time_of_color[green] - 1;
				count_road2 = time_of_color[red] - 1;

				status_traffic_light = green_red;

				Turn_on_color(Traffic_Light1, green);
				Turn_on_color(Traffic_Light2, red);
			}
		default:
			break;
	}

//	displayLCD();
}

void Manual_TrafficLight() {

	switch (status_traffic_light) {

		case green_red:

			Turn_on_color(Traffic_Light1, green);
			Turn_on_color(Traffic_Light2, red);

			break;

		case yellow_red:

			Turn_on_color(Traffic_Light1, yellow);
			Turn_on_color(Traffic_Light2, red);

			break;

		case red_green:

			Turn_on_color(Traffic_Light1, red);
			Turn_on_color(Traffic_Light2, green);

			break;

		case red_yellow:

			Turn_on_color(Traffic_Light1, red);
			Turn_on_color(Traffic_Light2, yellow);

			break;

		default:
			break;
	}
}

