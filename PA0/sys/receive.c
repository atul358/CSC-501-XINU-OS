/* receive.c - receive */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>
/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return it
 *------------------------------------------------------------------------
 */

extern long ctr1000;
extern int currpid;

SYSCALL	receive()
{
	int start_time, end_time;
	start_time = ctr1000;
	kprintf("\n receive start time %d \n", start_time);

	proctab[currpid].syscallcount[RECEIVE]++;

	STATWORD ps;    
	struct	pentry	*pptr;
	WORD	msg;

	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait for one	*/
		pptr->pstate = PRRECV;
		resched();
	}
	msg = pptr->pmsg;		/* retrieve message		*/
	pptr->phasmsg = FALSE;
	restore(ps);
	//syscallruntime(currpid, RECEIVE, starttime);
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[RECEIVE], start_time,end_time);	
	return(msg);
}
