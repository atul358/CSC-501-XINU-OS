/* sreset.c - sreset */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

#include <lab0.h>
extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 *  sreset  --  reset the count and queue of a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL sreset(int sem, int count)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	int	pid;
	int	slist;
			  int end_time;
        int start_time = ctr1000;
        kprintf("\n sreset start time %d \n", start_time);
        proctab[currpid].syscallcount[SRESET]++;

	disable(ps);
	if (isbadsem(sem) || count<0 || semaph[sem].sstate==SFREE) {
		restore(ps);
	 end_time = ctr1000;
syscallruntime(&proctab[currpid].syscalltime[SRESET], start_time,end_time);

		return(SYSERR);
	}
	sptr = &semaph[sem];
	slist = sptr->sqhead;
	while ((pid=getfirst(slist)) != EMPTY)
		ready(pid,RESCHNO);
	sptr->semcnt = count;
	resched();
	restore(ps);
	
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SRESET], start_time,end_time);
	return(OK);
}
