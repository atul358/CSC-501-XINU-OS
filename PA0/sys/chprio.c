/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{	int end_time;
	int start_time = ctr1000;
        proctab[currpid].syscallcount[CHPRIO]++;

	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		end_time = ctr1000;
	        syscallruntime(&proctab[currpid].syscalltime[CHPRIO], start_time,end_time);
		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[CHPRIO], start_time,end_time);
	return(newprio);
}
