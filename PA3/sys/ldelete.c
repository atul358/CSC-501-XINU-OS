#include <conf.h>
#include<kernel.h>
#include<sem.h>
#include<stdio.h>
#include <q.h>
#include<proc.h>
#include<lock.h>

int ldelete(int lck){
    STATWORD ps;
    disable(ps);
    struct pentry *proc_ptr;
    proc_ptr = &proctab[currpid];
    struct lentry *lock_ptr;
    lock_ptr = &locktab[lck];
    int proc_id;

    int temprhead= locktab[lck].lrqhead;
    int tempwhead = locktab[lck].lwqhead;
    int temp;

    while( q[temprhead].qnext != locktab[lck].lrqtail){
        proc_id = getlast(locktab[lck].lrqtail);
        proctab[proc_id].pwaitret = DELETED;
        proctab[proc_id].lockid = -1;
        ready(proc_id, RESCHNO);
    }
    resched();
    while( q[tempwhead].qnext != locktab[lck].lwqtail){
        proc_id = getlast(locktab[lck].lwqtail);
        proctab[proc_id].pwaitret = DELETED;
        proctab[proc_id].lockid = -1;
        ready(proc_id, RESCHNO);
    }
    resched();
    restore(ps);
    return OK;
}