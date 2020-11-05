/* vfreemem.c - vfreemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <proc.h>
#include <paging.h>
extern struct pentry proctab[];
/*------------------------------------------------------------------------
 *  vfreemem  --  free a virtual memory block, returning it to vmemlist
 *------------------------------------------------------------------------
 */
SYSCALL	vfreemem(block, size)
	struct	mblock	*block;
	unsigned size;
{
	STATWORD ps;
        struct  mblock  *p, *q;
        unsigned top;
	
        if (size==0 || (unsigned)block>(unsigned)maxaddr
            || ((unsigned)block)<((unsigned) &end))
                return(SYSERR);
        size = (unsigned)roundmb(size);
        disable(ps);
        struct pentry *pent;
	pent = &proctab[currpid];
	int m, n;
	m = pent->vmemlist->mnext;
	n = (struct mblock *) NULL;
	for (p = m; p != n; q = p ){
		for(q = &pent->vmemlist; p < block; p = p->mnext)
			{	
				;
			}
		}
	

        if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= pent->vmemlist) ||
            (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
                restore(ps);
                return(SYSERR);
        }
        if ( q!= pent->vmemlist && top == (unsigned)block )
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
        return(OK);	

}
