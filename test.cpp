#include <iostream>
#include "tree.cpp"

using namespace std;

int main() {
    Tree* tree = new Tree();

    while (true) {
        int key;
        cin >> key;
        tree->insert(key);
    }
    return 0;
}