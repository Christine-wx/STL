#include <iostream>

//����������ݽṹ
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
	// ���캯��
	SinglyLinkedList()
		: head(new SListNode<T>(T())) {}

	// ��������
	~SinglyLinkedList() {
		while (head) {
			SListNode<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}

	// �������ӡ
	void print() const {
		SListNode<T>* current = head->next; // ����ͷ�ڵ�
		while (current) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	// ������β��
	void pushBack(T x) {
		SListNode<T>* newNode = new SListNode<T>(x);
		SListNode<T>* current = head;
		while (current->next) {
			current = current->next;
		}
		current->next = newNode;
	}

	// ������ͷ��
	void pushFront(T x) {
		SListNode<T>* newNode = new SListNode<T>(x);
		newNode->next = head->next;
		head->next = newNode;
	}

	// ������βɾ
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

	// ������ͷɾ
	void popFront() {
		if (head->next) {
			SListNode<T>* temp = head->next;
			head->next = head->next->next;
			delete temp;
		}
	}

	// ���������
	SListNode<T>* find(T x) const {
		SListNode<T>* current = head->next; // ����ͷ�ڵ�
		while (current) {
			if (current->data == x) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	// ��������posλ��֮�����x
	void insertAfter(SListNode<T>* pos, T x) {
		if (pos == nullptr) {
			return;
		}
		SListNode<T>* newNode = new SListNode<T>(x);
		newNode->next = pos->next;
		pos->next = newNode;
	}
};




