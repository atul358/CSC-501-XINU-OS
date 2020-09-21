/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	STATWORD ps;    
	if (n<0 || clkruns==0)
		return(SYSERR);
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		return(OK);
	}
	kprintf("start n = %d \n", n);
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0){
		sleep10(10*n);
		kprintf("stop n = %d \n", n);}
	return(OK);
}
