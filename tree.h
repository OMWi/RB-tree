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
    Node* max(Node* node);
    Node* min(Node* node);    
    Node* successor(Node* node);

    Node* search(Node* current, int key);
    void insertFix(Node* newNode); 
    void removeFix(Node* parent, Node* child);
    
public:
    Node* root;
    Tree() {
        root = nullptr;
    } 
    Node* search(int key);
    void insert(int key); 
    void remove(int key);     
};