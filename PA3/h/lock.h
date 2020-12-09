
#ifndef _LOCK_H_
#define _LOCK_H_

#define READ   1
#define WRITE  2

#define LFREE  0
#define LUSED  1

#define inactive 0
#define active   1

#define blocking  1
#define nonblocking 0

#define NONE 0
SYSCALL lcreate();

/*
int lcreate();
int ldelete (int lockdescriptor);

int lock (int ldes1, int type, int priority);

int releaseall (int numlocks, int ldes1);
*/

typedef struct lentry{
        int llock;
        int lreaders;
        int lwriter;
        //int lqhead;
        //int lqtail;
        int  lwqhead;
        int  lwqtail;
        int  lrqhead;
        int  lrqtail;
        int type;
        int lstate;
        int total_locks;        //total locks per process
        int process_list[NPROC];
        int lockid;
        int lprio;
}lock_t;
extern lock_t locktab[];
extern  int  nextlock;

/*
typedef struct lentry
{
        char lstate;
        int  lprio;
        int  lnum;
        int  lwqhead;
        int  lwqtail;
        int  lrqhead;
        int  lrqtail;
	int  lguard;
	int  lflag;
        int  lpid;
 	int  ltype;       
}lock_t;

extern lock_t locktab[];
*/
#endif
