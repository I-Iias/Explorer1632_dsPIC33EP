/*
 * File:   Tasks.h
 * Author: Matthias Leeb
 *
 * Created on 22. April 2019, 13:44
 */

#ifndef TASKS_H
#define	TASKS_H

#include "types.h"

void Task_scheduler(void);
void Task_1ms(void);
void Task_10ms(void);
void Task_50ms(void);
void Task_100ms(void);
void Task_500ms(void);
void Task_1s(void);
void Task_10s(void);

#endif // TASKS_H