#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data) {
        parent = left = right = nullptr;
        // New nodes are always red
        color = RED;
    }
};

class RedBlackTree {
private:
    Node *root;

    void rotateLeft(Node *&root, Node *&ptr) {
        Node *ptr_right = ptr->right;
        ptr->right = ptr_right->left;

        if (ptr->right != nullptr)
            ptr->right->parent = ptr;

        ptr_right->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = ptr_right;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = ptr_right;
        else
            ptr->parent->right = ptr_right;

        ptr_right->left = ptr;
        ptr->parent = ptr_right;
    }

    void rotateRight(Node *&root, Node *&ptr) {
        Node *ptr_left = ptr->left;
        ptr->left = ptr_left->right;

        if (ptr->left != nullptr)
            ptr->left->parent = ptr;

        ptr_left->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = ptr_left;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = ptr_left;
        else
            ptr->parent->right = ptr_left;

        ptr_left->right = ptr;
        ptr->parent = ptr_left;
    }

    void fixInsertRBTree(Node *&root, Node *&ptr) {
        Node *parent_ptr = nullptr;
        Node *grand_parent_ptr = nullptr;

        while (ptr != root && ptr->color != BLACK && ptr->parent->color == RED) {
            parent_ptr = ptr->parent;
            grand_parent_ptr = ptr->parent->parent;

            if (parent_ptr == grand_parent_ptr->left) {
                Node *uncle_ptr = grand_parent_ptr->right;

                if (uncle_ptr != nullptr && uncle_ptr->color == RED) {
                    grand_parent_ptr->color = RED;
                    parent_ptr->color = BLACK;
                    uncle_ptr->color = BLACK;
                    ptr = grand_parent_ptr;
                } else {
                    if (ptr == parent_ptr->right) {
                        rotateLeft(root, parent_ptr);
                        ptr = parent_ptr;
                        parent_ptr = ptr->parent;
                    }

                    rotateRight(root, grand_parent_ptr);
                    swap(parent_ptr->color, grand_parent_ptr->color);
                    ptr = parent_ptr;
                }
            } else {
                Node *uncle_ptr = grand_parent_ptr->left;

                if (uncle_ptr != nullptr && uncle_ptr->color == RED) {
                    grand_parent_ptr->color = RED;
                    parent_ptr->color = BLACK;
                    uncle_ptr->color = BLACK;
                    ptr = grand_parent_ptr;
                } else {
                    if (ptr == parent_ptr->left) {
                        rotateRight(root, parent_ptr);
                        ptr = parent_ptr;
                        parent_ptr = ptr->parent;
                    }

                    rotateLeft(root, grand_parent_ptr);
                    swap(parent_ptr->color, grand_parent_ptr->color);
                    ptr = parent_ptr;
                }
            }
        }

        root->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const int data) {
        Node *new_node = new Node(data);
        if (root == nullptr) {
            root = new_node;
            root->color = BLACK;
            return;
        }

        Node *current = root;
        Node *parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (new_node->data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        new_node->parent = parent;
        if (parent == nullptr)
            root = new_node;
        else if (new_node->data < parent->data)
            parent->left = new_node;
        else
            parent->right = new_node;

        fixInsertRBTree(root, new_node);
    }

    void inorder(Node *node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void inorder() {
        inorder(root);
    }
};

int main() {
    RedBlackTree rbTree;

    // Inserting elements
    rbTree.insert(7);
    cout << "Inserted: 7" << endl;
    cout << "Inorder Traversal of the tree: ";
    rbTree.inorder();
    cout << endl;

    rbTree.insert(10);
    cout << "Inserted: 10" << endl;
    cout << "Inorder Traversal of the tree: ";
    rbTree.inorder();
    cout << endl;

    return 0;
}
