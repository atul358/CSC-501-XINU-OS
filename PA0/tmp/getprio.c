/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;
/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	int end_time;
	int start_time = ctr1000;
	kprintf("\n getprio start time %d \n", start_time);
	proctab[currpid].syscallcount[GETPRIO]++;
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		end_time = ctr1000;
        	syscallruntime(&proctab[currpid].syscalltime[GETPRIO], start_time,end_time);
		return(SYSERR);
	}
	restore(ps);
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[GETPRIO], start_time,end_time);
	return(pptr->pprio);
}
