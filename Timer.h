/*
 * File:   Timer.h
 * Author: Matthias Leeb
 *
 * Created on 22. April 2019, 13:44
 */

#ifndef TIMER_H
#define TIMER_H

#include "types.h"

extern volatile uint16 TickFlag;

void INIT_Timer1 (void);

#endif //TIMER_H