#include <iterator>
#include <cstddef>

enum Color {Black, Red};

class Node;
class Iterator;

class Node {
    public:
        int value;
        Color color;
        Node* left, *right, *parent;
        Node(int value) {
            this->value = value;
            left = right = nullptr;
        }
        Node* grandparent();
        Node* uncle();
        Node* sibling();
    };

class Tree {    
    Node* root;    
    void rotateLeft(Node* node);
    void rotateRight(Node* node); 
    void recolor(Node* node);
    Node* search(Node* current, int value);
    void insertFix(Node* newNode); 
    void removeFix(Node* parent, Node* child);
    
public:
    Tree() {
        root = nullptr;
    }     
    
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(pointer ptr, Tree* ptr1) : node_ptr(ptr), tree_ptr(ptr1) {}
        reference operator*() {
            return *node_ptr;
        }
        Iterator& operator++() {
            node_ptr = tree_ptr->successor(node_ptr);
            return *this;
        }
        friend bool operator== (Iterator& a, Iterator& b) { return a.node_ptr == b.node_ptr; }
        friend bool operator!= (Iterator& a, Iterator& b) { return a.node_ptr != b.node_ptr; }
    private:
        pointer node_ptr;
        Tree* tree_ptr;
    };    
    
    Iterator begin () { return Iterator(min(root), this); }
    Iterator end () { return root ? Iterator(max(root)->right, this) : Iterator(root, this); }
    
    Node* max(Node* node);
    Node* min(Node* node);    
    Node* successor(Node* node);
    Node* search(int value);
    void insert(int value); 
    void remove(int value);     
    Node* getRoot() {return root; } 
};