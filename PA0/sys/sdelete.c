/* sdelete.c - sdelete */

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
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{
	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;
	int end_time;
        int start_time = ctr1000;
        //kprintf("\n sdelete start time %d \n", start_time);
        proctab[currpid].syscallcount[SDELETE]++;

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);
		end_time = ctr1000;
        	syscallruntime(&proctab[currpid].syscalltime[SDELETE], start_time,end_time);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SDELETE], start_time,end_time);
	
	return(OK);
}
