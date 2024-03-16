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
		// ����ͷ��㲢ʹ��ѭ������
		head = new ListNode<T>(T());
		head->next = head;
		head->prev = head;
	}

	~DoublyLinkedList() {
		ListDestroy();
	}

	// ˫����������
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

	// ˫�������ӡ
	void ListPrint() const {
		ListNode<T>* cur = head->next;
		while (cur != head) {
			std::cout << cur->data << " ";
			cur = cur->next;
		}
		std::cout << std::endl;
	}

	// ˫������β��
	void ListPushBack(T x) {
		ListNode<T>* newNode = new ListNode<T>(x);
		ListNode<T>* tail = head->prev;

		tail->next = newNode;
		newNode->prev = tail;

		newNode->next = head;
		head->prev = newNode;
	}

	// ˫������βɾ
	void ListPopBack() {
		if (head->next == head) {
			return; // �������޷�ɾ��
		}

		ListNode<T>* tail = head->prev;
		ListNode<T>* newTail = tail->prev;

		delete tail;

		newTail->next = head;
		head->prev = newTail;
	}

	// ˫������ͷ��
	void ListPushFront(T x) {
		ListNode<T>* newNode = new ListNode<T>(x);
		ListNode<T>* first = head->next;

		head->next = newNode;
		newNode->prev = head;

		newNode->next = first;
		first->prev = newNode;
	}

	// ˫������ͷɾ
	void ListPopFront() {
		if (head->next == head) {
			return; // �������޷�ɾ��
		}

		ListNode<T>* first = head->next;
		ListNode<T>* newFirst = first->next;

		delete first;

		head->next = newFirst;
		newFirst->prev = head;
	}

	// ˫���������
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

	// ˫��������pos��ǰ����в���
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

	// ˫������ɾ��posλ�õĽڵ�
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

