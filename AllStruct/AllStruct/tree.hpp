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
	// ���캯��
	BinaryTree() : _root(nullptr) {}
	~BinaryTree() 
	{
		if(_root) BinaryTreeDestroyHelper(_root);
	}

	// ͨ��ǰ����������鹹��������
	void BinaryTreeCreate(T* a, int n, int& i) {
		_root = BinaryTreeCreateHelper(a, n, i);
	}

	// ����������
	void BinaryTreeDestroy() {
		BinaryTreeDestroyHelper(_root);
		_root = nullptr;
	}

	// �������ڵ����
	int BinaryTreeSize() const {
		return BinaryTreeSizeHelper(_root);
	}

	// ������Ҷ�ӽڵ����
	int BinaryTreeLeafSize() const {
		return BinaryTreeLeafSizeHelper(_root);
	}

	// ��������k��ڵ����
	int BinaryTreeLevelKSize(int k) const {
		return BinaryTreeLevelKSizeHelper(_root, k);
	}

	// ����������ֵΪx�Ľڵ�
	BinaryTreeNode<T>* BinaryTreeFind(T x) const {
		return BinaryTreeFindHelper(_root, x);
	}

	// ������ǰ�����
	void BinaryTreePrevOrder() const {
		BinaryTreePrevOrderHelper(_root);
		std::cout << std::endl;
	}

	// �������������
	void BinaryTreeInOrder() const {
		BinaryTreeInOrderHelper(_root);
		std::cout << std::endl;
	}

	// �������������
	void BinaryTreePostOrder() const {
		BinaryTreePostOrderHelper(_root);
		std::cout << std::endl;
	}

	// �������
	void BinaryTreeLevelOrder() const {
		BinaryTreeLevelOrderHelper(_root);
		std::cout << std::endl;
	}

	// �ж϶������Ƿ�����ȫ������
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
					return false; // �����ǿսڵ㣬��֮ǰ�Ѿ�������Ҷ�ӽڵ�
				}
				q.push(frontNode->_left);
			}
			else {
				leafStarted = true; // �����սڵ㣬���ΪҶ�ӽڵ㿪ʼ
			}

			if (frontNode->_right) {
				if (leafStarted) {
					return false; // �����ǿսڵ㣬��֮ǰ�Ѿ�������Ҷ�ӽڵ�
				}
				q.push(frontNode->_right);
			}
			else {
				leafStarted = true; // �����սڵ㣬���ΪҶ�ӽڵ㿪ʼ
			}

			q.pop();
		}

		return true;
	}
};


