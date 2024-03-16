#include<iostream>
#include "seqList.hpp"
#include "singlyLinkedList.hpp"
#include "doublyLinkedList.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "tree.hpp"
#include "heap.hpp"
using namespace std;

//动态数组
/*
int main() {
	// 使用示例
	seqlist<int> seqlist(4);

	seqlist.pushback(1);
	seqlist.pushback(2);
	seqlist.pushback(3);

	std::cout << "seqlist: ";
	seqlist.print();

	seqlist.popback();

	std::cout << "after popback: ";
	seqlist.print();

	seqlist.pushfront(0);

	std::cout << "after pushfront: ";
	seqlist.print();

	std::cout << "index of 2: " << seqlist.find(2) << std::endl;

	seqlist.insert(2, 5);

	std::cout << "after inserting 5 at position 2: ";
	seqlist.print();

	seqlist.erase(1);

	std::cout << "after erasing element at position 1: ";
	seqlist.print();

	return 0;
}
*/

//带头单链表
/*
int main() {
	SinglyLinkedList<int> list;

	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	std::cout << "Original list: ";
	list.print();

	list.pushFront(0);

	std::cout << "After pushing front 0: ";
	list.print();

	SListNode<int>* nodeToFind = list.find(2);
	if (nodeToFind) {
		list.insertAfter(nodeToFind, 5);
	}

	std::cout << "After inserting 5 after node with value 2: ";
	list.print();

	list.popBack();

	std::cout << "After popping back: ";
	list.print();

	list.popFront();

	std::cout << "After popping front: ";
	list.print();

	return 0;
}
*/

//双向带头循环链表
/*
int main() {
	DoublyLinkedList<int> list;

	list.ListPushBack(1);
	list.ListPushBack(2);
	list.ListPushBack(3);

	std::cout << "Original list: ";
	list.ListPrint();

	list.ListPushFront(0);

	std::cout << "After pushing front 0: ";
	list.ListPrint();

	ListNode<int>* nodeToFind = list.ListFind(2);
	if (nodeToFind) {
		list.ListInsert(nodeToFind, 5);
	}

	std::cout << "After inserting 5 after node with value 2: ";
	list.ListPrint();

	list.ListPopBack();

	std::cout << "After popping back: ";
	list.ListPrint();

	list.ListPopFront();

	std::cout << "After popping front: ";
	list.ListPrint();

	return 0;
}
*/

//栈
/*
int main()
{
	Stack<int> intStack;

	intStack.push(1);
	intStack.push(2);
	intStack.push(3);

	std::cout << "Top element: " << intStack.top() << std::endl;
	std::cout << "Stack size: " << intStack.size() << std::endl;

	intStack.pop();

	std::cout << "Top element after pop: " << intStack.top() << std::endl;
	std::cout << "Stack size after pop: " << intStack.size() << std::endl;

	return 0;
}
*/

//队列
/*
int main() {
	Queue<int> q;

	q.QueuePush(1);
	q.QueuePush(2);
	q.QueuePush(3);

	std::cout << "Queue Front: " << q.QueueFront() << std::endl;
	std::cout << "Queue Back: " << q.QueueBack() << std::endl;
	std::cout << "Queue Size: " << q.QueueSize() << std::endl;

	q.QueuePop();
	std::cout << "After Queue Pop, Front: " << q.QueueFront() << std::endl;
	std::cout << "Queue Size: " << q.QueueSize() << std::endl;

	q.QueueDestroy();

	return 0;
}
*/

//二叉树
/*
int main() {
	char arr[] = "ABD##E#H##CF##G##";
	int index = 0;

	BinaryTree<char> tree;
	tree.BinaryTreeCreate(arr, sizeof(arr) - 1, index);

	std::cout << "Binary Tree Preorder: ";
	tree.BinaryTreePrevOrder();

	std::cout << "Binary Tree Inorder: ";
	tree.BinaryTreeInOrder();

	std::cout << "Binary Tree Postorder: ";
	tree.BinaryTreePostOrder();

	std::cout << "Binary Tree Levelorder: ";
	tree.BinaryTreeLevelOrder();

	std::cout << "Binary Tree Size: " << tree.BinaryTreeSize() << std::endl;
	std::cout << "Binary Tree Leaf Size: " << tree.BinaryTreeLeafSize() << std::endl;

	int k = 3;
	std::cout << "Binary Tree Level " << k << " Size: " << tree.BinaryTreeLevelKSize(k) << std::endl;

	char x = 'E';
	BinaryTreeNode<char>* foundNode = tree.BinaryTreeFind(x);
	if (foundNode) {
		std::cout << "Found node with value " << x << std::endl;
	}
	else {
		std::cout << "Node with value " << x << " not found" << std::endl;
	}

	std::cout << "Is Binary Tree Complete: " << (tree.BinaryTreeComplete() ? "Yes" : "No") << std::endl;

	tree.BinaryTreeDestroy();

	return 0;
}
*/

//堆
int main() {
	Heap<int> heap;
	int arr[] = { 4, 2, 6, 1, 3, 5, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	
	heap.HeapCreate(arr, n);
	std::cout << "Original Heap: ";
	heap.PrintHeap();

	heap.HeapPush(8);
	std::cout << "Heap after Push: ";
	heap.PrintHeap();

	heap.HeapPop();
	std::cout << "Heap after Pop: ";
	heap.PrintHeap();

	std::cout << "Heap Top: " << heap.HeapTop() << std::endl;

	std::cout << "Heap Size: " << heap.HeapSize() << std::endl;

	heap.HeapSort();
	std::cout << "Heap after HeapSort: ";
	heap.PrintHeap();

	heap.HeapDestroy();

	return 0;
}

