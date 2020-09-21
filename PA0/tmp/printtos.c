#include <stdio.h>
#include <kernel.h>
#include <lab0.h>
static unsigned long *ebp, *esp;
void printtos(){
//unsigned long  *sp, *fp;

kprintf("\n\nprinttos()\n");

//kprintf("\nBefore ebp asm [0x%08x]: 0x%08x \n",ebp, *ebp);
//asm("mov %esp, esp");
asm("movl %ebp, ebp");
//fp = ebp;
//sp = esp;

//kprintf("Before [0x%08x]: 0x%08x \n", *(ebp-2), ebp-2);
kprintf("Before [0x%08x]: 0x%08x \n", ebp+2, *(ebp+2));
//kprintf("\n ebp+4 [0x%08x]: 0x%08x \n",ebp+4, *(ebp+4));
kprintf("After [0x%08x]: 0x%08x \n \n", ebp, *(ebp));


int i =0;
int a,b,s = 0;
a = b = 1;
for(i=0;i<4; i++){
	s = i+a+b;
//	fp = &s;
}

int c;
for(c=1;c<=4;c++)
{
kprintf("\telement [0x%08x]: 0x%08x\n", ebp+(c),*(ebp+(c)));
}

kprintf("\n");
/*
int f = 0;
while(sp<fp){
                       kprintf("\telement [0x%08X]:0x%08X \n", sp, *sp);
//f++;
//if(f ==  4){break;}

sp++;
}
kprintf("\n#############\n");
kprintf("\n element [0x%08x]: 0x%08x \n", fp, *(fp+4));
kprintf("\n element [0x%08x]: 0x%08x \n", fp, *(fp+3));
kprintf("\n element [0x%08x]: 0x%08x \n", fp, *(fp+2));
kprintf("\n element [0x%08x]: 0x%08x \n", fp, *(fp+1));
*/
	
}
