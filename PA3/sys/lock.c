#include <conf.h>
#include<kernel.h>
#include<sem.h>
#include<stdio.h>
#include <q.h>
#include<proc.h>
#include<lock.h>

extern int ctr1000;
int lock (int ldes1, int type, int priority){
    STATWORD ps;
    disable(ps);
    struct lentry *lock_ptr;
    struct pentry *proc_ptr;
    proctab[currpid].lock_descp[NLOCKS];
    proc_ptr = &proctab[currpid];
    lock_ptr = &locktab[ldes1];
    
    if(lock_ptr->llock == 0){
        if(type == READ){
            lock_ptr->lreaders++;
            lock_ptr->llock = 1;
            lock_ptr->type = READ;
            lock_ptr->lstate = LUSED;
            lock_ptr->process_list[currpid] = 1;
            proc_ptr[currpid].lock_descp[ldes1] = 1;
           
            
        }
        else if(type == WRITE){
            
            
            lock_ptr->type = WRITE;
            lock_ptr->llock = 1;
            lock_ptr->lstate = LUSED;
            lock_ptr->process_list[currpid] = 1;
            proc_ptr[currpid].lock_descp[ldes1] = 1;
             
 
           
        }
    }
    else if((lock_ptr->type == READ)){
        if((type == READ)){     
            if(lastkey(locktab[ldes1].lwqtail) > priority){               
                //Reader in wait when there is a higher priority writer already waiting for the lock
                // print_wait(locktab[ldes1].lwqhead, 0);

                proctab[currpid].wait_start = ctr1000;  
                proctab[currpid].pstate = PRWAIT;
                proctab[currpid].lockid = ldes1;
                insert(currpid, locktab[ldes1].lrqhead, priority);
                update_lprio(ldes1);
                resched();
            }
            else{
                
                lock_ptr->lreaders++;
                lock_ptr->lstate = LUSED;
  

                 lock_ptr->process_list[currpid] = 1;
                 proc_ptr[currpid].lock_descp[ldes1] = 1;
                

            }
        }
        else if (type == WRITE){
            
            


            proctab[currpid].wait_start = ctr1000;
            
           
            proctab[currpid].pstate = PRWAIT;
            proctab[currpid].lockid = ldes1;
             
            
            insert(currpid, locktab[ldes1].lwqhead, priority);
            update_lprio(ldes1);
            resched();
        }
    }
    
    else if(lock_ptr->type == WRITE){
        
        if(type == WRITE){        
            proctab[currpid].wait_start = ctr1000;
            proctab[currpid].pstate = PRWAIT;
            proctab[currpid].lockid = ldes1;            
            insert(currpid, locktab[ldes1].lwqhead, priority);
            update_lprio(ldes1);
            resched();
        } 

        else if(type == READ){
            proctab[currpid].wait_start = ctr1000;
            proctab[currpid].lockid = ldes1;
            proctab[currpid].pstate = PRWAIT;
            insert(currpid, locktab[ldes1].lrqhead, priority);
            update_lprio(ldes1);
            resched();
        }
    }
    
    restore(ps);
    return OK;
}

void rwlock_acquire_writelock(int i){
    i--;
    if(i == 0){
        wait(i);
    }


}
