/* bsm.c - manage the backing store mapping*/

#include <conf.h>
#include <kernel.h>
#include <paging.h>
#include <proc.h>
#define NONE -1
#define virt_page_num 4096
#define calc_pageth(vaddr,i)  vaddr/NBPG - bsm_tab[i].bs_vpno

/*-------------------------------------------------------------------------
 * init_bsm- initialize bsm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL init_bsm(int i)
{

	bsm_tab[i].bs_status = BSM_UNMAPPED;
    	bsm_tab[i].bs_pid = NOT_DEFINE;
    	bsm_tab[i].bs_vpno = VPN_BASE;
    	bsm_tab[i].bs_npages = NOT_SET;
    	bsm_tab[i].bs_sem = NOT_SET;
    	bsm_tab[i].bs_priv_heap = NOT_SET;


}

/*-------------------------------------------------------------------------
 * get_bsm - get a free entry from bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL get_bsm(int* avail)
{	
	STATWORD ps;
	disable(ps);
	int stat, i = 0;
	for(i; i<8;i++)
	{	stat =bsm_tab[i].bs_status; 
		if(stat == BSM_UNMAPPED)
		{	
			*avail = i;
			restore(ps);
			return OK;
			//break;
		}
	}
	restore(ps); 
	return SYSERR;
}


/*-------------------------------------------------------------------------
 * free_bsm - free an entry from bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL free_bsm(int i)
{
	return OK;
}

/*-------------------------------------------------------------------------
 * bsm_lookup - lookup bsm_tab and find the corresponding entry
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_lookup(int pid, long vaddr, int* store, int* pageth)
{	
	STATWORD ps;
        disable(ps);
	int i = 0;
	for(i; i<8; i++)
	{	if((bsm_tab[i].bs_pid == pid) && (bsm_tab[i].bs_status == BSM_MAPPED))
		{	*store = i;

			*pageth = calc_pageth(vaddr, i);

			restore(ps);
			return OK;
		}
	}
	restore(ps);
	return SYSERR;
}


/*-------------------------------------------------------------------------
 * bsm_map - add an mapping into bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_map(int pid, int vpno, int source, int npages)
{
 
 if(vpno < VPN_BASE) {return SYSERR;}
  if(npages <1){return SYSERR;}
  if(npages >256){return SYSERR;}
	bsm_tab[source].bs_status = BSM_MAPPED;
        bsm_tab[source].bs_pid = pid;
        bsm_tab[source].bs_vpno = vpno; 
        bsm_tab[source].bs_npages = VPN_BASE;
        bsm_tab[source].bs_sem = SET;
        bsm_tab[source].bs_priv_heap = NOT_SET;
 
	proctab[pid].vhpnpages = npages;
        proctab[pid].vmemlist->mnext = VPN_BASE * NBPG;
               
        proctab[currpid].vhpno = VPN_BASE;
        proctab[currpid].store = source;       
	return OK;

}



/*-------------------------------------------------------------------------
 * bsm_unmap - delete an mapping from bsm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_unmap(int pid, int vpno, int flag)
{
	int i,src, bs_num, vaddr, pageth;
	vaddr = vpno<<12;
	for(flag; flag< VPN_BASE; flag++){

		bsm_tab->bs_pid = NOT_SET;
		bsm_tab->bs_vpno = NOT_SET;
		bsm_tab->bs_npages = NOT_SET;
		bsm_tab->bs_iid = NOT_SET; 
		proctab[currpid].vhpno = NOT_SET;
		proctab[currpid].store = NOT_SET;


    }

}


