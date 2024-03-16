#include <iostream>
#include <cstdlib>

//stack ���ݽṹ
/*
typedef int STDataType;
#define N 10
typedef struct Stack
{
	STDataType _array[N];
	int _top; // ջ��
}Stack;
// ֧�ֶ�̬������ջ
typedef struct Stack
{
	STDataType* _array;
	int _top; // ջ��
	int _capacity; // ����
}Stack;
*/

template<typename T>
class Stack {
public:
	// ���캯��
	Stack() : _array(nullptr), _top(0), _capacity(4) {
		_array = new T[_capacity];
	}

	// ��������
	~Stack() {
		delete[] _array;
		_array = nullptr;
	}

	// ��ջ
	void push(const T& data) {
		if (_top == _capacity) {
			// ����Ϊԭ��������
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

	// ��ջ
	void pop() {
		if (_top > 0) {
			--_top;
		}
	}

	// ��ȡջ��Ԫ��
	T top() const {
		if (_top > 0) {
			return _array[_top - 1];
		}
		// ջΪ��ʱ�Ĵ���������Ը���ʵ����������޸�
		std::cerr << "Error: Stack is empty." << std::endl;
		exit(-1);
	}

	// ��ȡջ����ЧԪ�ظ���
	int size() const {
		return _top;
	}

	// ���ջ�Ƿ�Ϊ�գ����Ϊ�շ��� true�������Ϊ�շ��� false
	bool empty() const {
		return _top == 0;
	}

private:
	T* _array;          // ջ����
	int _top;       // ջ��
	int _capacity;  // ����
};

