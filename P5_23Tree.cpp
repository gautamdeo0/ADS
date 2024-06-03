#include <iostream>

using namespace std;

class Node {
public:
    int data1;
    int data2;
    Node* left;
    Node* middle;
    Node* right;
    Node(int data) {
        data1 = data;
        data2 = -1;
        left = middle = right = nullptr;
    }
};

class TwoThreeTree {
private:
    Node* root;

    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            root = new Node(data);
            return root;
        }

        if (root->data2 == -1) {
            if (data < root->data1) {
                root->data2 = root->data1;
                root->data1 = data;
            } else {
                root->data2 = data;
            }
            return root;
        }

        if (data < root->data1) {
            root->left = insert(root->left, data);
        } else if (data > root->data2) {
            root->right = insert(root->right, data);
        } else {
            root->middle = insert(root->middle, data);
        }

        return root;
    }

    Node* remove(Node* root, int data) {
        if (root == nullptr)
            return root;

        if (data < root->data1) {
            root->left = remove(root->left, data);
        } else if (data > root->data1 && (root->data2 == -1 || data < root->data2)) {
            root->middle = remove(root->middle, data);
        } else if (data > root->data1 && (root->data2 != -1 && data == root->data2)) {
            root->right = remove(root->right, data);
        } else {
            if (root->left == nullptr && root->middle == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }

            if (root->left == nullptr && root->middle != nullptr && root->right != nullptr) {
                root->data1 = root->data2;
                root->data2 = -1;
                root->left = root->middle;
                root->middle = root->right;
                root->right = nullptr;
            } else if (root->left != nullptr && root->middle == nullptr && root->right != nullptr) {
                root->data1 = root->left->data2;
                root->left->data2 = -1;
                root->middle = root->right;
                root->right = nullptr;
            } else if (root->left != nullptr && root->middle != nullptr && root->right == nullptr) {
                root->data2 = -1;
                root->right = root->middle;
                root->middle = nullptr;
            } else {
                Node* temp = findMin(root->right);
                root->data1 = temp->data1;
                root->right = remove(root->right, temp->data1);
            }
        }

        return root;
    }

    Node* findMin(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

public:
    TwoThreeTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

    void printInorder(Node* node) {
        if (node == nullptr)
            return;
        printInorder(node->left);
        cout << node->data1 << " ";
        if (node->data2 != -1)
            cout << node->data2 << " ";
        printInorder(node->middle);
        printInorder(node->right);
    }

    void printInorder() {
        printInorder(root);
    }
};

int main() {
    TwoThreeTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);

    cout << "Inorder traversal of the 2-3 tree: ";
    tree.printInorder();
    cout << endl;

    tree.remove(6);
    cout << "Inorder traversal after removing 6: ";
    tree.printInorder();
    cout << endl;

    return 0;
}
