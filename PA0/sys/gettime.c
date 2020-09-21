/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <proc.h>
#include <lab0.h>
extern int getutim(unsigned long *);
extern long ctr1000;
extern int currpid;

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
    /* long	now; */
	int end_time;
	int start_time = ctr1000;
	//kprintf("\n gettime start time %d \n", start_time);
	proctab[currpid].syscallcount[GETTIME]++;
	/* FIXME -- no getutim */
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[GETTIME], start_time,end_time);
    return OK;
}
