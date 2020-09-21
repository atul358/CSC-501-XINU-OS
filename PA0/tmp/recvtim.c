/* recvtim.c - recvtim */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 *  recvtim  -  wait to receive a message or timeout and return result
 *------------------------------------------------------------------------
 */
SYSCALL	recvtim(int maxwait)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	int	msg;
			  int end_time;
        int start_time = ctr1000;
        kprintf("\n recvtim start time %d \n", start_time);
        proctab[currpid].syscallcount[RECVTIM]++;

	if (maxwait<0 || clkruns == 0){
		end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[RECVTIM], start_time,end_time);
		return(SYSERR);}
	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait		*/
	        insertd(currpid, clockq, maxwait*1000);
		slnempty = TRUE;
		sltop = (int *)&q[q[clockq].qnext].qkey;
	        pptr->pstate = PRTRECV;
		resched();
	}
	if ( pptr->phasmsg ) {
		msg = pptr->pmsg;	/* msg. arrived => retrieve it	*/
		pptr->phasmsg = FALSE;
	} else {			/* still no message => TIMEOUT	*/
		msg = TIMEOUT;
	}
	restore(ps);
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[RECVTIM], start_time,end_time);
	return(msg);
}
