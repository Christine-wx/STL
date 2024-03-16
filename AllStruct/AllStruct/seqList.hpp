#include <iostream>

//seqList 数据结构
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
	// 构造函数
	SeqList(size_t capacity) 
		: array(new T[capacity]),
		  size(0),
		  capacity(capacity) {}

	// 析构函数
	~SeqList() {
		delete[] array;
		array = nullptr;
	}

	// 检查空间，如果满了，进行增容
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

	// 顺序表尾插
	void pushBack(const T& x) {
		checkCapacity();
		array[size++] = x;
	}

	// 顺序表尾删
	void popBack() {
		if (size > 0) {
			--size;
		}
	}

	// 顺序表头插
	void pushFront(const T& x) {
		checkCapacity();
		for (size_t i = size; i > 0; --i) {
			array[i] = array[i - 1];
		}
		array[0] = x;
		++size;
	}

	// 顺序表头删
	void popFront() {
		if (size > 0) {
			for (size_t i = 0; i < size - 1; ++i) {
				array[i] = array[i + 1];
			}
			--size;
		}
	}

	// 顺序表查找
	int find(const T& x) const {
		for (size_t i = 0; i < size; ++i) {
			if (array[i] == x) {
				return i;
			}
		}
		return -1; // 未找到
	}

	// 顺序表在pos位置插入x
	void insert(size_t pos, const T& x) {
		if (pos > size) {
			// 插入位置无效的处理，这里可以根据实际情况进行修改
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

	// 顺序表删除pos位置的值
	void erase(size_t pos) {
		if (pos >= size) {
			// 删除位置无效的处理，这里可以根据实际情况进行修改
			std::cerr << "Error: Invalid deletion position." << std::endl;
			exit(-1);
		}

		for (size_t i = pos; i < size - 1; ++i) {
			array[i] = array[i + 1];
		}
		--size;
	}

	// 顺序表打印
	void print() const {
		for (size_t i = 0; i < size; ++i) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

private:
	T* array;       // 指向动态开辟的数组
	size_t size;     // 有效数据个数
	size_t capacity; // 容量空间的大小
};


