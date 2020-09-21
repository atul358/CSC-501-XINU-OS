#include <stdio.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>
//#include <conf.h>


extern int etext, edata, *end;

void printsegaddress(){

kprintf("\nprintsegaddress()\n");
kprintf("\ncurrent etext [0x%08x] = 0x%08x, edata [0x%08x] = 0x%08x, ebss [0x%08x] = 0x%08x", &etext, etext, &edata, edata, end, *end );
kprintf("\nPreceding  etext [0x%08x] = 0x%08x, edata [0x%08x] = 0x%08x, ebss [0x%08x] = 0x%08x",(&etext-1), etext-1, (&edata-1), edata-1, (&end-1),*end-1 );
kprintf("\nAfter  etext [0x%08x] = 0x%08x, edata [0x%08x] = 0x%08x, ebss [0x%08x] = 0x%08x", (&etext+1), etext+1, (&edata+1), edata+1, (&end+1),*end+1 );



//kprintf("\n previous and next etext [0x%08x] = 0x%08x", etext--, end = &etext);


}

