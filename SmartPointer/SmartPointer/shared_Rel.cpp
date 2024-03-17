#include <iostream>
#include <mutex>

using namespace std;

template<class T>
class shared_ptr
{
public:
    // 构造函数
    explicit shared_ptr(T* ptr = nullptr)
        : _ptr(ptr)
        , _pcount(new int(1))
        , _pmtx(new mutex)
    {}

    // 析构函数
    ~shared_ptr()
    {
        Release();
    }

    /* 释放资源
    Release() 方法减少引用计数，并根据引用计数的值来判断是否需要删除指向的堆内存对象和引用计数对象。
    在操作之前，我们使用互斥量 _pmtx 进行加锁，以保证线程安全。*/
    void Release()
    {
        _pmtx->lock();
        bool deleteFlag = false;
        if (--(*_pcount) == 0)
        {
            if (_ptr)
            {
                // 删除器进行删除
                _del(_ptr);
            }

            delete _pcount;
            deleteFlag = true;
        }
        _pmtx->unlock();
        if (deleteFlag)
        {
            delete _pmtx;
        }
    }

    // 增加引用计数
    void AddCount()
    {
        _pmtx->lock();
        ++(*_pcount);
        _pmtx->unlock();
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr<T>& sp)
        : _ptr(sp._ptr)
        , _pcount(sp._pcount)
        , _pmtx(sp._pmtx)
    {
        AddCount();
    }

    // 赋值运算符重载
    shared_ptr<T>& operator=(const shared_ptr<T>& sp)
    {
        if (_ptr != sp._ptr)
        {
            Release();

            _ptr = sp._ptr;
            _pcount = sp._pcount;
            _pmtx = sp._pmtx;

            AddCount();
        }

        return *this;
    }

    // operator*() 重载
    T& operator*()
    {
        return *_ptr;
    }

    // operator->() 重载
    T* operator->()
    {
        return _ptr;
    }

    // get() 方法
    T* get()
    {
        return _ptr;
    }

    // use_count() 方法
    int use_count()
    {
        return *_pcount;
    }

    // swap() 方法，交换 2 个 shared_ptr 智能指针的内容
    void swap(shared_ptr<T>& sp) noexcept
    {
        std::swap(_ptr, sp._ptr);
        std::swap(_pcount, sp._pcount);
        std::swap(_pmtx, sp._pmtx);
    }

    // reset() 方法，重置 shared_ptr 智能指针对象
    void reset(T* ptr = nullptr)
    {
        // 释放原有资源
        Release();

        // 重新赋值
        _ptr = ptr;
        _pcount = new int(1);
        _pmtx = new mutex;
    }

private:
    T* _ptr;           // 指向堆内存对象的指针
    int* _pcount;      // 引用计数的指针
    mutex* _pmtx;      // 保护引用计数的互斥量

    // 包装器
    function<void(T*)> _del = [](T* ptr)
        {
            cout << "lambda delete:" << ptr << endl;
            delete ptr;
        };
};
