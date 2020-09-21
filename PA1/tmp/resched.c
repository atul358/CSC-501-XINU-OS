/* resched.c  -  resched */

#include "math.h"
#include "sched.h"
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <math.h>

#define lambda 0.1

unsigned long currSP; /* REAL sp of current process */
extern int ctxsw(int, int, int, int);
/*-----------------------------------------------------------------------
 * resched  --  reschedule processor to highest priority ready process
 *
 * Notes:	Upon entry, currpid gives current process id.
 *		Proctab[currpid].pstate gives correct NEXT state for
 *			current process if other than PRREADY.
 *------------------------------------------------------------------------
 */
int resched() {
  register struct pentry *optr; /* pointer to old process entry */
  register struct pentry *nptr; /* pointer to new process entry */
  int random;
  random = (int)expdev(lambda);
  int next_proc;
  int curr_proc;
  int old_proc;
  // kprintf("\n random value is = %d\n", random);

  if (EXPDISTSCHED == scheduler_type) {

    optr = &proctab[currpid];
    // kprintf("\n------------------------\n");
    // kprintf("\n Curr PID %d \n", currpid);
    // kprintf("\n value at random  %d \n", random);
    if (optr->pstate == PRCURR) {
      optr->pstate = PRREADY;
      insert(currpid, rdyhead, optr->pprio);
    }
    curr_proc = q[rdyhead].qnext;
    // old_proc = q[curr_proc].qprev;
    while (random >= q[curr_proc].qkey && q[curr_proc].qnext != rdytail) {
      curr_proc = q[curr_proc].qnext;
    }
    next_proc = curr_proc;
    dequeue(next_proc);
    currpid = next_proc;
    // kprintf("\n next_proc %d\n", next_proc);
    nptr = &proctab[next_proc];
    // kprintf("\n Next PID %s\n", nptr->pname);

    nptr->pstate = PRCURR; /* mark it currently running    */
#ifdef RTCLOCK
    preempt = QUANTUM; /* reset preemption counter     */
#endif

    ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp,
          (int)nptr->pirmask);
    return (OK);
  }

// LINUX SCHEDULER 

  else if (LINUXSCHED == scheduler_type) {
    optr = &proctab[currpid];
    //kprintf("##########################################\n");
    //kprintf("\ncurrent pid %d \n", currpid);
    if (currpid == NULLPROC) {
      //kprintf("nulproc and counter - 0");
      optr->counter = 0;
      optr->goodness = 0;
    }

    //kprintf("current process prio %d \n", optr->pprio);
   // kprintf("current process counter %d \n", optr->counter);
  

   if (optr->counter > 0 || preempt > 0) {
      optr->counter = preempt;
      optr->counter = (int)optr->counter / 2 + optr->pprio;
      optr->goodness = optr->counter + optr->pprio;
     // kprintf(">0 preempt counter & goodness -%d  %d %d\n", preempt,    
    }
    //kprintf("preempt =  %d\n",preempt);
    

   if (optr->counter <= 0 || preempt <= 0) { // kprintf("preempt <0 %d\n", preempt);
      optr->goodness = 0;
      optr->counter = optr->pprio;
      //kprintf("<=0 counter = prio %d \n", optr->counter);
    }
    int max_goodness = 0;
    int j = q[rdyhead].qnext;

    // linear search for max goodness value process in ready queue
    
   while (j != rdytail) {
        if (proctab[j].goodness > max_goodness) {
           max_goodness = proctab[j].goodness;
           next_proc = j;
           }
      // kprintf("max goodness %d \n",max_goodness);
        j = q[j].qnext;
    }
    
    /*int i= 0;
    while(i<NPROC)
    {
        nptr = &proctab[i];
        if(nptr->pstate != PRFREE)
        {
        nptr->goodness = nptr->pprio + nptr->counter;
        nptr->counter = (int)nptr->counter / 2 + nptr->pprio;
        }
        i++;
    }*/
	
    //kprintf("max goodness %d \n", max_goodness);
   // kprintf("next process %d \n", next_proc);

    /*if (currpid == NULLPROC){
                    kprintf("nulproc and counter - 0");
                    optr->counter = 0;
                    optr->goodness = 0;
    }*/

    if (max_goodness > optr->goodness) {
      //kprintf("max_goodness > optr->goodness %d %d\n", max_goodness,optr->goodness);
      optr->pstate = PRREADY;
      insert(currpid, rdyhead, optr->pprio);
      dequeue(next_proc);
      currpid = next_proc;
      nptr = &proctab[next_proc];
      nptr->pstate = PRCURR; /* mark it currently running    */
    

#ifdef RTCLOCK
    //preempt = QUANTUM;
    preempt = nptr->counter; /* reset preemption counter     */
#endif
    ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp,
          (int)nptr->pirmask);
    return (OK);
  } 
  

  else if (max_goodness <  optr->goodness && optr->counter > 0)

   {    
	//kprintf("max_goodness <  optr->goodness && optr->counter > 0    return OK");
	if (optr->pstate == PRCURR)
  		return OK;
	else
	 {
		
  		/* remove highest priority process at end of ready list */

  		nptr = &proctab[(currpid = getlast(rdytail))];
  		nptr->pstate = PRCURR; /* mark it currently running   */
		#ifdef RTCLOCK
  		   preempt = nptr->counter; /* reset preemption counter        */
                #endif

  		ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp,
        	(int)nptr->pirmask);
  		return (OK);


	 }
		
   }
  
   
 //Start of New Epoch | Null Proc will be scheduled
  
  else if (max_goodness == 0 && preempt <= 0) {
      //kprintf("\n");
     //kprintf("max gv is 0 and counter is 0");
    int trav=1;
    while(trav<NPROC)
    {   //kprintf("max_goodness == 0");
	nptr = &proctab[trav];
	if(nptr->pstate != PRFREE)
	{
	nptr->goodness = nptr->pprio + nptr->counter;
	nptr->counter = (int)nptr->counter / 2 + nptr->pprio;
	}
	trav++;
    }

    /*---------- NULLPROC HANDLING ------------*/	
    //kprintf("NULL PROC Handling done");

    optr->pstate = PRREADY;
    insert(currpid, rdyhead, optr->pprio);
    nptr = &proctab[NULLPROC];
    nptr->pstate = PRCURR;
    dequeue(NULLPROC);
    currpid = NULLPROC;
    //kprintf("NULL PROC Handling done");

#ifdef RTCLOCK
    preempt = QUANTUM; /* reset preemption counter     */
#endif
    ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp,
          (int)nptr->pirmask);
    return (OK);
  } 

 }

else {

  /* no switch needed if current process priority higher than next*/

  if (((optr = &proctab[currpid])->pstate == PRCURR) &&
      (lastkey(rdytail) < optr->pprio)) {
    return (OK);
  }

  /* force context switch */

  if (optr->pstate == PRCURR) {
    optr->pstate = PRREADY;
    insert(currpid, rdyhead, optr->pprio);
  }

  /* remove highest priority process at end of ready list */

  nptr = &proctab[(currpid = getlast(rdytail))];
  nptr->pstate = PRCURR; /* mark it currently running	*/
#ifdef RTCLOCK
  preempt = QUANTUM; /* reset preemption counter	*/
#endif

  ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp,
        (int)nptr->pirmask);

  return (OK);
  /* The OLD process returns here when resumed. */
}
}
