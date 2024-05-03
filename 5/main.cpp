#include <iostream>
#include <queue>

class Node { 
public:
	Node() : key(0), size(1), left(nullptr), right(nullptr), parent(nullptr) {};
	Node(int key) : size(1), left(nullptr), right(nullptr), parent(nullptr) { this->key = key; };
	int key;
	int size;
	Node* left;
	Node* right;
	Node* parent;
};

class Tree {
public:
	Node* root;
	Tree() : root(nullptr) {};
	Node* insert(int key);
	Node* insert(Node* root, int key);
	Node* insert(Node* root, Node* parent, int key);
	Node* insertAtRoot(Node* node, int key);
	Node* randomizedInsert(Node* node, int key);
	Node* find(Node* node, int key);
	Node* getInorderSucc(Node* node);
	Node* remove(Node* node, int key);
	void preorderTraversal(Node* node, void func(Node*));
	void postorderTraversal(Node* node, void func(Node*));
	void print();
	int getHeight(Node* node);
	int countNodes(Node* node);
	int individual(Node* node);
	int getSize(Node* node);
	void fixSize(Node* node);
	Node* rotateRight(Node* node);
	Node* rotateLeft(Node* node);
	static Tree genTree(int size, bool random);
	static Tree genRandomizedTree(int size, bool random);
};

// Вставка узла в дерево (обертка)
Node* Tree::insert(int key) {
	return insert(root, nullptr, key);
}

// Вставка узла в дерево
Node* Tree::insert(Node* node, Node* parent, int key) {
	if (!node) {
		Node* newNode = new Node(key);
		newNode->parent = parent;

		if (!root)
			root = newNode;

		return newNode;
	}

	if (key < node->key) {
		node->left = insert(node->left, node, key);
	} else if (key > node->key) {
		node->right = insert(node->right, node, key);
	}

	return node;
}

// Вставка узла в корень дерева
Node* Tree::insertAtRoot(Node* node, int key) {
	if (!node) {
		Node* newNode = new Node(key);

		if (!root)
			root = newNode;

		return newNode;
	}

	if (key < node->key) {
		node->left = insertAtRoot(node->left, key);
		return rotateRight(node);
	} else {
		node->right = insertAtRoot(node->right, key);
		return rotateLeft(node);
	}
}

// Случайная вставка meow meow me me meow миу мау миу мау ла ла ла ла ла       миу мау миу мау ла ла ла ла ла
Node* Tree::randomizedInsert(Node* node, int key) {
	if (!node) {
		Node* newNode = new Node(key);

		if (!root)
			root = newNode;

		return newNode;
	}

	if (rand() % (node->size + 1) == 0) {
		return insertAtRoot(node, key);
	}

	if (key < node->key)
		node->left = randomizedInsert(node->left, key);
	else
		node->right = randomizedInsert(node->right, key);

	fixSize(node);
	return node;
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

// Вариант 7. Посчитать сумму четных чисел во внутренних узлах
int Tree::individual(Node* node) {
	if (!node) 
		return 0;
	else if (node->key % 2 == 0 && (node->left || node->right))
		return node->key + individual(node->left) + individual(node->right);
	else
		return individual(node->left) + individual(node->right);
}

// Получить количество узлов в дереве/поддереве
int Tree::getSize(Node* node) {
	if (!node) return 0;
	return node->size;
}

// Записать количество узлов в дереве/поддереве
void Tree::fixSize(Node* node) {
	node->size = getSize(node->left) + getSize(node->right) + 1;
}

// Получить высоту дерева
int Tree::getHeight(Node* node) {
	if (!node) return 0;

	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);

	return 1 + std::max(leftHeight, rightHeight);
}

// Поворот дерева влево
Node* Tree::rotateLeft(Node* node) {
	if (!node->right) return node;

	Node* r = node->right;
	if (node == root) 
		root= r;

	node->right = r->left;
	r->left = node;
	r->size = node->size;
	fixSize(node);

	return r;
}

// Поворот дерева вправо
Node* Tree::rotateRight(Node* node) {
	if (!node->left) return node;

	Node* l = node->left;
	if (node == root)
		root = l;
	
	node->left = l->right;
	l->right = node;
	l->size = node->size;
	fixSize(node);

	return l;
}	


// Генерация дерева со случайными узлами
Tree Tree::genTree(int size, bool random) {
	srand((unsigned)time(nullptr));

	Tree tr;

	for (int i = 0; i < size; i++) {
		tr.insert(random ? rand() : i);
	}

	return tr;
}

// Генерация рандомизированного дерева (RBST)
Tree Tree::genRandomizedTree(int size, bool random) {
	srand((unsigned)time(nullptr));

	Tree tr;

	for (int i = 0; i < size; i++) {
		tr.randomizedInsert(tr.root, random ? rand() : i);
	}

	return tr;
}

int main() {
	/*std::cout << "random\n" << std::endl;
	std::cout << "=======BST=======" << std::endl;
	std::cout << "size\theight" << std::endl;
	for (int i = 1000; i <= 10000; i += 1000) {
		Tree tr = Tree::genTree(i, true);
		std::cout << i << "\t" << tr.getHeight(tr.root) << std::endl;
	}

	std::cout << "\n=======RBST=======" << std::endl;
	std::cout << "size\theight" << std::endl;
	for (int i = 1000; i <= 10000; i += 1000) {
		Tree tr = Tree::genRandomizedTree(i, true);
		std::cout << i << "\t" << tr.getHeight(tr.root) << std::endl;
	}

	std::cout << "\n\n\nordered\n" << std::endl;
	std::cout << "=======BST=======" << std::endl;
	std::cout << "size\theight" << std::endl;
	for (int i = 100; i <= 1000; i += 100) {
		Tree tr = Tree::genTree(i, false);
		std::cout << i << "\t" << tr.getHeight(tr.root) << std::endl;
	}

	std::cout << "\n=======RBST=======" << std::endl;
	std::cout << "size\theight" << std::endl;
	for (int i = 1000; i <= 10000; i += 1000) {
		Tree tr = Tree::genRandomizedTree(i, false);
		std::cout << i << "\t" << tr.getHeight(tr.root) << std::endl;
	}*/

	Tree tr = Tree();

	tr.insert(1500);
	tr.insert(2000);
	tr.insert(1000);
	tr.insert(1250);
	tr.insert(1750);

	tr.print();

		
	return 0;
}