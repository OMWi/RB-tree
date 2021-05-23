#include <iostream>
#include "tree.cpp"
#include <chrono>
#include <time.h>

using namespace std;

void print(Node* node, int level = 0) {
    if (!node) return;
    for (int i = 0; i < level*2; i++) {
        cout << ' ';
    }
    cout << node->value;
    if (node->color == Black) cout << "b" << endl;
    else cout << "r" << endl;
    print(node->left, level + 1);
    print(node->right, level + 1);
}

int main() {
    Tree tree;
    int len = 1000*1000;
    srand(time(nullptr));
    auto start = chrono::high_resolution_clock::now();

    for (int i = 1; i <= len; i++) {
        int newValue = rand() % 1000 - 500;
        tree.insert(newValue);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Insert duration(milliseconds) == " << duration.count() << endl;

    Tree iterExmp;
    for (int i = 1; i <= 11; i++) {
        iterExmp.insert(i);
        print(iterExmp.getRoot());
    }
    for (auto elem : iterExmp) {
        cout << elem.value << ' ';
    }
    cout << endl;
    for (int i = 1; i <= 11; i++) {
        iterExmp.remove(i);
    }
    for (auto elem : iterExmp) {
        cout << elem.value << ' ';
    }


    


    return 0;
}