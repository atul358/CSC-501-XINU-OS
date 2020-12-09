#include <conf.h>                                                                                                                                                                            
#include <kernel.h>                                                                                                                                                                          
#include <proc.h>                                                                                                                                                                            
#include <sem.h>                                                                                                                                                                             
#include <lock.h>
#include <stdio.h>

#define DEFAULT_LOCK_PRIO 20

#define assert(x,error) if(!(x)){ \
            kprintf(error);\
            return;\
            }
int mystrncmp(char* des,char* target,int n){
    int i;
    for (i=0;i<n;i++){
        if (target[i] == '.') continue;
        if (des[i] != target[i]) return 1;
    }
    return 0;
}

/*----------------------------------Test---------------------------*/

void reader(char *msg, int lck, int lprio)
{
    int lk;

    printf("  %s: to acquire lock\n", msg);
    lk = lock(lck, READ, lprio);
    printf("  %s: acquired lock, sleep 2s\n", msg);
    sleep(2);
    printf("  %s: to release lock\n", msg);
    releaseall(1, lck);
}

void writer(char *msg, int lck, int lprio)
{
    int lk;
    printf("  %s: to acquire lock\n", msg);
    lk = lock(lck, WRITE, lprio);
    printf("  %s: acquired lock, sleep 3s\n", msg);
    sleep(3);
    printf("  %s: to release lock\n", msg);
    releaseall(1, lck);
}

void sema(char *msg, int sem) 
{
    int lk;
    printf("  %s: to acquire sem\n", msg);
    lk = wait(sem);
    printf("  %s: acquired sem, sleep 2s\n", msg);
    sleep(2);
    printf("  %s: to release sem\n", msg);
    signal(sem);

}


int main()
{

     kprintf("\n------------ XINU semaphore ----------\n");

    int sem_w1, sem_w2, sem_r1, sem_r2; 
    int s;

    s  = screate(1); 
    sem_w1 = create(sema, 2000, 40, "writer", 3, "writer 3", s, 10);
    sem_r1 = create(sema, 2000, 10, "reader", 3, "reader 2", s, 20);
    sem_w2 = create(sema, 2000, 20, "writer", 3, "writer 4", s, 30);
    sem_r2 = create(sema, 2000, 15, "reader", 3, "reader 4", s, 40);


   kprintf("\n Writer/reader/writer/reader priority befor resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(sem_w1), getprio(sem_r1), getprio(sem_w2), getprio(sem_r2));
    kprintf("starts writer 1. writer 1 priority (prio 40) \n");
    resume(sem_w1);
    sleep(2);
   
   kprintf("\n Writer/reader/writer/reader priority after resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(sem_w1), getprio(sem_r1), getprio(sem_w2), getprio(sem_r2));
   kprintf("starts reader 1. reader 1 priority (prio 10)\n");
    resume(sem_r1);
    sleep(2);

   kprintf("\n Writer/reader/writer/reader priority after resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(sem_w1), getprio(sem_r1), getprio(sem_w2), getprio(sem_r2));
    kprintf(" \nstarts writer 2. writer 2 priority (prio 20)\n");
    resume(sem_r1);
    sleep(2);

    kprintf("\n Writer/reader/writer/reader priority after resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(sem_w1), getprio(sem_r1), getprio(sem_w2), getprio(sem_r2));
    kprintf("starts reader 2. reader 1 priority (prio 15)\n");
    resume(sem_w2);
    
    
    
    sleep(5);
    
    kprintf ("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

    int lw1, lw2, lr1, lr2;  
    int lck;

    kprintf("\n------------  Reader/Writer lock ------------\n");

    lck  = lcreate();
    lw1 = create(writer, 2000, 40, "writer", 3, "writer 1", lck, 10);
    lr1 = create(reader, 2000, 10, "reader", 3, "reader 1", lck, 20);
    lw2 = create(writer, 2000, 20, "writer", 3, "writer 2", lck, 30);
    lr2 = create(reader, 2000, 15, "reader", 3, "reader 2", lck, 40);


    kprintf("\n Writer/reader/writer/reader priority befor resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(lw1), getprio(lr1), getprio(lw2), getprio(lr2));
    kprintf("-start writer, then sleep 1s. lock granted to write (prio 40)\n");
    resume(lw1);
    sleep(1);

    kprintf("\n Writer/reader/writer/reader priority after resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(lw1), getprio(lr1), getprio(lw2), getprio(lr2));
    kprintf("-start reader A, then sleep 1s. reader A(prio 10) blocked on the lock\n");
    resume(lr1);
    sleep(1);

    kprintf("\n Writer/reader/writer/reader priority after resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(lw1), getprio(lr1), getprio(lw2), getprio(lr2));
    kprintf("-start writer, then sleep 1s. lock granted to write (prio 20)\n");
    resume(lr2);
    sleep(1);
    
    kprintf("\n Writer/reader/writer/reader priority after resuming [ writer 1 = %d reader 1 = %d writer 2 = %d reader 2 = %d] \n", getprio(lw1), getprio(lr1), getprio(lw2), getprio(lr2));
    kprintf("-start reader A, then sleep 1s. reader A(prio 15) blocked on the lock\n");
    resume(lw2);
    sleep(1);
    


    shutdown();
    return 0;
}