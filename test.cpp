#include <iostream>
#include "tree.cpp"

using namespace std;

void print(Node* node, int level = 0) {
    if (!node) return;
    for (int i = 0; i < level*2; i++) {
        cout << ' ';
    }
    cout << node->key;
    if (node->color == Black) cout << "b" << endl;
    else cout << "r" << endl;
    print(node->left, level + 1);
    print(node->right, level + 1);
}

int main() {
    Tree* tree = new Tree();
    while (true) {
        int key;
        cin >> key;
        if (key < 0) break;
        tree->insert(key);
        cout << "Tree:" << endl;
        print(tree->root);
        cout << endl;
    }

    print(tree->root);

    return 0;
}