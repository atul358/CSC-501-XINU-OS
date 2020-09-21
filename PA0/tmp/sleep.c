/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{	
	int end_time;
	int start_time = ctr1000;
	//kprintf("\n sleep start time %d \n", start_time);
	proctab[currpid].syscallcount[SLEEP]++;

	STATWORD ps;    
	if (n<0 || clkruns==0){
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SLEEP], start_time,end_time);
		return(SYSERR);}
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SLEEP], start_time,end_time);
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[SLEEP], start_time,end_time);
	return(OK);
}
