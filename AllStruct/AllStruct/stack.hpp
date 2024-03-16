#include <iostream>
#include <cstdlib>

//stack 数据结构
/*
typedef int STDataType;
#define N 10
typedef struct Stack
{
	STDataType _array[N];
	int _top; // 栈顶
}Stack;
// 支持动态增长的栈
typedef struct Stack
{
	STDataType* _array;
	int _top; // 栈顶
	int _capacity; // 容量
}Stack;
*/

template<typename T>
class Stack {
public:
	// 构造函数
	Stack() : _array(nullptr), _top(0), _capacity(4) {
		_array = new T[_capacity];
	}

	// 析构函数
	~Stack() {
		delete[] _array;
		_array = nullptr;
	}

	// 入栈
	void push(const T& data) {
		if (_top == _capacity) {
			// 扩容为原来的两倍
			_capacity *= 2;
			T* newA = new T[_capacity];
			for (int i = 0; i < _top; ++i) {
				newA[i] = _array[i];
			}
			delete[] _array;
			_array = newA;
		}
		_array[_top++] = data;
	}

	// 出栈
	void pop() {
		if (_top > 0) {
			--_top;
		}
	}

	// 获取栈顶元素
	T top() const {
		if (_top > 0) {
			return _array[_top - 1];
		}
		// 栈为空时的处理，这里可以根据实际情况进行修改
		std::cerr << "Error: Stack is empty." << std::endl;
		exit(-1);
	}

	// 获取栈中有效元素个数
	int size() const {
		return _top;
	}

	// 检测栈是否为空，如果为空返回 true，如果不为空返回 false
	bool empty() const {
		return _top == 0;
	}

private:
	T* _array;          // 栈数组
	int _top;       // 栈顶
	int _capacity;  // 容量
};

