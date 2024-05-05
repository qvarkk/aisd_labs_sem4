#include <iostream>

class Node {
public:
	Node() : key(0), left(nullptr), right(nullptr) {};
	Node(int key) : left(nullptr), right(nullptr) { this->key = key; };
	int key;
	Node* left;
	Node* right;
};

// Поворот вправо
Node* rightRotate(Node* node) {
    Node* l = node->left;
    node->left = l->right;
    l->right = node;
    return l;
}

// Поворот влево
Node* leftRotate(Node* node) {
    Node* r = node->right;
    node->right = r->left;
    r->left = node;
    return r;
}

// Расширение дерева
Node* splay(Node* root, int key) {
    if (!root || root->key == key) // base case scenario
        return root;

    if (key < root->key) { // if key is in left subtree
        if (!root->left) // base case scenario
            return root;

        if (key < root->left->key) { // if key is in left left subtree do splay on it and zag zag it
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (key > root->left->key) { // if key is in left right subtree do splay on it and zig zag it
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = leftRotate(root);
        }
        return (!root->left) ? root : rightRotate(root); // if left child is the key zag it
    } else { // if key is in right subtree or if key is root
        if (!root->right) // base case scenario
            return root;

        if (key < root->right->key) { // if key is in right left subtree do splay on it and zag zig it
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = rightRotate(root);
        } else if (key > root->right->key) { // if key is in right right subtree do splay on it and zig zig it
            root->right->left = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (!root->right) ? root : leftRotate(root); // if right child is the key zig it
    }
}

// Вставка в дерево
Node* insert(Node* root, int key) {
    if (root == nullptr)
        return new Node(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    Node* node = new Node(key);
    if (key < root->key) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    } else {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }
    return node;
}

void print(Node* root) {
    if (root) {
        int lk = 0, rk = 0;
        if (root->left)
            lk = root->left->key;
        if (root->right)
            rk = root->right->key;

        if (root->left || root->right) std::cout << "-------node-------" << std::endl;
        else std::cout << "-------leaf-------" << std::endl;
        std::cout << "this\tleft\tright" << std::endl;
        std::cout << root->key << "\t" << lk << "\t" << rk << "\n\n" << std::endl;
        print(root->left);
        print(root->right);
    }
}

int main() {
    Node* root = insert(nullptr, 50);
    root = insert(root, 100);
    root = insert(root, 150);
    root = insert(root, 200);
    root = insert(root, 500);
    root = insert(root, 175);

    print(root);

	return 0;
}