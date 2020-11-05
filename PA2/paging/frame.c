/* frame.c - manage physical frames */
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>
#define NOT_DEFINE -1
/*-------------------------------------------------------------------------
 * init_frm - initialize frm_tab
 *-------------------------------------------------------------------------
 */

fr_map_t frm_tab[NFRAMES];


SYSCALL init_frm(int i)
{

	
	frm_tab[i].fr_status = FRM_UNMAPPED;
	frm_tab[i].fr_type = FR_PAGE;
	frm_tab[i].fr_pid = NOT_DEFINE;
	frm_tab[i].fr_vpno = NOT_DEFINE;
	frm_tab[i].fr_dirty = NOT_DEFINE;
  	frm_tab[i].fr_refcnt = NOT_SET;

}

/*-------------------------------------------------------------------------
 * get_frm - get a free frame according page replacement policy
 *-------------------------------------------------------------------------
 */
SYSCALL get_frm(int* avail)
{
	STATWORD ps;
   	disable(ps);
	int i = 0;
	for(i; i < NFRAMES; i++)
	{
		if(frm_tab[i].fr_status == FRM_UNMAPPED)
		{	
			*avail = i;
		    restore(ps);
  			return 1;
	    }
    	}
	// Implement Page Replacement Policy
restore(ps);
return 2;
}

/*-------------------------------------------------------------------------
 * free_frm - free a frame 
 *-------------------------------------------------------------------------
 */
SYSCALL free_frm(int i)
{


  STATWORD ps;
  disable(ps);
  if(i<0) {restore(ps); return SYSERR;}

  restore(ps);
  return OK;
}


void frame_init_sc_policy(int i)
{	

		frame_queue[i].frm_id = i;
		frame_queue[i].next_frame = NOT_DEFINE;
		frame_queue[i].frm_age = NOT_SET;

}
