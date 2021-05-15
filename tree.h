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
    Node* sibling();
    bool hasRedChild();
};

class Tree {    
    Node* root;
    Node* search(Node* current, int key);
    void rotateLeft(Node* node);
    void rotateRight(Node* node); 
    void recolor(Node* node);
    void replace(Node* oldNode, Node* newNode);
    Node* max(Node* node);
    Node* min(Node* node);
    Node* successor(Node* node);
    void insertFix(Node* newNode); 
    Node* BSTreplace(Node* node);
    void removeFix(Node* node);
    void remove(Node* node);
public:
    Tree() {
        root = nullptr;
    } 
    void insert(int key); 
    void remove(int key);       
    Node* search(int key); 
};