/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <stdio.h>
#include <proc.h>
#include <lab0.h>
extern long ctr1000;
extern int currpid;
extern int total_proc[NPROC];
/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
SYSCALL	freemem(struct mblock *block, unsigned size)
{	
	int start_time = ctr1000;
	int end_time, run_time;
	proctab[currpid].syscallcount[FREEMEM]++;
	
	//total_proc[currpid] = 1;
	//kprintf("\nctr1000 === %d\n", ctr1000);
	STATWORD ps;    
	struct	mblock	*p, *q;
	unsigned top;

	if (size==0 || (unsigned)block>(unsigned)maxaddr
	    || ((unsigned)block)<((unsigned) &end))
		{end_time = ctr1000;
        	run_time = end_time - start_time;
		proctab[currpid].syscalltime[FREEMEM] = proctab[currpid].syscalltime[FREEMEM] + run_time;
		return(SYSERR);}
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);
		end_time = ctr1000;
                run_time = end_time - start_time;
                proctab[currpid].syscalltime[FREEMEM] = proctab[currpid].syscalltime[FREEMEM] + run_time;
		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);
	end_time = ctr1000;
	run_time = end_time - start_time;
	//syscallinit(currpid, FREEMEM, start_time );
        //syscallruntime(&proctab[currpid].syscalltime[FREEMEM], start_time, end_time);
	
	//kprintf("call_time %d\n", call_time);
	proctab[currpid].syscalltime[FREEMEM] = proctab[currpid].syscalltime[FREEMEM] + run_time;
	

	//kprintf("\nfreemem syscallcount %d \n", proctab[currpid].syscallcount[FREEMEM]);
	//kprintf("\nfreemem syscalltime %d \n", proctab[currpid].syscalltime[FREEMEM]);
	
	//kprintf("\nsystem call end time ctr1000 = %d %d \n",ctr1000, start_time);
	return(OK);
}
