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

const int MAX_THREADS = 1000; // 最大线程数目

template <typename T>
class threadPool
{
public:
    threadPool(int number = 1); // 默认开一个线程
    ~threadPool();
    bool append(T* request); // 往请求队列<task_queue>中添加任务<T>
    std::queue<T*> tasks_queue; // 任务队列
private:
    // 工作线程需要运行的函数，不断的从任务队列中取出并执行
    static void worker(threadPool<T>* pool);
    void run();
private:
    std::vector<std::thread> work_threads; // 工作线程

    std::mutex queue_mutex;
    std::condition_variable condition; // 必须与unique_lock配合使用
    bool stop;
};

// end class

// 构造函数，创建线程
template <typename T>
threadPool<T>::threadPool(int number) : stop(false)
{
    if (number <= 0 || number > MAX_THREADS)
        throw std::exception();

    for (int i = 0; i < number; i++)
    {
        std::cout << "created Thread num is : " << i << std::endl;
        work_threads.emplace_back(worker, this);
        // 添加线程
        // 直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
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
        ww.join(); // 可以在析构函数中join
}

// 添加任务
template <typename T>
bool threadPool<T>::append(T* request)
{
    // 操作工作队列时一定要加锁，因为他被所有线程共享
    std::unique_lock<std::mutex> lock(queue_mutex);
    tasks_queue.push(request);
    condition.notify_one(); // 线程池添加进去了任务，自然要通知等待的线程
    return true;
}

// 单个线程
template <typename T>
void threadPool<T>::worker(threadPool<T>* pool)
{
    pool->run(); // 线程运行
}

template <typename T>
void threadPool<T>::run()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(this->queue_mutex);
        // unique_lock(); // 出作用域会自动解锁
        this->condition.wait(lk, [this]
            { return this->stop || !this->tasks_queue.empty(); });
        // 如果任务为空，则wait，就停下来等待唤醒
        // 需要有任务，才启动该线程，不然就休眠
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
    threadPool<Task> pool(5); // 6个线程，vector
    std::string str;
    while (1)
    {
        Task* tt = new Task(); // 使用智能指针
        pool.append(tt);       // 不停的添加任务，任务是队列queue，因为只有固定的线程数
        cout << "添加的任务数量：" << pool.tasks_queue.size() << endl;
        delete tt;
    }
}
