#include <iostream>

//seqList ���ݽṹ
/*typedef int SLDataType;
typedef struct seqList 
{
	SLDataType array[];
	size_t size;
}seqList;
typedef struct seqList
{
	SLDataType* array;
	size_t size;
	size_t capicity;
}seqList;
*/
template<typename T>
class SeqList {
public:
	// ���캯��
	SeqList(size_t capacity) 
		: array(new T[capacity]),
		  size(0),
		  capacity(capacity) {}

	// ��������
	~SeqList() {
		delete[] array;
		array = nullptr;
	}

	// ���ռ䣬������ˣ���������
	void checkCapacity() {
		if (size == capacity) {
			capacity *= 2;
			T* newArray = new T[capacity];
			for (size_t i = 0; i < size; ++i) {
				newArray[i] = array[i];
			}
			delete[] array;
			array = newArray;
		}
	}

	// ˳���β��
	void pushBack(const T& x) {
		checkCapacity();
		array[size++] = x;
	}

	// ˳���βɾ
	void popBack() {
		if (size > 0) {
			--size;
		}
	}

	// ˳���ͷ��
	void pushFront(const T& x) {
		checkCapacity();
		for (size_t i = size; i > 0; --i) {
			array[i] = array[i - 1];
		}
		array[0] = x;
		++size;
	}

	// ˳���ͷɾ
	void popFront() {
		if (size > 0) {
			for (size_t i = 0; i < size - 1; ++i) {
				array[i] = array[i + 1];
			}
			--size;
		}
	}

	// ˳������
	int find(const T& x) const {
		for (size_t i = 0; i < size; ++i) {
			if (array[i] == x) {
				return i;
			}
		}
		return -1; // δ�ҵ�
	}

	// ˳�����posλ�ò���x
	void insert(size_t pos, const T& x) {
		if (pos > size) {
			// ����λ����Ч�Ĵ���������Ը���ʵ����������޸�
			std::cerr << "Error: Invalid insertion position." << std::endl;
			exit(-1);
		}

		checkCapacity();

		for (size_t i = size; i > pos; --i) {
			array[i] = array[i - 1];
		}
		array[pos] = x;
		++size;
	}

	// ˳���ɾ��posλ�õ�ֵ
	void erase(size_t pos) {
		if (pos >= size) {
			// ɾ��λ����Ч�Ĵ���������Ը���ʵ����������޸�
			std::cerr << "Error: Invalid deletion position." << std::endl;
			exit(-1);
		}

		for (size_t i = pos; i < size - 1; ++i) {
			array[i] = array[i + 1];
		}
		--size;
	}

	// ˳����ӡ
	void print() const {
		for (size_t i = 0; i < size; ++i) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

private:
	T* array;       // ָ��̬���ٵ�����
	size_t size;     // ��Ч���ݸ���
	size_t capacity; // �����ռ�Ĵ�С
};


