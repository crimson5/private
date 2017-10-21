// handlers.h, 159

#ifndef _HANDLERS_H_
#define _HANDLERS_H_

#include "types.h"   // need definition of 'func_p_t' below

void NewProcHandler(func_p_t);//phase 1

void TimerHandler(void);//phase 2
void GetPidHandler(void);
void WriteHandler(proc_frame_t *p);
void SleepHandler(void);

void MutexLockHandler(void);//phase 3
void MutexUnlockHandler(void);

void GetCharHandler(int fileno);//phase 5
void TermHandler(int port);
#endif
