#include <conf.h>
#include<kernel.h>
#include<sem.h>
#include<stdio.h>
#include <q.h>
#include<proc.h>
#include<lock.h>

extern int ctr1000;

int releaseall(int numlocks, long locks){
    STATWORD ps;
    disable(ps);
    int lk,i =0;
    unsigned long *l;
    l = (&locks);
    l = l+ (numlocks-1);

    int lock_list[NLOCKS];
    
    
    for(i; numlocks>0; numlocks--, l--, i++){
        
        
        lock_list[i] = *l;
        lk = *l;
      
        release_lock(lk);
        
        
    }

    restore(ps);
    return OK;
}

int release_lock(int ldes1){
    STATWORD ps;
    disable(ps);
    struct lentry *lock_ptr;
    struct pentry *proc_ptr;
    lock_ptr = &locktab[ldes1];
    
    if(lock_ptr->type == READ){  
       
        lock_ptr->lreaders--;
        
          

        if(lock_ptr->lreaders == 0){
            locking_policy(ldes1);
        }

    }
    else if(lock_ptr->type == WRITE){
        
        locking_policy(ldes1);
    }
    restore(ps);
    return OK;
}


int locking_policy(int ldes1){
    STATWORD ps;
    disable(ps);
    
    int proc_id, priority,proc_id_rd, proc_id_wr;
    struct lentry *lock_ptr;
    struct pentry *proc_ptr;
    unsigned long max_wait_rd, max_wait_wr, wait_diff;
    int wr_priority;
    lock_ptr = &locktab[ldes1];   
    if(lastkey(locktab[ldes1].lwqtail) > lastkey(locktab[ldes1].lrqtail)){
        proc_id = getlast(locktab[ldes1].lwqtail);
        if(proc_id > 0){
         lock_ptr->type = WRITE;        
            lock_ptr->process_list[currpid] = 1;
            proc_ptr[proc_id].lock_descp[ldes1] = 1;
            proctab[proc_id].lockid = ldes1;
            ready(proc_id, RESCHYES);
            update_lprio(ldes1);
            restore(ps);
            return OK;
            restore(ps);
            }

        // given to writer i.e. highest waiting priority process

    }
    else if(lastkey(locktab[ldes1].lwqtail) < lastkey(locktab[ldes1].lrqtail)){
    
        wr_priority = lastkey(locktab[ldes1].lwqtail);
        if(wr_priority < 0){
            wr_priority =0;
        }
        while(wr_priority <= lastkey(locktab[ldes1].lrqtail)){
            proc_id = getlast(locktab[ldes1].lrqtail);
            lock_ptr->type = READ;          
            lock_ptr->lreaders++;
            lock_ptr->process_list[currpid] = 1;
            proc_ptr[proc_id].lock_descp[ldes1] = 1;
            ready(proc_id, RESCHNO);
            update_lprio(ldes1);
        }
        proctab[proc_id].lockid = ldes1;
        resched();
        restore(ps);
        return OK;
        }
    else {       
        proc_id_wr = lastid(locktab[ldes1].lwqtail);
        proc_id_rd = lastid(locktab[ldes1].lrqtail);

        // proc_id_wr = getlast(locktab[ldes1].lwqtail);
        // proc_id_rd = getlast(locktab[ldes1].lrqtail);

    
        if((proc_id_wr > 0) && (proc_id_rd >0)){
            
            proc_ptr = &proctab[proc_id];
            max_wait_wr = (ctr1000 - proctab[proc_id_wr].wait_start)/1000;
            max_wait_rd = (ctr1000 - proctab[proc_id_rd].wait_start)/1000;
              //calculate wait time and give to longest waiting process if <=1
            
            if(max_wait_rd - max_wait_wr <=1){
 
                proc_id = getlast(locktab[ldes1].lwqtail);
                if(proc_id > 0){                  
                    lock_ptr->type = WRITE;
                    lock_ptr->process_list[currpid] = 1;
                    proc_ptr[proc_id].lock_descp[ldes1] = 1;
                    proctab[proc_id].lockid = ldes1;
                    ready(proc_id, RESCHYES);
                    update_lprio(ldes1);
                    restore(ps);
                    return OK;

                    }
                
            }    
        
            else if(max_wait_rd > max_wait_wr) {

                wr_priority = lastkey(locktab[ldes1].lwqtail);
                if(wr_priority < 0){
                    wr_priority =0;
                }
                while(wr_priority <= lastkey(locktab[ldes1].lrqtail)){
                    proc_id = getlast(locktab[ldes1].lrqtail);
                    lock_ptr->type = READ;
                    //lock_ptr->lstate = LUSED;
                    lock_ptr->lreaders++;
                    proctab[proc_id].lockid = ldes1;
                    ready(proc_id, RESCHNO);
                    update_lprio(ldes1);

                }
                resched();
                restore(ps);
                return OK;

                
            }
            else if(max_wait_rd < max_wait_wr){
                        //priority = lastkey(locktab[ldes1].lwqtail);
                        // proc_id = lastid(locktab[ldes1].lwqtail);

                        proc_id = getlast(locktab[ldes1].lwqtail);
                        if(proc_id > 0){
                            lock_ptr->type = WRITE;                          
                            lock_ptr->process_list[currpid] = 1;
                            proc_ptr[proc_id].lock_descp[ldes1] = 1;
                            proctab[proc_id].lockid = ldes1;
                            ready(proc_id, RESCHYES);
                            update_lprio(ldes1);
                            restore(ps);
                            return OK;
                            }
                }
        } else {

            lock_ptr->llock = 0;
            lock_ptr->type = 0;
            resched();
        }
    }
    
    restore(ps);
    return OK;
}

int update_lprio(int ldesp){
    STATWORD ps;
    disable(ps);
    // return OK;
    int max = 0;
    int proc;
    int rqhead = locktab[ldesp].lrqhead;
    int wrqhead = locktab[ldesp].lwqhead;
    int temp;
    int curr = q[rqhead].qnext;
    while(curr != locktab[ldesp].lrqtail){

        if (proctab[curr].pinh == 0){
            temp = proctab[curr].pprio;
        }
        else{
            temp = proctab[curr].pinh;
        }
    
        if(temp > max){
            max = temp;       
        }
        curr = q[curr].qnext;
    }
    
    // print_wait(rqhead, 1);
    
    curr = q[wrqhead].qnext;
    while(curr != locktab[ldesp].lwqtail){

        //chech pinh if not equal to zero
        if(proctab[curr].pprio > max){
            max = proctab[curr].pprio;
        }
        curr = q[curr].qnext;
    }
    locktab[ldesp].lprio = max;

    max_lock_prio(ldesp);
    //sleep(10);
    // call update priority to pinh process
    // print_wait(wrqhead, 0);
    
    restore(ps);
    return OK;
}

int max_lock_prio(int ldes1){
     
    STATWORD ps;
    disable(ps);
    int i, max = 0;
    struct lentry *lock_ptr;
    lock_ptr = &locktab[ldes1];
    for(i = 0; i <NLOCKS; i++){ 
        if(lock_ptr->process_list[i] == 1){       
            if((lock_ptr->lprio > proctab[i].pprio) || (lock_ptr->lprio != proctab[i].pinh) ){
                proctab[i].pinh = lock_ptr->lprio;
            }
        }
    }
restore(ps);     
return OK;
}