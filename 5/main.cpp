#include <iostream>
#include <queue>

struct Node { 
	int data;
	Node* left;
	Node* right;
};

Node* newNode(int data) {
	Node* n = new Node;
	n->left = nullptr;
	n->right = nullptr;
	n->data = data;
	return n;
}

Node* insert(Node* root, int data) {
	if (!root)
		return newNode(data);
	else
		if (data < root->data)
			root->left = insert(root->left, data);
		else
			root->right = insert(root->right, data);

	return root;
}

Node* search(Node* root, int data) {
	if (!root) return nullptr;

	if (data == root->data)
		return root;
	else if (data < root->data)
		return search(root->left, data);
	else
		return search(root->right, data);
}

Node* remove(Node* root, int data) {
	if (!root) return nullptr;
}

void preorderTraversal(Node* root, void function(Node*)) {
	if (!root) return;

	function(root);
	preorderTraversal(root->left, function);
	preorderTraversal(root->right, function);
}

void inorderTraversal(Node* root, void function(Node*)) {
	if (!root) return;

	preorderTraversal(root->left, function);
	function(root);
	preorderTraversal(root->right, function);
}

void postorderTraversal(Node* root, void function(Node*)) {
	if (!root) return;

	preorderTraversal(root->left, function);
	preorderTraversal(root->right, function);
	function(root);
}

void print(Node* root) {
	preorderTraversal(root, [](Node* node) {
		std::cout << node << ": " << node->data << std::endl;
		std::cout << "\tL: " << node->left << std::endl;
		std::cout << "\tR: " << node->right << "\n" << std::endl;
	});
}

int main() {
	Node* root = newNode(100);
	insert(root, 80);
	insert(root, 40);
	insert(root, 90);
	insert(root, 25);
	insert(root, 55);
	insert(root, 15);
	insert(root, 85);
	insert(root, 95);
	insert(root, 5);
	insert(root, 110);
	insert(root, 45);
	insert(root, 65);
	insert(root, 35);
	insert(root, 75);
	insert(root, 105);
	insert(root, 115);
	insert(root, 125);
	insert(root, 135);
	insert(root, 145);
	insert(root, 155);
	insert(root, 165);
	insert(root, 175);
	insert(root, 185);
	insert(root, 195);

	print(root);

	return 0;
}