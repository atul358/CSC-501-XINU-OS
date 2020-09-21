/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{
	int end_time;
	int start_time = ctr1000;
	//kprintf("\n RECVCLR start time %d \n", start_time);
	proctab[currpid].syscallcount[RECVCLR]++;
	STATWORD ps;    
	WORD	msg;

	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[RECVCLR], start_time, end_time);
	return(msg);
}
