#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

extern pt_t *global_page_table[4];

void create_pd(int proc)
{
	int resp, frm_num;
	pd_t *page_dir_entery;
	resp = get_frm(&frm_num);
        switch(resp)	{
		case 1: pg_dir_entry(frm_num);
		        int i;
  		        for(i=0;i<4;i++)
		         {
				page_dir_entery= get_base(frm_num)*i;
        			page_dir_entery->pd_pres=SET;
        			page_dir_entery->pd_base=((int)global_page_table[i])>>12;
        			page_dir_entery->pd_write=SET;			
		         }
	
			proctab[proc].pdbr = get_pdbr(frm_num); 
			update_frame(frm_num, proc, 2);
		default : return SYSERR;}
}

void pg_dir_entry(int frm)
{
pd_t *pd_entry;
int j,k;
k = 0;
for(j = 0; j<(NBPG/4); j++)
  {
   pd_entry = get_pt_base(frm,j);
   pd_entry[j].pd_write = k+SET;
   pd_entry[j].pd_base = k;
   pd_entry[j].pd_pres = k;
   pd_entry[j].pd_avail = k;


}
}




