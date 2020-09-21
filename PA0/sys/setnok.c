/* setnok.c - setnok */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 *  setnok  -  set next-of-kin (notified at death) for a given process
 *------------------------------------------------------------------------
 */
SYSCALL	setnok(int nok, int pid)
{	
	int end_time;
	int start_time = ctr1000;
	//kprintf("\n SETNOK start time %d \n", start_time);
	proctab[currpid].syscallcount[SETNOK]++;
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid)) {
		restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SETNOK], start_time,end_time);
		return(SYSERR);
	}
	pptr = &proctab[pid];
	pptr->pnxtkin = nok;
	restore(ps);
	
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[SETNOK], start_time,end_time);
	
	return(OK);
}
