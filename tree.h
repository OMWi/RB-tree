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
    //Node* root;    
    void rotateLeft(Node* node);
    void rotateRight(Node* node); 
    void recolor(Node* node);

    void insertFix(Node* newNode); 
    Node* max(Node* node);
    Node* min(Node* node);
    //void replace(Node* oldNode, Node* newNode);
    
    //Node* successor(Node* node);
    
    //Node* BSTreplace(Node* node);
    //void removeFix(Node* node);
    //void remove(Node* node);
    Node* search(Node* current, int key);
public:
    Node* root;
    Tree() {
        root = nullptr;
    } 
    void insert(int key); 
    //void remove(int key);       
    //Node* search(int key); 
};