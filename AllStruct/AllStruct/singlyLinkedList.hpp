#include <iostream>

//单链表的数据结构
/*typedef int SLTDateType;
typedef struct SListNode
{
	SLTDateType data;
	struct SListNode* next;
}SListNode;
*/

template <typename T>
class SListNode {
public:
	T data;
	SListNode* next;

	SListNode(T x) : data(x), next(nullptr) {}
};

template <typename T>
class SinglyLinkedList {
private:
	SListNode<T>* head;

public:
	// 构造函数
	SinglyLinkedList()
		: head(new SListNode<T>(T())) {}

	// 析构函数
	~SinglyLinkedList() {
		while (head) {
			SListNode<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}

	// 单链表打印
	void print() const {
		SListNode<T>* current = head->next; // 跳过头节点
		while (current) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	// 单链表尾插
	void pushBack(T x) {
		SListNode<T>* newNode = new SListNode<T>(x);
		SListNode<T>* current = head;
		while (current->next) {
			current = current->next;
		}
		current->next = newNode;
	}

	// 单链表头插
	void pushFront(T x) {
		SListNode<T>* newNode = new SListNode<T>(x);
		newNode->next = head->next;
		head->next = newNode;
	}

	// 单链表尾删
	void popBack() {
		SListNode<T>* current = head;
		while (current->next && current->next->next) {
			current = current->next;
		}
		if (current->next) {
			delete current->next;
			current->next = nullptr;
		}
	}

	// 单链表头删
	void popFront() {
		if (head->next) {
			SListNode<T>* temp = head->next;
			head->next = head->next->next;
			delete temp;
		}
	}

	// 单链表查找
	SListNode<T>* find(T x) const {
		SListNode<T>* current = head->next; // 跳过头节点
		while (current) {
			if (current->data == x) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	// 单链表在pos位置之后插入x
	void insertAfter(SListNode<T>* pos, T x) {
		if (pos == nullptr) {
			return;
		}
		SListNode<T>* newNode = new SListNode<T>(x);
		newNode->next = pos->next;
		pos->next = newNode;
	}
};




