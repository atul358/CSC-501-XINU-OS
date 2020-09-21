/* wait.c - wait */

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
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	struct	pentry	*pptr;
	
			  int end_time;
        int start_time = ctr1000;
        //kprintf("\n wait start time %d \n", start_time);
        proctab[currpid].syscallcount[WAIT]++;

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[WAIT], start_time,end_time);
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[WAIT], start_time,end_time);
		return pptr->pwaitret;
	}
	restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[WAIT], start_time,end_time);
	return(OK);
}
