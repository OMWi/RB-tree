enum Color {Black, Red};

struct Node {
    int key;
    Color color;
    Node* left, *right, *parent;
    Node(int key) {
        this->key = key;
        left = right = nullptr;
    }
    Node* grandparent();
    Node* uncle();
};

class Tree {    
    Node* root;
    Node* search(Node* current, int key);
    void rotateLeft(Node* node);
    void rotateRight(Node* node); 
    void recolor(Node* node);
    void transplant(Node* node1, Node* node2);
    Node* max(Node* node);
    Node* min(Node* node);
    Node* successor(Node* node);

    void insertFix(Node* newNode); 
    Node* bstRemove(Node* node, int key);
    void removeFix(Node* node);
public:
    Tree() {
        root = nullptr;
    }
    
    

    void insert(int key); 
    void remove(int key);  

    Node* search(int key); 
};