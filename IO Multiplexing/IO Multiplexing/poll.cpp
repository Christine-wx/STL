#include <poll.h>
int poll(struct pollfd fds[], nfds_t nfds, int timeout)��
typedef struct pollfd {
	int fd;                         /* ��Ҫ������ѡ����ļ�������*/
	short events;                   /* ���ļ�������fd�ϸ���Ȥ���¼� */
	short revents;                  /* �ļ�������fd�ϵ�ǰʵ�ʷ������¼�*/
} pollfd_t;