/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;
/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	short	*nxtdev;
			  int end_time;
        int start_time = ctr1000;
       // kprintf("\n setdev start time %d \n", start_time);
        proctab[currpid].syscallcount[SETDEV]++;

	if (isbadpid(pid)){
		end_time = ctr1000;
	        syscallruntime(&proctab[currpid].syscalltime[SETDEV], start_time,end_time);
		return(SYSERR);
}
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;

	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SETDEV], start_time,end_time);
	return(OK);
}
