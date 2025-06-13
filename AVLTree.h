#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

// Κλάση για AVL δέντρο
class AVLTree {
private:
    // Κόμβος του δέντρου
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;      // Ρίζα δέντρου
    int tree_size;   // Μέγεθος δέντρου

    int getHeight(Node* node) const;             // Επιστρέφει ύψος κόμβου
    int getBalanceFactor(Node* node) const;      // Επιστρέφει συντελεστή ισορροπίας
    Node* rotateLeft(Node* node);                // Αριστερή περιστροφή
    Node* rotateRight(Node* node);               // Δεξιά περιστροφή
    Node* balance(Node* node);                   // Ισορροπεί τον κόμβο
    Node* insertNode(Node* node, int key);       // Εισαγωγή κόμβου
    Node* deleteNode(Node* node, int key);       // Διαγραφή κόμβου
    Node* minValueNode(Node* node) const;        // Ελάχιστος κόμβος
    bool searchNode(Node* node, int key) const;  // Αναζήτηση κόμβου
    void clear(Node* node);                      // Καθαρισμός δέντρου

public:
    AVLTree();      // Κατασκευαστής
    ~AVLTree();     // Καταστροφέας

    bool buildFromFile(const std::string& filename); // Δημιουργία από αρχείο
    void insert(int key);                            // Εισαγωγή κλειδιού
    bool search(int key) const;                      // Αναζήτηση κλειδιού
    void remove(int key);                            // Διαγραφή κλειδιού
    int findMin() const;                             // Εύρεση ελάχιστου
    int size() const;                                // Μέγεθος δέντρου
};

#endif // AVLTREE_H