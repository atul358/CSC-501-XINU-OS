/* vcreate.c - vcreate */
    
#include <conf.h>
#include <i386.h>
#include <kernel.h>
#include <proc.h>
#include <sem.h>
#include <mem.h>
#include <io.h>
#include <paging.h>

/*
static unsigned long esp;
*/

#define index_len(heap) heap * NBPG

LOCAL	newpid();
/*------------------------------------------------------------------------
 *  create  -  create a process to start running a procedure
 *------------------------------------------------------------------------
 */


SYSCALL vcreate(procaddr,ssize,hsize,priority,name,nargs,args)
	int	*procaddr;		/* procedure address		*/
	int	ssize;			/* stack size in words		*/
	int	hsize;			/* virtual heap size in pages	*/
	int	priority;		/* process priority > 0		*/
	char	*name;			/* name (for debugging)		*/
	int	nargs;			/* number of args that follow	*/
	long	args;			/* arguments (treated like an	*/
					/* array in the code)		*/
{
	 STATWORD ps;
        disable(ps);
	int proc_id;
	int source, resp1, resp2;
	proc_id = create(procaddr,ssize,priority,name,nargs,args);
	if (proc_id != SYSERR){
		if(resp1 = get_bsm(&source) != SYSERR)
		{	
			
			if(resp2 = (bsm_map(proc_id, VPN_BASE, source,hsize)) != SYSERR)
			{
				
				struct mblock *index;
				index = calc_index(source);
				index->mlen = index_len(hsize);
				index->mnext = NULL;
        			restore(ps);
       				return proc_id;
			
			}
		}
		

	restore(ps);
	return SYSERR;
	}
}


/*------------------------------------------------------------------------
 * newpid  --  obtain a new (free) process id
 *------------------------------------------------------------------------
 */
LOCAL	newpid()
{
	int	pid;			/* process id to return		*/
	int	i;

	for (i=0 ; i<NPROC ; i++) {	/* check all NPROC slots	*/
		if ( (pid=nextproc--) <= 0)
			nextproc = NPROC-1;
		if (proctab[pid].pstate == PRFREE)
			return(pid);
	}
	return(SYSERR);
}
