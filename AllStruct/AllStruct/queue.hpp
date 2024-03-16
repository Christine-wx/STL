


//队列的数据结构
/*typedef struct QListNode
{
	struct QListNode* _pNext;
	QDataType _data;
}QNode;
typedef struct Queue
{
	QNode* _front;
	QNode* _rear;
}Queue;
*/


#include <iostream>

template <typename T>
struct QListNode {
	QListNode* _pNext;
	T _data;

	QListNode(T data) : _pNext(nullptr), _data(data) {}
};

template <typename T>
class Queue {
private:
	QListNode<T>* _front;
	QListNode<T>* _rear;

public:
	// 构造函数
	Queue() : _front(nullptr), _rear(nullptr) {}
	~Queue() 
	{
		QueueDestroy();
	}

	// 队尾入队列
	void QueuePush(T data) {
		QListNode<T>* newNode = new QListNode<T>(data);
		if (_rear == nullptr) {
			_front = newNode;
			_rear = newNode;
		}
		else {
			_rear->_pNext = newNode;
			_rear = newNode;
		}
	}

	// 队头出队列
	void QueuePop() {
		if (_front == nullptr) {
			return; // 空队列无法出队
		}

		QListNode<T>* temp = _front;
		_front = _front->_pNext;
		delete temp;

		if (_front == nullptr) {
			_rear = nullptr; // 出队后队列为空，更新队尾指针
		}
	}

	// 获取队列头部元素
	T QueueFront() const {
		if (_front == nullptr) {
			throw std::out_of_range("Queue is empty");
		}
		return _front->_data;
	}

	// 获取队列队尾元素
	T QueueBack() const {
		if (_rear == nullptr) {
			throw std::out_of_range("Queue is empty");
		}
		return _rear->_data;
	}

	// 获取队列中有效元素个数
	int QueueSize() const {
		int count = 0;
		QListNode<T>* current = _front;
		while (current) {
			count++;
			current = current->_pNext;
		}
		return count;
	}

	// 检测队列是否为空，如果为空返回非零结果，如果非空返回0
	bool QueueEmpty() const {
		return _front == nullptr;
	}

	// 销毁队列
	void QueueDestroy() {
		while (_front) {
			QListNode<T>* temp = _front;
			_front = _front->_pNext;
			delete temp;
		}
		_rear = nullptr;
	}
};

