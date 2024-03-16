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
/*
struct rb_node rbn: 用于构建红黑树的节点。红黑树是一种自平衡的二叉搜索树，用于存储文件描述符（fd）和相关事件。
struct list_head rdllink: 用于将 epitem 结构体链接到事件就绪链表中。就绪链表存储已准备好的事件。
struct epitem* next: 指向下一个 epitem 结构体的指针，用于构建链表。
struct epoll_filefd ffd: 与文件描述符相关的信息。
int nwait: 等待的数量。
struct list_head pwqlist: 用于链入等待事件的进程的链表。
struct eventpoll* ep: 指向关联的 eventpoll 结构体的指针。
struct list_head fllink: 用于将 epitem 结构体链接到文件列表中。
struct epoll_event event: epoll_event 结构体，存储与事件相关的信息。

*/

struct eventpoll {
	spin_lock_t       lock;
	struct mutex      mtx;
	wait_queue_head_t     wq;
	wait_queue_head_t   poll_wait;
	struct list_head    rdllist;   //就绪链表
	struct rb_root      rbr;      //红黑树根节点 
	struct epitem* ovflist;
};
/*
spin_lock_t lock: 自旋锁，用于保护 eventpoll 结构体的访问。
struct mutex mtx: 互斥锁，用于保护 eventpoll 结构体的访问。
wait_queue_head_t wq: 等待队列头，用于进程等待事件的唤醒。
wait_queue_head_t poll_wait: 等待队列头，用于进程等待事件的唤醒。
struct list_head rdllist: 就绪链表，存储已准备好的事件。
struct rb_root rbr: 红黑树根节点，用于存储文件描述符（fd）和相关事件。
struct epitem* ovflist: 溢出链表，存储无法在红黑树中存放的 epitem 结构体。
*/

//用户数据载体
typedef union epoll_data {
	void* ptr;
	int      fd;
	uint32_t u32;
	uint64_t u64;
} epoll_data_t;
/*
union epoll_data: 是一个联合体，用于在 epoll_event 结构体中存储用户数据。
void* ptr: 指针类型的数据。
int fd: 整型的文件描述符。
uint32_t u32: 32 位无符号整型数据。
uint64_t u64: 64 位无符号整型数据。
*/

//fd装载入内核的载体
struct epoll_event {
	uint32_t     events;    /* Epoll events */
	epoll_data_t data;      /* User data variable */
};
/*
uint32_t events: 表示关联的事件类型。可以是 EPOLLIN、EPOLLOUT、EPOLLERR 等。
epoll_data_t data: 联合体，用于存储用户数据或文件描述符。
*/

//创建一个 epoll 实例，并返回一个文件描述符，size 参数用于指定红黑树的大小。
int epoll_create(int size);

//制 epoll 实例，可以添加、修改或删除事件。
//op 参数指定操作类型，可以是 EPOLL_CTL_ADD、EPOLL_CTL_MOD 或 EPOLL_CTL_DEL。
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);

//等待事件的发生。
//maxevents 参数指定最大的事件数量，timeout 参数指定超时时间。
int epoll_wait(int epfd, struct epoll_event* events,
	int maxevents, int timeout);
