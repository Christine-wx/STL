#include <iostream>
#include <vector>

template <typename T>
class Heap {
private:
    std::vector<T> _a;

public:
    // 构造函数
    Heap() {}

    // 构建堆
    void HeapCreate(T* a, int n);

    // 销毁堆
    void HeapDestroy();

    // 插入元素
    void HeapPush(T x);

    // 删除堆顶元素
    void HeapPop();

    // 取堆顶的数据
    T HeapTop() const;

    // 堆的数据个数
    int HeapSize() const;

    // 堆的判空
    bool HeapEmpty() const;

    // 对数组进行堆排序
    void HeapSort();

    // 打印堆
    void PrintHeap() const;

private:
    // 自上而下调整堆
    void AdjustDown(int parent, int size);

    // 自下而上调整堆
    void AdjustUp(int child);
};

template <typename T>
void Heap<T>::HeapCreate(T* a, int n) {
    _a.assign(a, a + n);

    // 从最后一个非叶子节点开始，自上而下调整堆
    for (int i = (_a.size() - 1) / 2; i >= 0; --i) {
        AdjustDown(i, _a.size());
    }
}

template <typename T>
void Heap<T>::HeapDestroy() {
    _a.clear();
}

template <typename T>
void Heap<T>::HeapPush(T x) {
    _a.push_back(x);
    AdjustUp(_a.size() - 1);
}

template <typename T>
void Heap<T>::HeapPop() {
    if (!_a.empty()) {
        std::swap(_a[0], _a.back());
        _a.pop_back();
        AdjustDown(0, _a.size());
    }
}

template <typename T>
T Heap<T>::HeapTop() const {
    if (!_a.empty()) {
        return _a.front();
    }
    throw std::out_of_range("Heap is empty");
}

template <typename T>
int Heap<T>::HeapSize() const {
    return _a.size();
}

template <typename T>
bool Heap<T>::HeapEmpty() const {
    return _a.empty();
}

template <typename T>
void Heap<T>::HeapSort() {
    int n = _a.size();
    for (int i = n - 1; i > 0; --i) {
        std::swap(_a[0], _a[i]);
        AdjustDown(0, i);
    }
}

template <typename T>
void Heap<T>::PrintHeap() const {
    for (const auto& elem : _a) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Heap<T>::AdjustDown(int parent, int size) {
    int child = 2 * parent + 1;
    while (child < size) {
        if (child + 1 < size && _a[child] < _a[child + 1]) {
            ++child;
        }
        if (_a[parent] < _a[child]) {
            std::swap(_a[parent], _a[child]);
            parent = child;
            child = 2 * parent + 1;
        }
        else {
            break;
        }
    }
}

template <typename T>
void Heap<T>::AdjustUp(int child) {
    int parent = (child - 1) / 2;
    while (parent >= 0) {
        if (_a[parent] < _a[child]) {
            std::swap(_a[parent], _a[child]);
            child = parent;
            parent = (child - 1) / 2;
        }
        else {
            break;
        }
    }
}

