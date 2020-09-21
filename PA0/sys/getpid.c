/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;


/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	int end_time, start_time;
	start_time = ctr1000;
	//kprintf("\n getpid start time %d \n", start_time);
	proctab[currpid].syscallcount[GETPID]++;
	
	
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[GETPID], start_time,end_time);
	return(currpid);
}
