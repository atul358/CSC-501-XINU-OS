/* signaln.c - signaln */

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
 *  signaln -- signal a semaphore n times
 *------------------------------------------------------------------------
 */
SYSCALL signaln(int sem, int count)
{
	STATWORD ps;    
	struct	sentry	*sptr;
			  int end_time;
        int start_time = ctr1000;
 //       kprintf("\n signaln start time %d \n", start_time);
        proctab[currpid].syscallcount[SIGNALN]++;
	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE || count<=0) {
		restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SIGNALN], start_time,end_time);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	for (; count > 0  ; count--)
		if ((sptr->semcnt++) < 0)
			ready(getfirst(sptr->sqhead), RESCHNO);
	resched();
	restore(ps);

	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SIGNALN], start_time,end_time);
	return(OK);
}
