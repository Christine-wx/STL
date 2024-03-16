struct epitem {
	struct rb_node  rbn;
	struct list_head  rdllink;
	struct epitem* next;
	struct epoll_filefd  ffd;
	int  nwait;
	struct list_head  pwqlist;
	struct eventpoll* ep;
	struct list_head  fllink;
	struct epoll_event  event;
};

struct eventpoll {
	spin_lock_t       lock;
	struct mutex      mtx;
	wait_queue_head_t     wq;
	wait_queue_head_t   poll_wait;
	struct list_head    rdllist;   //就绪链表
	struct rb_root      rbr;      //红黑树根节点 
	struct epitem* ovflist;
};

//用户数据载体
typedef union epoll_data {
	void* ptr;
	int      fd;
	uint32_t u32;
	uint64_t u64;
} epoll_data_t;
//fd装载入内核的载体
struct epoll_event {
	uint32_t     events;    /* Epoll events */
	epoll_data_t data;      /* User data variable */
};
//三板斧api
int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
int epoll_wait(int epfd, struct epoll_event* events,
	int maxevents, int timeout);
