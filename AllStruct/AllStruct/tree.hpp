#include <iostream>
#include <queue>

template <typename T>
struct BinaryTreeNode {
	T _data;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;

	BinaryTreeNode(T data) : _data(data), _left(nullptr), _right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
	BinaryTreeNode<T>* _root;

public:
	// 构造函数
	BinaryTree() : _root(nullptr) {}
	~BinaryTree() 
	{
		if(_root) BinaryTreeDestroyHelper(_root);
	}

	// 通过前序遍历的数组构建二叉树
	void BinaryTreeCreate(T* a, int n, int& i) {
		_root = BinaryTreeCreateHelper(a, n, i);
	}

	// 二叉树销毁
	void BinaryTreeDestroy() {
		BinaryTreeDestroyHelper(_root);
		_root = nullptr;
	}

	// 二叉树节点个数
	int BinaryTreeSize() const {
		return BinaryTreeSizeHelper(_root);
	}

	// 二叉树叶子节点个数
	int BinaryTreeLeafSize() const {
		return BinaryTreeLeafSizeHelper(_root);
	}

	// 二叉树第k层节点个数
	int BinaryTreeLevelKSize(int k) const {
		return BinaryTreeLevelKSizeHelper(_root, k);
	}

	// 二叉树查找值为x的节点
	BinaryTreeNode<T>* BinaryTreeFind(T x) const {
		return BinaryTreeFindHelper(_root, x);
	}

	// 二叉树前序遍历
	void BinaryTreePrevOrder() const {
		BinaryTreePrevOrderHelper(_root);
		std::cout << std::endl;
	}

	// 二叉树中序遍历
	void BinaryTreeInOrder() const {
		BinaryTreeInOrderHelper(_root);
		std::cout << std::endl;
	}

	// 二叉树后序遍历
	void BinaryTreePostOrder() const {
		BinaryTreePostOrderHelper(_root);
		std::cout << std::endl;
	}

	// 层序遍历
	void BinaryTreeLevelOrder() const {
		BinaryTreeLevelOrderHelper(_root);
		std::cout << std::endl;
	}

	// 判断二叉树是否是完全二叉树
	bool BinaryTreeComplete() const {
		return BinaryTreeCompleteHelper(_root);
	}

private:
	BinaryTreeNode<T>* BinaryTreeCreateHelper(T* a, int n, int& i) {
		if (i < n && a[i] != '#') {
			BinaryTreeNode<T>* root = new BinaryTreeNode<T>(a[i]);
			++i;
			root->_left = BinaryTreeCreateHelper(a, n, i);
			++i;
			root->_right = BinaryTreeCreateHelper(a, n, i);
			return root;
		}
		return nullptr;
	}

	void BinaryTreeDestroyHelper(BinaryTreeNode<T>*& root) {
		if (root) {
			BinaryTreeDestroyHelper(root->_left);
			BinaryTreeDestroyHelper(root->_right);
			delete root;
			root = nullptr;
		}
	}

	int BinaryTreeSizeHelper(const BinaryTreeNode<T>* root) const {
		if (root == nullptr) {
			return 0;
		}
		return 1 + BinaryTreeSizeHelper(root->_left) + BinaryTreeSizeHelper(root->_right);
	}

	int BinaryTreeLeafSizeHelper(const BinaryTreeNode<T>* root) const {
		if (root == nullptr) {
			return 0;
		}
		if (root->_left == nullptr && root->_right == nullptr) {
			return 1;
		}
		return BinaryTreeLeafSizeHelper(root->_left) + BinaryTreeLeafSizeHelper(root->_right);
	}

	int BinaryTreeLevelKSizeHelper(const BinaryTreeNode<T>* root, int k) const {
		if (root == nullptr || k < 1) {
			return 0;
		}
		if (k == 1) {
			return 1;
		}
		return BinaryTreeLevelKSizeHelper(root->_left, k - 1) + BinaryTreeLevelKSizeHelper(root->_right, k - 1);
	}

	BinaryTreeNode<T>* BinaryTreeFindHelper(const BinaryTreeNode<T>* root, T x) const {
		if (root == nullptr) {
			return nullptr;
		}
		if (root->_data == x) {
			return const_cast<BinaryTreeNode<T>*>(root);
		}
		BinaryTreeNode<T>* leftResult = BinaryTreeFindHelper(root->_left, x);
		if (leftResult) {
			return leftResult;
		}
		return BinaryTreeFindHelper(root->_right, x);
	}

	void BinaryTreePrevOrderHelper(const BinaryTreeNode<T>* root) const {
		if (root) {
			std::cout << root->_data << " ";
			BinaryTreePrevOrderHelper(root->_left);
			BinaryTreePrevOrderHelper(root->_right);
		}
	}

	void BinaryTreeInOrderHelper(const BinaryTreeNode<T>* root) const {
		if (root) {
			BinaryTreeInOrderHelper(root->_left);
			std::cout << root->_data << " ";
			BinaryTreeInOrderHelper(root->_right);
		}
	}

	void BinaryTreePostOrderHelper(const BinaryTreeNode<T>* root) const {
		if (root) {
			BinaryTreePostOrderHelper(root->_left);
			BinaryTreePostOrderHelper(root->_right);
			std::cout << root->_data << " ";
		}
	}

	void BinaryTreeLevelOrderHelper(const BinaryTreeNode<T>* root) const {
		if (root == nullptr) {
			return;
		}

		std::queue<const BinaryTreeNode<T>*> q;
		q.push(root);

		while (!q.empty()) {
			const BinaryTreeNode<T>* frontNode = q.front();
			std::cout << frontNode->_data << " ";

			if (frontNode->_left) {
				q.push(frontNode->_left);
			}

			if (frontNode->_right) {
				q.push(frontNode->_right);
			}

			q.pop();
		}
	}

	bool BinaryTreeCompleteHelper(const BinaryTreeNode<T>* root) const {
		if (root == nullptr) {
			return true;
		}

		std::queue<const BinaryTreeNode<T>*> q;
		q.push(root);

		bool leafStarted = false;

		while (!q.empty()) {
			const BinaryTreeNode<T>* frontNode = q.front();

			if (frontNode->_left) {
				if (leafStarted) {
					return false; // 遇到非空节点，但之前已经遇到过叶子节点
				}
				q.push(frontNode->_left);
			}
			else {
				leafStarted = true; // 遇到空节点，标记为叶子节点开始
			}

			if (frontNode->_right) {
				if (leafStarted) {
					return false; // 遇到非空节点，但之前已经遇到过叶子节点
				}
				q.push(frontNode->_right);
			}
			else {
				leafStarted = true; // 遇到空节点，标记为叶子节点开始
			}

			q.pop();
		}

		return true;
	}
};


