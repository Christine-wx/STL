//// ָ�򵥸����Ͷ���
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
//	explicit unique_ptr(pointer __p) noexcept : _M_t(__p, deleter_type())     // ��ָ�빹�캯����explicit��ֹ��ʽ����
//	{
//		static_assert(!is_pointer<deleter_type>::value,
//			"constructed with null function pointer deleter");
//	}
//
//	unique_ptr(unique_ptr&& __u) noexcept                 // �ƶ����캯��
//		: _M_t(__u.release(), std::forward<deleter_type>(__u.get_deleter())) { }
//
//	~unique_ptr() noexcept                                // ��������
//	{
//		auto& __ptr = std::get<0>(_M_t);
//		if (__ptr != nullptr)
//			get_deleter()(__ptr);
//		__ptr = pointer();
//	}
//
//	unique_ptr& operator=(unique_ptr&& __u) noexcept      // move��ֵ���������
//	{
//		reset(__u.release());
//		get_deleter() = std::forward<deleter_type>(__u.get_deleter());
//		return *this;
//	}
//
//	typename add_lvalue_reference<element_type>::type operator*() const   // ������
//	{
//		_GLIBCXX_DEBUG_ASSERT(get() != pointer());
//		return *get();
//	}
//
//	pointer operator->() const noexcept                   // ����ָ��->�����
//	{
//		_GLIBCXX_DEBUG_ASSERT(get() != pointer());
//		return get();
//	}
//
//	pointer get() const noexcept                          // �����ָ��
//	{
//		return std::get<0>(_M_t);
//	}
//
//	deleter_type& get_deleter() noexcept                  // ��ȡɾ����
//	{
//		return std::get<1>(_M_t);
//	}
//
//	explicit operator bool() const noexcept               // ����ת������������������䣬��if(uniptr)֮��
//	{
//		return get() == pointer() ? false : true;
//	}
//
//	pointer release() noexcept                            // �ͷ�ָ��
//	{
//		pointer __p = get();
//		std::get<0>(_M_t) = pointer();
//		return __p;
//	}
//
//	void reset(pointer __p = pointer()) noexcept          // ����ָ��
//	{
//		using std::swap;
//		swap(std::get<0>(_M_t), __p);
//		if (__p != pointer())
//			get_deleter()(__p);
//	}
//
//	void swap(unique_ptr& __u) noexcept                   // ����ָ��
//	{
//		using std::swap;
//		swap(_M_t, __u._M_t);
//	}
//
//	unique_ptr(const unique_ptr&) = delete;               // ��ֹ�������캯��
//	unique_ptr& operator=(const unique_ptr&) = delete;    // ��ֹcopy��ֵ���������
//};
//
//// ָ����������
//template<typename _Tp, typename _Dp>
//class unique_ptr<_Tp[], _Dp>
//{
//	...           // �����Ĵ������ƣ�ʡ��
//
//public:
//	typename std::add_lvalue_reference<element_type>::type operator[](size_t __i) const     // ����[]������
//	{
//		_GLIBCXX_DEBUG_ASSERT(get() != pointer());
//		return get()[__i];
//	}
//};