/* pfint.c - pfint */

#include <conf.h>
#include <kernel.h>
#include <paging.h>
#include <proc.h>
#include <stdio.h>

#define page_dir_offset(addr_off)	addr_off>>22
#define get_base(fn)	fn + FRAME0	
#define pg_dir_offset(i)  (unsigned long) (i * sizeof(pd_t)

/*-------------------------------------------------------------------------
 * pfint - paging fault ISR
 *-------------------------------------------------------------------------
 */

SYSCALL pfint()
{
   STATWORD ps;
   disable(ps);
   unsigned long local_virt_addr;
   int new_frame_num, def_page;
   local_virt_addr  = read_cr2();
   unsigned long vir_add = local_virt_addr>>12;
   int pageth, store, temp;

         unsigned int pg_dir_offset;
 	 unsigned int pg_tab_offset;  
         pg_dir_offset = get_page_dir_offset(local_virt_addr);
         pg_tab_offset = (get_page_tab_offset(local_virt_addr));
         
         
         pd_t *pg_dbr;
         int pd_d_t;
	 pd_t* pd_entry=(pd_t*)proctab[currpid].pdbr;
  	 pd_entry+=pg_dir_offset;         
	
         if(pd_entry->pd_pres == 0)
            {
                  new_frame_num = page_table(currpid);
             	  new_frame_num = update_frame(new_frame_num, currpid);

	          pd_entry->pd_pres = 1;
		  pd_entry->pd_base = get_base(new_frame_num);
                  frm_tab[new_frame_num].fr_type = FR_TBL;
                  temp = (pd_entry->pd_base);
            }
	    int resp;
           resp = get_page_table(currpid, pg_tab_offset,temp,new_frame_num, vir_add, local_virt_addr);
            
	   if(resp == 1){
            	restore(ps);
		return OK;}

	   else { 
		restore(ps);
		return SYSERR;
		}

}

int get_page_dir_offset(unsigned long x)
{
return x>>22;

}

int get_page_tab_offset(unsigned long x)
{
	return x>>12&0x000003ff;
}

int get_page_table(int proc_id,unsigned int pg_tab_offset,unsigned int temp,int frame_num, int virt_page, unsigned long local_virt_addr)
{
   int page, store, def_page;
   char dst;
   pt_t *pt_ent;
   pt_ent = (pt_t*)(temp<<12);
   pt_ent = pt_ent + pg_tab_offset;
   pt_ent->pt_pres=1;
   int resp, frm_num;
   frm_num = 0;
   resp = get_frm(&frm_num);
   if(resp != SYSERR)
   {
      
      pt_ent->pt_base = get_base(frm_num);
      pt_ent->pt_pres = 1;
      pt_ent->pt_write = 1;
      frm_tab[frm_num].fr_status=FRM_MAPPED;
      frm_tab[frm_num].fr_pid=proc_id;
      frm_tab[frm_num].fr_vpno=virt_page;
      frm_tab[frm_num].fr_refcnt++;
      def_page = frm_tab[frm_num].fr_type;
      if(def_page == -1)
      {
         frm_tab[frm_num].fr_type=FR_PAGE;
      }
      frm_tab[frm_num].fr_dirty=1;

      bsm_lookup(proc_id,local_virt_addr, &store, &page );
      dst = (char*)(get_pdbr(frm_num));   
      read_bs((char*)((FRAME0+frm_num)*NBPG),store, page);
      write_cr3(proctab[proc_id].pdbr);
      return 1;     
   }
   else {
	 kill(currpid);
         return 2;

	}
}

