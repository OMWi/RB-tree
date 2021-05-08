enum Color {Black, Red};

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
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
public:
    Tree() {
        root = nullptr;
    }
    void rotateLeft(Node* node);
    void rotateRight(Node* node); 
    void recolor(Node* node);

    void insert(int key);   
    void insertFix(Node* newNode);   

    Node* search(int key); 

};