


//���е����ݽṹ
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
	// ���캯��
	Queue() : _front(nullptr), _rear(nullptr) {}
	~Queue() 
	{
		QueueDestroy();
	}

	// ��β�����
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

	// ��ͷ������
	void QueuePop() {
		if (_front == nullptr) {
			return; // �ն����޷�����
		}

		QListNode<T>* temp = _front;
		_front = _front->_pNext;
		delete temp;

		if (_front == nullptr) {
			_rear = nullptr; // ���Ӻ����Ϊ�գ����¶�βָ��
		}
	}

	// ��ȡ����ͷ��Ԫ��
	T QueueFront() const {
		if (_front == nullptr) {
			throw std::out_of_range("Queue is empty");
		}
		return _front->_data;
	}

	// ��ȡ���ж�βԪ��
	T QueueBack() const {
		if (_rear == nullptr) {
			throw std::out_of_range("Queue is empty");
		}
		return _rear->_data;
	}

	// ��ȡ��������ЧԪ�ظ���
	int QueueSize() const {
		int count = 0;
		QListNode<T>* current = _front;
		while (current) {
			count++;
			current = current->_pNext;
		}
		return count;
	}

	// �������Ƿ�Ϊ�գ����Ϊ�շ��ط�����������ǿշ���0
	bool QueueEmpty() const {
		return _front == nullptr;
	}

	// ���ٶ���
	void QueueDestroy() {
		while (_front) {
			QListNode<T>* temp = _front;
			_front = _front->_pNext;
			delete temp;
		}
		_rear = nullptr;
	}
};

