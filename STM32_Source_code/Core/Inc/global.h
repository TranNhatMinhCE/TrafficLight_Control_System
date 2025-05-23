/*
 * global.h
 *
 *  Created on: Nov 10, 2024
 *      Author: LEGION
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdint.h>
#include "main.h"
#include "button.h"
#include "software_timer.h"
#include "scheduler.h"
#include "i2c-lcd.h"
#include <stdio.h>


typedef	uint8_t			STATUS;

typedef struct {
	GPIO_TypeDef* Port; // Port GPIO
	uint16_t Pin;		// Pin GPIO
} GPIO_Config;


/*-------------- Traffic light -----------------*/

typedef	uint8_t		COLOR;
#define	NUM_COLOR	3

#define red			0
#define	yellow		1
#define	green		2

// Traffic light state
#define INIT			0
#define green_red 		2
#define	yellow_red		3
#define	red_green		4
#define	red_yellow		5


extern STATUS status_traffic_light;
extern uint16_t time_of_color[NUM_COLOR];
extern uint16_t default_time_of_color[NUM_COLOR];
extern GPIO_Config Traffic_Light1[2];
extern GPIO_Config Traffic_Light2[2];

/*-------------- END Traffic light -----------------*/


/*--------------------- FMS Mode --------------------*/

#define NORMAL		10
#define SET_RED		11
#define SET_YELLOW	12
#define SET_GREEN	13
#define MANUAL		14

extern STATUS status_mode;

/*--------------------- END FMS Mode --------------------*/

extern uint16_t count_road1;
extern uint16_t count_road2;

void displayLCD();

#endif /* INC_GLOBAL_H_ */
