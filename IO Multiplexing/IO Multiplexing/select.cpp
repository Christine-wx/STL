/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set* readfds, fd_set* writefds,
    fd_set* exceptfds, struct timeval* timeout);
/**
    nfds:        监控的文件描述符集里最大文件描述符加1，因为此参数会告诉内核检测前多少个文件描述符的状态
    readfds：    监控有读数据到达文件描述符集合，传入传出参数
    writefds：   监控写数据到达文件描述符集合，传入传出参数
    exceptfds：  监控异常发生达文件描述符集合,如带外数据到达异常，传入传出参数
    timeout：    定时阻塞监控时间，3种情况
                1.NULL，永远等下去
                2.设置timeval，等待固定时间
                3.设置timeval里时间均为0，检查描述字后立即返回，轮询
    struct timeval {
        long tv_sec; // seconds
        long tv_usec; // microseconds
    };
*/
void FD_CLR(int fd, fd_set* set);   // 把文件描述符集合里fd清0
int  FD_ISSET(int fd, fd_set* set); // 测试文件描述符集合里fd是否置1
void FD_SET(int fd, fd_set* set);   // 把文件描述符集合里fd位置1
void FD_ZERO(fd_set* set);         //把文件描述符集合里所有位清0