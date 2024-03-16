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

std::atomic_int tar = 0; //ԭ���ԣ�
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
std::mutex g_i_mutex;  // protects g_i����������g_i

void safe_increment()
{
	const std::lock_guard<std::mutex> lock(g_i_mutex);
	++g_i;
	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';// g_i_mutex�Զ�����}int main(){
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
//	//����
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
//	//���̴߳�����ʹ��
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
//	//ʹ�û�������atomic<ԭ�Ӳ���>
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
//	//�첽����
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
//	// ÿ�εȴ�1��
//	while (fut.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
//		std::cout << '.' << std::flush;
//	std::cout << std::endl << "Finished!" << std::endl;
//	
//	safe_increment();
//	
//	return;
//}


//
//����	ʹ��	˵��
//get_id	std::this_thread::get_id()	��ȡ�߳�id
//yield	std::this_thread::yield()	�����߳�ִ�У��ص�����״̬
//sleep_for	std::this_thread::sleep_for(std::chrono::seconds(1));	��ͣ1��
//sleep_until	����	һ���Ӻ�ִ��������
//using std::chrono::system_clock;
//std::time_t tt = system_clock::to_time_t(system_clock::now());
//struct std::tm* ptm = std::localtime(&tt);
//cout << "Waiting for the next minute to begin...\n";
//++ptm->tm_min; //��һ����
//ptm->tm_sec = 0; //��������Ϊ0//��ִͣ�У�����һ����ִ��
//this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
//2��mutex
//mutexͷ�ļ���Ҫ�������뻥����(mutex)��ص��ࡣmutex�ṩ��4�ֻ������ͣ����±���ʾ��
//
//����	˵��
//std::mutex	������� Mutex �ࡣ
//std::recursive_mutex	�ݹ� Mutex �ࡣ
//std::time_mutex	��ʱ Mutex �ࡣ
//std::recursive_timed_mutex	��ʱ�ݹ� Mutex �ࡣ
//std::mutex ��C++11 ��������Ļ�������std::mutex �����ṩ�˶�ռ����Ȩ�����ԡ�������֧�ֵݹ�ض� std::mutex ������������ std::recursive_lock ����Եݹ�ضԻ���������������
