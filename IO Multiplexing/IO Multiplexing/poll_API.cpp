#include <poll.h>
int poll(struct pollfd fds[], nfds_t nfds, int timeout)；
typedef struct pollfd {
	int fd;                         /* 需要被检测或选择的文件描述符*/
	short events;                   /* 对文件描述符fd上感兴趣的事件 */
	short revents;                  /* 文件描述符fd上当前实际发生的事件*/
} pollfd_t;
