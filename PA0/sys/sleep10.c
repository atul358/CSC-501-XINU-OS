/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep10(int n)
{
	int end_time;
	int start_time = ctr1000;
	//kprintf("\n SLEEP10 start time %d \n", start_time);
	proctab[currpid].syscallcount[SLEEP10]++;
	STATWORD ps;    
	if (n < 0  || clkruns==0)
	{
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SLEEP10], start_time,end_time);
         return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[SLEEP10], start_time,end_time);
	return(OK);
}
