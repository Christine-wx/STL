#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <stdexcept>
#include <condition_variable>
#include <memory> // unique_ptr
#include <functional> // function
#include <assert.h>

using namespace std;

const int MAX_THREADS = 1000; // ����߳���Ŀ

template <typename T>
class threadPool
{
public:
    threadPool(int number = 1); // Ĭ�Ͽ�һ���߳�
    ~threadPool();
    bool append(T* request); // ���������<task_queue>���������<T>
    std::queue<T*> tasks_queue; // �������
private:
    // �����߳���Ҫ���еĺ��������ϵĴ����������ȡ����ִ��
    static void worker(threadPool<T>* pool);
    void run();
private:
    std::vector<std::thread> work_threads; // �����߳�

    std::mutex queue_mutex;
    std::condition_variable condition; // ������unique_lock���ʹ��
    bool stop;
};

// end class

// ���캯���������߳�
template <typename T>
threadPool<T>::threadPool(int number) : stop(false)
{
    if (number <= 0 || number > MAX_THREADS)
        throw std::exception();

    for (int i = 0; i < number; i++)
    {
        std::cout << "created Thread num is : " << i << std::endl;
        work_threads.emplace_back(worker, this);
        // ����߳�
        // ֱ��������β���������Ԫ�أ�ʡȥ�˿������ƶ�Ԫ�صĹ��̡�
    }
}

template <typename T>
inline threadPool<T>::~threadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }

    condition.notify_all();
    for (auto& ww : work_threads)
        ww.join(); // ����������������join
}

// �������
template <typename T>
bool threadPool<T>::append(T* request)
{
    // ������������ʱһ��Ҫ��������Ϊ���������̹߳���
    std::unique_lock<std::mutex> lock(queue_mutex);
    tasks_queue.push(request);
    condition.notify_one(); // �̳߳���ӽ�ȥ��������ȻҪ֪ͨ�ȴ����߳�
    return true;
}

// �����߳�
template <typename T>
void threadPool<T>::worker(threadPool<T>* pool)
{
    pool->run(); // �߳�����
}

template <typename T>
void threadPool<T>::run()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(this->queue_mutex);
        // unique_lock(); // ����������Զ�����
        this->condition.wait(lk, [this]
            { return this->stop || !this->tasks_queue.empty(); });
        // �������Ϊ�գ���wait����ͣ�����ȴ�����
        // ��Ҫ�����񣬲��������̣߳���Ȼ������
        if (this->stop && this->tasks_queue.empty())
        {
            return;
        }

        T* request = tasks_queue.front();
        tasks_queue.pop();
        lk.unlock();

        if (request)
            request->process();
    }
}

#endif

class Task
{
public:
    void process()
    {
        long i = 1000000;
        while (i != 0)
        {
            int j = sqrt(i);
            i--;
        }
    }
};

int main(void)
{
    threadPool<Task> pool(5); // 6���̣߳�vector
    std::string str;
    while (1)
    {
        Task* tt = new Task(); // ʹ������ָ��
        pool.append(tt);       // ��ͣ��������������Ƕ���queue����Ϊֻ�й̶����߳���
        cout << "��ӵ�����������" << pool.tasks_queue.size() << endl;
        delete tt;
    }
}
