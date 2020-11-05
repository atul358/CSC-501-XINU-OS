/* paging.h */

typedef unsigned int	 bsd_t;

/* Structure for a page directory entry */

typedef struct {

  unsigned int pd_pres	: 1;		/* page table present?		*/
  unsigned int pd_write : 1;		/* page is writable?		*/
  unsigned int pd_user	: 1;		/* is use level protection?	*/
  unsigned int pd_pwt	: 1;		/* write through cachine for pt?*/
  unsigned int pd_pcd	: 1;		/* cache disable for this pt?	*/
  unsigned int pd_acc	: 1;		/* page table was accessed?	*/
  unsigned int pd_mbz	: 1;		/* must be zero			*/
  unsigned int pd_fmb	: 1;		/* four MB pages?		*/
  unsigned int pd_global: 1;		/* global (ignored)		*/
  unsigned int pd_avail : 3;		/* for programmer's use		*/
  unsigned int pd_base	: 20;		/* location of page table?	*/
} pd_t;

/* Structure for a page table entry */

typedef struct {

  unsigned int pt_pres	: 1;		/* page is present?		*/
  unsigned int pt_write : 1;		/* page is writable?		*/
  unsigned int pt_user	: 1;		/* is use level protection?	*/
  unsigned int pt_pwt	: 1;		/* write through for this page? */
  unsigned int pt_pcd	: 1;		/* cache disable for this page? */
  unsigned int pt_acc	: 1;		/* page was accessed?		*/
  unsigned int pt_dirty : 1;		/* page was written?		*/
  unsigned int pt_mbz	: 1;		/* must be zero			*/
  unsigned int pt_global: 1;		/* should be zero in 586	*/
  unsigned int pt_avail : 3;		/* for programmer's use		*/
  unsigned int pt_base	: 20;		/* location of page?		*/
} pt_t;

typedef struct{
  unsigned int pg_offset : 12;		/* page offset			*/
  unsigned int pt_offset : 10;		/* page table offset		*/
  unsigned int pd_offset : 10;		/* page directory offset	*/
} virt_addr_t;


typedef struct{
  int bs_status;			/* MAPPED or UNMAPPED		*/
  int bs_pid;				  /* process id using this slot   */
  int bs_vpno;				/* starting virtual page number */
  int bs_iid;
  int bs_npages;			/* number of pages in the store */
  int bs_sem;				  /* semaphore mechanism ?	*/
  int bs_priv_heap;
} bs_map_t;

typedef struct{
  int fr_status;			/* MAPPED or UNMAPPED		*/
  int fr_pid;				  /* process id using this frame  */
  int fr_vpno;				/* corresponding virtual page no*/
  int fr_refcnt;			/* reference count		*/
  int fr_type;				/* FR_DIR, FR_TBL, FR_PAGE	*/
  int fr_dirty;
}fr_map_t;

typedef struct{
int next_frame;
int frm_age;
int frm_id;
}queue_node;

struct sc_queue_node{
int frm_num;
struct sc_queue_node *next;
}sc_queue;

extern int debug, queue_head;
int bs_map;
extern bs_map_t bsm_tab[];
extern fr_map_t frm_tab[];
queue_node frame_queue[];

/* Prototypes for required API calls */

SYSCALL xmmap(int, bsd_t, int);
SYSCALL xunmap(int);
void frame_init_sc_policy(int i);
void insert_frame_SC_policy(int frm);
/* given calls for dealing with backing store */

int get_bs(bsd_t, unsigned int);
SYSCALL release_bs(bsd_t);
SYSCALL read_bs(char *, bsd_t, int);
SYSCALL write_bs(char *, bsd_t, int);

#define NBPG		4096	/* number of bytes per page	*/
#define FRAME0		1024	/* zero-th frame		*/
#define NFRAMES 	1024	/* number of frames		*/
//#define NFRAMES         30
#define BS_MAX          8
#define BSM_UNMAPPED	0
#define BSM_MAPPED	1
#define VPN_BASE 	4096
#define FRM_UNMAPPED	0
#define FRM_MAPPED	1

#define FR_PAGE		0
#define FR_TBL		1
#define FR_DIR		2

#define SC 		3
#define AGING 		4
#define get_base(f) (FRAME0+(f))*NBPG+sizeof(pd_t)
#define get_pdbr(f) (FRAME0+(frm_num))*NBPG
#define get_pt_base(f,i) (FRAME0+(f))*NBPG+sizeof(pd_t)*i
#define BACKING_STORE_BASE	0x00800000
#define BACKING_STORE_UNIT_SIZE 0x00100000

#define calc_index(s) BACKING_STORE_BASE + (s * BACKING_STORE_UNIT_SIZE)

#define NOT_DEFINE -1
#define SET		1
#define NOT_SET		0
extern int curr_frame, prev_frame;
