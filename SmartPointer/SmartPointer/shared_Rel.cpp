#include <iostream>
#include <mutex>

using namespace std;

template<class T>
class shared_ptr
{
public:
    // ���캯��
    explicit shared_ptr(T* ptr = nullptr)
        : _ptr(ptr)
        , _pcount(new int(1))
        , _pmtx(new mutex)
    {}

    // ��������
    ~shared_ptr()
    {
        Release();
    }

    /* �ͷ���Դ
    Release() �����������ü��������������ü�����ֵ���ж��Ƿ���Ҫɾ��ָ��Ķ��ڴ��������ü�������
    �ڲ���֮ǰ������ʹ�û����� _pmtx ���м������Ա�֤�̰߳�ȫ��*/
    void Release()
    {
        _pmtx->lock();
        bool deleteFlag = false;
        if (--(*_pcount) == 0)
        {
            if (_ptr)
            {
                // ɾ��������ɾ��
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

    // �������ü���
    void AddCount()
    {
        _pmtx->lock();
        ++(*_pcount);
        _pmtx->unlock();
    }

    // �������캯��
    shared_ptr(const shared_ptr<T>& sp)
        : _ptr(sp._ptr)
        , _pcount(sp._pcount)
        , _pmtx(sp._pmtx)
    {
        AddCount();
    }

    // ��ֵ���������
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

    // operator*() ����
    T& operator*()
    {
        return *_ptr;
    }

    // operator->() ����
    T* operator->()
    {
        return _ptr;
    }

    // get() ����
    T* get()
    {
        return _ptr;
    }

    // use_count() ����
    int use_count()
    {
        return *_pcount;
    }

    // swap() ���������� 2 �� shared_ptr ����ָ�������
    void swap(shared_ptr<T>& sp) noexcept
    {
        std::swap(_ptr, sp._ptr);
        std::swap(_pcount, sp._pcount);
        std::swap(_pmtx, sp._pmtx);
    }

    // reset() ���������� shared_ptr ����ָ�����
    void reset(T* ptr = nullptr)
    {
        // �ͷ�ԭ����Դ
        Release();

        // ���¸�ֵ
        _ptr = ptr;
        _pcount = new int(1);
        _pmtx = new mutex;
    }

private:
    T* _ptr;           // ָ����ڴ�����ָ��
    int* _pcount;      // ���ü�����ָ��
    mutex* _pmtx;      // �������ü����Ļ�����

    // ��װ��
    function<void(T*)> _del = [](T* ptr)
        {
            cout << "lambda delete:" << ptr << endl;
            delete ptr;
        };
};
