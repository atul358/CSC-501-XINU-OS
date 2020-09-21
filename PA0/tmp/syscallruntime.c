#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

void syscallruntime(int *p, int stime,  int etime)
{
	//kprintf("\n syscallruntime stime %d etime %d\n", stime, etime);
       	int run_time;
	run_time = etime - stime;
	*p = *p + run_time;
	//kprintf("\n avgtime = %d \n", avg_time);
	//proctab[currpid].syscalltime[CREATE] = proctab[currpid].syscalltime[CREATE] + avg_time;
	//kprintf("\n syscallruntime pointer   %d \n", *p );

	return;
}
