/* policy.c = srpolicy*/

#include <conf.h>
#include <kernel.h>
#include <paging.h>
#include <proc.h>
#define NOT_DEFINE -1
#define DEFINE 1

extern int debug;
extern int page_replace_policy;


/*-------------------------------------------------------------------------
 * srpolicy - set page replace policy 
 *-------------------------------------------------------------------------
 */
SYSCALL srpolicy(int policy)
{

  return OK;
}

/*-------------------------------------------------------------------------
 * grpolicy - get page replace policy 
 *-------------------------------------------------------------------------
 */
SYSCALL grpolicy()
{
  return page_replace_policy;
}
/*
void insert_frame_SC_policy(int frm){
sc_queue *sc_head;
sc_queue *sc_tail;

if(sc_head == NULL){

sc_head->frm_num = frm;
sc_head-> next = NULL;
sc_tail = sc_head;
return OK;

}

else if(sc_head->next == NULL) {

sc_tail->frm_num = frm;
sc_tail->next = NULL;
sc_head->next = sc_tail;

return OK;
}
sc_queue *temp;
temp->frm_num = frm;
temp->next = NULL;
sc_tail = temp;

kprintf("\nInsert fram SC Policy frame number %d\n", temp->frm_num);
return OK;
}
*/






