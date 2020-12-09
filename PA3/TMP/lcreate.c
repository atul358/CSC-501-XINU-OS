#include <conf.h>
#include<kernel.h>
#include<sem.h>
#include<stdio.h>
#include <q.h>
#include<proc.h>
#include<lock.h>



SYSCALL lcreate()
{
	STATWORD ps;
	disable(ps);
	int	ldescp;			
	int	i;
	
	for (i=0 ; i<NLOCKS ; i++) {	

		if (locktab[currpid].lstate == LFREE)
			
            locktab[i].lstate = LUSED;
			restore(ps);
            return(i);
	}
	
	restore(ps);
	return(SYSERR);
}



