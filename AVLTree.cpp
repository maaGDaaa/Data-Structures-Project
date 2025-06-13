#include "AVLTree.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <iostream> // Για είσοδο/έξοδο

AVLTree::AVLTree() : root(nullptr), tree_size(0) {}

AVLTree::~AVLTree() {
    clear(root); // Καθαρισμός μνήμης
}

void AVLTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

int AVLTree::getHeight(Node* node) const {
    return node ? node->height : 0; // Επιστρέφει ύψος κόμβου
}

int AVLTree::getBalanceFactor(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0; // Συντελεστής ισορροπίας
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    return y; // Περιστροφή αριστερά
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    return x; // Περιστροφή δεξιά
}

AVLTree::Node* AVLTree::balance(Node* node) {
    int bf = getBalanceFactor(node);

    if (bf > 1) {
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        node = rotateRight(node);
    }
    else if (bf < -1) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        node = rotateLeft(node);
    }
    return node; // Εξισορρόπηση κόμβου
}

AVLTree::Node* AVLTree::insertNode(Node* node, int key) {
    if (!node) {
        tree_size++;
        return new Node(key); // Εισαγωγή νέου κόμβου
    }
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // Ήδη υπάρχει

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    return balance(node);
}

AVLTree::Node* AVLTree::deleteNode(Node* node, int key) {
    if (!node) return nullptr;
    if (key < node->key)
        node->left = deleteNode(node->left, key);
    else if (key > node->key)
        node->right = deleteNode(node->right, key);
    else {
        tree_size--;
        if (!node->left || !node->right) {
            Node* tmp = node->left ? node->left : node->right;
            delete node;
            return tmp; // Διαγραφή κόμβου με 0 ή 1 παιδί
        } else {
            Node* minNode = minValueNode(node->right);
            node->key = minNode->key;
            node->right = deleteNode(node->right, minNode->key);
        }
    }
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    return balance(node);
}

AVLTree::Node* AVLTree::minValueNode(Node* node) const {
    Node* curr = node;
    while (curr && curr->left)
        curr = curr->left;
    return curr; // Ελάχιστος κόμβος
}

bool AVLTree::searchNode(Node* node, int key) const {
    if (!node) return false;
    if (key == node->key) return true;
    else if (key < node->key) return searchNode(node->left, key);
    else return searchNode(node->right, key); // Αναζήτηση
}

bool AVLTree::buildFromFile(const std::string& filename) {
    clear(root);
    root = nullptr;
    tree_size = 0;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }

    int x;
    while (file >> x) {
        root = insertNode(root, x); // Εισαγωγή από αρχείο
    }

    file.close();
    return true;
}

void AVLTree::insert(int key) {
    root = insertNode(root, key); // Εισαγωγή κλειδιού
}

bool AVLTree::search(int key) const {
    return searchNode(root, key); // Αναζήτηση κλειδιού
}

void AVLTree::remove(int key) {
    root = deleteNode(root, key); // Διαγραφή κλειδιού
}

int AVLTree::findMin() const {
    Node* node = minValueNode(root);
    if (!node) throw std::runtime_error("AVLTree is empty");
    return node->key; // Ελάχιστο στοιχείο
}

int AVLTree::size() const {
    return tree_size; // Μέγεθος δέντρου
}
