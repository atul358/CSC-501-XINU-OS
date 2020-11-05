#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

SYSCALL release_bs(bsd_t bs_id) {

  /* release the backing store with ID bs_id */


  if((bs_id >0) && (bsm_tab[bs_id].bs_status = BSM_UNMAPPED))
  {
    if((bs_id <8) && (bsm_tab[bs_id].bs_status = BSM_UNMAPPED))
    {
         bsm_tab[bs_id].bs_status = BSM_UNMAPPED;
         bsm_tab[bs_id].bs_iid = NOT_SET; 
	 bsm_tab[bs_id].bs_priv_heap = NOT_SET;
	 bsm_tab[bs_id].bs_npages = NOT_SET;
	 bsm_tab[bs_id].bs_pid = NOT_DEFINE;
	 bsm_tab[bs_id].bs_vpno = VPN_BASE;
	 bsm_tab[bs_id].bs_sem = NOT_SET;
	 return OK;
    }
    return SYSERR;
  }
   return SYSERR;
}

