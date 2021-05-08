#include "tree.h"

Node* Node::grandparent() {
    if ((this != nullptr) && (this->parent != nullptr)) 
        return this->parent->parent;
    else
        return nullptr;
}

Node* Node::uncle() {
    Node* grand = grandparent();
    if (grand == nullptr) 
        return nullptr;
    if (this->parent == grand->left) 
        return grand->right;
    else 
        return grand->left;
}


void Tree::rotateLeft(Node* node) {
    Node* pivot = node->right;

    pivot->parent = node->parent;

    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = pivot;
        else 
            node->parent->right = pivot;
    }

    node->right = pivot->left;
    if (pivot->left != nullptr)
        pivot->left->parent = node;

    node->parent = pivot;
    pivot->left = node;
}

void Tree::rotateRight(Node* node) {
    Node* pivot = node->left;

    pivot->parent = node->parent;

    if (node->parent != nullptr) {
        if (node->parent->left == pivot)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    }

    node->left = pivot->right;
    if (pivot->right != nullptr) 
        pivot->right->parent = node;
    
    node->parent = pivot;
    pivot->right = node;
}

void Tree::recolor(Node* node) {
    if (node->color == Color::Black) 
        node->color = Color::Red;
    else
        node->color = Color::Black;
}

void Tree::insert(int key) {
    Node* parent = nullptr, *current = root;
    while (current) {
        parent = current;
        if (key > current->key) {
            current = current->right;
        }
        else if (key < current->key) {
            current = current->left;
        }
    }
    Node* newNode = new Node(key);
    current = newNode;
    current->parent = parent;
    if (parent) {
        if (current->key < parent->key) {
            parent->left = current;
        }
        else {
            parent->right = current;
        }
    }    
    else {
        root = current;
        root->color = Black;
        return;
    }
    current->color = Red;
    if (current->parent->color == Red)
        insertFix(current); 
}

void Tree::insertFix(Node* x) {
    if (x == root) {
        x->color = Black;
        return;
    }
    if (!x->uncle() || x->uncle()->color == Black) {
        Node* p = x->parent;
        Node* g = x->grandparent();
        if (p == g->right) {
            if (x == p->left) {
                rotateRight(p);
            }
            rotateLeft(g);
            recolor(g);
            recolor(g->parent);
        }
        else {
            if (x == p->right) {
                rotateLeft(p);
            }
            rotateRight(g);
            recolor(g);
            recolor(g->parent);
        }
        if (root->parent) root = root->parent;
        if (root->color == Red) recolor(root);
    }
    else {
        Node* g = x->grandparent();
        recolor(g);
        recolor(g->left);
        recolor(g->right);
        insertFix(g);        
    }
}





Node* Tree::search(int key) {
    return search(root, key);
}

Node* Tree::search(Node* current, int key) {
    if (!current || current->key == key) return current;
    if (key > current->key) return search(current->right, key);
    else if (key < current->key) return search(current->left, key);
}

