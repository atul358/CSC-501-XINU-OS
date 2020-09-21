#include <kernel.h>
#include <proc.h>
#include <q.h>
#include "sched.h"
#include "math.h"

scheduler_type=0;

void setschedclass(int sched_type)
{
      	 scheduler_type = sched_type;
}
