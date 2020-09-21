/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
SYSCALL	send(int pid, WORD msg)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	int end_time;
        int start_time = ctr1000;
        //kprintf("\n send start time %d \n", start_time);
        proctab[currpid].syscallcount[SEND]++;

	disable(ps);
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SEND], start_time,end_time);
		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV)	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SEND], start_time,end_time);

	return(OK);
}
