#include "process.h"
#include "x86sync.h"

/*****************************************************************************
 * p-schedos-app-1
 *
 *   This tiny application prints red "1"s to the console.
 *   It yields the CPU to the kernel after each "1" using the sys_yield()
 *   system call.  This lets the kernel (kernel.c) pick another
 *   application to run, if it wants.
 *
 *   The other p-schedos-app-* processes simply #include this file after defining
 *   PRINTCHAR appropriately.
 *
 *****************************************************************************/

#ifndef PRINTCHAR
#define PRINTCHAR	('1' | 0x0C00)
#endif

#ifndef PRIORITY
#define PRIORITY 1
#endif

void
pmain(void)
{
	sys_setpriority(PRIORITY);
	int i;

	for (i = 0; i < RUNCOUNT; i++) {
		// Write characters to the console, yielding after each one.
		sys_printchar(PRINTCHAR);
		sys_yield();
	}
	// exit instead of yield
	sys_exit(0);
}
