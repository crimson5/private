// proc.c, 159
// all processes are coded here
// processes do not use kernel space (data.h) or code (handlers, tools, etc.)
// all must be done thru system service calls

#include "spede.h"      // cons_...() needs
#include "data.h"       // run_pid needed
#include "proc.h"       // prototypes of processes
#include "syscalls.h"   // API of system service calls

void SystemProc(void) {
	while(1) asm("inb $0x80"); // do nothing for now
}

void UserProc(void) {
	char my_str[] = "  ";  // 2 spaces
	char my_msg[] = " : Hello, World!\n\r";

	while(1) {
		if(GetPid() % 2 == 0){
			my_str[0] = GetPid() + '0';  // fill out 1st space
			Write(TERM2, my_str);       // STDOUT fileno == term2
			Write(TERM2, my_msg);
			GetChar(TERM2);
			Sleep( GetPid() % 20 );       // sleep for a few seconds (PID 5?)
		}
		else{
			my_str[0] = GetPid() + '0';  // fill out 1st space
			Write(TERM1, my_str);       // STDOUT fileno == Term1
			Write(TERM1, my_msg);
			GetChar(TERM1);
			Sleep( GetPid() % 20 );       // sleep for a few seconds (PID 5?)
		}
		
	}
}

void CookerProc(void) {   // will be created by pressing 'c' key
	int i;

	while(1) {
		Mutex(LOCK);
		if(pies == 99) {
			cons_printf("+++++ Cooker %i: too many pies!\n", GetPid());
		}
		else {
			cons_printf("Cooker %i: making pie # %i...\n", GetPid(), ++pies);
			for(i=0; i<LOOP; i++) asm("inb $0x80");      // pie-making time
		}
	Mutex(UNLOCK);
	}
}

void EaterProc(void) {   // will be created by pressing 'e' key
	int i;

	while(1) {
		Mutex(LOCK);
		if(pies == 0) {
			cons_printf("----- Eater %i: no pie to eat!\n", GetPid());
		}
		else {
			cons_printf("Eater %i: eating pie # %i...\n", GetPid(), pies--);
			for(i=0; i<LOOP; i++) asm("inb $0x80");
		}
		Mutex(UNLOCK);
	}
}

