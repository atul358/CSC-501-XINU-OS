#ifndef _SCHED_H_
#define _SCHED_H_


#define EXPDISTSCHED 1
#define LINUXSCHED 2

extern int scheduler_type;

void setschedclass(int sched_class);


#endif
