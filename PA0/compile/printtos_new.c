#include <stdio.h>
#include <kernel.h>

static unsigned long *ebp;
void printtos(){


kprintf("\n--- printos ---\n");

//kprintf("\nBefore ebp asm [0x%08x]: 0x%08x \n",ebp, *ebp);
asm("mov %esp, ebp");

//kprintf("Before [0x%08x]: 0x%08x \n", *(ebp-2), ebp-2);
kprintf("Before [0x%08x]: 0x%08x \n", *ebp, ebp);
//kprintf("\n ebp+2 [0x%08x]: 0x%08x \n",ebp+2, *(ebp+2));
int i =0;

int a,b,s = 0;
a = b = 1;
for(i = 0; i<4; i++){
	s = i+a+b;
}


kprintf("\n element [0x%08x]: 0x%08x \n", ebp, *(ebp-1));
kprintf("\n element [0x%08x]: 0x%08x \n", ebp, *(ebp-2));
kprintf("\n element [0x%08x]: 0x%08x \n", ebp, *(ebp-3));
kprintf("\n element [0x%08x]: 0x%08x \n", ebp, *(ebp-4));

kprintf("After [0x%08x]: 0x%08x \n", *ebp, ebp);
	
}
