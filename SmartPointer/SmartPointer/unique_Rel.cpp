#include <utility>
#include<iostream>

/****
 * ����ָ��unique_ptr�ļ�ʵ��
 *
 * �ص㣺������ָ��Ķ���Ҳ����˵��ͬʱֻ��һ��unique_ptrָ��ͬһ�����󣬵����unique_ptr������ʱ��ָ��Ķ���Ҳ�漴������
 *
 * ������;��
 * 1. ��һ����������һ��A* ptr = new A(), ��������Ҫ��delete������unique_ptr���Ͳ���Ҫ�Լ�����delete
 * 2. ��Ϊһ����ı������������ֻ�ڱ���ʹ�ã����ᱻ��������ã�Ҳ������Ϊ�������ݸ�ĳ������
 * */
template<typename T>
class unique_ptr
{
private:
	T* ptr_resource = nullptr;

public:
	//explicit���캯����������ֹ��ʽת��, ��������д��unique_ptr<T> tempPtr = T;
	//std::move�ǽ������״̬��������Ȩ��һ������ת�Ƶ���һ������ֻ��ת�ƣ�û���ڴ�İ�Ǩ�����ڴ濽�����Կ����������Ч��,��������.
	//move֮��raw_resource�ڲ�����Դ�������ٱ�raw_resourceʹ��
	explicit unique_ptr(T* raw_resource) noexcept : ptr_resource(std::move(raw_resource)) {}
	unique_ptr(std::nullptr_t) : ptr_resource(nullptr) {}

	unique_ptr() noexcept : ptr_resource(nullptr) {}

	//����ʱ, �ͷ��йܵĶ�����Դ
	~unique_ptr() noexcept
	{
		delete ptr_resource;
	}
	// Disables the copy/ctor and copy assignment operator. We cannot have two copies exist or it'll bypass the RAII concept.
	//��Ҫ����ֹ���ֿ����ĸ�ֵ��ʽ
	//ʹ��"=delete"���Σ���ʾ����������Ϊdeleted��Ҳ����ζ�������Ա���������ٱ����ã�����ͻ����
	unique_ptr(const unique_ptr<T>&) noexcept = delete;
	unique_ptr& operator = (const unique_ptr&) noexcept = delete;

public:
	//&& ����ֵ���ã���https://zhuanlan.zhihu.com/p/107445960
	// �����ƶ����塣��Ȼ�޷�����unique_ptr�������԰�ȫ���ƶ���
	//���ӣ�unique_ptr<Test> tPtr3(std::move(tPtr1));
	unique_ptr(unique_ptr&& move) noexcept
	{
		std::cout << "construct for unique_ptr&&" << std::endl;
		move.swap(*this);
	}
	// ptr = std::move(resource)
	unique_ptr& operator=(unique_ptr&& move) noexcept
	{
		std::cout << "operator= for unique_ptr&&" << std::endl;

		move.swap(*this);
		return *this;
	}

	explicit operator bool() const noexcept
	{
		return this->ptr_resource;
	}
	// releases the ownership of the resource. The user is now responsible for memory clean-up.
	T* release() noexcept
	{
		return std::exchange(ptr_resource, nullptr);
	}
	// returns a pointer to the resource
	T* get() const noexcept
	{
		return ptr_resource;
	}
	// swaps the resources
	void swap(unique_ptr<T>& resource_ptr) noexcept
	{
		std::swap(ptr_resource, resource_ptr.ptr_resource);
	}
	// reset��ɾ���ϵģ�ָ���µ�
	void reset(T* resource_ptr) noexcept(false)
	{
		// ensure a invalid resource is not passed or program will be terminated
		if (resource_ptr == nullptr)
			throw std::invalid_argument("An invalid pointer was passed, resources will not be swapped");

		delete ptr_resource;

		ptr_resource = nullptr;

		std::swap(ptr_resource, resource_ptr);
	}
public:
	// overloaded operators
	T* operator->() const noexcept
	{
		return this->ptr_resource;
	}
	T& operator*() const noexcept
	{
		return *this->ptr_resource;
	}
	// ����˵��noexcept
	//noexcept C++11�ؼ���, ���߱������������в��ᷢ���쳣,�����ڱ������Գ�����������Ż�
	//C++�е��쳣������������ʱ�����Ǳ���ʱ���ġ�Ϊ��ʵ������ʱ��⣬��������������Ĵ��룬Ȼ�������������Ż�
};
