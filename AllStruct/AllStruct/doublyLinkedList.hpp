#include <iostream>

template <typename T>
class ListNode {
public:
	T data;
	ListNode* next;
	ListNode* prev;

	ListNode(T x) : data(x), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
	ListNode<T>* head;

public:
	DoublyLinkedList() : head(nullptr) {
		// 创建头结点并使其循环链接
		head = new ListNode<T>(T());
		head->next = head;
		head->prev = head;
	}

	~DoublyLinkedList() {
		ListDestroy();
	}

	// 双向链表销毁
	void ListDestroy() {
		ListNode<T>* cur = head->next;
		while (cur != head) {
			ListNode<T>* next = cur->next;
			delete cur;
			cur = next;
		}
		delete head;
		head = nullptr;
	}

	// 双向链表打印
	void ListPrint() const {
		ListNode<T>* cur = head->next;
		while (cur != head) {
			std::cout << cur->data << " ";
			cur = cur->next;
		}
		std::cout << std::endl;
	}

	// 双向链表尾插
	void ListPushBack(T x) {
		ListNode<T>* newNode = new ListNode<T>(x);
		ListNode<T>* tail = head->prev;

		tail->next = newNode;
		newNode->prev = tail;

		newNode->next = head;
		head->prev = newNode;
	}

	// 双向链表尾删
	void ListPopBack() {
		if (head->next == head) {
			return; // 空链表无法删除
		}

		ListNode<T>* tail = head->prev;
		ListNode<T>* newTail = tail->prev;

		delete tail;

		newTail->next = head;
		head->prev = newTail;
	}

	// 双向链表头插
	void ListPushFront(T x) {
		ListNode<T>* newNode = new ListNode<T>(x);
		ListNode<T>* first = head->next;

		head->next = newNode;
		newNode->prev = head;

		newNode->next = first;
		first->prev = newNode;
	}

	// 双向链表头删
	void ListPopFront() {
		if (head->next == head) {
			return; // 空链表无法删除
		}

		ListNode<T>* first = head->next;
		ListNode<T>* newFirst = first->next;

		delete first;

		head->next = newFirst;
		newFirst->prev = head;
	}

	// 双向链表查找
	ListNode<T>* ListFind(T x) const {
		ListNode<T>* cur = head->next;
		while (cur != head) {
			if (cur->data == x) {
				return cur;
			}
			cur = cur->next;
		}
		return nullptr;
	}

	// 双向链表在pos的前面进行插入
	void ListInsert(ListNode<T>* pos, T x) {
		if (pos == nullptr || pos == head) {
			return;
		}

		ListNode<T>* newNode = new ListNode<T>(x);
		ListNode<T>* prevNode = pos->prev;

		prevNode->next = newNode;
		newNode->prev = prevNode;

		newNode->next = pos;
		pos->prev = newNode;
	}

	// 双向链表删除pos位置的节点
	void ListErase(ListNode<T>* pos) {
		if (pos == nullptr || pos == head) {
			return;
		}

		ListNode<T>* prevNode = pos->prev;
		ListNode<T>* nextNode = pos->next;

		delete pos;

		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	}
};

