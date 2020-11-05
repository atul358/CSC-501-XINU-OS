#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

int get_bs(bsd_t bs_id, unsigned int npages) {
	

	STATWORD ps;
	disable(ps);
  	/* requests a new mapping of npages with ID map_id */
	int min_page, max_page;
        min_page = 1;
        max_page = 256;

	if(npages > 256){
	
	return SYSERR;
	}
	if(npages <1){
	
	return SYSERR;
	}
	if(bs_id > 7){
	
        return SYSERR;
	}
	if(bs_id < 0){
       
        return SYSERR;
        }
	if(bsm_tab[bs_id].bs_iid == bs_id){
        return bsm_tab[bs_id].bs_npages;
        return SYSERR;
        }
	if(bsm_tab[bs_id].bs_priv_heap == 1){
        return bsm_tab[bs_id].bs_npages;
        return SYSERR;
        }
	if(bsm_tab[bs_id].bs_pid == currpid){
	 	restore(ps);
		return bsm_tab[bs_id].bs_npages;
	
	}
   	if(bsm_tab[bs_id].bs_status == BSM_MAPPED){
        restore(ps);
		return bsm_tab[bs_id].bs_npages;
	}
	if(bsm_tab[bs_id].bs_pid != currpid){
		if(bsm_tab[bs_id].bs_status == BSM_UNMAPPED)
		{
			bsm_tab[bs_id].bs_status = BSM_MAPPED;
       			bsm_tab[bs_id].bs_iid = bs_id;
        		bsm_tab[bs_id].bs_sem = NOT_SET;
        		bsm_tab[bs_id].bs_pid = currpid;
			restore(ps);
			return bsm_tab[bs_id].bs_npages;		
		}
}
	npages = bsm_tab[bs_id].bs_npages;


restore(ps);
return npages;

}


