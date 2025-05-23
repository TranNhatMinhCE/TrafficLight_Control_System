/*
 * global.c
 *
 *  Created on: Nov 10, 2024
 *      Author: LEGION
 */
#include "global.h"

// Gan cac chan vat ly cho khoi chuc nang

/*-------------- Traffic light -----------------*/

STATUS status_traffic_light = INIT;

uint16_t time_of_color[NUM_COLOR] = {5,2,3};
uint16_t default_time_of_color[NUM_COLOR] = {5,2,3};

GPIO_Config Traffic_Light1[2] = {
		{Light11_GPIO_Port, Light11_Pin},
		{Light12_GPIO_Port, Light12_Pin}
};

GPIO_Config Traffic_Light2[2] = {
		{Light21_GPIO_Port, Light21_Pin},
		{Light22_GPIO_Port, Light22_Pin}
};

/*-------------- END Traffic light -----------------*/

STATUS status_mode = INIT;

uint16_t count_road1 = 0;
uint16_t count_road2 = 0;
uint16_t mode = 0;
char ouput1[50], ouput2[50];
void displayLCD() {

	if(is_flag_set(2)) {
		//lcd_clear_display();
		setTimer(2, 40);


		for(int i = 0; i < 50; i++) {
				ouput1[i] = 0;
				ouput2[i] = 0;
			}

		if(status_mode == MANUAL) {

			lcd_goto_XY(1,0);
			lcd_send_string("  MANUAL   ");
			lcd_goto_XY(0,0);
			lcd_send_string(" Customers ");
			lcd_goto_XY(1, 11);
			lcd_send_string("Mode");
			lcd_goto_XY(0, 12);
			lcd_send_string("1");
			return;
		}
		if(status_mode == SET_RED) {
			lcd_goto_XY(0, 0);
			sprintf(ouput1, "t: %ds       ", count_road1);
			lcd_send_string(ouput1);

			lcd_goto_XY(1, 11);
			lcd_send_string("Mode");
			lcd_goto_XY(0, 12);
			lcd_send_string("2");

			lcd_goto_XY(1, 0);
//			sprintf(ouput2, "%d             ", count_road2);
			lcd_send_string("RED       ");

			return;
		}

		if(status_mode == SET_YELLOW) {

			lcd_goto_XY(0,0);
			sprintf(ouput1, "t: %ds       ", count_road1);
			lcd_send_string(ouput1);

			lcd_goto_XY(1, 11);
			lcd_send_string("Mode");
			lcd_goto_XY(0, 12);
			lcd_send_string("3");

			lcd_goto_XY(1, 0);

			lcd_send_string("YELLOW   ");

			return;
		}

		if(status_mode == SET_GREEN) {

			lcd_goto_XY(0, 0);
			sprintf(ouput1, "t: %ds       ", count_road1);
			lcd_send_string(ouput1);

			lcd_goto_XY(1, 11);
			lcd_send_string("Mode");
			lcd_goto_XY(0, 12);
			lcd_send_string("4");

			lcd_goto_XY(1, 0);
			lcd_send_string("GREEN    ");

			return;
		}

		switch(status_traffic_light) {
			case green_red:
				lcd_goto_XY(0, 0);
				sprintf(ouput1, "GREEN:  %d ", count_road1);
				lcd_send_string(ouput1);

				lcd_goto_XY(1, 0);
				sprintf(ouput2, "RED:    %d ", count_road2);
				lcd_send_string(ouput2);

				lcd_goto_XY(1, 11);
				lcd_send_string("Mode");
				lcd_goto_XY(0, 12);
				lcd_send_string("0");

				break;

			case yellow_red:

				lcd_goto_XY(0, 0);
				sprintf(ouput1, "YELLOW: %d ", count_road1);
				lcd_send_string(ouput1);

				lcd_goto_XY(1, 0);
				sprintf(ouput2, "RED:    %d ", count_road2);
				lcd_send_string(ouput2);

				lcd_goto_XY(1, 11);
				lcd_send_string("Mode");
				lcd_goto_XY(0, 12);
				lcd_send_string("0");
				break;

			case red_green:

				lcd_goto_XY(0, 0);
				sprintf(ouput1, "RED:    %d ", count_road1);
				lcd_send_string(ouput1);

				lcd_goto_XY(1, 0);
				sprintf(ouput2, "GREEN:  %d ", count_road2);
				lcd_send_string(ouput2);

				lcd_goto_XY(1, 11);
				lcd_send_string("Mode");
				lcd_goto_XY(0, 12);
				lcd_send_string("0");
				break;

			case red_yellow:
				lcd_goto_XY(0, 0);
				sprintf(ouput1, "RED:    %d ", count_road1);
				lcd_send_string(ouput1);

				lcd_goto_XY(1, 0);
				sprintf(ouput2, "YELLOW: %d ", count_road2);
				lcd_send_string(ouput2);

				lcd_goto_XY(1, 11);
				lcd_send_string("Mode");
				lcd_goto_XY(0, 12);
				lcd_send_string("0");
				break;

			default:
				break;
		}

	}
}

