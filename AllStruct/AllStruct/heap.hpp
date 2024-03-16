#include <iostream>
#include <vector>

template <typename T>
class Heap {
private:
    std::vector<T> _a;

public:
    // ���캯��
    Heap() {}

    // ������
    void HeapCreate(T* a, int n);

    // ���ٶ�
    void HeapDestroy();

    // ����Ԫ��
    void HeapPush(T x);

    // ɾ���Ѷ�Ԫ��
    void HeapPop();

    // ȡ�Ѷ�������
    T HeapTop() const;

    // �ѵ����ݸ���
    int HeapSize() const;

    // �ѵ��п�
    bool HeapEmpty() const;

    // ��������ж�����
    void HeapSort();

    // ��ӡ��
    void PrintHeap() const;

private:
    // ���϶��µ�����
    void AdjustDown(int parent, int size);

    // ���¶��ϵ�����
    void AdjustUp(int child);
};

template <typename T>
void Heap<T>::HeapCreate(T* a, int n) {
    _a.assign(a, a + n);

    // �����һ����Ҷ�ӽڵ㿪ʼ�����϶��µ�����
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

