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
        if (node->parent->left == node)
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
    if (!node) return node;
    while (node->right) {
        node = node->right;
    }
    return node;
}

Node* Tree::min(Node* node) {
    if (!node) return node;
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node* Tree::search(int value) {
    return search(root, value);
}

Node* Tree::search(Node* current, int value) {
    if (!current || current->value == value) return current;
    if (value > current->value) return search(current->right, value);
    else if (value < current->value) return search(current->left, value);
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


void Tree::insert(int value) {
    Node* parent = nullptr, *current = root;
    while (current) {
        parent = current;
        if (value >= current->value) {
            current = current->right;
        }
        else if (value < current->value) {
            current = current->left;
        }
    }
    Node* newNode = new Node(value);
    current = newNode;
    current->parent = parent;
    if (parent) {
        if (current->value < parent->value) {
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

void Tree::remove(int value) {
    Node* x = search(value);
    if (!x) return;  

    if (x->left && x->right) {
        //internal node
        Node* pred = max(x->left);
        x->value = pred->value;
        x = pred;
    }
    Node* parent = x->parent;
    Node* child = nullptr;
    if (x->left == nullptr && x->right == nullptr) {
        //leaf
        if (x == root) {
            root = nullptr;
            delete x;
            return;
        }
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
        if (x->parent) {
            if (x == x->parent->right)
                x->parent->right = child;
            else
                x->parent->left = child;
        }
        else {
            if (x->left) root = x->left;
            else root = x->right;
        }
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
                if (s->right && s->right->color == Red) {
                    //RRcase
                    recolor(s->right);
                    rotateLeft(parent);
                }
                else {
                    //RLcase
                    recolor(s->left);
                    rotateRight(s);
                    rotateLeft(parent);
                }
            }
            else {
                if (s->left && s->left->color == Red) {
                    //LLcase
                    recolor(s->left);
                    rotateRight(parent);
                }
                else {
                    //LRcase
                    recolor(s->right);
                    rotateLeft(s);
                    rotateRight(parent);
                }
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
        if (root->parent) root = root->parent;
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
        if (root->parent) root = root->parent;
        removeFix(parent, child);
    }
}

