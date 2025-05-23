/*
 * button.c
 *
 *  Created on: Nov 10, 2024
 *      Author: LEGION
 */
#include "button.h"

uint16_t KeyReg[MAX_BUTTON][4]; // [number button][register key]

uint16_t TimeOutForKeyPress[MAX_BUTTON];
uint16_t button_pressed[MAX_BUTTON] = {0};
uint16_t button_long_pressed[MAX_BUTTON] = {0};
uint16_t button_flag[MAX_BUTTON] = {0};

void init_button(){
    for (int i = 0; i < MAX_BUTTON; i++) {
        for (int j = 0; j < 4; j++) {
            KeyReg[i][j] = NORMAL_STATE;
        }
        TimeOutForKeyPress[i] = TIME_OUT;
    }
}

void init_gpi_button(int i) {
    switch (i) {
        case 0:
            KeyReg[i][0] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
            break;
        case 1:
            KeyReg[i][0] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
            break;
        case 2:
            KeyReg[i][0] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
            break;
        default:
            break;
    }
}
int isButtonPressed(int number){
	if(button_flag[number] == 1){
		button_flag[number] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int number){
	if(button_long_pressed[number] == 1){
		button_long_pressed[number] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput() {
    for (int i = 0; i < MAX_BUTTON; i++) {
        KeyReg[i][2] = KeyReg[i][1];
        KeyReg[i][1] = KeyReg[i][0];
    }

    for (int i = 0; i < MAX_BUTTON; i++) {
        init_gpi_button(i);

        if ((KeyReg[i][1] == KeyReg[i][0]) && (KeyReg[i][2] == KeyReg[i][1])) {

        	if (KeyReg[i][2] != KeyReg[i][3]) {
                KeyReg[i][3] = KeyReg[i][2];

                if (KeyReg[i][3] == PRESSED_STATE) {
                    TimeOutForKeyPress[i] = TIME_OUT;
                    button_flag[i] = 1;
                }
            }
            else {
                TimeOutForKeyPress[i]--;

                if (TimeOutForKeyPress[i] == 0) {
                    TimeOutForKeyPress[i] = TIME_OUT;

                    if (KeyReg[i][3] == PRESSED_STATE){
                    	button_flag[i] = 0;
                        button_long_pressed[i] = 1;
                    }
                }
            }
        }
    }

}
