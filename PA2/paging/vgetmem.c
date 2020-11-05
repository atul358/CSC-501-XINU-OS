
/* vgetmem.c - vgetmem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <proc.h>
#include <paging.h>

extern struct pentry proctab[];

/*------------------------------------------------------------------------
 *  * vgetmem  --  allocate virtual heap storage, returning lowest WORD address
 *   *------------------------------------------------------------------------
 *    */
WORD	*vgetmem(nbytes)
	unsigned nbytes;
{
STATWORD ps;
	if (nbytes == 0){
                kprintf("ERROR in vgetmem: Zero bytes requested.\n");
                restore(ps);
                return( (WORD *)SYSERR);
        }
	
	//struct pentry *pptr = &proctab[currpid];
	struct	mblock	*p, *q, *leftover;
	struct pentry *pent;
	pent = &proctab[currpid];
	disable(ps);
	int m,n;
	m = (struct mblock *)NULL;
	n = pent->vmemlist->mnext;
	  if (nbytes == 0){
                kprintf("ERROR in vgetmem: Zero bytes requested.\n");
                restore(ps);
                return( (WORD *)SYSERR);
        }


	else if (m == n)
	{
		kprintf("ERROR in vgetmem: Zero bytes requested.\n");
                restore(ps);
                return( (WORD *)SYSERR);
	}
	else 
	{
	nbytes = (unsigned int) roundmb(nbytes);
	q = &pent->vmemlist;	
	    do{
		for (p = n; ; p = p->mnext){
		if ( p->mlen == nbytes) {
			q->mnext = p->mnext;
			restore(ps);
			return( (WORD *)p );
		} else if ( p->mlen > nbytes ) {
			leftover = (struct mblock *)( (unsigned)p + nbytes );
			q->mnext = leftover;
			leftover->mnext = p->mnext;
			leftover->mlen = p->mlen - nbytes;
			restore(ps);
			return( (WORD *)p );
			}
		}
	q = p;
	restore(ps);
	return( (WORD *)SYSERR );
	}while(p!=m);
    }
}

