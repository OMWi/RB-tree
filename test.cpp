#include <iostream>
#include "tree.cpp"

using namespace std;


int main() {
    Tree* tree = new Tree();
/*
    while (true) {
        int key;
        cin >> key;
        tree->insert(key);
    }
*/
    tree->insert(3);
    tree->insert(4);
    tree->insert(5);
    tree->remove(4);
    return 0;
}