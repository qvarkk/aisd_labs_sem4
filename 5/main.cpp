#include <iostream>
#include <queue>

class Node { 
public:
	Node() : key(0), left(nullptr), right(nullptr), parent(nullptr) {};
	Node(int key) : left(nullptr), right(nullptr), parent(nullptr) { this->key = key; };
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

class Tree {
public:
	Node* root;
	Tree() : root(nullptr) {};
	static Tree genSortedTree(int size);
	static Tree genRandomTree(int size);
	void insert(int key);
	Node* find(Node* node, int key);
	Node* remove(Node* node, int key);
	Node* getInorderSucc(Node* node);
	void preorderTraversal(void func(Node*));
	void postorderTraversal(void func(Node*));
	void print();
	int getHeight();
	int getNodesCount();
};

void Tree::insert(int key) {
	if (!root) {
		root = new Node(key);
		return;
	}

	Node* tmp = root, *parent = root;
	while (tmp != nullptr) {
		if (key < tmp->key) {
			parent = tmp;
			tmp = tmp->left;
		} else {
			parent = tmp;
			tmp = tmp->right;
		}
	}

	Node* node = new Node(key);
	node->parent = parent;
	if (key < parent->key) {
		parent->left = node;
	} else {
		parent->right = node;
	}
}

Node* Tree::find(Node* node, int key) {
	if (!node) return nullptr;
	else if (node->key == key) return node;
	else if (key < node->key) find(node->left, key);
	else find(node->right, key);
}

Node* Tree::getInorderSucc(Node* node) {
	Node* tmp = node;
	while (tmp->left != nullptr) {
		tmp = tmp->left;
	}
	return tmp;
}

Node* Tree::remove(Node* node, int key) {
	if (!root || !node) return nullptr;

	if (key < node->key) {
		node->left = remove(node->left, key);
		return node;
	} else if (key > node->key) {
		node->right = remove(node->right, key);
		return node;
	}

	if (node->right)
}

int main() {
	Tree tr = Tree();
	tr.insert(50);
	tr.insert(70);
	tr.insert(30);
	tr.insert(40);
	tr.insert(60);
	tr.insert(90);
	tr.insert(55);

	return 0;
}