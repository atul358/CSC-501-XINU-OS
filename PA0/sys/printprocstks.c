#include<stdio.h>
#include<kernel.h>
#include<proc.h>

static unsigned long *esp;

void printprocstks(int p){
extern int currpid;
struct pentry *temp;

int i;
int a[NPROC];

for(i = 0; i< NPROC; i++)
{       temp = &proctab[i];
	if(temp->pprio > p){
		a[i] = 1;
	}
	else {
		a[i] = 0;
	}
}
kprintf("\nvoid printprocstks(int priority)\n");
for(i = 0; i< NPROC; i++){
	temp = &proctab[i];
	if(temp->pstate != PRFREE){
	if(a[i] == 1){
		kprintf("\nprocess : %s \n", temp->pname);
		kprintf("\tpid : %d \n", i);
		kprintf("\tpriority : %d \n",temp->pprio);
		kprintf("\tbase : 0x%08x \n",temp->pbase);
		kprintf("\tlen : %d \n", temp->pstklen);
		kprintf("\tlimit:  0x%08x \n", temp->plimit);
		//kprintf("\tpointer:  0x%08x \n",temp->pesp);
	
		if(temp->pstate == PRCURR){
				asm("movl %esp,esp");
				kprintf("\tpointer: 0x%08x\n",esp);
			}
			else
				kprintf("\tpointer: 0x%08x\n",temp->pesp);	
	
			}
	   }
	}
}

