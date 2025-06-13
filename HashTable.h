#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>

// Κλάση για υλοποίηση Hash Table
class HashTable {
private:
    static const int TABLE_SIZE = 103; // μέγεθος πίνακα
    std::vector<std::list<int>> table; // ο πίνακας με λίστες
    int numElements; // πλήθος στοιχείων

    int hashFunction(int key) const; // συνάρτηση κατακερματισμού

public:
    HashTable(); // κατασκευαστής

    bool buildFromFile(const std::string& filename); // φόρτωση από αρχείο
    int getSize() const; // επιστρέφει το μέγεθος
    bool search(int number) const; // αναζήτηση στοιχείου
    void insert(int number); // εισαγωγή στοιχείου
};

#endif
