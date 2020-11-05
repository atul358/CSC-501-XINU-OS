/* xm.c = xmmap xmunmap */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

int *i =0;
/*-------------------------------------------------------------------------
 * xmmap - xmmap
 *-------------------------------------------------------------------------
 */
SYSCALL xmmap(int virtpage, bsd_t source, int npages)
{
  STATWORD ps;
  disable(ps);
  if(source < 0){kprintf("\nsource <0\n");return SYSERR;}
  if(source > 7){kprintf("\nsource >7\n");return SYSERR;}
  if(virtpage < VPN_BASE) {kprintf("\nvirtpage <VPN_base\n");return SYSERR;}
  if(npages <1){kprintf("\nnpages <1\n");return SYSERR;}
  if(npages >256){kprintf("\nnpages >256\n");return SYSERR;}
   bsm_tab[source].bs_status = BSM_MAPPED;
  bsm_tab[source].bs_pid = currpid;
  bsm_tab[source].bs_vpno = virtpage;
  bsm_tab[source].bs_npages = npages;
  bsm_tab[source].bs_priv_heap = 0;
  bsm_tab[source].bs_iid = source;
  bsm_tab[source].bs_sem = 1; 

 proctab[currpid].vhpno = virtpage;
  proctab[currpid].store = source;
  

  
  restore(ps);
 return 1;

restore(ps);
return SYSERR;


}



/*-------------------------------------------------------------------------
 * xmunmap - xmunmap
 *-------------------------------------------------------------------------
 */

SYSCALL xmunmap(int virtpage)
{
  STATWORD ps;
  disable(ps);
 int f = 0;
  int j = 0;

if(virtpage < VPN_BASE){restore(ps); return SYSERR;}

bsm_unmap(currpid, virtpage,j);

restore(ps);
 return OK;
}
