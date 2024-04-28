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
	int size;
	Node* root;
	Tree() : size(0), root(nullptr) {};
	void insert(int key); 
	void insertAtRoot(int key);
	Node* find(Node* node, int key);
	Node* getInorderSucc(Node* node);
	Node* remove(Node* node, int key);
	void preorderTraversal(Node* node, void func(Node*));
	void postorderTraversal(Node* node, void func(Node*));
	void print();
	int getHeight(Node* node);
	int countNodes(Node* node);
	void rotateRight();
	void rotateLeft();
	static Tree genTreeWithRandomValues(int size);
};

// Вставка узла в дерево
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

// Вставка узла в корень дерева (не работает)
void Tree::insertAtRoot(int key) {
	Node* newNode = new Node(key);

	if (!root) {
		root = newNode;
		return;
	}

	Node* current = root;
	Node* tmp = nullptr;

	while (current) {
		tmp = current;
		if (key < current->key)
			current = current->left;
		else
			current = current->right;
	}

	newNode->parent = tmp;

	if (key < tmp->key)
		tmp->left = newNode;
	else
		tmp->right = newNode;

	while (newNode->parent != nullptr) {
		if (newNode->parent->left == newNode) {
			rotateRight();
		} else {
			rotateLeft();
		}
	}
}

// Поиск узла по дереву
Node* Tree::find(Node* node, int key) {
	if (!node) return nullptr;
	else if (node->key == key) return node;
	else if (key < node->key) return find(node->left, key);
	else return find(node->right, key);
}

// Нахождение минимального узла в поддереве
Node* Tree::getInorderSucc(Node* node) {
	Node* tmp = node;
	while (tmp->left != nullptr) {
		tmp = tmp->left;
	}
	return tmp;
}

// Удаление узла (возвращает значение, записанное на место удаленного)
Node* Tree::remove(Node* node, int key) {
	if (!root || !node) return nullptr;

	if (key < node->key) {
		node->left = remove(node->left, key);
		return node;
	} else if (key > node->key) {
		node->right = remove(node->right, key);
		return node;
	}

	if (!node->left) {
		Node* tmp = node->right;
		delete node;
		return tmp;
	} else if (!node->right) {
		Node* tmp = node->left;
		delete node;
		return tmp;
	}

	Node* succ = getInorderSucc(node->right);

	node->key = succ->key;

	if (succ->parent->left == succ)
		succ->parent->left = succ->right;
	else
		succ->parent->right = succ->right;

	delete succ;
	return node;
}

// Прямой обход дерева
void Tree::preorderTraversal(Node* node, void func(Node*)) {
	if (!node) return;

	func(node);
	preorderTraversal(node->left, func);
	preorderTraversal(node->right, func);
}

// Обратный обход дерева
void Tree::postorderTraversal(Node* node, void func(Node*)) {
	if (!node) return;

	postorderTraversal(node->left, func);
	postorderTraversal(node->right, func);
	func(node);
}

// Вывод дерева
void Tree::print() {
	preorderTraversal(root, [](Node* node) {
		int lk = 0, rk = 0, pk = 0;

		if (node->left) lk = node->left->key;
		if (node->right) rk = node->right->key;
		if (node->parent) pk = node->parent->key;

		if (node->parent == nullptr) std::cout << "=============root=============" << std::endl;
		else std::cout << "-------------node-------------" << std::endl;

		std::cout << "this\t" << "left\t" << "right\t" << "parent\t" << std::endl;
		std::cout << node->key << "\t" << lk << "\t" << rk << "\t" << pk << "\t\n" << std::endl;
	});
}

// Получить количество узлов дерева/поддерева
int Tree::countNodes(Node* node) {
	if (!node)
		return 0;
	else
		return 1 + countNodes(node->left) + countNodes(node->right);
}

// Получить высоту дерева
int Tree::getHeight(Node* node) {
	if (!node) return -1;

	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);

	return 1 + std::max(leftHeight, rightHeight);
}

// Поворот дерева влево
void Tree::rotateLeft() {
	if (!root || !root->right) return;

	Node* newRoot = root->right;
	root->right = newRoot->left;
	if (newRoot->left)
		newRoot->left->parent = root;

	newRoot->left = root;
	newRoot->parent = nullptr;
	root->parent = newRoot;
	root = newRoot;
}

// Поворот дерева вправо
void Tree::rotateRight() {
	if (!root || !root->left) return;

	Node* newRoot = root->left;
	root->left = newRoot->right;
	if (newRoot->right)
		newRoot->right->parent = root;

	newRoot->right = root;
	newRoot->parent = nullptr;
	root->parent = newRoot;
	root = newRoot;
}	


// Генерация дерева со случайными узлами
Tree Tree::genTreeWithRandomValues(int size) {
	srand((unsigned)time(nullptr));

	Tree tr;

	for (int i = 0; i < size; i++) {
		tr.insert(rand());
	}

	return tr;
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

	tr.insertAtRoot(80);
	tr.print();

	return 0;
}