/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <proc.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;


/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
extern	struct	sentry	semaph[];
	
	
	int end_time;
	int start_time = ctr1000;
	//kprintf("\n scount start time %d \n", start_time);
	proctab[currpid].syscallcount[SCOUNT]++;


	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
	{	
	end_time = ctr1000;
        syscallruntime(&proctab[currpid].syscalltime[SCOUNT], start_time,end_time);
	return(SYSERR);
	}
	end_time = ctr1000;
	syscallruntime(&proctab[currpid].syscalltime[SCOUNT], start_time,end_time);
	return(semaph[sem].semcnt);
}
