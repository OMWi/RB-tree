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

Node* Node::sibling() {
    if (parent == nullptr) 
        return nullptr;
    if (this == parent->left)
        return parent->right;
    return parent->left;
}

/*
bool Node::hasRedChild() {
    return (left != nullptr && left->color == Red) 
        || (right != nullptr && right->color == Red);
}
*/
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

Node* Tree::max(Node* node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}

Node* Tree::min(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node* Tree::search(int key) {
    return search(root, key);
}

Node* Tree::search(Node* current, int key) {
    if (!current || current->key == key) return current;
    if (key > current->key) return search(current->right, key);
    else if (key < current->key) return search(current->left, key);
}

Node* Tree::successor(Node* x) {
    if (x->right != nullptr) {
        return min(x->right);
    } 
    Node* y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
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
    if (!(x->color == Red && x->parent->color == Red))
        return;
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

void Tree::remove(int key) {
    Node* x = search(key);
    if (!x) return;   

    if (x->left && x->right) {
        //internal node
        Node* pred = max(x->left);
        x->key = pred->key;
        x = pred;
    }
    Node* parent = x->parent;
    Node* child = nullptr;
    if (x->left == nullptr && x->right == nullptr) {
        //leaf
        if (x == x->parent->right) 
            x->parent->right = nullptr;
        else
            x->parent->left = nullptr;
        Color color = x->color;
        delete x;
        if (color == Black)
            removeFix(parent, child); 
        return;       
    }    
    if (x->left || x->right) {
        //1 child
        if (x->left)
            child = x->left;
        else
            child = x->right;
        child->parent = x->parent;
        if (x == x->parent->right)
            x->parent->right = child;
        else
            x->parent->left = child;
        child->color = Black;    
        delete x;
        return;        
    }
    
}

void Tree::removeFix(Node* parent, Node* child) {
    if (child == root) {
        root->color = Black;
        return;
    }
    Node* s;
    if (!child) {
        if (parent->left)
            s = parent->left;
        else 
            s = parent->right;
    }
    else {
        s = child->sibling();
    }    
    if (!s || s->color == Black) {
        //black sibling
        if ((s->left && s->left->color == Red) || (s->right && s->right->color == Red)) {
            //has red children
            if (s == s->parent->right) {
                if (s->left) {
                    //RLcase
                    rotateRight(s);
                }
                //RRcase
                rotateLeft(parent);
            }
            else {
                if (s->right) {
                    //LRcase
                    rotateLeft(s);
                }
                //LLcase
                rotateRight(parent);
            }
        }
        else {
            //both children are black
            s->color = Red;
            if (parent->color == Red)
                parent->color = Black;
            else
                removeFix(parent->parent, parent);
        }
    }
    else {
        //red sibling
        if (s == parent->left) {
            //LeftCase
            rotateRight(parent);
        }
        else {
            //RightCase
            rotateLeft(parent);
        }
        recolor(parent);
        recolor(s);
    }
}