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

bool Node::hasRedChild() {
    return (left != nullptr && left->color == Red) 
        || (right != nullptr && right->color == Red);
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

Node* Tree::successor(Node* x) {
    if (x->right) {
        return min(x->right);
    } 
    Node* y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

void Tree::replace(Node* oldNode, Node* newNode) {
    if (oldNode->parent == nullptr) {
        root = newNode;
    }
    else {
        if (oldNode == oldNode->parent->left) 
            oldNode->parent->left = newNode;
        else 
            oldNode->parent->right = newNode;
    }
    if (newNode != nullptr) {
        newNode->parent = oldNode->parent;
    }
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

void Tree::remove(int key) {
    remove(search(key));
}

Node* Tree::BSTreplace(Node* x) {
    if (x->left != nullptr && x->right != nullptr)
        return successor(x->right);
    if (x->left == nullptr && x->right == nullptr)
        return nullptr;
    if (x->left != nullptr) 
        return x->left;
    else
        return x->right;
}

void Tree::remove(Node* v) {
    Node* u = BSTreplace(v);
    bool uvBlack = ((!u || u->color == Black) && (v->color == Black));
    Node* parent = v->parent;

    if (u == nullptr) {
        if (v == root) {
            root = nullptr;
        }
        else {
            if (uvBlack) {
                removeFix(v);
            }
            else {
                if (v->sibling() != nullptr) 
                    v->sibling()->color = Red;
            }
        }
        if (v == v->parent->left)
            parent->left = nullptr;
        else 
            parent->right = nullptr;
        delete v;
        return;
    }

    if (v->left == nullptr || v->right == nullptr) {
        if (v == root) {
            v->key = u->key;
            v->left = v->right = nullptr;
            delete u;
        }
        else {
            if (v == v->parent->left) {
                parent->left = u;
            }
            else {
                parent->right = u;
            }
            delete v;
            u->parent = parent;
            if (uvBlack) {
                removeFix(u);
            }
            else {
                u->color = Black;
            }
        }
    }


    int temp = u->key;
    u->key = v->key;
    v->key = temp;
    remove(u);
}

void Tree::removeFix(Node* x) {
    if (x == root)
        // Reached root
        return;
 
    Node *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
        // No sibiling, double black pushed up
        removeFix(parent);
    } 
    else {
        if (sibling->color == Red) {
            // Sibling red
            parent->color = Red;
        sibling->color = Black;
        if (sibling == sibling->parent->left) {
          // left case
          rotateRight(parent);
        } else {
          // right case
          rotateLeft(parent);
        }
        removeFix(x);
      } else {
        // Sibling black
        if (sibling->hasRedChild()) {
          // at least 1 red children
          if (sibling->left != NULL and sibling->left->color == Red) {
            if (sibling == sibling->parent->left) {
              // left left
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rotateRight(parent);
            } else {
              // right left
              sibling->left->color = parent->color;
              rotateRight(sibling);
              rotateLeft(parent);
            }
          } else {
            if (sibling == sibling->parent->left) {
              // left right
              sibling->right->color = parent->color;
              rotateLeft(sibling);
              rotateRight(parent);
            } else {
              // right right
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              rotateLeft(parent);
            }
          }
          parent->color = Black;
        } else {
          // 2 black children
          sibling->color = Red;
          if (parent->color == Black)
            removeFix(parent);
          else
            parent->color = Black;
        }
      }
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

