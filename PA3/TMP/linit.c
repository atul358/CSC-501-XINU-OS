#include <conf.h>
#include<kernel.h>
#include<sem.h>
#include<stdio.h>
#include <q.h>
#include<proc.h>
#include<lock.h>


lock_t locktab[NLOCKS];


void linit(){
	//lock_t *lock_ptr;
	struct lentry *lock_ptr;
	int i,nxt_lock = 0;
	for(i = 0; i<NLOCKS;i++){
		lock_ptr = &locktab[i];
		lock_ptr->llock = 0;
		lock_ptr->lstate = LFREE;
		lock_ptr->lreaders = 0;
		lock_ptr->lwriter = 0;
		lock_ptr->lwqtail = (lock_ptr->lwqhead=newqueue()) + 1;
		lock_ptr->lrqtail = (lock_ptr->lrqhead=newqueue()) + 1;
		lock_ptr->type = NONE;
		proctab[i].pinh = 0;
		lock_ptr->lprio = 0;
		proctab[i].lockid = -1;

	}
}


