#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int v) :val(v), left(NULL), right(NULL) {}
};

class AvlTree {
private:
	Node* root;
	int get_height(Node*);
	Node* left_rotate(Node*);
	Node* right_rotate(Node*);
public:
	AvlTree(int val);
	AvlTree();
	Node* get_root();
	Node* insert(int, Node*);
	void add(int);
};

Node* AvlTree::get_root() {
	return root;
}

AvlTree::AvlTree(int val) {
	root = new Node(val);
}

AvlTree::AvlTree() {
	root = NULL;
}

Node* AvlTree::insert(int val, Node* n) {
	auto node = n;
	if (!node) {
		node = new Node(val);
		return node;
	}
	if (val == node->val) return n;
	else if (val < node->val) {
		node->left = insert(val, node->left);
		//也可能直到根节点才出现失衡，因此在这里主要是对当前返回节点的左右节点都进行高度计算
		if (get_height(node->left) - get_height(node->right) >= 2) {
			if (val < node->left->val) {
				//左左 
				node = right_rotate(node);
			}
			else {
				//左右
				node->left = left_rotate(node->left);
				node = right_rotate(node);
			}
		}
	}
	else {
		node->right = insert(val, node->right);
		if (get_height(node->right) - get_height(node->left) >= 2) {
			if (val < node->left->val) {
				//右左 
				node->right = right_rotate(node->right);
				node = left_rotate(node);
			}
			else {
				//右右
				node = left_rotate(node);
			}
		}
	}
	return node;
}

int AvlTree::get_height(Node* n) {
	if (!n) return 0;
	int lh = get_height(n->left), rh = get_height(n->right);
	return lh > rh ? lh + 1 : rh + 1;
}

Node* AvlTree::left_rotate(Node* n) {
	auto nn = n->right;
	n->right = nn->left;
	nn->left = n;
	return nn;
}
Node* AvlTree::right_rotate(Node* n) {
	auto nn = n->left;
	n->left = nn->right;
	nn->right = n;
	return nn;
}
void AvlTree::add(int val) {
	root = insert(val, root);
}

void printTree(Node* root) {
	if (!root) return;
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		int sz = q.size();
		for (int i = 0; i < sz; ++i) {
			Node* node = q.front();
			cout << node->val << " ";
			if (node->left != NULL) q.push(node->left);
			if (node->right != NULL) q.push(node->right);
			q.pop();
		}
		cout << endl;
	}
}

int main()
{
	AvlTree tree;
	int x;
	while (cin >> x) {
		if (x == -1) break;
		tree.add(x);
	}
	printTree(tree.get_root());
	return 0;
}