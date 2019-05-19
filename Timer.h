/*
 * File:   Timer.h
 * Author: Matthias Leeb
 *
 * Created on 22. April 2019, 13:44
 */

#ifndef TIMER_H
#define TIMER_H

#include "types.h"

typedef void (*FUNCTION_HANDLER)(void);


void INIT_Timer1 (void);
void RequestFunction_Timer1 (FUNCTION_HANDLER handle_new);


#endif //TIMER_H