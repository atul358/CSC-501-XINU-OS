#include<stdio.h>
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern int currpid;
int flag[NPROC];
//int total_proc[NPROC];

void syscallsummary_start()
{ int i,j; 

for(j = 0; j<NPROC; j++)
    {
     flag[i] = 1;
     for(i = 0; i<27; i++)

	{ proctab[j].syscalltime[i] = 0;
	  proctab[j].syscallcount[i] = 0;
	}
    }
}

void syscallsummary_stop(){}
void printsyscallsummary()
{
int i ;
kprintf("\nvoid printsyscallsummary()\n");
struct  pentry *temp;
for(i=0; i<NPROC; i++){
	int j;
	temp = &proctab[i];
	
	if(temp->pprio > 0){
//	for(j=0; j<27;j++){
	//if(i >= 0 && i < NPROC){
	kprintf("\n\nProcess [pid :%d] \n", i);
	syscallavgtime("screate", proctab[i].syscalltime[SCREATE], proctab[i].syscallcount[SCREATE]);
	syscallavgtime("resume", proctab[i].syscalltime[RESUME], proctab[i].syscallcount[RESUME]);
	syscallavgtime("chprio", proctab[i].syscalltime[CHPRIO], proctab[i].syscallcount[CHPRIO]);
	syscallavgtime("freemem", proctab[i].syscalltime[FREEMEM], proctab[i].syscallcount[FREEMEM]);
	syscallavgtime("getpid", proctab[i].syscalltime[GETPID], proctab[i].syscallcount[GETPID]);
	syscallavgtime("getprio", proctab[i].syscalltime[GETPRIO], proctab[i].syscallcount[GETPRIO]);
	syscallavgtime("gettime", proctab[i].syscalltime[GETTIME], proctab[i].syscallcount[GETTIME]);
	syscallavgtime("kill", proctab[i].syscalltime[KILL], proctab[i].syscallcount[KILL]);
	syscallavgtime("receive", proctab[i].syscalltime[RECEIVE], proctab[i].syscallcount[RECEIVE]);
	syscallavgtime("recvclr", proctab[i].syscalltime[RECVCLR], proctab[i].syscallcount[RECVCLR]);
	syscallavgtime("recvtim", proctab[i].syscalltime[RECVTIM], proctab[i].syscallcount[RECVTIM]);
	syscallavgtime("scount", proctab[i].syscalltime[SCOUNT], proctab[i].syscallcount[SCOUNT]);
	syscallavgtime("sdelete", proctab[i].syscalltime[SDELETE], proctab[i].syscallcount[SDELETE]);
	syscallavgtime("send", proctab[i].syscalltime[SEND], proctab[i].syscallcount[SEND]);
	syscallavgtime("setdev", proctab[i].syscalltime[SETDEV], proctab[i].syscallcount[SETDEV]);
	syscallavgtime("setnok", proctab[i].syscalltime[SETNOK], proctab[i].syscallcount[SETNOK]);
	syscallavgtime("signal", proctab[i].syscalltime[SIGNAL], proctab[i].syscallcount[SIGNAL]);
	syscallavgtime("signaln", proctab[i].syscalltime[SIGNALN], proctab[i].syscallcount[SIGNALN]);
	syscallavgtime("sleep", proctab[i].syscalltime[SLEEP], proctab[i].syscallcount[SLEEP]);
}
//}
}
}

