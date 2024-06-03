#include <iostream>
using namespace std;

const int MAX_KEYS = 3; // Maximum number of keys in a node

struct BTreeNode {
    int keys[MAX_KEYS];
    BTreeNode* children[MAX_KEYS + 1];
    int num_keys;
    bool is_leaf;

    BTreeNode() {
        num_keys = 0;
        is_leaf = true;
        for (int i = 0; i < MAX_KEYS + 1; ++i)
            children[i] = nullptr;
    }
};

void insert(BTreeNode* root, int key) {
    if (root->num_keys == MAX_KEYS) {
        // Split root
        BTreeNode* new_root = new BTreeNode();
        new_root->is_leaf = false;
        new_root->children[0] = root;

        // Split the old root and move one key to the new root
        BTreeNode* new_child = new BTreeNode();
        new_child->is_leaf = root->is_leaf;
        new_child->num_keys = MAX_KEYS / 2;
        for (int i = 0; i < new_child->num_keys; ++i) {
            new_child->keys[i] = root->keys[MAX_KEYS / 2 + i];
            root->keys[MAX_KEYS / 2 + i] = 0; // Clear the old key
        }
        root->num_keys = MAX_KEYS / 2;

        new_root->keys[0] = new_child->keys[0];
        new_root->children[1] = new_child;

        root = new_root;
    }

    // Insert key into root or its child
    if (root->is_leaf) {
        // Find the position to insert the new key
        int i = root->num_keys - 1;
        while (i >= 0 && root->keys[i] > key) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = key;
        root->num_keys++;
    } else {
        // Find the child to insert the new key
        int i = root->num_keys - 1;
        while (i >= 0 && root->keys[i] > key)
            i--;

        // Check if child is full
        if (root->children[i + 1]->num_keys == MAX_KEYS)
            insert(root->children[i + 1], key);
        else
            insert(root->children[i + 1], key);
    }
}

void printBTree(BTreeNode* root) {
    if (root) {
        for (int i = 0; i < root->num_keys; ++i) {
            cout << root->keys[i] << " ";
        }
        cout << endl;
        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; ++i) {
                printBTree(root->children[i]);
            }
        }
    }
}

int main() {
    BTreeNode* root = new BTreeNode();

    insert(root, 10);
    insert(root, 20);
    insert(root, 5);
    insert(root, 6);
    insert(root, 12);

    cout << "B-tree contents:" << endl;
    printBTree(root);

    return 0;
}
