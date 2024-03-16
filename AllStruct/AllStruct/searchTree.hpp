#include <iostream>

template <class T>
struct BSTNode {
	BSTNode(const T& data = T())
		: _pLeft(nullptr), _pRight(nullptr), _data(data) {}

	BSTNode<T>* _pLeft;
	BSTNode<T>* _pRight;
	T _data;
};

template <class T>
class BSTree {
	typedef BSTNode<T> Node;
	typedef Node* pNode;

public:
	pNode Find(const T& data)
	{
		while (root) {
			if (data < root->_data) {
				root = root->_pLeft;
			}
			else if (data > root->_data) {
				root = root->_pRight;
			}
			else {
				return root;
			}
		}
		return nullptr;
	}

	bool insert(const T& data) {
		if (_pRoot == nullptr) {
			_pRoot = new Node(data);
			return true;
		}
		pNode pCur = _pRoot;
		pNode pParent = nullptr;
		while (pCur) {
			pParent = pCur;
			if (data < pCur->_data) {
				pCur = pCur->_pLeft;
			}
			else if (data > pCur->_data) {
				pCur = pCur->_pRight;
			}
			else {
				return false;
			}
		}
		pCur = new Node(data);
		if (data < pParent->_data) {
			pParent->_pLeft = pCur;
		}
		else {
			pParent->_pRight = pCur;
		}
		return true;
	}

	bool erase(const T& data) {
		if (root == nullptr) {
			return false; // 未找到要删除的元素
		}
		else if (data < root->_data) {
			return Erase(root->_pLeft, data);
		}
		else if (data > root->_data) {
			return Erase(root->_pRight, data);
		}
		else {
			// 找到要删除的元素
			pNode toDelete = root;
			if (root->_pLeft == nullptr) {
				root = root->_pRight;
			}
			else if (root->_pRight == nullptr) {
				root = root->_pLeft;
			}
			else {
				// 要删除的节点有两个子节点
				pNode& minNode = FindMin(root->_pRight);
				root->_data = minNode->_data;
				Erase(root->_pRight, minNode->_data);
			}
			delete toDelete;
			return true;
		}
	}

	pNode& FindMin(pNode& root) {
		while (root->_pLeft) {
			root = root->_pLeft;
		}
		return root;
   }

private:
	pNode _pRoot;
};
