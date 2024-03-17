//// 指向单个类型对象
//template <typename _Tp, typename _Dp = default_delete<_Tp> >
//class unique_ptr
//{
//	class _Pointer {};
//
//	typedef std::tuple<typename _Pointer::type, _Dp>  __tuple_type;
//	__tuple_type                                      _M_t;
//
//public:
//	typedef typename _Pointer::type   pointer;
//	typedef _Tp                       element_type;
//	typedef _Dp                       deleter_type;
//
//	constexpr unique_ptr() noexcept : _M_t()
//	{
//		static_assert(!is_pointer<deleter_type>::value,
//			"constructed with null function pointer deleter");
//	}
//
//	explicit unique_ptr(pointer __p) noexcept : _M_t(__p, deleter_type())     // 裸指针构造函数，explicit阻止隐式构造
//	{
//		static_assert(!is_pointer<deleter_type>::value,
//			"constructed with null function pointer deleter");
//	}
//
//	unique_ptr(unique_ptr&& __u) noexcept                 // 移动构造函数
//		: _M_t(__u.release(), std::forward<deleter_type>(__u.get_deleter())) { }
//
//	~unique_ptr() noexcept                                // 析构函数
//	{
//		auto& __ptr = std::get<0>(_M_t);
//		if (__ptr != nullptr)
//			get_deleter()(__ptr);
//		__ptr = pointer();
//	}
//
//	unique_ptr& operator=(unique_ptr&& __u) noexcept      // move赋值运算符重载
//	{
//		reset(__u.release());
//		get_deleter() = std::forward<deleter_type>(__u.get_deleter());
//		return *this;
//	}
//
//	typename add_lvalue_reference<element_type>::type operator*() const   // 解引用
//	{
//		_GLIBCXX_DEBUG_ASSERT(get() != pointer());
//		return *get();
//	}
//
//	pointer operator->() const noexcept                   // 智能指针->运算符
//	{
//		_GLIBCXX_DEBUG_ASSERT(get() != pointer());
//		return get();
//	}
//
//	pointer get() const noexcept                          // 获得裸指针
//	{
//		return std::get<0>(_M_t);
//	}
//
//	deleter_type& get_deleter() noexcept                  // 获取删除器
//	{
//		return std::get<1>(_M_t);
//	}
//
//	explicit operator bool() const noexcept               // 类型转换函数，用于条件语句，如if(uniptr)之类
//	{
//		return get() == pointer() ? false : true;
//	}
//
//	pointer release() noexcept                            // 释放指针
//	{
//		pointer __p = get();
//		std::get<0>(_M_t) = pointer();
//		return __p;
//	}
//
//	void reset(pointer __p = pointer()) noexcept          // 重置指针
//	{
//		using std::swap;
//		swap(std::get<0>(_M_t), __p);
//		if (__p != pointer())
//			get_deleter()(__p);
//	}
//
//	void swap(unique_ptr& __u) noexcept                   // 交换指针
//	{
//		using std::swap;
//		swap(_M_t, __u._M_t);
//	}
//
//	unique_ptr(const unique_ptr&) = delete;               // 禁止拷贝构造函数
//	unique_ptr& operator=(const unique_ptr&) = delete;    // 禁止copy赋值运算符重载
//};
//
//// 指向数组类型
//template<typename _Tp, typename _Dp>
//class unique_ptr<_Tp[], _Dp>
//{
//	...           // 与上文代码类似，省略
//
//public:
//	typename std::add_lvalue_reference<element_type>::type operator[](size_t __i) const     // 数组[]操作符
//	{
//		_GLIBCXX_DEBUG_ASSERT(get() != pointer());
//		return get()[__i];
//	}
//};