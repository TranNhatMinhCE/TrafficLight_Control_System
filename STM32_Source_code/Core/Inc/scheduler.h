/*
 * scheduler.h
 *
 *  Created on: Dec 12, 2024
 *      Author: LEGION
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#include <stdlib.h>
#include <stdint.h>
#include "software_timer.h"



#define NUM_TASKS	20

typedef struct TaskNode {

	void (* pTask)(void);
	uint8_t taskID;
	uint32_t delay;
	uint32_t period;
	struct TaskNode* next;

} TaskNode;

typedef struct ListTasks {

	TaskNode* tail;
	uint32_t numTask;
	uint32_t total_delay;
	uint32_t emptyslot;

} ListTasks;

TaskNode* create_new_node(void (*pfunc)(), uint32_t delay, uint32_t period);

void sche_init();
void sche_update();
void sche_dispatcher();
uint8_t sche_add_task(void (*pfunc)(), uint32_t delay, uint32_t period);
void sche_delete_task(uint8_t taskID);


#endif /* INC_SCHEDULER_H_ */
