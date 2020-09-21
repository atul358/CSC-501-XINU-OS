/* sleep100.c - sleep100 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 * sleep100  --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep100(int n)
{	
	int end_time;
	int start_time = ctr1000;
	kprintf("\n SLEEP100 start time %d \n", start_time);
	proctab[currpid].syscallcount[SLEEP100]++;

	STATWORD ps;    

	if (n < 0  || clkruns==0)
	{
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SLEEP100], start_time,end_time);
         return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep100(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*10);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[SLEEP100], start_time,end_time);

	return(OK);
}
