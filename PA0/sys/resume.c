/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;


/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{	int end_time;
	int start_time = ctr1000;
	proctab[currpid].syscallcount[RESUME]++;
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/
	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);
		end_time = ctr1000;
		syscallruntime(&proctab[currpid].syscalltime[RESUME], start_time,end_time);
		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[RESUME], start_time,end_time);
	return(prio);
}
