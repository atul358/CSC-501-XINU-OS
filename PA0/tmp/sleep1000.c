/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
{	
	int end_time;
	int start_time = ctr1000;
	kprintf("\n SLEEP1000 start time %d \n", start_time);
	proctab[currpid].syscallcount[SLEEP1000]++;
	STATWORD ps;    

	if (n < 0  || clkruns==0)
	{ 
	 end_time = ctr1000;
syscallruntime(&proctab[currpid].syscalltime[SLEEP1000], start_time,end_time);
        return(SYSERR);
	
	}
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	end_time = ctr1000;
syscallruntime(&proctab[currpid].syscalltime[SLEEP1000], start_time,end_time);

	return(OK);
}
