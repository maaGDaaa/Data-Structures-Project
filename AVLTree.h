#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;
    int tree_size;

    int getHeight(Node* node) const;
    int getBalanceFactor(Node* node) const;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balance(Node* node);
    Node* insertNode(Node* node, int key);
    Node* deleteNode(Node* node, int key);
    Node* minValueNode(Node* node) const;
    bool searchNode(Node* node, int key) const;
    void clear(Node* node);

public:
    AVLTree();
    ~AVLTree();

    void buildFromFile(const std::string& filename);
    void insert(int key);
    bool search(int key) const;
    void remove(int key);
    int findMin() const;
    int size() const;
};

#endif // AVLTREE_H