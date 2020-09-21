/* suspend.c - suspend */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;


/*------------------------------------------------------------------------
 *  suspend  --  suspend a process, placing it in hibernation
 *------------------------------------------------------------------------
 */
SYSCALL	suspend(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority returned		*/
	int end_time;
        int start_time = ctr1000;
        //kprintf("\n suspend start time %d \n", start_time);
        proctab[currpid].syscallcount[SUSPEND]++;

	disable(ps);
	if (isbadpid(pid) || pid==NULLPROC ||
	 ((pptr= &proctab[pid])->pstate!=PRCURR && pptr->pstate!=PRREADY)) {
		restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SUSPEND], start_time,end_time);
		return(SYSERR);
	}
	if (pptr->pstate == PRREADY) {
		pptr->pstate = PRSUSP;
		dequeue(pid);
	}
	else {
		pptr->pstate = PRSUSP;
		resched();
	}
	prio = pptr->pprio;
	restore(ps);

	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SUSPEND], start_time,end_time);
	return(prio);
}
