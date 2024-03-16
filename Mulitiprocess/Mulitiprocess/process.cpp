#include<thread>
#include<iostream>
#include <mutex>
#include <future>

void foo() 
{
	std::cout << "c++ 11" <<std::endl;
}

std::once_flag f;
void mythread() 
{
	std::call_once(f, foo);
}

template<typename T>
void change(T& x,T val) 
{
	x = val;
}

std::atomic_int tar = 0; //原子性；
//std::mutex mtx;
void count() 
{
	for (int i = 0; i < 10000; ++i) 
	{
		//mtx.lock();
		tar++;
		//mtx.unlock();
	}
}

void cuntbig() 
{
	for (int i = 0; i < 10'0000'0000; i++);
}

int g_i = 0;
std::mutex g_i_mutex;  // protects g_i，用来保护g_i

void safe_increment()
{
	const std::lock_guard<std::mutex> lock(g_i_mutex);
	++g_i;
	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';// g_i_mutex自动解锁}int main(){
	std::cout << "main id: " << std::this_thread::get_id() << std::endl;
	std::cout << "main: " << g_i << '\n';

	std::thread t1(safe_increment);
	std::thread t2(safe_increment);

	t1.join();
	t2.join();

	std::cout << "main: " << g_i << '\n';
}

//void main() 
//{
//
//	std::thread thread(foo);
//	//分离
//	thread.detach();
//	std::thread threads[10];
//	/*for (std::thread& th : threads) 
//	{
//		th = std::thread(mythread);
//	}
//
//	for (std::thread& th : threads)
//	{
//		th.join();
//	}*/
//
//	//多线程创建，使用
//	int nums[10];
//	for (int i = 0; i < 10; ++i) 
//	{
//		threads[i] = std::thread(change<int>, std::ref(nums[i]), i + 1);
//	}
//	for (int i = 0; i < 10; ++i)
//	{
//		threads[i].join();
//		std::cout << nums[i] << std::endl;
//	}
//
//	//使用互斥锁、atomic<原子操作>
//	std::thread t1[10];
//	for (std::thread& x : t1) 
//	{
//		x = std::thread(count);
//	}
//	for (std::thread& x : t1) 
//	{
//		x.join();
//	}
//
//	//异步调用
//	std::future<void> val = std::async(std::launch::async,
//		[](const char* message) 
//		{
//			std::cout << message<<std::flush;
//		},"hello, "
//	);
//
//	std::cout << tar << std::endl;
//	std::cout << "c++" << std::endl;
//
//	std::future<void> fut = std::async(std::launch::async, cuntbig);
//	std::cout << "Please wait" << std::flush;
//	// 每次等待1秒
//	while (fut.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
//		std::cout << '.' << std::flush;
//	std::cout << std::endl << "Finished!" << std::endl;
//	
//	safe_increment();
//	
//	return;
//}


//
//函数	使用	说明
//get_id	std::this_thread::get_id()	获取线程id
//yield	std::this_thread::yield()	放弃线程执行，回到就绪状态
//sleep_for	std::this_thread::sleep_for(std::chrono::seconds(1));	暂停1秒
//sleep_until	如下	一分钟后执行吗，如下
//using std::chrono::system_clock;
//std::time_t tt = system_clock::to_time_t(system_clock::now());
//struct std::tm* ptm = std::localtime(&tt);
//cout << "Waiting for the next minute to begin...\n";
//++ptm->tm_min; //加一分钟
//ptm->tm_sec = 0; //秒数设置为0//暂停执行，到下一整分执行
//this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
//2、mutex
//mutex头文件主要声明了与互斥量(mutex)相关的类。mutex提供了4种互斥类型，如下表所示。
//
//类型	说明
//std::mutex	最基本的 Mutex 类。
//std::recursive_mutex	递归 Mutex 类。
//std::time_mutex	定时 Mutex 类。
//std::recursive_timed_mutex	定时递归 Mutex 类。
//std::mutex 是C++11 中最基本的互斥量，std::mutex 对象提供了独占所有权的特性——即不支持递归地对 std::mutex 对象上锁，而 std::recursive_lock 则可以递归地对互斥量对象上锁。
