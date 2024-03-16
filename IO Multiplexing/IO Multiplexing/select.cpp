/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set* readfds, fd_set* writefds,
    fd_set* exceptfds, struct timeval* timeout);
/**
    nfds:        ��ص��ļ���������������ļ���������1����Ϊ�˲���������ں˼��ǰ���ٸ��ļ���������״̬
    readfds��    ����ж����ݵ����ļ����������ϣ����봫������
    writefds��   ���д���ݵ����ļ����������ϣ����봫������
    exceptfds��  ����쳣�������ļ�����������,��������ݵ����쳣�����봫������
    timeout��    ��ʱ�������ʱ�䣬3�����
                1.NULL����Զ����ȥ
                2.����timeval���ȴ��̶�ʱ��
                3.����timeval��ʱ���Ϊ0����������ֺ��������أ���ѯ
    struct timeval {
        long tv_sec; // seconds
        long tv_usec; // microseconds
    };
*/
void FD_CLR(int fd, fd_set* set);   // ���ļ�������������fd��0
int  FD_ISSET(int fd, fd_set* set); // �����ļ�������������fd�Ƿ���1
void FD_SET(int fd, fd_set* set);   // ���ļ�������������fdλ��1
void FD_ZERO(fd_set* set);         //���ļ�����������������λ��0