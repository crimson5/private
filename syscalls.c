// syscalls.c
// API calls to kernel system services

// GetPid() call
int GetPid(void) {          // no input, has return
	int pid;

	asm("
		pushl %%EAX;        // save register EAX to stack
		movl $100, %%EAX;   // service #100
		int $128;           // interrupt CPU with IDT Event 128
		movl %%EAX, %0;     // after, copy EAX to variable 'pid' (%0 means 1st item below)
		popl %%EAX"         // restore original EAX
			: "=g" (pid)         // output syntax, for output argument
			:                    // no input items
	);
	return pid;
}

// Write() call
void Write(int fileno, char *p) {
	asm("
		pushl %%EAX; 
		pushl %%EBX; 
		pushl %%ECX;	//   save registers that will be used here
		movl $4, %%EAX;
		movl %0, %%EBX;
		movl %1, %%ECX;	//   send in service #, fileno, and p via three suitable registers
		int $128;	//   issue syscall
		popl %%ECX;
		popl %%EBX;
		popl %%EAX"//   recover those saved registers
			:          // no outputs, otherwise, use "=g" (...)
			: "g" (fileno), "g" ((int)p)  // inputs, %0 and %1
	);
}

void Sleep(int i) {
	asm("
		pushl %%EBX; 
		pushl %%EAX;
		movl $101, %%EAX;
		movl %0, %%EBX;// send in # of seconds to sleep (in EBX)
		int $128;
		popl %%EAX;
		popl %%EBX
		"// 101 -> EAX, call "int 128", 
			:
			: "g" (i)
	);
}
void Mutex(int i){
	asm("
		pushl %%EAX;
		pushl %%EBX;
		movl $102, %%EAX;  //move mutex syscall #
		movl %0, %%EBX;   //move arguement
		int $128;
 		popl %%EBX;
		popl %%EAX"//recove registers
			:
			:"g" (i)
	);
}

char GetChar(int fileno){
	char ch;
	asm("
		pushl %%EAX;
		pushl %%EBX;
		movl $103, %%EAX;
		movl %1, %%EBX;
		int $128;
		movl %%EAX, %0;
		popl %%EBX;
		popl %%EAX"
		
			: "=g" ((int) ch)
			: "g" (fileno)
	);
	return ch;
			
}
