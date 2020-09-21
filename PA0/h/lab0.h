#ifndef _lab0_h_
#define _lab0_h_

/* lab-0 part 1 */
long zfunction();

/* lab-0- part 2 */
void printsegaddress();
extern int edata;
extern int etext;


/* lab-0- part 3 */
void printtos();

/* lab-0- part 4 */
void printprocstks();

/* lab-0 part 5 */
void syscallsummary_start();
void syscallsummary();
void syscallavgtime();
void syscallruntime();
void syscallsummary_stop();
void printsyscallsummary();
#endif
