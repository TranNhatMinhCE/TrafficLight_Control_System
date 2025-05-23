/*
 * scheduler.c
 *
 *  Created on: Dec 12, 2024
 *      Author: LEGION
 */

#include "scheduler.h"

ListTasks* list_tasks = NULL;

TaskNode* create_new_node(void (*pfunc)(), uint32_t delay, uint32_t period) {
	TaskNode *newNode = (struct TaskNode*)malloc(sizeof(TaskNode));
	newNode->delay = delay;
	newNode->period = period;
	newNode->pTask = pfunc;
	newNode->next = NULL;
	return newNode;
}

void sche_init() {

	timer_init();

	list_tasks = (struct ListTasks*)malloc(sizeof(ListTasks));
	list_tasks->tail = NULL;
	list_tasks->numTask = 0;
	list_tasks->total_delay = 0;
	list_tasks->emptyslot = 0;
}

uint8_t sche_add_task(void (*pfunc)(void), uint32_t delay, uint32_t period) {

		TaskNode* newNode;

		if(list_tasks->tail == NULL) {
			newNode = create_new_node(pfunc, delay, period);
			list_tasks->tail = newNode;
			list_tasks->tail->next = newNode;

			list_tasks->total_delay = delay;

			list_tasks->numTask++;
			return 0;
		}
		TaskNode* temp = list_tasks->tail->next; //head
		// Them vao dau hang doi
		if (delay <= temp->delay) {
			newNode = create_new_node(pfunc, delay, period);
			newNode->next = temp;
			list_tasks->tail->next = newNode;

			temp->delay -= delay;

			list_tasks->numTask++;
			return 0;
		}
		// Them vao cuoi hang doi
		if (delay >= list_tasks->total_delay) {
			newNode = create_new_node(pfunc, delay - list_tasks->total_delay, period);
			newNode->next = temp;
			list_tasks->tail->next = newNode;
			list_tasks->tail = newNode;

			list_tasks->total_delay = delay;

			list_tasks->numTask++;

			return list_tasks->numTask - 1;
		}

		//Them vao giua hang doi
		uint32_t sum_delay = 0;
		uint8_t index = 0;
		while (temp != list_tasks->tail) {

			sum_delay += temp->delay;

			if(delay < sum_delay + temp->next->delay) {

				newNode = create_new_node(pfunc, delay - sum_delay, period);
				newNode->next = temp->next;
				temp->next = newNode;

				newNode->next->delay -= newNode->delay;

				list_tasks->numTask++;
				return index;
			}
			temp = temp->next;
			index++;
		}

		return NUM_TASKS;
}

void sche_update() {

	if(list_tasks == NULL || list_tasks->tail == NULL) return;

	if(list_tasks->tail->next->delay > 0) list_tasks->tail->next->delay--;

	list_tasks->total_delay--;
}

void sche_dispatcher() {

	if(list_tasks == NULL || list_tasks->tail == NULL) return;

	TaskNode* cur_task = list_tasks->tail->next; // head

	if(cur_task->delay == 0) {

		(*(cur_task->pTask))();

		uint32_t save_period = cur_task->period;
		void (*save_pfunc)(void) = cur_task->pTask;

		sche_delete_task(0); // xoa task o dau hang doi

		if(save_period > 0) sche_add_task(save_pfunc, save_period, save_period);

//		cur_task = cur_task->next;
	}
}

void sche_delete_task(uint8_t taskID) {

	if(taskID >= list_tasks->numTask) return;

	TaskNode* preNode = list_tasks->tail;

	if(preNode == preNode->next) {
		list_tasks->tail = NULL;
		free(preNode);
		return;
	}

	for(uint8_t i = 0; i < taskID; i++) preNode = preNode->next;

	TaskNode* delNode = preNode->next;
	preNode->next = delNode->next;

	free(delNode);

	list_tasks->numTask--;
}



