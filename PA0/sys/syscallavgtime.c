#include<stdio.h>
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

void syscallavgtime(char *syscall, int total_time, int total_count)
{

///kprintf("\nsyscall %s\t", syscall);
int avg_time;
if(total_count != 0){

	//kprintf("total_time %d", total_time);
	//kprintf("\t total_count %d\n", total_count);
	avg_time = total_time/total_count;
	kprintf("\nSyscall: sys_%s, count: %d, average execution time: %d (ms)", syscall, total_count, avg_time);
}
else {
//kprintf("\n\tSyscall: sys_%s, count: %d, average execution time: %d (ms)", syscall, avg_time, total_count);

return;
}
}
