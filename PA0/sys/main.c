/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>
int prX;
void halt();

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */


prch(c)
char c;
{
	int i;
	sleep(5);	
}
int main()
{
	kprintf("\n\nHello World, Xinu lives\n\n");
 	kprintf("\nzfunction()\n");
        kprintf("\t0x%08x\n",zfunction(0xaabbccdd));
        /*long zfunc = zfunction(0xaabbccdd);
 *         kprintf("zfunc(0xaabbccdd) = 0x%08x\n",zfunc);*/
	//resume(prX = create(prch,2000,40,"proc A",1,'A'));
	printsegaddress();
        printtos();
        printprocstks(1);
	

	syscallsummary_start();
	resume(prX = create(prch,2000,30,"proc A",1,'A'));
        sleep(2);
	printsegaddress();
        printtos();
        printprocstks(1);
	syscallsummary_stop();
	sleep(2);
	printsyscallsummary();
	//kprintf("\nMain ends \n");

	return 0;
}
